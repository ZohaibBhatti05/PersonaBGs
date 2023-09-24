#pragma once

#include "Renderer.h"
#include "stb_image.h"

#include <iostream>

class Texture
{
protected:
	unsigned int m_TextureID;
	unsigned char* m_TextureData;
	int m_Width, m_Height, m_Channels;
	unsigned int m_Unit;

public:
	
	Texture(unsigned int unit);
	~Texture();

	virtual void Bind() const { };
	virtual void Unbind() const { };

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
	inline int GetID() const { return m_TextureID; }
	inline int GetUnit() const { return m_Unit; }
};