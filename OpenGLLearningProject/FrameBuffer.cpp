#include "FrameBuffer.h"
#include <iostream>

FrameBuffer::FrameBuffer(int _width, int _height)
{
	width = _width;
	height = _height;
}

void FrameBuffer::Initialize()
{
	glGenFramebuffers(1, &m_framebufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferID);
	CreateTexture();
	CreateRenderBuffer();

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cerr << "ERROR: Framebuffer is incomplete!" << std::endl;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
 
void FrameBuffer::CreateRenderBuffer()
{
	glGenRenderbuffers(1, &m_renderbufferID);
	glBindRenderbuffer(GL_RENDERBUFFER, m_renderbufferID);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderbufferID);
}

void FrameBuffer::BindFrameBuffer(GLenum _target)
{
	m_frametarget = _target;
	glBindFramebuffer(m_frametarget, m_framebufferID);
}

void FrameBuffer::UnbindFrameBuffer(GLenum _target)
{
	m_frametarget = _target;
	glBindFramebuffer(m_frametarget, 0);
}

void FrameBuffer::CreateTexture()
{
	glGenTextures(1, &m_coltextureID);
	glBindTexture(GL_TEXTURE_2D, m_coltextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_coltextureID, 0);

	glGenTextures(1, &m_depthtextureID);
	glBindTexture(GL_TEXTURE_2D, m_depthtextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthtextureID,0);
}

void FrameBuffer::Finalize()
{
	glDeleteBuffers(1, &m_framebufferID);
	glDeleteBuffers(1, &m_renderbufferID);
	glDeleteTextures(1, &m_coltextureID);
}
