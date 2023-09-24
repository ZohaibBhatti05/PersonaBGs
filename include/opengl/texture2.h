#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm/glm.hpp>

#include "stb_image.h"
#include "vertex_data.h"
#include "shader.h"

#include <iostream>
#include <vector>

class Texture2D {

private:

    GLuint texture;
    std::vector<VertexData>* vertices;
    int boundLocation;

    GLuint vertexBuffer;

    Shader* textureShader;

public:

    void loadShader(Shader* shader) {
        textureShader = shader;
    }

    void loadTexture(char const* image_path, GLint WRAP_S_P, GLint WRAP_T_P, GLint MIN_FILTER, GLint MAG_FILTER)
    {
        glGenTextures(1, &texture);

        int width, height, nrComponents;
        unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
        if (data)
        {
            GLenum format = 1;
            if (nrComponents == 1)
                format = GL_RED;
            else if (nrComponents == 3)
                format = GL_RGB;
            else if (nrComponents == 4)
                format = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WRAP_S_P);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WRAP_T_P);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, MIN_FILTER);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, MAG_FILTER);

            stbi_image_free(data);
        }
        else
        {
            std::cout << "Texture failed to load at path: " << image_path << std::endl;
            stbi_image_free(data);
        }
    }

    static unsigned int loadTexture(char const* path)
    {
        unsigned int textureID;
        glGenTextures(1, &textureID);

        int width, height, nrComponents;
        unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
        if (data)
        {
            GLenum format = 1;
            if (nrComponents == 1)
                format = GL_RED;
            else if (nrComponents == 3)
                format = GL_RGB;
            else if (nrComponents == 4)
                format = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_image_free(data);
        }
        else
        {
            std::cout << "Texture failed to load at path: " << path << std::endl;
            stbi_image_free(data);
        }

        return textureID;
    }

    void loadVertexData(std::vector<VertexData>* data) {

        vertices = data;

        glCreateBuffers(1, &vertexBuffer);
        glNamedBufferStorage(vertexBuffer,
            sizeof(VertexData) * vertices->size(),
            (const void*)vertices->data(),
            GL_DYNAMIC_STORAGE_BIT);
    }

    void draw(glm::mat4 projection, glm::mat4 view) {

        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, vertexBuffer);

        textureShader->use();

        textureShader->setMat4("projection", projection);
        textureShader->setMat4("view", view);

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }

    void bindToLocation(int location) {
        glBindTextureUnit(location, texture);
    }

    void boundAt() {
        std::cout << "Texture is bound to texture location " << boundLocation << std::endl;
    }
};
