#include "Texture2D.h"

// texture from image
Texture2D::Texture2D(const std::string& imagePath, unsigned int unit) : Texture(unit)
{
    ////////////////////////////////////
    stbi_set_flip_vertically_on_load(0);
    ////////////////////////////////////

    Bind();

    m_TextureData = stbi_load(imagePath.c_str(), &m_Width, &m_Height, &m_Channels, 4);

    if (m_TextureData) // image read successfully
    {
        GLenum format = 1;
        if (m_Channels == 1)
            format = GL_RED;
        else if (m_Channels == 3)
            format = GL_RGB;
        else if (m_Channels == 4)
            format = GL_RGBA;

        SetFilters();

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, m_TextureData);

        stbi_image_free(m_TextureData); // free data from CPU memory
    }
    else // error
    {
        std::cout << "TEXTURE DIDNT FUCKING LOAD : " << imagePath << std::endl;
    }
}

// 1x1 texture from colour
Texture2D::Texture2D(const glm::vec4& colour, unsigned int unit) : Texture(unit)
{
    Bind();

    m_Width = 1;
    m_Height = 1;
    m_Channels = 4;

    GLubyte data[4]
    {
        (GLubyte)colour.x, (GLubyte)colour.y, (GLubyte)colour.z, (GLubyte)colour.w
    };

    SetFilters();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}

// blank texture with w/h specified
Texture2D::Texture2D(const unsigned int& width, const unsigned int& height, unsigned int unit) : Texture(unit)
{
    Bind();

    m_Width = width;
    m_Height = height;
    m_Channels = 4;

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    Unbind();
}

// set minify/magnify/wrap filters
void Texture2D::SetFilters() const
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void Texture2D::Bind() const
{
    glActiveTexture(GL_TEXTURE0 + m_Unit);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

void Texture2D::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}