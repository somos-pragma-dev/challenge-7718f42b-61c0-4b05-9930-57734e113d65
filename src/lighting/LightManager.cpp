#include "lighting/LightManager.hpp"
#include "utils/ErrorHandler.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>

namespace OpenGLRenderer {

LightManager::LightManager() 
    : lights_()
    , globalAmbient_{0.1f, 0.1f, 0.1f}
    , shadowsEnabled_{false}
    , nextLightId_{0}
    , pointLightCount_{0}
    , directionalLightCount_{0}
    , spotLightCount_{0}
{
    lights_.reserve(MAX_POINT_LIGHTS + MAX_DIRECTIONAL_LIGHTS + MAX_SPOT_LIGHTS);
}

LightManager::~LightManager() = default;

LightManager::LightManager(LightManager&& other) noexcept
    : lights_(std::move(other.lights_))
    , globalAmbient_(other.globalAmbient_)
    , shadowsEnabled_(other.shadowsEnabled_)
    , nextLightId_(other.nextLightId_)
    , pointLightCount_(other.pointLightCount_)
    , directionalLightCount_(other.directionalLightCount_)
    , spotLightCount_(other.spotLightCount_)
{
    other.lights_.clear();
    other.nextLightId_ = 0;
    other.pointLightCount_ = 0;
    other.directionalLightCount_ = 0;
    other.spotLightCount_ = 0;
}

LightManager& LightManager::operator=(LightManager&& other) noexcept {
    if (this != &other) {
        lights_ = std::move(other.lights_);
        globalAmbient_ = other.globalAmbient_;
        shadowsEnabled_ = other.shadowsEnabled_;
        nextLightId_ = other.nextLightId_;
        pointLightCount_ = other.pointLightCount_;
        directionalLightCount_ = other.directionalLightCount_;
        spotLightCount_ = other.spotLightCount_;
        
        other.lights_.clear();
        other.nextLightId_ = 0;
        other.pointLightCount_ = 0;
        other.directionalLightCount_ = 0;
        other.spotLightCount_ = 0;
    }
    return *this;
}

int LightManager::addLight(LightType type, const LightProperties& properties) {
    if (!validateLightTypeLimit(type)) {
        throw std::runtime_error("Maximum number of lights for type exceeded");
    }
    
    LightData data;
    data.type = type;
    data.properties = properties;
    data.shadowConfig = ShadowMapConfig{};
    
    int lightId = nextLightId_++;
    lights_.push_back(std::move(data));
    
    switch (type) {
        case LightType::POINT_LIGHT:
            ++pointLightCount_;
            break;
        case LightType::DIRECTIONAL_LIGHT:
            ++directionalLightCount_;
            if (shadowsEnabled_) {
                lights_.back().shadowConfig.enabled = true;
            }
            break;
        case LightType::SPOT_LIGHT:
            ++spotLightCount_;
            if (shadowsEnabled_) {
                lights_.back().shadowConfig.enabled = true;
            }
            break;
    }
    
    return lightId;
}

void LightManager::removeLight(int lightId) {
    auto it = std::find_if(lights_.begin(), lights_.end(), 
        [lightId](const LightData& data) { 
            return static_cast<int>(std::distance(&lights_.front(), &data)) == lightId;
        });
    
    if (it == lights_.end()) {
        return;
    }
    
    switch (it->type) {
        case LightType::POINT_LIGHT:
            --pointLightCount_;
            break;
        case LightType::DIRECTIONAL_LIGHT:
            --directionalLightCount_;
            break;
        case LightType::SPOT_LIGHT:
            --spotLightCount_;
            break;
    }
    
    lights_.erase(it);
}

void LightManager::updateLight(int lightId, const LightProperties& properties) {
    auto it = std::find_if(lights_.begin(), lights_.end(), 
        [lightId](const LightData& data) {
            return static_cast<int>(std::distance(&lights_.front(), &data)) == lightId;
        });
    
    if (it != lights_.end()) {
        it->properties = properties;
        updateAttenuation(it->properties);
    }
}

const LightProperties* LightManager::getLight(int lightId) const {
    auto it = std::find_if(lights_.begin(), lights_.end(), 
        [lightId](const LightData& data) {
            return static_cast<int>(std::distance(&lights_.front(), &data)) == lightId;
        });
    
    return (it != lights_.end()) ? &it->properties : nullptr;
}

void LightManager::setAmbientLight(const glm::vec3& ambient) {
    globalAmbient_ = ambient;
}

void LightManager::setShadowEnabled(bool enabled) {
    shadowsEnabled_ = enabled;
    for (auto& light : lights_) {
        if (light.type != LightType::POINT_LIGHT) {
            light.shadowConfig.enabled = enabled;
        }
    }
}

void LightManager::configureShadowMap(int lightId, const ShadowMapConfig& config) {
    auto it = std::find_if(lights_.begin(), lights_.end(), 
        [lightId](const LightData& data) {
            return static_cast<int>(std::distance(&lights_.front(), &data)) == lightId;
        });
    
    if (it != lights_.end() && it->type != LightType::POINT_LIGHT) {
        it->shadowConfig = config;
        calculateLightSpaceMatrix(lightId);
    }
}

const ShadowMapConfig* LightManager::getShadowConfig(int lightId) const {
    auto it = std::find_if(lights_.begin(), lights_.end(), 
        [lightId](const LightData& data) {
            return static_cast<int>(std::distance(&lights_.front(), &data)) == lightId;
        });
    
    return (it != lights_.end()) ? &it->shadowConfig : nullptr;
}

void LightManager::updateShaderUniforms(unsigned int shaderProgram) {
    glUseProgram(shaderProgram);
    
    glUniform3fv(glGetUniformLocation(shaderProgram, "u_globalAmbient"), 1, 
                 &globalAmbient_[0]);
    
    int pointLightIndex = 0;
    int directionalLightIndex = 0;
    int spotLightIndex = 0;
    
    for (const auto& light : lights_) {
        if (!light.properties.enabled) continue;
        
        std::string prefix;
        int index = 0;
        
        switch (light.type) {
            case LightType::POINT_LIGHT:
                prefix = "u_pointLights[" + std::to_string(pointLightIndex) + "]";
                index = pointLightIndex++;
                break;
            case LightType::DIRECTIONAL_LIGHT:
                prefix = "u_directionalLights[" + std::to_string(directionalLightIndex) + "]";
                index = directionalLightIndex++;
                break;
            case LightType::SPOT_LIGHT:
                prefix = "u_spotLights[" + std::to_string(spotLightIndex) + "]";
                index = spotLightIndex++;
                break;
        }
        
        std::string basePrefix = prefix + ".";
        
        glUniform3fv(glGetUniformLocation(shaderProgram, 
            (basePrefix + "position").c_str()), 1, &light.properties.position[0]);
        glUniform3fv(glGetUniformLocation(shaderProgram, 
            (basePrefix + "direction").c_str()), 1, &light.properties.direction[0]);
        glUniform3fv(glGetUniformLocation(shaderProgram, 
            (basePrefix + "color").c_str()), 1, &light.properties.color[0]);
        glUniform3fv(glGetUniformLocation(shaderProgram, 
            (basePrefix + "ambient").c_str()), 1, &light.properties.ambient[0]);
        glUniform3fv(glGetUniformLocation(shaderProgram, 
            (basePrefix + "diffuse").c_str()), 1, &light.properties.diffuse[0]);
        glUniform3fv(glGetUniformLocation(shaderProgram, 
            (basePrefix + "specular").c_str()), 1, &light.properties.specular[0]);
        
        glUniform1f(glGetUniformLocation(shaderProgram, 
            (basePrefix + "intensity").c_str()), light.properties.intensity);
        glUniform1f(glGetUniformLocation(shaderProgram, 
            (basePrefix + "constant").c_str()), light.properties.constant);
        glUniform1f(glGetUniformLocation(shaderProgram, 
            (basePrefix + "linear").c_str()), light.properties.linear);
        glUniform1f(glGetUniformLocation(shaderProgram, 
            (basePrefix + "quadratic").c_str()), light.properties.quadratic);
        
        if (light.type == LightType::SPOT_LIGHT) {
            glUniform1f(glGetUniformLocation(shaderProgram, 
                (basePrefix + "cutOff").c_str()), 
                glm::cos(glm::radians(light.properties.cutOffAngle)));
            glUniform1f(glGetUniformLocation(shaderProgram, 
                (basePrefix + "outerCutOff").c_str()), 
                glm::cos(glm::radians(light.properties.outerCutOffAngle)));
        }
    }
    
    glUniform1i(glGetUniformLocation(shaderProgram, "u_pointLightCount"), pointLightIndex);
    glUniform1i(glGetUniformLocation(shaderProgram, "u_directionalLightCount"), directionalLightIndex);
    glUniform1i(glGetUniformLocation(shaderProgram, "u_spotLightCount"), spotLightIndex);
    glUniform1i(glGetUniformLocation(shaderProgram, "u_shadowsEnabled"), shadowsEnabled_ ? 1 : 0);
}

void LightManager::updateLightSpaceMatrices(const glm::mat4& viewProjection) {
    for (auto& light : lights_) {
        if (light.shadowConfig.enabled) {
            light.shadowConfig.lightSpaceMatrix = viewProjection * 
                glm::lookAt(light.properties.position, 
                           light.properties.position + light.properties.direction,
                           glm::vec3(0.0f, 1.0f, 0.0f));
        }
    }
}

void LightManager::setLightPosition(int lightId, const glm::vec3& position) {
    auto it = std::find_if(lights_.begin(), lights_.end(), 
        [lightId](const LightData& data) {
            return static_cast<int>(std::distance(&lights_.front(), &data)) == lightId;
        });
    
    if (it != lights_.end()) {
        it->properties.position = position;
        if (it->shadowConfig.enabled) {
            calculateLightSpaceMatrix(lightId);
        }
    }
}

void LightManager::setLightDirection(int lightId, const glm::vec3& direction) {
    auto it = std::find_if(lights_.begin(), lights_.end(), 
        [lightId](const LightData& data) {
            return static_cast<int>(std::distance(&lights_.front(), &data)) == lightId;
        });
    
    if (it != lights_.end()) {
        it->properties.direction = glm::normalize(direction);
        if (it->shadowConfig.enabled) {
            calculateLightSpaceMatrix(lightId);
        }
    }
}

void LightManager::setLightColor(int lightId, const glm::vec3& color) {
    auto it = std::find_if(lights_.begin(), lights_.end(), 
        [lightId](const LightData& data) {
            return static_cast<int>(std::distance(&lights_.front(), &data)) == lightId;
        });
    
    if (it != lights_.end()) {
        it->properties.color = color;
    }
}

void LightManager::setLightIntensity(int lightId, float intensity) {
    auto it = std::find_if(lights_.begin(), lights_.end(), 
        [lightId](const LightData& data) {
            return static_cast<int>(std::distance(&lights_.front(), &data)) == lightId;
        });
    
    if (it != lights_.end()) {
        it->properties.intensity = intensity;
    }
}

void LightManager::loadLightingConfig(const std::string& configPath) {
    std::ifstream file(configPath);
    if (!file.is_open()) {
        return;
    }
    
    lights_.clear();
    nextLightId_ = 0;
    pointLightCount_ = 0;
    directionalLightCount_ = 0;
    spotLightCount_ = 0;
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        
        std::istringstream iss(line);
        std::string key;
        iss >> key;
        
        if (key == "ambient") {
            glm::vec3 ambient;
            iss >> ambient.x >> ambient.y >> ambient.z;
            globalAmbient_ = ambient;
        } else if (key == "shadows") {
            int enabled;
            iss >> enabled;
            shadowsEnabled_ = (enabled != 0);
        } else if (key == "point" || key == "directional" || key == "spot") {
            LightType type = stringToLightType(key);
            LightProperties props;
            iss >> props.position.x >> props.position.y >> props.position.z
                >> props.color.r >> props.color.g >> props.color.b
                >> props.intensity;
            addLight(type, props);
        }
    }
}

