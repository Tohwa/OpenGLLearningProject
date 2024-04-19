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

    ObjFile.close();

}

        
