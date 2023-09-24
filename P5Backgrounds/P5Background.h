#pragma once

#include <glm/glm/glm.hpp>
#include <iostream>
#include <vector>
#include <glm/glm/ext/matrix_transform.hpp>

#include "Renderer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture2D.h"

#include "GlobalSettings.h"


struct Star {
	glm::vec2 position;
	float scale;
	float rotation;
	bool bw;
	bool reversed;
	float offset;
};

enum class BackgroundState
{
	NORMAL,
	PERSONA,
	REQUEST
};

class P5Background
{
private:

	BackgroundState m_BackgroundState;

#pragma region Stars

	std::unique_ptr<VertexArray> m_StarVAO;
	std::unique_ptr<IndexBuffer> m_StarEBO;
	std::unique_ptr<Shader> m_StarShader;

	const float starVertices[20] = {
		0.0f,	-48.92f,
		14.7f,	-19.1f,
		47.5f,	-14.4f,
		23.8f,	8.8f,
		29.5f,	41.6f,
		0.0f,	26.1f,
		-29.5f,	41.6f,
		-23.8f,	8.8f,
		-47.5f, -14.4f,
		-14.7f, -19.1f,
	};

	const unsigned int starIndices[24] = {
		0, 1, 9, 1, 2, 3, 3, 4, 5,
		5, 6, 7, 7, 8, 9, 1, 5, 9,
		1, 3, 5, 5, 7, 9
	};

