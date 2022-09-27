#include "Source.h"
#include "FileSystem.h"

int main() {
    RECT desktop;
    SetProcessDPIAware();
    const HWND hDesktop{ GetDesktopWindow() };
    GetWindowRect(hDesktop, &desktop);
    const unsigned int SCR_WIDTH = desktop.right - desktop.left;
    const unsigned int SCR_HEIGHT = desktop.bottom - desktop.top;

    // INITIALISE OGL
        // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    // glfw window creation
    // --------------------
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "PERSONA2BG", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_MULTISAMPLE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_STENCIL_TEST);

    glClearColor(0, 0, 0, 0);

    init();
    while (!glfwWindowShouldClose(window))
    {
        update();
        draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void init() {
    glStencilOp(GL_KEEP, GL_REPLACE, GL_REPLACE);

    // init shaders
    starShader.init("Shaders/starShader.vs", "Shaders/starShader.fs");
    textureShader.init("Shaders/textureShader.vs", "Shaders/textureShader.fs");

    // init bg textures and vao/vbo
    glGenVertexArrays(1, &bgVAO);
    glGenBuffers(1, &bgVBO);
    glBindVertexArray(bgVAO);
    glBindBuffer(GL_ARRAY_BUFFER, bgVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bgVertices), bgVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glActiveTexture(GL_TEXTURE0);
    bgTexture = FileSystem::loadTexture("Textures/Background.png");

    glActiveTexture(GL_TEXTURE1);
    glGenTextures(1, &bgMaskTexture);
    GLubyte texture[4]{ 255, 0, 0, 100 };
    glBindTexture(GL_TEXTURE_2D, bgMaskTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glActiveTexture(GL_TEXTURE2);
    maskTexture = FileSystem::loadTexture("Textures/Mask.png");
    glActiveTexture(GL_TEXTURE3);
    frontTexture = FileSystem::loadTexture("Textures/Front.png");

    glActiveTexture(GL_TEXTURE0);

    // initialise star bg
    glGenVertexArrays(1, &starVAO);
    glGenBuffers(1, &starVBO);
    glGenBuffers(1, &starEBO);
    glBindVertexArray(starVAO);
    glBindBuffer(GL_ARRAY_BUFFER, starVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(starVertices), starVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, starEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(starIndices), starIndices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // init sampler
    glGenSamplers(1, &sampler);
    glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void update() {
    currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

void draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glStencilFunc(GL_ALWAYS, 0, 0xff);

    // draw background image
    if (GL_NV_draw_texture) {
        glDrawTextureNV(bgTexture, sampler, 0, 0, 1920, 1080, 0, 0, 1, 1, 0);
    }
    else {
        glBindVertexArray(bgVAO);
        textureShader.use();
        textureShader.setInt("Texture", 0);
        textureShader.setMat4("transformation", projection);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }
    //

    // draw transparent mask
    if (GL_NV_draw_texture) {
        glDrawTextureNV(bgMaskTexture, sampler, 0, 0, 1920, 1080, 0, 0, 1, 1, 0);
    }
    else {
        textureShader.setInt("Texture", 1);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }

    // draw mask for stars
    glStencilFunc(GL_ALWAYS, 1, 0xff);

    if (GL_NV_draw_texture) {
        glBindVertexArray(bgVAO);
        textureShader.use();
        textureShader.setMat4("transformation", projection);
    }
    textureShader.setInt("Texture", 2);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // draw stars
    glStencilFunc(GL_EQUAL, 1, 0xff);

    glBindVertexArray(starVAO);
    starShader.use();

    drawStars(glm::vec2(1830, 810), 1.3, -0.05, true, true, 0.0, persona, 0); //
    drawStars(glm::vec2(980, 300), 1.3, 0.0, true, true, 0.2, persona, 1); //
    drawStars(glm::vec2(100, 1030), 1.2, 0.2, true, true, 0.4, persona, 2); //
    drawStars(glm::vec2(1800, 480), 1.2, -0.1, false, true, 0.6, persona, 3); //
    drawStars(glm::vec2(555, 780), 1.2, -0.7, true, false, 0.8, persona, 4); //
    drawStars(glm::vec2(1340, 880), 1.2, 0.35, false, false, 1.0, persona, 5); //
    drawStars(glm::vec2(540, 400), 1.2, 0.75, true, true, 1.2, persona, 6); //
    drawStars(glm::vec2(1290, 380), 1.2, 0.3, false, true, 1.4, persona, 7); //

    drawStars(glm::vec2(125, 570), 1.15, -0.2, true, false, 1.6, persona, 8); //
    drawStars(glm::vec2(1000, 520), 1.1, 0.9, true, false, 1.8, persona, 9); //
    drawStars(glm::vec2(800, 910), 1.1, -0.2, true, true, 0.1, persona, 10); //
    drawStars(glm::vec2(20, 850), 1.1, -0.3, false, false, 0.3, persona, 11); //
    drawStars(glm::vec2(1230, 980), 1.1, -0.05, true, true, 0.5, persona, 12); //
    drawStars(glm::vec2(1485, 545), 1.1, -0.75, false, false, 0.7, persona, 13); // 

    drawStars(glm::vec2(250, 460), 1.05, -0.1, false, true, 0.9, persona, 14); //

    glDrawElementsInstanced(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0, 11 * 15);

    drawStars(glm::vec2(1620, 665), 1.05, -0.2, true, false, 1.1, persona, 0); //
    drawStars(glm::vec2(755, 1050), 1.0, -0.3, true, true, 1.3, persona, 1); //
    drawStars(glm::vec2(1650, 310), 1.0, -0.1, false, true, 1.5, persona, 2); //
    drawStars(glm::vec2(1140, 580), 1.0, -0.7, true, false, 1.7, persona, 3);
    drawStars(glm::vec2(1620, 880), 1.0, -0.4, true, false, 1.9, persona, 4); //
    drawStars(glm::vec2(440, 620), 1.0, -1.1, false, false, 0.0, persona, 5); //

    drawStars(glm::vec2(980, 980), 1.0, -0.3, true, false, 0.2, persona, 6); //
    drawStars(glm::vec2(1900, 270), 1.0, 0.3, true, true, 0.4, persona, 7); //
    drawStars(glm::vec2(810, 710), 1.0, -0.2, false, true, 0.6, persona, 8); //

    drawStars(glm::vec2(-30, 410), 0.95, -0.1, true, true, 0.8, persona, 9);  //
    drawStars(glm::vec2(340, 980), 0.95, 0.4, false, false, 1.0, persona, 10); //
    drawStars(glm::vec2(790, 590), 0.9, 0.7, true, false, 1.2, persona, 11); // 
    drawStars(glm::vec2(1140, 770), 0.9, -06, true, false, 1.4, persona, 12); //
    drawStars(glm::vec2(300, 780), 0.9, -0.7, false, true, 1.6, persona, 13); //
    drawStars(glm::vec2(560, 1000), 0.9, 0.8, true, true, 1.8, persona, 14); //

    glDrawElementsInstanced(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0, 11 * 15);

    drawStars(glm::vec2(995, 750), 0.9, -0.3, true, true, 0.1, persona, 0); //
    drawStars(glm::vec2(600, 610), 0.8, 0.3, true, true, 0.3, persona, 1); //
    drawStars(glm::vec2(720, 400), 0.8, 0.4, true, false, 0.5, persona, 2); //
    drawStars(glm::vec2(1330, 680), 0.8, 0.5, false, true, 0.7, persona, 3); //
    drawStars(glm::vec2(1500, 310), 0.8, 0.15, false, true, 0.9, persona, 4); //
    drawStars(glm::vec2(20, 690), 0.8, 0.4, true, true, 1.1, persona, 5); //

    glDrawElementsInstanced(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0, 11 * 6);

    glStencilFunc(GL_ALWAYS, 1, 0xff);
    // draw front image
    if (GL_NV_draw_texture) {
        glDrawTextureNV(frontTexture, sampler, 0, 0, 1920, 1080, 0, 0, 1, 1, 0);
    }
    else {
        textureShader.setInt("Texture", 3);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }
    //
}

void drawStars(glm::vec2 position, float scale, float rotation, bool bw, bool reversed, float offset, bool persona, int j)
{
    float t{ float(fmod((currentFrame * 0.7f) + offset, 2)) };
    if (reversed) {
        t = 2 - t;
    }

    glm::mat4 sview{ glm::translate(glm::mat4(1.0), glm::vec3(position, 0.0)) };

    for (unsigned int i = 11; i > 0; i--)
    {
        // SCALE BY POSITION IN ARRAY
        float x{ t + i - 2 };
        if (x > 9.0f) {
            x = 9.0f;
        }
        if (!(x > 0.0)) {
            x = 0.0f;   // i dont know why but continue stopped working after I added instancing and this fixed it
            //continue;
        }

        x /= 2.0;

        // COLOUR
        if (i % 2 == 0) {
            starShader.setFloat(("colors[" + std::to_string(11 - i + (11 * j)) + "]"), 0.8f);
        }
        else {
            if (bw) {
                starShader.setFloat(("colors[" + std::to_string(11 - i + (11 * j)) + "]"), 0.0f);
            }
            else {
                starShader.setFloat(("colors[" + std::to_string(11 - i + (11 * j)) + "]"), 0.3f);
            }
        }

        // CREATE MATRICES
        glm::mat4 model{ glm::mat4(1.0) };

        model = glm::scale(model, glm::vec3(x, x, 1.0));
        model = glm::scale(model, glm::vec3(scale, scale, 1.0));
        if (persona)
        {
            float r{ -0.35f * log2(x * 0.1f) };
            model = glm::rotate(model, r, glm::vec3(0.0, 0.0, 1.0));
        }
        model = glm::rotate(model, rotation, glm::vec3(0.0, 0.0, 1.0));

        glm::mat4 transformation{ projection * sview * model };
        starShader.setMat4(("transformations[" + std::to_string(11 - i + (11 * j)) + "]"), transformation);
    }
}