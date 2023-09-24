#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm/glm.hpp>

#include <vector>
#include <iostream>

enum class BackgroundState;
struct Star;
class IndexBuffer;
class VertexArray;
class Shader;
class Texture2D;

class Renderer {
private:

	std::unique_ptr<Shader> m_TextureShader;

public:

	// generic functions
	Renderer();

	void Draw(const VertexArray& vao, const IndexBuffer& ebo, const Shader& shader) const;

	void DrawStrip(const VertexArray& vao, const Shader& shader) const;

	void DrawArraysInstanced(const unsigned int& count, const unsigned int& instanceCount) const;

	void DrawElementsInstanced(const unsigned int& count, const unsigned int& instanceCount) const;

	void DrawTexture(const unsigned int& unit, const unsigned int& first) const;

	// inline stuff

	inline void ClearBufferColour() const { glClear(GL_COLOR_BUFFER_BIT); }
	inline void ClearBufferColourStencil() const { glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); }
	inline void ClearBufferColourDepth() const { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }
	inline void ClearBufferColourStencilDepth() const { glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

	inline void ChangeViewport(const unsigned int& width, const unsigned int& height) const { glViewport(0, 0, width, height); }

	// specific functions

private:

};