#pragma once

#include "Renderer.h"

class VertexBuffer {
private:

	GLuint m_BufferID;
	GLuint m_Size;

public:
	VertexBuffer(const void* data, const GLuint& size, bool isDynamic);
	VertexBuffer(const GLuint& size, const bool& isDynamic) : VertexBuffer(NULL, size, isDynamic) { }
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	void Update(const void* data) const;

};