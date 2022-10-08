#pragma once

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "shader.h"
#include "stb_image.h"

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include <windows.h>


GLFWwindow* window;

double currentFrame;
double lastFrame;
double deltaTime;

const double fpsLimit = 1.0f / 30.0f;
double lastUpdateTime = 0;  // number of seconds since the last loop
double lastFrameTime = 0;   // number of seconds since the last frame

const glm::mat4 projection{ glm::ortho(0.0f, 1920.0f, 1080.0f, 0.0f, 10.0f, -10.0f) };
const glm::mat4 identity{ glm::mat4(1.0) };

int main();
void init();
void update();
void draw();
void drawSquares(bool reverse);

//

float vertices[]{
	// actual squares
	-20.0, -20.0, 0.0, 0.0,
	20.0, -20.0, 1.0, 0.0,
	-20.0, 20.0, 0.0, 1.0,
	20.0, 20.0, 1.0, 1.0,

	// mask
	0.0, 0.0, 0.0, 0.0,
	1920.0, 0.0, 1.0, 0.0,
	0.0, 1080.0, 0.0, 1.0,
	1920.0, 1080.0, 1.0, 1.0,

	// square
	470.0, 0.0, 0.0, 0.0,
	1920.0, 0.0, 1.0, 0.0,
	470.0, 1080.0, 0.0, 1.0,
	1920.0, 1080.0, 1.0, 1.0,

	// portrait
	0.0, 197.0, 0.0, 0.0,
	940.0, 197.0, 1.0, 0.0,
	0.0, 1080.0, 0.0, 1.0,
	940.0, 1080.0, 1.0, 1.0,

};

unsigned int refTexture, bgVAO, bgVBO, sampler, maskTexture, maskOutline, portraitTexture, squareTexture;

Shader bgShader, textureShader;