#include "ObjLoader.h"

ObjLoader::ObjLoader(const std::string& filePath) : path(filePath){}

//float ObjLoader::randomFloat01()
//{
//	// Erstelle einen Zufallszahlengenerator
//	std::random_device rd;
//	std::mt19937 gen(rd());
//	std::uniform_real_distribution<float> dis(0.0f, 1.0f);
//
//	// Generiere und gib eine zufällige Float-Zahl zurück
//	return dis(gen);
//}

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
                // Store indices directly instead of loading vertices, normals, and uvs
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

std::vector<SVertex> ObjLoader::GenerateVertices() {
    std::vector<SVertex> vertices;

    // Generate unique indices for vertices, normals, and uvs
    indices = GenerateIndices(vertexIndices, normalIndices, uvIndices);

    // Create vertices using the generated indices
    for (unsigned int index : indices) {
        glm::vec3 vertex = temp_vertices[vertexIndices[index] - 1];
        glm::vec3 normal = temp_normals[normalIndices[index] - 1];
        glm::vec2 uv = temp_uvs[uvIndices[index] - 1];
        vertices.push_back({ vertex, glm::vec4{ 0.0f, 0.0f, 0.0f,1.0}, normal, uv });
    }

    return vertices;
}


std::vector<unsigned int> ObjLoader::GenerateIndices(const std::vector<unsigned int>& vertexIndices, 
                                                     const std::vector<unsigned int>& normalIndices, 
                                                     const std::vector<unsigned int>& uvIndices) {
    std::vector<unsigned int> indices;

    // Create a map to store unique combinations of vertex, normal, and texture coordinate indices
    std::unordered_map<std::string, unsigned int> IndexMap;

    // Iterate through all indices and generate unique combinations
    for (size_t i = 0; i < vertexIndices.size(); ++i) {
        std::string key = std::to_string(vertexIndices[i]);
        if (!normalIndices.empty()) {
            key += "_" + std::to_string(normalIndices[i]);
        }
        if (!uvIndices.empty()) {
            key += "_" + std::to_string(uvIndices[i]);
        }

        // Check if the combination already exists in the map
        auto it = IndexMap.find(key);
        if (it == IndexMap.end()) {
            // If not, add it to the map and the indices vector
            unsigned int newIndex = static_cast<unsigned int>(indices.size());
            indices.push_back(newIndex);
            IndexMap[key] = newIndex;
        }
        else {
            // If it exists, use the existing index
            indices.push_back(it->second);
        }
    }

    return indices;
}       
