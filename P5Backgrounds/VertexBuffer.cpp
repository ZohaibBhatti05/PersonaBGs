#include "VertexBuffer.h"

// vertex buffer from data
VertexBuffer::VertexBuffer(const void* data, const GLuint& size, bool isDynamic)
	: m_Size(size)
{
	glGenBuffers(1, &m_BufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);

	if (isDynamic)
	{
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
	}
	else
	{
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_BufferID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// update whole buffer from data
void VertexBuffer::Update(const void* data) const
{
	Bind();
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_Size, data);
}
