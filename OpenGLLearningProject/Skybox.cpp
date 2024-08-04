#include "Skybox.h"
#include <GLM/gtx/transform.hpp>

// Initializes the skybox by setting up vertices, indices, shaders, and textures.
void Skybox::Initialize()
{
    // Define the vertices of the skybox. Each vertex includes position, color, normal, and UV coordinates.
    vertices = {
        // Position            Color                   Normal              UV
        // Front face
        {{ -1,  1, 1}, {0.7f, 1.0f, 0.1f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.33f, 1.0f}},
        {{ -1, -1, 1}, {0.7f, 1.0f, 0.1f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.66f, 1.0f}},
        {{  1, -1, 1}, {0.7f, 1.0f, 0.1f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.66f, 0.75f}},
        {{  1,  1, 1}, {0.7f, 1.0f, 0.1f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.33f, 0.75f}},
        // Top face
        {{ -1,  1, 1}, {0.0f, 1.0f, 0.1f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.33f, 0.75f}},
        {{  1,  1, 1}, {0.0f, 1.0f, 0.1f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.66f, 0.75f}},
        {{  1,  1,-1}, {0.0f, 1.0f, 0.1f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.66f, 0.5f}},
        {{ -1,  1,-1}, {0.0f, 1.0f, 0.1f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.33f, 0.5f}},
        // Right face
        {{  1,  1, 1}, {0.0f, 0.5f, 0.5f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.66f, 0.75f}},
        {{  1, -1, 1}, {0.0f, 0.5f, 0.5f, 1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.75f}},
        {{  1, -1,-1}, {0.0f, 0.5f, 0.5f, 1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.5f}},
        {{  1,  1,-1}, {0.0f, 0.5f, 0.5f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.66f, 0.5f}},
        // Back face
        {{  1,  1,-1}, {1.0f, 0.5f, 0.5f, 1.0f}, {0.0f, 0.0f, -1.0f}, {0.33f, 0.5f}},
        {{  1, -1,-1}, {1.0f, 0.5f, 0.5f, 1.0f}, {0.0f, 0.0f, -1.0f}, {0.66f, 0.5f}},
        {{ -1, -1,-1}, {1.0f, 0.5f, 0.5f, 1.0f}, {0.0f, 0.0f, -1.0f}, {0.66f, 0.25f}},
        {{ -1,  1,-1}, {1.0f, 0.5f, 0.5f, 1.0f}, {0.0f, 0.0f, -1.0f}, {0.33f, 0.25f}},
        // Left face
        {{ -1,  1,-1}, {0.7f, 0.2f, 0.5f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {0.33f, 0.75f}},
        {{ -1, -1,-1}, {0.7f, 0.2f, 0.5f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.75f}},
        {{ -1, -1, 1}, {0.7f, 0.2f, 0.5f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.5f}},
        {{ -1,  1, 1}, {0.7f, 0.2f, 0.5f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {0.33f, 0.5f}},
        // Bottom face
        {{ -1, -1, 1}, {1.0f, 0.5f, 1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {0.33f, 0.25f}},
        {{ -1, -1,-1}, {1.0f, 0.5f, 1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {0.66f, 0.25f}},
        {{  1, -1,-1}, {1.0f, 0.5f, 1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {0.66f, 0.0f}},
        {{  1, -1, 1}, {1.0f, 0.5f, 1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {0.33f, 0.0f}}
    };

    // Define the indices for drawing the skybox faces as triangles
    for (size_t i = 0; i < 6; i++)
    {
        // Define two triangles for each face of the skybox
        indices.push_back(0 + i * 4); // First vertex
        indices.push_back(3 + i * 4); // Second vertex
        indices.push_back(2 + i * 4); // Third vertex
        indices.push_back(0 + i * 4); // Repeated vertex for the second triangle
        indices.push_back(2 + i * 4); // Fourth vertex
        indices.push_back(1 + i * 4); // Fifth vertex
    }

    // Load the skybox shaders
    shader = SShader("SkyboxVertex.glsl", "SkyboxFragment.glsl");
    CreateBuffers(); // Set up vertex and index buffers

    // Generate and bind a texture for the skybox
    glGenTextures(1, &cubeMapTexture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTexture);

    int i = 0;
    stbi_set_flip_vertically_on_load(false); // Ensure images are not flipped vertically

    // Load each face of the cube map texture
    for (const std::string& path : cubeFaces) {
        int width, height, bitPerPixel;

        // Load the texture image
        unsigned char* buffer = stbi_load(path.c_str(), &width, &height, &bitPerPixel, 0);

        if (buffer) {
            // Set texture parameters for cube map
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

            // Assign the loaded texture to the appropriate cube map face
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer);
            stbi_image_free(buffer); // Free the loaded image data
        }
        else {
            // Print an error message if texture loading failed
            std::cout << "Failed to load Texture!" << std::endl;
            stbi_image_free(buffer); // Free the buffer if loading failed
        }
        i++;
    }

    // Unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);

    // Use the shader and set up uniform locations
    shader.Use();
    m_viewID = glGetUniformLocation(shader.id, "view");
    m_projID = glGetUniformLocation(shader.id, "projection");
    m_skyID = glGetUniformLocation(shader.id, "skybox");

    // Set the texture unit for the skybox texture
    glUniform1i(m_skyID, 0);
    model = glm::translate(glm::mat4(1.0), position); // Initialize the model matrix
}

// Draws the skybox using the provided camera information.
void Skybox::Draw(const Camera& _camera)
{
    GLint currentDepthFunc;
    glGetIntegerv(GL_DEPTH_FUNC, &currentDepthFunc); // Get the current depth function
    glDepthFunc(GL_LEQUAL); // Set depth function for skybox rendering

    shader.Use(); // Use the skybox shader
    glActiveTexture(GL_TEXTURE0); // Activate texture unit 0

    // Set up view and projection matrices
    view = glm::lookAt(glm::vec3(0.0f), _camera.direction, _camera.up);
    glUniformMatrix4fv(m_viewID, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(m_projID, 1, GL_FALSE, &_camera.projection[0][0]);

    // Bind the vertex array and texture for drawing
    glBindVertexArray(m_vao);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTexture);

    // Draw the skybox
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    // Restore the previous depth function
    glDepthFunc(currentDepthFunc);
}

// Creates and sets up the buffers required for rendering the skybox.
void Skybox::CreateBuffers()
{
    glGenVertexArrays(1, &m_vao); // Generate a vertex array object
    glBindVertexArray(m_vao); // Bind the vertex array object

    // Create and set up the vertex buffer
    m_vertexBuffer.CreateBufferObject();
    m_vertexBuffer.Bind(GL_ARRAY_BUFFER);
    m_vertexBuffer.BufferFill(sizeof(SVertex) * vertices.size(), &vertices.front(), GL_STATIC_DRAW);

    // Set up the vertex attribute pointers
    const char* attributeName = "_pos";
    unsigned int attributeID = shader.GetAttributeLocation(attributeName);
    m_vertexBuffer.SetAttributeID(attributeName, attributeID);
    m_vertexBuffer.LinkAttribute(3, GL_FLOAT, false, sizeof(SVertex), 0);

    // Create and set up the index buffer
    m_indexBuffer.CreateBufferObject();
    m_indexBuffer.Bind(GL_ELEMENT_ARRAY_BUFFER);
    m_indexBuffer.BufferFill(sizeof(unsigned int) * indices.size(), &indices.front(), GL_STATIC_DRAW);

    glBindVertexArray(0); // Unbind the vertex array object
}