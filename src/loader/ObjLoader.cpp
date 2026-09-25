#include "loader/ObjLoader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace engine {

ObjLoader::ObjLoader() : loadedCount_(0) {}

MeshData ObjLoader::load(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        lastError_ = "No se pudo abrir el archivo: " + filePath;
        return MeshData();
    }

    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texCoords;
    MeshData mesh(extractFileName(filePath));

    std::string line;
    unsigned int lineNumber = 0;

    while (std::getline(file, line)) {
        lineNumber++;
        if (line.empty() || line[0] == '#') {
            continue;
        }

        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") {
            parseVertexLine(line, positions);
        } else if (prefix == "vn") {
            parseNormalLine(line, normals);
        } else if (prefix == "vt") {
            parseTexCoordLine(line, texCoords);
        } else if (prefix == "f") {
            parseFaceLine(line, mesh, positions, normals, texCoords);
        }
    }

    file.close();

    if (mesh.isEmpty()) {
        lastError_ = "El archivo OBJ no contiene caras válidas: " + filePath;
        return MeshData();
    }

    if (normals.empty()) {
        computeMissingNormals(mesh);
    }

    loadedCount_++;
    return mesh;
}

void ObjLoader::parseVertexLine(const std::string& line, std::vector<glm::vec3>& positions) {
    std::istringstream iss(line);
    char prefix;
    float x, y, z;

    iss >> prefix >> x >> y >> z;
    if (iss.fail()) {
        lastError_ = "Formato de vértice inválido: " + line;
        return;
    }

    positions.emplace_back(x, y, z);
}

void ObjLoader::parseNormalLine(const std::string& line, std::vector<glm::vec3>& normals) {
    std::istringstream iss(line);
    char prefix;
    float x, y, z;

    iss >> prefix >> x >> y >> z;
    if (iss.fail()) {
        lastError_ = "Formato de normal inválido: " + line;
        return;
    }

    normals.emplace_back(x, y, z);
}

void ObjLoader::parseTexCoordLine(const std::string& line, std::vector<glm::vec2>& texCoords) {
    std::istringstream iss(line);
    char prefix;
    float u, v;

    iss >> prefix >> u >> v;
    if (iss.fail()) {
        lastError_ = "Formato de coordenada de textura inválido: " + line;
        return;
    }

    texCoords.emplace_back(u, v);
}

void ObjLoader::parseFaceLine(const std::string& line, MeshData& mesh,
                               const std::vector<glm::vec3>& positions,
                               const std::vector<glm::vec3>& normals,
                               const std::vector<glm::vec2>& texCoords) {
    std::istringstream iss(line);
    char prefix;
    iss >> prefix;

    std::vector<Vertex> faceVertices;
    std::string vertexStr;

    while (iss >> vertexStr) {
        unsigned int vIdx, nIdx, tIdx;
        processFaceIndices(vertexStr, vIdx, nIdx, tIdx);

        Vertex v;

        if (vIdx > 0 && vIdx <= positions.size()) {
            v.position = positions[vIdx - 1];
        } else {
            lastError_ = "Índice de vértice fuera de rango: " + std::to_string(vIdx);
            return;
        }

        if (!normals.empty() && nIdx > 0 && nIdx <= normals.size()) {
            v.normal = normals[nIdx - 1];
        }

        if (!texCoords.empty() && tIdx > 0 && tIdx <= texCoords.size()) {
            v.texCoord = texCoords[tIdx - 1];
        }

        faceVertices.push_back(v);
    }

    triangulateFace(faceVertices, mesh.vertices);
}

void ObjLoader::processFaceIndices(const std::string& vertexStr, unsigned int& outVertexIdx,
                                    unsigned int& outNormalIdx, unsigned int& outTexCoordIdx) {
    std::istringstream iss(vertexStr);
    std::string token;

    outVertexIdx = 0;
    outNormalIdx = 0;
    outTexCoordIdx = 0;

    int index = 0;
    while (std::getline(iss, token, '/')) {
        if (!token.empty()) {
            try {
                unsigned int value = std::stoul(token);
                if (index == 0) outVertexIdx = value;
                else if (index == 1) outTexCoordIdx = value;
                else if (index == 2) outNormalIdx = value;
            } catch (const std::exception&) {
                lastError_ = "Índice inválido en cara: " + token;
            }
        }
        index++;
    }
}

void ObjLoader::computeMissingNormals(MeshData& mesh) {
    for (size_t i = 0; i < mesh.indices.size(); i += 3) {
        unsigned int i0 = mesh.indices[i];
        unsigned int i1 = mesh.indices[i + 1];
        unsigned int i2 = mesh.indices[i + 2];

        const glm::vec3& v0 = mesh.vertices[i0].position;
        const glm::vec3& v1 = mesh.vertices[i1].position;
        const glm::vec3& v2 = mesh.vertices[i2].position;

        glm::vec3 edge1 = v1 - v0;
        glm::vec3 edge2 = v2 - v0;
        glm::vec3 faceNormal = glm::normalize(glm::cross(edge1, edge2));

        mesh.vertices[i0].normal += faceNormal;
        mesh.vertices[i1].normal += faceNormal;
        mesh.vertices[i2].normal += faceNormal;
    }

    for (auto& vertex : mesh.vertices) {
        vertex.normal = glm::normalize(vertex.normal);
    }
}

void ObjLoader::triangulateFace(std::vector<Vertex>& faceVertices, std::vector<unsigned int>& vertices) {
    if (faceVertices.size() < 3) {
        return;
    }

    size_t baseIndex = vertices.size();

    for (size_t i = 0; i < faceVertices.size(); ++i) {
        vertices.push_back(faceVertices[i]);
    }

    if (faceVertices.size() == 3) {
        vertices.push_back(0);
        vertices.push_back(1);
        vertices.push_back(2);
    } else if (faceVertices.size() == 4) {
        vertices.push_back(baseIndex);
        vertices.push_back(baseIndex + 1);
        vertices.push_back(baseIndex + 2);

        vertices.push_back(baseIndex);
        vertices.push_back(baseIndex + 2);
        vertices.push_back(baseIndex + 3);
    } else {
        for (size_t i = 1; i < faceVertices.size() - 1; ++i) {
            vertices.push_back(baseIndex);
            vertices.push_back(baseIndex + i);
            vertices.push_back(baseIndex + i + 1);
        }
    }
}

std::string ObjLoader::extractFileName(const std::string& path) const {
    size_t lastSlash = path.find_last_of("/\\");
    std::string fileName = (lastSlash != std::string::npos) ? path.substr(lastSlash + 1) : path;

    size_t dotPos = fileName.rfind(".obj");
    if (dotPos != std::string::npos) {
        fileName = fileName.substr(0, dotPos);
    }

    return fileName;
}

bool ObjLoader::validate() const {
    return lastError_.empty();
}

std::string ObjLoader::getLastError() const {
    return lastError_;
}

unsigned int ObjLoader::getLoadedCount() const {
    return loadedCount_;
}

} // namespace engine