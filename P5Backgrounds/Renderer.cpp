#include "Renderer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "IndexBuffer.h"
#include "P5Background.h"


Renderer::Renderer()
{
	// initialise renderer shit
	m_TextureShader = std::make_unique<Shader>("Shaders/Global/TextureShader");
	m_TextureShader->Bind();
	m_TextureShader->SetMat4("transformation", Globals::Ortho);
}

// make variable whether to add ibo or what mode to draw in
// change to take material (shader & uniforms) instead of shaders
void Renderer::Draw(const VertexArray& vao, const IndexBuffer& ebo, const Shader& shader) const
{
	shader.Bind();
	vao.Bind();
	ebo.Bind();
	glDrawElements(GL_TRIANGLES, ebo.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::DrawStrip(const VertexArray& vao, const Shader& shader) const
{
	shader.Bind();
	vao.Bind();
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Renderer::DrawArraysInstanced(const unsigned int& count, const unsigned int& instanceCount) const
{
	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, count, instanceCount);
}

void Renderer::DrawElementsInstanced(const unsigned int& count, const unsigned int& instanceCount) const
{
	glDrawElementsInstanced(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0, instanceCount);
}

void Renderer::DrawTexture(const unsigned int& unit, const unsigned int& first) const
{
	m_TextureShader->Bind();
	m_TextureShader->SetInt("Texture", unit);
	m_TextureShader->SetMat4("transformation", Globals::Ortho);
	glDrawArrays(GL_TRIANGLE_STRIP, first, 4);
}

// specialised functions
