#include "ObjLoader.h"
//#include <cstdio>

ObjLoader::ObjLoader(const std::string& filePath) : path(filePath){}

void ObjLoader::ReadFile() {
    std::ifstream ObjFile(path);

    if (!ObjFile.is_open()) {       
        std::cout << "Failed to read file!" << std::endl;
        return;
    }

    char lineHeader[128];

    while (ObjFile >> lineHeader) {
        if (strcmp(lineHeader, "v") == 0) {
            glm::vec3 vertex;
            ObjFile >> vertex.x >> vertex.y >> vertex.z;
            temp_vertices.push_back(vertex);
        }
        else if (strcmp(lineHeader, "vt") == 0) {
            glm::vec2 uv;
            ObjFile >> uv.x >> uv.y;
            temp_uvs.push_back(uv);
        }
        else if (strcmp(lineHeader, "vn") == 0) {
            glm::vec3 normal;
            ObjFile >> normal.x >> normal.y >> normal.z;
            temp_normals.push_back(normal);
        }
        else if (strcmp(lineHeader, "f") == 0) {
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            for (int i = 0; i < 3; ++i) {
                ObjFile >> vertexIndex[i];
                ObjFile.ignore(1); // Ignore '/'
                ObjFile >> uvIndex[i];
                ObjFile.ignore(1); // Ignore '/'
                ObjFile >> normalIndex[i];
            }

            for (int i = 0; i < 3; ++i) {
                vertexIndices.push_back(vertexIndex[i]);
                uvIndices.push_back(uvIndex[i]);
                normalIndices.push_back(normalIndex[i]);
            }
        }
        else {
            // Ignore other types of lines
            std::string dummyLine;
            std::getline(ObjFile, dummyLine);
        }
    }


    for (int i = 0; i < vertexIndices.size(); i++) {
        unsigned int vertexIndex = vertexIndices[i];
        glm::vec3 vertex = temp_vertices[vertexIndex - 1];
        out_vertices.push_back(vertex);
    }

    for (int i = 0; i < normalIndices.size(); i++) {
        unsigned int normalIndex = normalIndices[i];
        glm::vec3 normal = temp_normals[normalIndex - 1];
        out_normals.push_back(normal);
    }

    for (int i = 0; i < uvIndices.size(); i++) {
        unsigned int uvIndex = uvIndices[i];
        glm::vec2 UV = temp_uvs[uvIndex - 1];
        out_uvs.push_back(UV);
    }

    for (int i = 0; i < vertexIndices.size(); i++) {
        SVertex vertex{ out_vertices[i], glm::vec4{1.0,1.0,1.0,1.0}, out_normals[i], out_uvs[i] };
        finalVertices.push_back(vertex);
    }

    ObjFile.close();

}

std::vector<unsigned int> ObjLoader::GenerateIndices(std::vector<glm::vec3> _vertices, std::vector<glm::vec3> _normals, std::vector<glm::vec2> _uvs, std::vector<unsigned int> _indices)
{
    _indices.clear();

    for (size_t i = 0; i < _vertices.size(); ++i) {
        // Erzeuge einen eindeutigen Schlüssel für Position, Normale und Texturkoordinaten
        std::string key = std::to_string(i);
        if (!_normals.empty()) {
            key += "_" + std::to_string(i);
        }
        if (!_uvs.empty()) {
            key += "_" + std::to_string(i);
        }

        // Überprüfe, ob dieser Schlüssel bereits existiert
        auto it = IndexMap.find(key);
        if (it == IndexMap.end()) {
            // Wenn nicht, füge diesen Schlüssel hinzu und füge den Index hinzu
            unsigned int newIndex = static_cast<unsigned int>(_indices.size());
            _indices.push_back(newIndex);
            IndexMap[key] = newIndex;
        }
        else {
            // Wenn ja, verwende den vorhandenen Index
            _indices.push_back(it->second);
        }
    }

    return _indices;
}

        