void LightManager::saveLightingConfig(const std::string& configPath) const {
    std::ofstream file(configPath);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open config file for writing: " + configPath);
    }
    
    file << "# Lighting Configuration\n";
    file << "ambient " << globalAmbient_.x << " " << globalAmbient_.y << " " << globalAmbient_.z << "\n";
    file << "shadows " << (shadowsEnabled_ ? 1 : 0) << "\n";
    
    for (const auto& light : lights_) {
        file << lightTypeToString(light.type) << " "
             << light.properties.position.x << " " << light.properties.position.y << " " << light.properties.position.z << " "
             << light.properties.color.r << " " << light.properties.color.g << " " << light.properties.color.b << " "
             << light.properties.intensity << "\n";
    }
}

bool LightManager::validateLightTypeLimit(LightType type) const {
    switch (type) {
        case LightType::POINT_LIGHT:
            return pointLightCount_ < MAX_POINT_LIGHTS;
        case LightType::DIRECTIONAL_LIGHT:
            return directionalLightCount_ < MAX_DIRECTIONAL_LIGHTS;
        case LightType::SPOT_LIGHT:
            return spotLightCount_ < MAX_SPOT_LIGHTS;
    }
    return false;
}

void LightManager::updateAttenuation(LightProperties& light) const {
    float distance = glm::length(light.position);
    if (distance > 0.0f) {
        float attenuation = 1.0f / (light.constant + light.linear * distance + 
                                     light.quadratic * distance * distance);
        light.intensity = attenuation;
    }
}

