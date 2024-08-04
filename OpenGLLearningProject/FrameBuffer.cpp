#include "FrameBuffer.h"
#include <iostream>

// Constructor for the FrameBuffer class
FrameBuffer::FrameBuffer(int _width, int _height)
{
    width = _width;  
    height = _height; 
}

// Initializes the framebuffer, creates textures and renderbuffers
void FrameBuffer::Initialize()
{
    // Generate a new framebuffer
    glGenFramebuffers(1, &m_framebufferID);
    // Bind the framebuffer for subsequent operations
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferID);

    // Create textures and renderbuffers for the framebuffer
    CreateTexture();
    CreateRenderBuffer();

    // Check if the framebuffer was created correctly
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "ERROR: Framebuffer is incomplete!" << std::endl;
    }

    // Unbind the framebuffer to stop affecting it
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

// Creates a renderbuffer for depth and stencil tests
void FrameBuffer::CreateRenderBuffer()
{
    // Generate a renderbuffer
    glGenRenderbuffers(1, &m_renderbufferID);
    // Bind the renderbuffer for subsequent operations
    glBindRenderbuffer(GL_RENDERBUFFER, m_renderbufferID);
    // Allocate storage for the renderbuffer with depth and stencil attachments
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    // Attach the renderbuffer to the framebuffer
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderbufferID);
}

// Binds the framebuffer for rendering
void FrameBuffer::BindFrameBuffer(GLenum _target)
{
    m_frametarget = _target; // Set the target for the framebuffer
    glBindFramebuffer(m_frametarget, m_framebufferID); // Bind the framebuffer
    // Set the clear color and clear the color and depth buffers
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// Unbinds the framebuffer
void FrameBuffer::UnbindFrameBuffer(GLenum _target)
{
    m_frametarget = _target; // Set the target for the framebuffer
    glBindFramebuffer(m_frametarget, 0); // Unbind the framebuffer
    // Set the clear color and clear the color buffer
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

// Creates textures for the framebuffer
void FrameBuffer::CreateTexture()
{
    // Generate two textures for color attachments
    glGenTextures(2, m_colBuffers);
    for (int i = 0; i < 2; i++)
    {
        glBindTexture(GL_TEXTURE_2D, m_colBuffers[i]);
        // Allocate storage for the texture with floating-point color format
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
        // Set texture parameters for filtering and wrapping
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        // Attach the texture to the framebuffer
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_colBuffers[i], 0);
    }

    // Generate a texture for depth and stencil attachments
    glGenTextures(1, &m_depthBuffer);
    glBindTexture(GL_TEXTURE_2D, m_depthBuffer);
    // Allocate storage for the texture with depth and stencil format
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
    // Set texture parameters for filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Attach the depth texture to the framebuffer
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depthBuffer, 0);

    // Unbind the texture to stop affecting it
    glBindTexture(GL_TEXTURE_2D, 0);
}

// Finalizes the framebuffer by deleting buffers and textures
void FrameBuffer::Finalize()
{
    // Delete the framebuffer, renderbuffer, and depth texture
    glDeleteBuffers(1, &m_framebufferID);
    glDeleteBuffers(1, &m_renderbufferID);
    glDeleteTextures(1, &m_depthBuffer);
}