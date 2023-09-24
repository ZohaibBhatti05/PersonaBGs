#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "P5Menu.h"

#include <iostream>

#include "VertexArray.h"
#include "FrameBuffer.h"
#include "RenderBuffer.h"

#include "GlobalSettings.h"
#include "Texture2D.h"


class Program
{
private:

    GLFWwindow* window;

    P5Menu m_Menu;
    std::unique_ptr<Renderer> m_Renderer;

    std::unique_ptr<VertexArray> m_ScreenVAO;
    std::unique_ptr<Shader> m_ScreenShader;

    std::unique_ptr<FrameBuffer> m_ScreenFBO;
    std::unique_ptr<RenderBuffer> m_ScreenRBO;

    const float screenVertices[16] = {
        -1.0f, 1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 0.0f,

        //-0.5f, 0.5f, 0.0f, 1.0f,
        //-0.5f, -0.5f, 0.0f, 0.0f,
        //0.5f, 0.5f, 1.0f, 1.0f,
        //0.5f, -0.5f, 1.0f, 0.0f,
    };

    const float debugVertices[16] = {
        -0.5f, 0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, 1.0f, 0.0f,
    };

public:

    Program()
        : window(0) {}
    ~Program() {}

	void Run();

    void ConfigGlfw() const;

    void ConfigGL() const;

	void Init();

	void Update(const float& currentTime);

	void Draw();


private:

    static void debug_message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const* message, void const* user_param)
    {
        auto const src_str = [source]() {
            switch (source)
            {
            case GL_DEBUG_SOURCE_API: return "API";
            case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return "WINDOW SYSTEM";
            case GL_DEBUG_SOURCE_SHADER_COMPILER: return "SHADER COMPILER";
            case GL_DEBUG_SOURCE_THIRD_PARTY: return "THIRD PARTY";
            case GL_DEBUG_SOURCE_APPLICATION: return "APPLICATION";
            case GL_DEBUG_SOURCE_OTHER: return "OTHER";
            default: return "";
            }
        }();

        auto const type_str = [type]() {
            switch (type)
            {
            case GL_DEBUG_TYPE_ERROR: return "ERROR";
            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "DEPRECATED_BEHAVIOR";
            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "UNDEFINED_BEHAVIOR";
            case GL_DEBUG_TYPE_PORTABILITY: return "PORTABILITY";
            case GL_DEBUG_TYPE_PERFORMANCE: return "PERFORMANCE";
            case GL_DEBUG_TYPE_MARKER: return "MARKER";
            case GL_DEBUG_TYPE_OTHER: return "OTHER";
            default: return "";
            }
        }();

        auto const severity_str = [severity]() {
            switch (severity) {
            case GL_DEBUG_SEVERITY_NOTIFICATION: return "NOTIFICATION";
            case GL_DEBUG_SEVERITY_LOW: return "LOW";
            case GL_DEBUG_SEVERITY_MEDIUM: return "MEDIUM";
            case GL_DEBUG_SEVERITY_HIGH: return "HIGH";
            default: return "";
            }
        }();
        std::cout << src_str << ", " << type_str << ", " << severity_str << ", " << id << ": " << message << '\n';
    }
};