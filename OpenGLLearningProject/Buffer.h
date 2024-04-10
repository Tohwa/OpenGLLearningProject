#ifndef BUFFER_H
#define BUFFER_H

#include <GLAD/glad.h>

struct SBuffer
{
	void CreateBufferObject();
	void SetAttributeID(const char* _name, unsigned int _id);
	void Bind(GLenum);
	void BufferFill(GLsizeiptr, const void*, GLenum);
	void LinkAttribute(unsigned int, GLenum, bool, GLsizei, const void*);
	void EnableAttribute();
	void Finalize();

private:
	unsigned int m_bufferID;
	unsigned int m_attributeID;
	GLenum m_target;
};

#endif // !SBUFFER_H



