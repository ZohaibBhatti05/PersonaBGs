#include "Source.h"
#include "FileSystem.h"

int main() {
    RECT desktop;
    SetProcessDPIAware();
    const HWND hDesktop{ GetDesktopWindow() };
    GetWindowRect(hDesktop, &desktop);
    const unsigned int SCR_WIDTH = desktop.right - desktop.left;
    const unsigned int SCR_HEIGHT = desktop.bottom - desktop.top;

    //const unsigned int SCR_WIDTH = 1920;
    //const unsigned int SCR_HEIGHT = 1080;

    // INITIALISE OGL
        // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GL_SAMPLES, 4);

    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

    // glfw window creation
    // --------------------
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "RequestBG", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_MULTISAMPLE);

    glEnable(GL_STENCIL_TEST);

    glClearColor(255, 255, 255, 100);

    init();
    while (!glfwWindowShouldClose(window))
    {
        update();

        if ((currentFrame - lastFrameTime) >= fpsLimit) {
            draw();
            lastFrameTime = currentFrame;
        }
        lastUpdateTime = currentFrame;

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void init() {
    bgShader.init("Shaders/requestShader.vs", "Shaders/requestShader.fs");
    textureShader.init("Shaders/textureShader.vs", "Shaders/textureShader.fs");

    // init bg texture and vao/vbo
    glGenVertexArrays(1, &bgVAO);
    glGenBuffers(1, &bgVBO);
    glBindVertexArray(bgVAO);
    glBindBuffer(GL_ARRAY_BUFFER, bgVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);


    glGenSamplers(1, &sampler);
    glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load textures
    glActiveTexture(GL_TEXTURE0);
    maskTexture = FileSystem::loadTexture(FileSystem::getPath("Textures/Mask.png").c_str());

    glActiveTexture(GL_TEXTURE1);
    maskOutline = FileSystem::loadTexture(FileSystem::getPath("Textures/MaskOutline.png").c_str());

    glActiveTexture(GL_TEXTURE2);
    portraitTexture = FileSystem::loadTexture(FileSystem::getPath("Textures/Portrait.png").c_str());

    glActiveTexture(GL_TEXTURE3);
    squareTexture = FileSystem::loadTexture(FileSystem::getPath("Textures/Square.png").c_str());

    glActiveTexture(GL_TEXTURE0);
}

void update() {
    currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

void draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glStencilOp(GL_KEEP, GL_REPLACE, GL_REPLACE);

    // draw forward
    glStencilFunc(GL_ALWAYS, 0, 0xff);
    glBindVertexArray(bgVAO);
    bgShader.use();
    drawSquares(false);
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, 100);

    // draw mask
    glStencilFunc(GL_ALWAYS, 1, 0xff);
    textureShader.use();
    textureShader.setInt("Texture", 0);
    textureShader.setMat4("transformation", projection);
    glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);

    // draw reverse
    glStencilFunc(GL_EQUAL, 1, 0xff);
    bgShader.use();
    drawSquares(true);
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, 100);

    // draw mask outline
    glStencilFunc(GL_ALWAYS, 1, 0xff);
    if (GL_NV_draw_texture) {
        glDrawTextureNV(maskOutline, sampler, 0, 0, 1920, 1080, 0, 0, 1, 1, 0);
    }
    else {
        textureShader.use();
        textureShader.setInt("Texture", 1);
        textureShader.setMat4("transformation", projection);
        glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);
    }

    // square
    if (GL_NV_draw_texture) {
        glDrawTextureNV(squareTexture, sampler, 470, 0, 1920, 1080, 0, 0, 1, 1, 0);
    }
    else {
        textureShader.setInt("Texture", 3);
        glDrawArrays(GL_TRIANGLE_STRIP, 8, 4);
    }

    // portrait
    if (GL_NV_draw_texture) {
        glDrawTextureNV(portraitTexture, sampler, 0, 0, 940, 883, 0, 0, 1, 1, 0);
    }
    else {
        textureShader.setInt("Texture", 2);
        glDrawArrays(GL_TRIANGLE_STRIP, 12, 4);;
    }
}

void drawSquares(bool reverse) {
    glm::mat4 view{ glm::translate(identity, glm::vec3(390, 355, 0)) }; // translation

    float t{ float(fmod((currentFrame * 0.3f), 2)) };

    if (!reverse) { t = 2 - t; }

    for (int i = 0; i < 38; i++) {
        float index = max(35 - i + t, 0);

        glm::mat4 model{ glm::scale(identity, glm::vec3(pow(1.9, index * 0.2))) };

        model = glm::rotate(model,
            1 + (index * 0.13f), glm::vec3(0.0, 0.0, 1.0));

        bgShader.setMat4(("transformations[" + std::to_string(i) + "]"), projection * view * model);
        bgShader.setVec3(("colors[" + std::to_string(i) + "]"), (i % 2 == 0) ? glm::vec3(0, 0, 0) : glm::vec3(1, 1, 1));
    }
}