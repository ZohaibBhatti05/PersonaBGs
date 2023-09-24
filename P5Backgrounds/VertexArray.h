#pragma once

#include <iostream>

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray {
private:

	GLuint m_ArrayID;
	std::unique_ptr<VertexBuffer> m_BufferID;

public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBufferLayout& layout, const void* data, const GLuint& size, const bool& isDynamic);
	void AddBuffer(const VertexBufferLayout& layout, const VertexBuffer& buffer);

	void Bind() const;
	void Unbind() const;

	void BindBuffer() const;
};