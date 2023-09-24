#include "Texture.h"

Texture::Texture(unsigned int unit)
    :m_TextureID(0), m_Width(0), m_Height(0), m_Channels(0), m_TextureData(nullptr), m_Unit(unit)
{
    glGenTextures(1, &m_TextureID);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_TextureID);
}