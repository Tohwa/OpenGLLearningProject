#include "QuadView.h"

// Creates a vertex buffer object for a fullscreen quad and sets up the vertex attributes
void QuadView::CreateQuadBuffer(SShader& _shader)
{
    // Vertex data for a fullscreen quad with positions and UV coordinates
    float quad[] = {
        -1.0f, 1.0f, 0.0f, 1.0f,  // Top-left corner
        -1.0f, -1.0f, 0.0f, 0.0f,  // Bottom-left corner
        1.0f, -1.0f, 1.0f, 0.0f,   // Bottom-right corner
        -1.0f, 1.0f, 0.0f, 1.0f,   // Top-left corner (repeat for the next triangle)
        1.0f, -1.0f, 1.0f, 0.0f,   // Bottom-right corner
        1.0f, 1.0f, 1.0f, 1.0f     // Top-right corner
    };

    m_shader = _shader; // Store the shader for later use

    // Generate and bind a vertex array object (VAO)
    glGenVertexArrays(1, &frameVAO);
    glBindVertexArray(frameVAO);

    // Create and bind a vertex buffer object (VBO)
    frameBuffer.CreateBufferObject();
    frameBuffer.Bind(GL_ARRAY_BUFFER);

    // Upload the vertex data to the GPU
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24, &quad, GL_STATIC_DRAW);

    // Set up the position attribute
    const char* attributeName = "aPos";
    unsigned int attributeID = m_shader.GetAttributeLocation(attributeName);
    frameBuffer.SetAttributeID(attributeName, attributeID);
    frameBuffer.LinkAttribute(2, GL_FLOAT, false, sizeof(float) * 4, 0);

    // Set up the UV coordinates attribute
    attributeName = "aUVs";
    attributeID = m_shader.GetAttributeLocation(attributeName);
    frameBuffer.SetAttributeID(attributeName, attributeID);
    frameBuffer.LinkAttribute(2, GL_FLOAT, false, sizeof(float) * 4, (void*)(sizeof(float) * 2));

    // Unbind the VAO
    glBindVertexArray(0);
}

// Renders the fullscreen quad
void QuadView::RenderQuad()
{
    // Bind the VAO and draw the quad
    glBindVertexArray(frameVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0); // Unbind the VAO
}
