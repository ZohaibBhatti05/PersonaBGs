#pragma once

#include "Renderer.h"
#include "RenderBuffer.h"
#include "Texture2D.h"

class FrameBuffer
{
private:

	unsigned int m_FrameBufferID;
	unsigned int m_RenderBufferID;
	std::unique_ptr<Texture2D> m_Texture;

public:

	FrameBuffer(const unsigned int& width, const unsigned int& height);
	~FrameBuffer();

	void Bind() const;
	void BindTexture();
	void Unbind() const;

private:

	void CheckIfComplete();
};