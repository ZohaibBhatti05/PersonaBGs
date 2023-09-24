#include "P5Menu.h"

void P5Menu::Init()
{ 
	m_Background = std::make_unique<P5Background>();
}

void P5Menu::Update(const float& currentTime)
{
	this->currentTime = currentTime;
}

void P5Menu::Draw(const Renderer& renderer)
{
	m_Background->Draw(renderer, currentTime);
}

void P5Menu::SetBackgroundState(const int& state)
{
	m_Background->SetBackgroundState(state);
}