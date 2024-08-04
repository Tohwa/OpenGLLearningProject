#include "ObjLoader.h"

// Constructor that initializes the ObjLoader with a file path.
// `filePath` is the path to the .obj file to be loaded.
ObjLoader::ObjLoader(const std::string& filePath) : path(filePath) {}

// Reads the .obj file and parses its contents.
void ObjLoader::ReadFile() {
    std::ifstream ObjFile(path); // Open the .obj file for reading

    if (!ObjFile.is_open()) { // Check if the file was successfully opened
        std::cout << "Failed to read file!" << std::endl;
        return;
    }

    char lineHeader[128]; // Buffer to hold the header of each line in the file

    while (ObjFile >> lineHeader) { // Read each line header
        if (strcmp(lineHeader, "v") == 0) { // If the line starts with 'v', it defines a vertex
            glm::vec3 vertex;
            ObjFile >> vertex.x >> vertex.y >> vertex.z; // Read the vertex coordinates
            temp_vertices.push_back(vertex); // Store the vertex in the temporary vector
        }
        else if (strcmp(lineHeader, "vt") == 0) { // If the line starts with 'vt', it defines a texture coordinate
            glm::vec2 uv;
            ObjFile >> uv.x >> uv.y; // Read the texture coordinates
            temp_uvs.push_back(uv); // Store the texture coordinates in the temporary vector
        }
        else if (strcmp(lineHeader, "vn") == 0) { // If the line starts with 'vn', it defines a normal vector
            glm::vec3 normal;
            ObjFile >> normal.x >> normal.y >> normal.z; // Read the normal vector components
            temp_normals.push_back(normal); // Store the normal vector in the temporary vector
        }
        else if (strcmp(lineHeader, "f") == 0) { // If the line starts with 'f', it defines a face
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            for (int i = 0; i < 3; ++i) { // Read the indices for each vertex, UV, and normal
                ObjFile >> vertexIndex[i];
                ObjFile.ignore(1); // Ignore '/'
                ObjFile >> uvIndex[i];
                ObjFile.ignore(1); // Ignore '/'
                ObjFile >> normalIndex[i];
            }

            for (int i = 0; i < 3; ++i) {
                // Store indices directly rather than loading vertices, normals, and UVs
                vertexIndices.push_back(vertexIndex[i]);
                uvIndices.push_back(uvIndex[i]);
                normalIndices.push_back(normalIndex[i]);
            }
        }
        else {
            // Ignore lines that do not start with 'v', 'vt', 'vn', or 'f'
            std::string dummyLine;
            std::getline(ObjFile, dummyLine);
        }
    }

    ObjFile.close(); // Close the file after reading
}

// Generates a vector of SVertex structures from the parsed data.
// SVertex combines vertex position, normal vector, and texture coordinates.
std::vector<SVertex> ObjLoader::GenerateVertices() {
    std::vector<SVertex> vertices;

    // Generate unique indices for vertices, normals, and UVs
    indices = GenerateIndices(vertexIndices, normalIndices, uvIndices);

    // Create vertices using the generated indices
    for (unsigned int index : indices) {
        glm::vec3 vertex = temp_vertices[vertexIndices[index] - 1];
        glm::vec3 normal = temp_normals[normalIndices[index] - 1];
        glm::vec2 uv = temp_uvs[uvIndices[index] - 1];
        vertices.push_back({ vertex, glm::vec4{ 0.0f, 0.0f, 0.0f, 1.0f }, normal, uv });
    }

    return vertices; // Return the generated vertex data
}

// Generates unique indices for vertex, normal, and texture coordinate combinations.
// This method ensures that each combination is unique and avoids duplications.
std::vector<unsigned int> ObjLoader::GenerateIndices(const std::vector<unsigned int>& vertexIndices,
    const std::vector<unsigned int>& normalIndices,
    const std::vector<unsigned int>& uvIndices) {
    std::vector<unsigned int> indices;

    // Create a map to store unique combinations of vertex, normal, and texture coordinate indices
    std::unordered_map<std::string, unsigned int> IndexMap;

    // Iterate through all index combinations and generate unique indices
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

    return indices; // Return the generated indices
}
