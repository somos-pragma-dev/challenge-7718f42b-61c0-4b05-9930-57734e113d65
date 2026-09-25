#ifndef OBJ_LOADER_HPP
#define OBJ_LOADER_HPP

#include <string>
#include <vector>
#include <glm/glm.hpp>

namespace engine {

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;

    Vertex() : position(0.0f), normal(0.0f), texCoord(0.0f) {}
    Vertex(const glm::vec3& pos) : position(pos), normal(0.0f), texCoord(0.0f) {}
    Vertex(const glm::vec3& pos, const glm::vec3& norm, const glm::vec2& uv)
        : position(pos), normal(norm), texCoord(uv) {}
};

struct MeshData {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::string name;

    MeshData() : name("default") {}
    explicit MeshData(const std::string& meshName) : name(meshName) {}

    void clear() {
        vertices.clear();
        indices.clear();
    }

    bool isEmpty() const {
        return vertices.empty();
    }
};

class ObjLoader {
public:
    explicit ObjLoader();
    ~ObjLoader() = default;

    ObjLoader(const ObjLoader&) = delete;
    ObjLoader& operator=(const ObjLoader&) = delete;
    ObjLoader(ObjLoader&&) = default;
    ObjLoader& operator=(ObjLoader&&) = default;

    MeshData load(const std::string& filePath);
    bool validate() const;
    std::string getLastError() const;
    unsigned int getLoadedCount() const;

private:
    std::string lastError_;
    unsigned int loadedCount_;

    void parseVertexLine(const std::string& line, std::vector<glm::vec3>& positions);
    void parseNormalLine(const std::string& line, std::vector<glm::vec3>& normals);
    void parseTexCoordLine(const std::string& line, std::vector<glm::vec2>& texCoords);
    void parseFaceLine(const std::string& line, MeshData& mesh,
                       const std::vector<glm::vec3>& positions,
                       const std::vector<glm::vec3>& normals,
                       const std::vector<glm::vec2>& texCoords);
    void processFaceIndices(const std::string& vertexStr, unsigned int& outVertexIdx,
                            unsigned int& outNormalIdx, unsigned int& outTexCoordIdx);
    void computeMissingNormals(MeshData& mesh);
    void triangulateFace(std::vector<Vertex>& faceVertices, std::vector<unsigned int>& faceIndices);
    std::string extractFileName(const std::string& path) const;
};

} // namespace engine

#endif // OBJ_LOADER_HPP