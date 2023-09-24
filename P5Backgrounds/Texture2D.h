#pragma once

#include "Texture.h"
#include <glm/glm/glm.hpp>

class Texture2D : public Texture
{
private:

	void SetFilters() const;

public:

	Texture2D(const std::string& path, unsigned int unit);
	Texture2D(const glm::vec4& colour, unsigned int unit);
	Texture2D(const glm::vec3& colour, unsigned int unit) : Texture2D(glm::vec4(colour, 1.0), unit) { }
	Texture2D(const unsigned int& width, const unsigned int& height, unsigned int unit);
	~Texture2D() {};

	void Bind() const override;
	void Unbind() const override;

};