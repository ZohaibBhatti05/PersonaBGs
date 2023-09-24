#pragma once

#include "VertexArray.h"
#include "Shader.h"
#include "P5Background.h"

class P5Menu
{
private:

	float currentTime;
	std::unique_ptr<P5Background> m_Background;

public:

	P5Menu() : currentTime(0) {}

	void Init();

	void Update(const float& currentTime);

	void Draw(const Renderer& renderer);

	void SetBackgroundState(const int& state);
};