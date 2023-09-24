#pragma once

class IndexBuffer {
private:

	GLuint m_BufferID;
	GLuint m_Count;

public:
	IndexBuffer(const GLuint* data, GLuint count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_Count; }

};