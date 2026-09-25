#ifndef LIGHT_MANAGER_HPP
#define LIGHT_MANAGER_HPP

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <vector>
#include <string>
#include <memory>

namespace OpenGLRenderer {

enum class LightType {
    POINT_LIGHT,
    DIRECTIONAL_LIGHT,
    SPOT_LIGHT
};

struct LightProperties {
    glm::vec3 position{0.0f, 0.0f, 0.0f};
    glm::vec3 direction{0.0f, -1.0f, 0.0f};
    glm::vec3 color{1.0f, 1.0f, 1.0f};
    glm::vec3 ambient{0.1f, 0.1f, 0.1f};
    glm::vec3 diffuse{0.8f, 0.8f, 0.8f};
    glm::vec3 specular{1.0f, 1.0f, 1.0f};
    
    float intensity{1.0f};
    float constant{1.0f};
    float linear{0.09f};
    float quadratic{0.032f};
    
    float cutOffAngle{12.5f};
    float outerCutOffAngle{15.0f};
    
    bool enabled{true};
    int shadowMapIndex{-1};
};

struct ShadowMapConfig {
    int width{1024};
    int height{1024};
    float nearPlane{0.1f};
    float farPlane{100.0f};
    glm::mat4 lightSpaceMatrix{1.0f};
    bool enabled{false};
};

class LightManager {
public:
    LightManager();
    ~LightManager();
    
    LightManager(const LightManager&) = delete;
    LightManager& operator=(const LightManager&) = delete;
    LightManager(LightManager&&) noexcept;
    LightManager& operator=(LightManager&&) noexcept;
    
    int addLight(LightType type, const LightProperties& properties);
    void removeLight(int lightId);
    void updateLight(int lightId, const LightProperties& properties);
    
    const LightProperties* getLight(int lightId) const;
    const std::vector<LightProperties>& getAllLights() const { return lights_; }
    size_t getLightCount() const { return lights_. size(); }
    
    void setAmbientLight(const glm::vec3& ambient);
    const glm::vec3& getAmbientLight() const { return globalAmbient_; }
    
    void setShadowEnabled(bool enabled);
    bool isShadowEnabled() const { return shadowsEnabled_; }
    
    void configureShadowMap(int lightId, const ShadowMapConfig& config);
    const ShadowMapConfig* getShadowConfig(int lightId) const;
    
    void updateShaderUniforms(unsigned int shaderProgram);
    void updateLightSpaceMatrices(const glm::mat4& viewProjection);
    
    void setLightPosition(int lightId, const glm::vec3& position);
    void setLightDirection(int lightId, const glm::vec3& direction);
    void setLightColor(int lightId, const glm::vec3& color);
    void setLightIntensity(int lightId, float intensity);
    
    void loadLightingConfig(const std::string& configPath);
    void saveLightingConfig(const std::string& configPath) const;
    
    static const int MAX_POINT_LIGHTS = 16;
    static const int MAX_DIRECTIONAL_LIGHTS = 4;
    static const int MAX_SPOT_LIGHTS = 8;
    static const int MAX_SHADOW_MAPS = 4;

private:
    struct LightData {
        LightType type;
        LightProperties properties;
        ShadowMapConfig shadowConfig;
    };
    
    std::vector<LightData> lights_;
    glm::vec3 globalAmbient_{0.1f, 0.1f, 0.1f};
    bool shadowsEnabled_{false};
    
    int nextLightId_{0};
    int pointLightCount_{0};
    int directionalLightCount_{0};
    int spotLightCount_{0};
    
    bool validateLightTypeLimit(LightType type) const;
    void updateAttenuation(LightProperties& light) const;
    void calculateLightSpaceMatrix(int lightId);
    
    std::string lightTypeToString(LightType type) const;
    LightType stringToLightType(const std::string& str) const;
};

}

#endif