void LightManager::calculateLightSpaceMatrix(int lightId) {
    auto it = std::find_if(lights_.begin(), lights_.end(), 
        [lightId](const LightData& data) {
            return static_cast<int>(std::distance(&lights_.front(), &data)) == lightId;
        });
    
    if (it != lights_.end() && it->shadowConfig.enabled) {
        glm::mat4 lightView = glm::lookAt(it->properties.position,
                                          it->properties.position + it->properties.direction,
                                          glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 lightProj = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f,
                                         it->shadowConfig.nearPlane, 
                                         it->shadowConfig.farPlane);
        it->shadowConfig.lightSpaceMatrix = lightProj * lightView;
    }
}

std::string LightManager::lightTypeToString(LightType type) const {
    switch (type) {
        case LightType::POINT_LIGHT: return "point";
        case LightType::DIRECTIONAL_LIGHT: return "directional";
        case LightType::SPOT_LIGHT: return "spot";
    }
    return "unknown";
}

LightType LightManager::stringToLightType(const std::string& str) const {
    if (str == "point") return LightType::POINT_LIGHT;
    if (str == "directional") return LightType::DIRECTIONAL_LIGHT;
    if (str == "spot") return LightType::SPOT_LIGHT;
    return LightType::POINT_LIGHT;
}

}