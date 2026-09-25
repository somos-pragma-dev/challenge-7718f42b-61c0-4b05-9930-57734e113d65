#include "Renderer.hpp"
#include "../utils/ErrorHandler.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

namespace opengl_renderer {

Renderer::Renderer(GLFWwindow* window)
    : m_window(window)
    , m_shaderProgram(0)
    , m_vertexShader(0)
    , m_fragmentShader(0)
    , m_viewMatrix(1.0f)
    , m_projectionMatrix(1.0f)
    , m_ambientLight(0.1f)
    , m_lastFrameTime(0.0)
    , m_fps(0.0f)
    , m_frameCount(0)
    , m_fpsTimer(0.0)
    , m_initialized(false) {
    
    m_lightPositions.resize(4, glm::vec3(0.0f, 5.0f, 5.0f));
    m_lightColors.resize(4, glm::vec3(1.0f, 1.0f, 1.0f));
    m_lightIntensities.resize(4, 1.0f);
}

Renderer::~Renderer() {
    cleanup();
}

bool Renderer::initialize() {
    if (m_initialized) {
        ErrorHandler::log("Renderer ya inicializado");
        return true;
    }
    
    if (!m_window) {
        ErrorHandler::reportError("Renderer: ventana nula en inicializacion");
        return false;
    }
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    m_initialized = true;
    ErrorHandler::log("Renderer inicializado correctamente");
    return true;
}

bool Renderer::loadShaders(const std::string& vertexPath, const std::string& fragmentPath) {
    std::string vertexSource = readShaderFile(vertexPath);
    std::string fragmentSource = readShaderFile(fragmentPath);
    
    if (vertexSource.empty() || fragmentSource.empty()) {
        ErrorHandler::reportError("Renderer: fallo al cargar archivos de shader");
        return false;
    }
    
    m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
    m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    if (!compileShader(m_vertexShader, vertexSource)) {
        ErrorHandler::reportError("Renderer: fallo al compilar vertex shader");
        return false;
    }
    
    if (!compileShader(m_fragmentShader, fragmentSource)) {
        ErrorHandler::reportError("Renderer: fallo al compilar fragment shader");
        return false;
    }
    
    if (!linkProgram()) {
        ErrorHandler::reportError("Renderer: fallo al vincular programa de shaders");
        return false;
    }
    
    glDeleteShader(m_vertexShader);
    glDeleteShader(m_fragmentShader);
    m_vertexShader = 0;
    m_fragmentShader = 0;
    
    ErrorHandler::log("Shaders cargados y compilados correctamente");
    return true;
}

std::string Renderer::readShaderFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        ErrorHandler::reportError("Renderer: no se pudo abrir archivo shader: " + path);
        return "";
    }
    
    std::stringstream stream;
    stream << file.rdbuf();
    return stream.str();
}

bool Renderer::compileShader(GLuint shader, const std::string& source) {
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        ErrorHandler::reportError("Renderer: error de compilacion de shader: " + std::string(infoLog));
        return false;
    }
    
    return true;
}

bool Renderer::linkProgram() {
    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, m_vertexShader);
    glAttachShader(m_shaderProgram, m_fragmentShader);
    glLinkProgram(m_shaderProgram);
    
    GLint success;
    glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
    
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(m_shaderProgram, 512, nullptr, infoLog);
        ErrorHandler::reportError("Renderer: error de vinculacion de programa: " + std::string(infoLog));
        return false;
    }
    
    return true;
}

Mesh Renderer::createMesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices) {
    Mesh mesh;
    
    glGenVertexArrays(1, &mesh.vao);
    glGenBuffers(1, &mesh.vbo);
    glGenBuffers(1, &mesh.ebo);
    
    glBindVertexArray(mesh.vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
    
    GLsizei stride = sizeof(Vertex);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);
    
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(Vertex, texCoords));
    glEnableVertexAttribArray(2);
    
    glBindVertexArray(0);
    
    mesh.indexCount = static_cast<GLsizei>(indices.size());
    
    ErrorHandler::log("Mesh creado con " + std::to_string(vertices.size()) + " vertices");
    return mesh;
}

void Renderer::addObject(const RenderObject& object) {
    m_objects.push_back(object);
    ErrorHandler::log("Objeto anadido al renderer: " + object.name);
}

void Renderer::removeObject(const std::string& name) {
    auto it = std::remove_if(m_objects.begin(), m_objects.end(), 
        [&name](const RenderObject& obj) { return obj.name == name; });
    m_objects.erase(it, m_objects.end());
}

void Renderer::clearObjects() {
    m_objects.clear();
    ErrorHandler::log("Todos los objetos eliminados del renderer");
}

void Renderer::setViewMatrix(const glm::mat4& view) {
    m_viewMatrix = view;
}

void Renderer::setProjectionMatrix(const glm::mat4& projection) {
    m_projectionMatrix = projection;
}

