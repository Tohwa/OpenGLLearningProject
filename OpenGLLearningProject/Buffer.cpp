#include "Buffer.h"
#include <iostream>

void SBuffer::CreateBufferObject()
{
	glGenBuffers(1, &m_bufferID);
}

void SBuffer::SetAttributeID(const char* _name, unsigned int _id)
{
	m_attributeID = _id;
	if (m_attributeID == -1) {
		std::cout << _name << " Attribute does not exist!" << std::endl;
	}
}

void SBuffer::Bind(GLenum _target)
{
	m_target = _target;
	glBindBuffer(m_target, m_bufferID);
}

void SBuffer::BufferFill(GLsizeiptr _size, const void* _data, GLenum _usage)
{
	glBufferData(m_target, _size, _data, _usage);
}

void SBuffer::LinkAttribute(unsigned int _size, GLenum _type, bool _normalized, GLsizei _stride, const void* _offset)
{
	glVertexAttribPointer(m_attributeID, _size, _type, _normalized, _stride, _offset);
}

void SBuffer::EnableAttribute()
{

}

void SBuffer::Finalize()
{
	glDeleteBuffers(1, &m_bufferID);
}
