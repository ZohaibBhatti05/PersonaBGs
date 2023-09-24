#pragma once

#include <GLFW/glfw3.h>
#include <assert.h>
#include <vector>

struct VertexBufferElement {

	GLuint type;
	GLuint count;
	unsigned char normalised;

	VertexBufferElement(GLuint t, GLuint c, GLboolean n)
		: type(t), count(c), normalised(n) {}
};

class VertexBufferLayout {
private:

	std::vector<VertexBufferElement> m_Elements;
	GLuint m_Stride;

public:
	VertexBufferLayout()
		: m_Stride(0) {}

	template<typename T>
	void Push(GLuint count) {
		assert(false);
	}

	template<>
	void Push<float>(GLuint count) {
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += count * sizeof(GL_FLOAT);
	}

	template<>
	void Push<GLuint>(GLuint count) {
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += count * sizeof(GL_UNSIGNED_INT);
	}

	template<>
	void Push<unsigned char>(GLuint count) {
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += count * sizeof(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }
};