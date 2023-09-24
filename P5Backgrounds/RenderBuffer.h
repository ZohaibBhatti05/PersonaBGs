#pragma once

#include "Renderer.h"

class RenderBuffer
{
private:

	unsigned int m_RenderBufferID;
	unsigned int m_Width;
	unsigned int m_Height;

public:

	RenderBuffer(const unsigned int& width, const unsigned int& height);
	~RenderBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetID() const { return m_RenderBufferID; }
	inline unsigned int GetWidth() const { return m_Width; }
	inline unsigned int GetHeight() const { return m_Height; }

};