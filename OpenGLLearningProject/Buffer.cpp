#include "Buffer.h"
#include <iostream>

// Creates a buffer object and assigns it an ID
void SBuffer::CreateBufferObject()
{
    glGenBuffers(1, &m_bufferID);
}

/// <summary>
/// Sets the attribute ID for the buffer and checks if the attribute exists
/// </summary>
/// <param name="_name"> name of the attribute </param>
/// <param name="_id"> ID of the attribute </param>
void SBuffer::SetAttributeID(const char* _name, unsigned int _id)
{
    m_attributeID = _id;
    // Check if the attribute ID is invalid
    if (m_attributeID == -1) {
        std::cout << _name << " Attribute does not exist!" << std::endl;
    }
}

/// <summary>
/// Binds the buffer to a specified target
/// </summary>
/// <param name="_target"> target to bind the buffer to (e.g., GL_ARRAY_BUFFER) </param>
void SBuffer::Bind(GLenum _target)
{
    m_target = _target;
    glBindBuffer(m_target, m_bufferID);
}

/// <summary>
/// Fills the buffer with data
/// </summary>
/// <param name="_size"> size of the data </param>
/// <param name="_data"> pointer to the data </param>
/// <param name="_usage"> usage pattern of the data store (e.g., GL_STATIC_DRAW) </param>
void SBuffer::BufferFill(GLsizeiptr _size, const void* _data, GLenum _usage)
{
    glBufferData(m_target, _size, _data, _usage);
}

/// <summary>
/// Links a vertex attribute to the buffer
/// </summary>
/// <param name="_size"> number of components per attribute </param>
/// <param name="_type"> data type of each component (e.g., GL_FLOAT) </param>
/// <param name="_normalized"> whether fixed-point data values should be normalized </param>
/// <param name="_stride"> byte offset between consecutive attributes </param>
/// <param name="_offset"> offset of the first component of the first attribute in the array </param>
void SBuffer::LinkAttribute(unsigned int _size, GLenum _type, bool _normalized, GLsizei _stride, const void* _offset)
{
    glVertexAttribPointer(m_attributeID, _size, _type, _normalized, _stride, _offset);
    glEnableVertexAttribArray(m_attributeID);
}

// Placeholder for enabling attribute (currently not used)
void SBuffer::EnableAttribute()
{
    // Placeholder for enabling attribute code
}

// Finalizes the buffer by deleting it
void SBuffer::Finalize()
{
    glDeleteBuffers(1, &m_bufferID);
}