	const std::vector<Star> bgStars = {
		{ glm::vec2(920, 753), 1.4f, -0.178f, true,		true, 0.0f },
		{ glm::vec2(720, 615), 1.0f, 0.064f, true,		false, 0.1f },
		{ glm::vec2(1860, 810), 1.2f, -0.619f, true,	true, 0.2f },
		{ glm::vec2(1360, 83), 1.4f, -0.352f, true,		false, 0.3f },
		{ glm::vec2(580, 780), 1.25f, 0.0f, true,		true, 0.4f },
		{ glm::vec2(1790, 975), 1.25f, -0.499f, true,	true, 0.5f },
		{ glm::vec2(1045, 40), 1.2f, 0.179f, true,		false, 0.6f },
		{ glm::vec2(875, 430), 1.4f, -0.289f, true,		true, 0.7f },
		{ glm::vec2(1223, 535), 1.4f, -0.075f, true,	true, 0.8f },
		{ glm::vec2(430, 540), 1.4f, 0.121f, true,		false, 0.9f },
		{ glm::vec2(730, 965), 1.4f, -0.305f, true,		false, 1.0f },
		{ glm::vec2(1195, 745), 1.0f, 0.145f, true,		false, 1.1f },
		{ glm::vec2(1610, 1015), 1.25f, 0.325f, true,	true, 1.2f },
		{ glm::vec2(1135, 245), 1.4f, -0.459f, true,	true, 1.3f },
		{ glm::vec2(275, 315), 1.25f, -0.227f, true,	false, 1.4f },
		{ glm::vec2(1070, 475), 0.75f, 0.169f, true,	true, 1.5f },
		{ glm::vec2(1010, 975), 1.2f, -0.282f, true,	false, 1.6f },
		{ glm::vec2(1380, 965), 1.2f, -0.242f, true,	true, 1.7f },
		{ glm::vec2(1845, 540), 1.4f, 0.151f, true,		true, 1.8f },
		{ glm::vec2(1245, 1010), 1.0f, 0.221f, false,	true, 1.9f },
		{ glm::vec2(1665, 760), 0.75f, 0.604f, false,	false, 0.0f },
		{ glm::vec2(1950, 215), 1.20f, -0.149f, false,	true, 0.1f },
		{ glm::vec2(1570, 70), 0.75f, 0.611f, false,	true, 0.2f },
		{ glm::vec2(120, 65), 1.4f, -0.389f, false,		false, 0.3f },
		{ glm::vec2(115, 750), 1.25f, -0.354f, false,	true, 0.4f },
		{ glm::vec2(1070, 670), 1.2f, 0.368f, false,	false, 0.5f },
		{ glm::vec2(1605, 470), 1.2f, 0.295f, false,	false, 0.6f },
		{ glm::vec2(320, 60), 0.75f, 0.646f, true,		true, 0.7f },
		{ glm::vec2(25, 620), 0.75f, 0.261f, true,		true, 0.8f },
		{ glm::vec2(385, 815), 1.0f, 0.268f, true,		false, 0.9f },
		{ glm::vec2(1260, 870), 0.75f, 0.595f, true,	true, 1.0f },
		{ glm::vec2(1520, 805), 1.0f, -0.042f, true,	false, 1.1f },
		{ glm::vec2(80, 1000), 1.4f, -0.316f, true,		false, 1.2f },
		{ glm::vec2(505, 1040), 1.0f, -0.161f, true,	true, 1.3f },
		{ glm::vec2(710, 135), 1.4f, 0.351f, true,		true, 1.4f },
		{ glm::vec2(1775, 120), 1.4f, -0.592f, true,	false, 1.5f },
		{ glm::vec2(20, 340), 1.4f, -0.428f, true,		true, 1.6f },
		{ glm::vec2(500, 80), 1.2f, 0.302f, true,		false, 1.7f },
		{ glm::vec2(345, 985), 0.75f, 0.510f, false,	true, 1.8f },
		{ glm::vec2(1450, 660), 1.4f, 0.222f, true,		true, 1.9f },
		{ glm::vec2(1795, 360), 1.0f, 0.524f, false,	false, 0.0f },
		{ glm::vec2(450, 270), 0.75f, 0.515f, false,	true, 0.1f },
		{ glm::vec2(850, 225), 1.0f, -0.223f, false,	true, 0.2f },
		{ glm::vec2(1405, 350), 1.2f, 0.180f, false,	false, 0.3f },
		{ glm::vec2(210, 1095), 1.0f, 0.255f, true,		true, 0.4f },
		{ glm::vec2(210, 565), 1.0f, 0.241f, true,		false, 0.5f },
		{ glm::vec2(615, 390), 1.25f, 0.155f, true,		true, 0.6f },
		{ glm::vec2(785, 10), 0.85f, -0.540f, true,		true, 0.7f },
		{ glm::vec2(1575, 270), 1.0f, -0.184f, true,	false, 0.8f },
	};

#pragma endregion

#pragma region Squares

	std::unique_ptr<VertexArray> m_SquareVAO;
	std::unique_ptr<Shader> m_SquareShader;
	std::unique_ptr<Texture2D> m_SquareBGTexture;

	const float squareVertices[48] = {
		// square
		-20.0, -20.0, 0.0, 0.0,
		20.0, -20.0, 1.0, 0.0,
		-20.0, 20.0, 0.0, 1.0,
		20.0, 20.0, 1.0, 1.0,

		// mask
		0.0, 0.0, 0.0, 0.0,
		1920.0, 0.0, 1.0, 0.0,
		0.0, 1080.0, 0.0, 0.5,
		1920.0, 1080.0, 1.0, 0.5,

		// outline
		0.0, 0.0, 0.0, 0.5,
		1920.0, 0.0, 1.0, 0.5,
		0.0, 1080.0, 0.0, 1.0,
		1920.0, 1080.0, 1.0, 1.0,
	};

	const glm::mat4 squareTranslation{ glm::translate(Globals::Identity, glm::vec3(390, 355, 0)) }; // translation

#pragma endregion

public:

	P5Background();

	void Draw(const Renderer& renderer, const float& currentTime);

	void SetBackgroundState(const int& state);

private:

	void DrawStars(const float& bgTimer, const Star& star, const bool& persona, const unsigned int& j);

	void DrawSquares(const bool& reverse, const float& bgTimer);
};