#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

namespace opengl_renderer {

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

struct Mesh {
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    GLsizei indexCount;
    GLenum primitiveType;
    
    Mesh() : vao(0), vbo(0), ebo(0), indexCount(0), primitiveType(GL_TRIANGLES) {}
    
    ~Mesh() {
        if (vao != 0) glDeleteVertexArrays(1, &vao);
        if (vbo != 0) glDeleteBuffers(1, &vbo);
        if (ebo != 0) glDeleteBuffers(1, &ebo);
    }
    
    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;
    
    Mesh(Mesh&& other) noexcept 
        : vao(other.vao), vbo(other.vbo), ebo(other.ebo),
          indexCount(other.indexCount), primitiveType(other.primitiveType) {
        other.vao = 0;
        other.vbo = 0;
        other.ebo = 0;
        other.indexCount = 0;
    }
    
    Mesh& operator=(Mesh&& other) noexcept {
        if (this != &other) {
            if (vao != 0) glDeleteVertexArrays(1, &vao);
            if (vbo != 0) glDeleteBuffers(1, &vbo);
            if (ebo != 0) glDeleteBuffers(1, &ebo);
            
            vao = other.vao;
            vbo = other.vbo;
            ebo = other.ebo;
            indexCount = other.indexCount;
            primitiveType = other.primitiveType;
            
            other.vao = 0;
            other.vbo = 0;
            other.ebo = 0;
            other.indexCount = 0;
        }
        return *this;
    }
};

struct RenderObject {
    std::string name;
    Mesh mesh;
    glm::mat4 modelMatrix;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    glm::vec3 color;
    float shininess;
    
    RenderObject() 
        : name("default"), 
          modelMatrix(1.0f), 
          position(0.0f), 
          rotation(0.0f), 
          scale(1.0f), 
          color(1.0f, 1.0f, 1.0f),
          shininess(32.0f) {}
};

class Renderer {
public:
    Renderer(GLFWwindow* window);
    ~Renderer();
    
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    
    bool initialize();
    void renderFrame();
    void addObject(const RenderObject& object);
    void removeObject(const std::string& name);
    void clearObjects();
    
    void setViewMatrix(const glm::mat4& view);
    void setProjectionMatrix(const glm::mat4& projection);
    void setAmbientLight(float ambient);
    void setLightPosition(int lightIndex, const glm::vec3& position);
    void setLightColor(int lightIndex, const glm::vec3& color);
    void setLightIntensity(int lightIndex, float intensity);
    
    bool loadShaders(const std::string& vertexPath, const std::string& fragmentPath);
    void cleanup();
    
    int getObjectCount() const { return static_cast<int>(m_objects.size()); }
    float getFPS() const { return m_fps; }
    
private:
    GLFWwindow* m_window;
    GLuint m_shaderProgram;
    GLuint m_vertexShader;
    GLuint m_fragmentShader;
    
    std::vector<RenderObject> m_objects;
    std::unordered_map<std::string, Mesh> m_meshCache;
    
    glm::mat4 m_viewMatrix;
    glm::mat4 m_projectionMatrix;
    
    float m_ambientLight;
    std::vector<glm::vec3> m_lightPositions;
    std::vector<glm::vec3> m_lightColors;
    std::vector<float> m_lightIntensities;
    
    double m_lastFrameTime;
    float m_fps;
    int m_frameCount;
    double m_fpsTimer;
    
    bool m_initialized;
    
    bool compileShader(GLuint shader, const std::string& source);
    bool linkProgram();
    std::string readShaderFile(const std::string& path);
    Mesh createMesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices);
    void updateModelMatrix(RenderObject& obj);
    void setupLightingUniforms();
    void setupObjectUniforms(const RenderObject& obj);
};

}

#endif