#pragma once

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>

namespace Globals
{
	const double FPS_LIMIT = 60.0; // does what it says on the tin

	const int WINDOW_HEIGHT = 1080; //p
	const int RENDER_HEIGHT = 1440; //p

	const int WINDOW_WIDTH = WINDOW_HEIGHT * 16 / 9;
	const int RENDER_WIDTH = RENDER_HEIGHT * 16 / 9;

	const float RENDER_SCALE = 1920.0f / (float)RENDER_WIDTH;

	// matrices

	const glm::mat4 RES_SCALE = glm::scale(glm::mat4(1.0), glm::vec3(RENDER_SCALE, RENDER_SCALE, 1.0));

	const glm::mat4 Identity{ glm::mat4(1.0) };

	const glm::mat4 Ortho{ glm::ortho(0.0f, RENDER_WIDTH* RENDER_SCALE, RENDER_HEIGHT * RENDER_SCALE, 0.0f) };
	const glm::mat4 OrthoFlipped{ glm::ortho(0.0f, RENDER_WIDTH* RENDER_SCALE, 0.0f, RENDER_HEIGHT* RENDER_SCALE) };


	// COLOURS

	const glm::vec3 BLACK_COLOUR = glm::vec3(0.0, 0.0, 0.0);
	const glm::vec3 WHITE_COLOUR = glm::vec3(1.0, 1.0, 1.0);
	const glm::vec3 LGRAY_COLOUR = glm::vec3(0.8, 0.8, 0.8);
	const glm::vec3 DGRAY_COLOUR = glm::vec3(0.3, 0.3, 0.3);

	const glm::vec3 RED_COLOUR = glm::vec3(1.0, 0.0, 0.0);

	// TEXTURES

	const int P5_TEXTURE_REQUEST_MASK = 1;
	const int P5_TEXTURE_REQUEST_OUTLINE = 2;
}