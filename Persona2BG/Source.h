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

const double fpsLimit = 1.0f / 30.0f;
double lastUpdateTime = 0;  // number of seconds since the last loop
double lastFrameTime = 0;   // number of seconds since the last frame

float currentFrame;
float lastFrame;
float deltaTime;

const glm::mat4 projection{ glm::ortho(0.0f, 1920.0f, 1080.0f, 0.0f, 10.0f, -10.0f) };
const glm::mat4 identiity{ glm::mat4(1.0) };

int main();
void init();
void update();
void draw();

//

Shader textureShader;
Shader starShader;

unsigned int bgTexture, frontTexture, maskTexture, bgMaskTexture;
unsigned int bgVAO, bgVBO;
const float bgVertices[]{
    0.0, 0.0, 0.0, 0.0,
    1920.0, 0.0, 1.0, 0.0,
    0.0, 1080.0, 0.0, 1.0,
    1920.0, 1080.0, 1.0, 1.0
};
bool persona = true;

unsigned int starVAO, starVBO, starEBO;
void drawStars(glm::vec2 position, float scale, float rotation, bool bw, bool reversed, float offset, bool persona, int j);
const float starVertices[]{
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
const unsigned int starIndices[]{
    0, 1, 9, 1, 2, 3, 3, 4, 5,
    5, 6, 7, 7, 8, 9, 1, 5, 9,
    1, 3, 5, 5, 7, 9
};

unsigned int sampler;