#include "ObjLoader.h"
//#include <cstdio>

ObjLoader::ObjLoader(const std::string& filePath) : path(filePath){}

bool ObjLoader::ReadObject() {
    FILE* file;
    errno_t err = fopen_s(&file, path.c_str(), "r");
    if (err != 0 || file == NULL) {
        printf("Impossible to open the file: %s\n", path.c_str());
        return false;
    }

    while (true) {
        char lineHeader[128];
        int res = fscanf_s(file, "%s", lineHeader);
        if (res == EOF)
            break;

        if (strcmp(lineHeader, "v") == 0) {
            glm::vec3 vertex;
            fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            temp_vertices.push_back(vertex);
        }
        else if (strcmp(lineHeader, "vt") == 0) {
            glm::vec2 uv;
            fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
            temp_uvs.push_back(uv);
        }
        else if (strcmp(lineHeader, "vn") == 0) {
            glm::vec3 normal;
            fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            temp_normals.push_back(normal);
        }
        else if (strcmp(lineHeader, "f") == 0) {
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
            if (matches != 9) { 
                printf("File can't be read!\n");
                return false;
            }
            for (int i = 0; i < 3; ++i) {
                vertexIndices.push_back(vertexIndex[i]);
                uvIndices.push_back(uvIndex[i]);
                normalIndices.push_back(normalIndex[i]);
            }
        }
    }
    fclose(file);


    return true;
}

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

    ObjFile.close();

}

        
