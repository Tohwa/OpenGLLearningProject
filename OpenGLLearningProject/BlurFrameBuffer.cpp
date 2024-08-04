#include "BlurFrameBuffer.h"
#include <iostream>

// Constructor for BlurFrameBuffer, initializes width and height
BlurFrameBuffer::BlurFrameBuffer(int _width, int _height)
{
    width = _width;
    height = _height;
}

// Initialize method for BlurFrameBuffer
void BlurFrameBuffer::Initialize()
{
    // Generate two framebuffers
    glGenFramebuffers(2, m_blurFramebufferID);

    // Create texture attachments for the framebuffers
    CreateTexture();
}

// Placeholder method for creating render buffer (currently not used)
void BlurFrameBuffer::CreateRenderBuffer()
{
}

/// <summary>
/// Bind a framebuffer for rendering
/// </summary>
/// <param name="_target"> the framebuffer target (e.g., GL_FRAMEBUFFER) </param>
/// <param name="_horizontal"> boolean flag indicating which framebuffer to bind </param>
void BlurFrameBuffer::BindFrameBuffer(GLenum _target, bool _horizontal)
{
    m_frametarget = _target;
    // Bind the appropriate framebuffer based on the _horizontal flag
    glBindFramebuffer(m_frametarget, m_blurFramebufferID[_horizontal]);
}

/// <summary>
/// Unbind the framebuffer
/// </summary>
/// <param name="_target"> the framebuffer target (e.g., GL_FRAMEBUFFER) </param>
void BlurFrameBuffer::UnbindFrameBuffer(GLenum _target)
{
    m_frametarget = _target;
    // Bind the default framebuffer (0) to unbind the current framebuffer
    glBindFramebuffer(m_frametarget, 0);
}

// Create texture attachments for the blur framebuffers
void BlurFrameBuffer::CreateTexture()
{
    // Generate two textures for the blur framebuffers
    glGenTextures(2, m_blurColBuffers);
    for (int i = 0; i < 2; i++)
    {
        // Bind the framebuffer and texture
        glBindFramebuffer(GL_FRAMEBUFFER, m_blurFramebufferID[i]);
        glBindTexture(GL_TEXTURE_2D, m_blurColBuffers[i]);

        // Define the texture storage with RGBA16F format
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);

        // Set texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        // Attach the texture to the framebuffer
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_blurColBuffers[i], 0);
    }
    // Unbind the framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

/// <summary>
/// Bind a texture for use in rendering
/// </summary>
/// <param name="_iteration"> boolean flag for choosing which texture to bind </param>
/// <param name="_horizontal"> boolean flag indicating the direction of the blur pass </param>
/// <param name="_texID"> array of texture IDs for the input textures </param>
void BlurFrameBuffer::BindTexture(bool _iteration, bool _horizontal, unsigned int _texID[2])
{
    // Activate and bind the appropriate texture based on the flags
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _iteration ? _texID[1] : m_blurColBuffers[!_horizontal]);
}

// Finalize method for BlurFrameBuffer, placeholder for cleanup
void BlurFrameBuffer::Finalize()
{
    // Placeholder for any cleanup operations
}