#include "Renderer.h"

#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_ArrayID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_ArrayID);
}

void VertexArray::AddBuffer(const VertexBufferLayout& layout, const void* data, const GLuint& size, const bool& isDynamic)
{
	// bind VAO and VBO
	Bind();

	m_BufferID = std::make_unique<VertexBuffer>(data, size, isDynamic);
	m_BufferID->Bind();

	const auto& elements = layout.GetElements();
	int offset = 0;
	for (GLuint i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, GL_FALSE, layout.GetStride(), (const void*)offset);
		offset += element.count * sizeof(element.type);
	}
	// fill attribs
}

void VertexArray::AddBuffer(const VertexBufferLayout& layout, const VertexBuffer& buffer)
{
	// bind VAO and VBO
	Bind();
	buffer.Bind();

	const auto& elements = layout.GetElements();
	int offset = 0;
	for (GLuint i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, GL_FALSE, layout.GetStride(), (const void*)offset);
		offset += element.count * sizeof(element.type);
	}
	// fill attribs
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_ArrayID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::BindBuffer() const
{
	m_BufferID->Bind();
}