void Renderer::setAmbientLight(float ambient) {
    m_ambientLight = glm::clamp(ambient, 0.0f, 1.0f);
}

void Renderer::setLightPosition(int lightIndex, const glm::vec3& position) {
    if (lightIndex >= 0 && lightIndex < static_cast<int>(m_lightPositions.size())) {
        m_lightPositions[lightIndex] = position;
    }
}

void Renderer::setLightColor(int lightIndex, const glm::vec3& color) {
    if (lightIndex >= 0 && lightIndex < static_cast<int>(m_lightColors.size())) {
        m_lightColors[lightIndex] = color;
    }
}

void Renderer::setLightIntensity(int lightIndex, float intensity) {
    if (lightIndex >= 0 && lightIndex < static_cast<int>(m_lightIntensities.size())) {
        m_lightIntensities[lightIndex] = glm::clamp(intensity, 0.0f, 10.0f);
    }
}

void Renderer::updateModelMatrix(RenderObject& obj) {
    glm::mat4 translation = glm::translate(glm::mat4(1.0f), obj.position);
    glm::mat4 rotationX = glm::rotate(glm::mat4(1.0f), obj.rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rotationY = glm::rotate(glm::mat4(1.0f), obj.rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rotationZ = glm::rotate(glm::mat4(1.0f), obj.rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), obj.scale);
    
    obj.modelMatrix = translation * rotationX * rotationY * rotationZ * scale;
}

void Renderer::setupLightingUniforms() {
    GLint ambientLoc = glGetUniformLocation(m_shaderProgram, "ambientLight");
    glUniform1f(ambientLoc, m_ambientLight);
    
    for (size_t i = 0; i < m_lightPositions.size(); ++i) {
        std::string posName = "lights[" + std::to_string(i) + "].position";
        std::string colorName = "lights[" + std::to_string(i) + "].color";
        std::string intensityName = "lights[" + std::to_string(i) + "].intensity";
        
        GLint posLoc = glGetUniformLocation(m_shaderProgram, posName.c_str());
        GLint colorLoc = glGetUniformLocation(m_shaderProgram, colorName.c_str());
        GLint intensityLoc = glGetUniformLocation(m_shaderProgram, intensityName.c_str());
        
        glUniform3fv(posLoc, 1, glm::value_ptr(m_lightPositions[i]));
        glUniform3fv(colorLoc, 1, glm::value_ptr(m_lightColors[i]));
        glUniform1f(intensityLoc, m_lightIntensities[i]);
    }
}

void Renderer::setupObjectUniforms(const RenderObject& obj) {
    GLint modelLoc = glGetUniformLocation(m_shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(obj.modelMatrix));
    
    GLint viewLoc = glGetUniformLocation(m_shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(m_viewMatrix));
    
    GLint projectionLoc = glGetUniformLocation(m_shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(m_projectionMatrix));
    
    GLint colorLoc = glGetUniformLocation(m_shaderProgram, "objectColor");
    glUniform3fv(colorLoc, 1, glm::value_ptr(obj.color));
    
    GLint shininessLoc = glGetUniformLocation(m_shaderProgram, "shininess");
    glUniform1f(shininessLoc, obj.shininess);
}

void Renderer::renderFrame() {
    if (!m_initialized) {
        ErrorHandler::reportError("Renderer: intento de renderizar sin inicializar");
        return;
    }
    
    double currentTime = glfwGetTime();
    double deltaTime = currentTime - m_lastFrameTime;
    m_lastFrameTime = currentTime;
    
    m_frameCount++;
    m_fpsTimer += deltaTime;
    if (m_fpsTimer >= 1.0) {
        m_fps = static_cast<float>(m_frameCount) / static_cast<float>(m_fpsTimer);
        m_frameCount = 0;
        m_fpsTimer = 0.0;
    }
    
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if (m_shaderProgram == 0) {
        ErrorHandler::reportError("Renderer: programa de shader no cargado");
        return;
    }
    
    glUseProgram(m_shaderProgram);
    setupLightingUniforms();
    
    for (auto& obj : m_objects) {
        updateModelMatrix(obj);
        setupObjectUniforms(obj);
        
        glBindVertexArray(obj.mesh.vao);
        
        if (obj.mesh.indexCount > 0) {
            glDrawElements(obj.mesh.primitiveType, obj.mesh.indexCount, GL_UNSIGNED_INT, nullptr);
        } else {
            glDrawArrays(obj.mesh.primitiveType, 0, obj.mesh.indexCount);
        }
        
        glBindVertexArray(0);
    }
    
    glUseProgram(0);
}

void Renderer::cleanup() {
    if (m_shaderProgram != 0) {
        glDeleteProgram(m_shaderProgram);
        m_shaderProgram = 0;
    }
    
    m_objects.clear();
    m_meshCache.clear();
    
    m_initialized = false;
    ErrorHandler::log("Renderer limpiado correctamente");
}

}