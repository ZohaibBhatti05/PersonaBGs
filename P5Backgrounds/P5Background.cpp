#include "P5Background.h"

P5Background::P5Background()
	: m_BackgroundState(BackgroundState::NORMAL)
{
	// set up star stuff

	m_StarShader = std::make_unique<Shader>("Shaders/Background/StarShader");
	m_StarVAO = std::make_unique<VertexArray>();
	m_StarEBO = std::make_unique<IndexBuffer>(starIndices, 24 * sizeof(unsigned int));
	VertexBufferLayout starVBOLayout;
	starVBOLayout.Push<float>(2);
	m_StarVAO->AddBuffer(starVBOLayout, starVertices, 20 * sizeof(float), false);

	// square stuff

	m_SquareShader = std::make_unique<Shader>("Shaders/Background/SquareShader");
	m_SquareVAO = std::make_unique<VertexArray>();
	VertexBufferLayout squareVBOLayout;
	squareVBOLayout.Push<float>(2);
	squareVBOLayout.Push<float>(2);
    m_SquareVAO->AddBuffer(squareVBOLayout, squareVertices, 48 * sizeof(float), false);

	// LOAD TEXTURES

    m_SquareBGTexture = std::make_unique<Texture2D>("Textures/Background/MaskOutline.png", 2);
}


void P5Background::Draw(const Renderer& renderer, const float& currentTime)
{

    // STAR background
    if (m_BackgroundState != BackgroundState::REQUEST)
    {
        bool persona = (m_BackgroundState == BackgroundState::PERSONA);

        m_StarVAO->Bind();
        m_StarEBO->Bind();
        m_StarShader->Bind();

        int j = 0;
        for (const Star& i : bgStars)
        {
            DrawStars(currentTime, i, persona, j);
            j++;
            if (j % 18 == 0) {
                renderer.DrawElementsInstanced(24, 11 * j);
                j = 0;
            }
        }

        renderer.DrawElementsInstanced(24, 11 * j);
    }
    else // REQUEST bg
    {
        // draw forward

        glStencilFunc(GL_ALWAYS, 0, 0xff);
        m_SquareVAO->Bind();
        m_SquareShader->Bind();
        DrawSquares(true, currentTime);
        renderer.DrawArraysInstanced(4, 38);

        // draw mask

        m_SquareBGTexture->Bind();
        glStencilFunc(GL_ALWAYS, 1, 0xff);
        renderer.DrawTexture(2, 4);

        // draw reverse

        glStencilFunc(GL_EQUAL, 1, 0xff);
        m_SquareShader->Bind();
        DrawSquares(false, currentTime);
        renderer.DrawArraysInstanced(4, 38);

        // draw mask outline

        glStencilFunc(GL_ALWAYS, 0, 0xff);
        renderer.DrawTexture(2, 8);
    }
}

// draws a single set of stars given some stuff
void P5Background::DrawStars(const float& bgTimer, const Star& star, const bool& persona, const unsigned int& j)
{
    float scale{ star.scale };

    float t{ float(fmod((bgTimer * 0.7f) + star.offset, 2)) };
    if (star.reversed) {
        t = 2 - t;
    }

    glm::mat4 sview{ glm::translate(glm::mat4(1.0), glm::vec3(star.position, 0.0)) };

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
            m_StarShader->SetVec3(("colours[" + std::to_string(11 - i + (11 * j)) + "]"), Globals::LGRAY_COLOUR);
        }
        else {
            if (star.bw) {
                m_StarShader->SetVec3(("colours[" + std::to_string(11 - i + (11 * j)) + "]"), Globals::BLACK_COLOUR);
            }
            else {
                m_StarShader->SetVec3(("colours[" + std::to_string(11 - i + (11 * j)) + "]"), Globals::DGRAY_COLOUR);
            }
        }

        // CREATE MATRICES
        glm::mat4 model{ glm::mat4(1.0) };

        model = glm::scale(model, glm::vec3(x, x, 1.0));
        model = glm::scale(model, glm::vec3(star.scale, scale, 1.0));
        if (persona)
        {
            float r{ -0.45f * log(x / 4.5f) };
            model = glm::rotate(model, r, glm::vec3(0.0, 0.0, 1.0));
        }
        model = glm::rotate(model, star.rotation, glm::vec3(0.0, 0.0, 1.0));

        glm::mat4 transformation{ Globals::Ortho * sview * model };
        m_StarShader->SetMat4(("transformations[" + std::to_string(11 - i + (11 * j)) + "]"), transformation);
    }
}

// draws the squares in the bg of the request menu
void P5Background::DrawSquares(const bool& reverse, const float& bgTimer)
{
    float t{ float(fmod((bgTimer * 0.3f), 2)) };

    if (!reverse) { t = 2 - t; }

    for (int i = 0; i < 38; i++) {
        float index = 35 - i + t;
        if (index < 0) {
            index = 0;
        }

        glm::mat4 model{ glm::scale(Globals::Identity, glm::vec3(pow(1.9, index * 0.2))) };

        model = glm::rotate(model,
            1 + (index * 0.13f), glm::vec3(0.0, 0.0, 1.0));

        m_SquareShader->SetMat4(("transformations[" + std::to_string(i) + "]"), Globals::Ortho * squareTranslation * model);
        m_SquareShader->SetVec3(("colours[" + std::to_string(i) + "]"), (i % 2 == 0) ? Globals::WHITE_COLOUR : Globals::BLACK_COLOUR);
    }
    m_SquareShader->SetVec3(("colours[37]"), Globals::RED_COLOUR);
}

void P5Background::SetBackgroundState(const int& state)
{
    switch (state)
    {
    case 0:
        m_BackgroundState = BackgroundState::NORMAL;
        break;
    case 1:
        m_BackgroundState = BackgroundState::PERSONA;
        break;
    case 2:
        m_BackgroundState = BackgroundState::REQUEST;
        break;
    }
}