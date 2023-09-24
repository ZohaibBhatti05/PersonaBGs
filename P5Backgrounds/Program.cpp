#include "Program.h"

// SETUP OPENGL
void Program::Run()
{
    // INITIALISE OGL
        // glfw: initialize and configure
        // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE); // REMOVE LATER

    ConfigGlfw();

    // glfw window creation
    // --------------------
    window = glfwCreateWindow(Globals::WINDOW_WIDTH, Globals::WINDOW_HEIGHT, "P5Backgrounds", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    gladLoadGL();

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(debug_message_callback, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);

    ConfigGL();

    Init();

    const double fpsLimit = 1.0 / Globals::FPS_LIMIT; // fps limit

    double deltaTime = 0;// change in time since last UPDATE

    double currentFrame = 0; // current time
    double lastUpdateTime = 0; // time of last UPDATE
    double lastRenderTime = 0; // time of last RENDER

    while (!glfwWindowShouldClose(window))
    {
        currentFrame = float(glfwGetTime());
        deltaTime = currentFrame - lastUpdateTime;

        Update((const float&)currentFrame);

        if ((currentFrame - lastRenderTime) >= // if time *since* last RENDER exceeds fps limit, draw
            fpsLimit) {
            
            Draw();

            lastRenderTime = currentFrame;

            glfwSwapBuffers(window);
        }
        lastUpdateTime = currentFrame;

        glfwPollEvents();
    }

    glfwTerminate();
    return;

}

void Program::ConfigGlfw() const
{
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_FALSE);
    glfwWindowHint(GLFW_SAMPLES, 4);
}

void Program::ConfigGL() const
{
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_REPLACE, GL_REPLACE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_MULTISAMPLE);
}

void Program::Init()
{
    m_Menu.Init();
    m_Renderer = std::make_unique<Renderer>();

    m_ScreenFBO = std::make_unique<FrameBuffer>(Globals::RENDER_WIDTH, Globals::RENDER_HEIGHT);

    // define other members
    m_ScreenShader = std::make_unique<Shader>("Shaders/ScreenShader");
    m_ScreenVAO = std::make_unique<VertexArray>();

    // set up vbo
    VertexBufferLayout screenVBOLayout;
    screenVBOLayout.Push<float>(4);
    m_ScreenVAO->AddBuffer(screenVBOLayout, screenVertices, 16 * sizeof(float), false);

}

void Program::Update(const float& currentTime)
{
    m_Menu.Update(currentTime);

    // input block
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        m_Menu.SetBackgroundState(0);
    }
    else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        m_Menu.SetBackgroundState(1);
    }
    else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        m_Menu.SetBackgroundState(2);
    }
}

void Program::Draw()
{
    // first pass
    m_ScreenFBO->Bind();
    m_Renderer->ClearBufferColourStencil();
    m_Renderer->ChangeViewport(Globals::RENDER_WIDTH, Globals::RENDER_HEIGHT);

    // DRAW MENU
    m_Menu.Draw(*m_Renderer);

    // DEBUG

    // DEBUG

    // second pass
    m_ScreenFBO->Unbind();
    m_Renderer->ClearBufferColourStencil();

    glStencilFunc(GL_ALWAYS, 0, 0xff);
    m_Renderer->ChangeViewport(Globals::WINDOW_WIDTH, Globals::WINDOW_HEIGHT);

    glActiveTexture(GL_TEXTURE0);
    m_ScreenFBO->BindTexture();
    m_Renderer->DrawStrip(*m_ScreenVAO, *m_ScreenShader);


}
