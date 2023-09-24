#pragma once
#include "Renderer.h"

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>

#include <unordered_map>

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;

};

class Shader {
private:
	std::string m_FilePath;
	GLuint m_ShaderID;

	// caching for uniforms
	std::unordered_map<std::string, int> m_UniformLocationCache;

public:
	Shader(const std::string& filePath);
	~Shader();



	void Bind() const;
	void Unbind() const;


	// set uniforms
	void SetBool(const std::string& name, bool value)
	{
		glUniform1i(GetUniformLocation(name), (int)value);
	}
	void SetInt(const std::string& name, int value)
	{
		glUniform1i(GetUniformLocation(name), value);
	}
	void SetInt(const std::string& name, const unsigned int& length, int* value)
	{
		glUniform1iv(GetUniformLocation(name), length, value);
	}
	void SetFloat(const std::string& name, float value)
	{
		glUniform1f(GetUniformLocation(name), value);
	}
	void SetMat4(const std::string& name, glm::mat4 value)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
	}
	void SetMat4(const std::string& name, const unsigned int& length, const float* value)
	{
		glUniformMatrix4fv(GetUniformLocation(name), length, GL_FALSE, value);
	}
	void SetVec2(const std::string& name, glm::vec2 value)
	{
		glUniform2fv(GetUniformLocation(name), 1, glm::value_ptr(value));
	}
	void SetVec3(const std::string& name, glm::vec3 value)
	{
		glUniform3fv(GetUniformLocation(name.c_str()), 1, glm::value_ptr(value));
	}
	void SetVec4(const std::string& name, glm::vec4 value)
	{
		glUniform4fv(GetUniformLocation(name.c_str()), 1, glm::value_ptr(value));
	}

private:

	GLint GetUniformLocation(const std::string& name);

	void CheckCompileErrors(GLuint shader, std::string type);
};


