#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <array>
#include <unordered_map>
#include <glm\matrix.hpp>
#include <glm\gtc\type_ptr.hpp>

struct ShaderPathList {
	const std::string shaderPath;
	const std::string vertexPath;
	const std::string fragmentPath;
};

class ShaderProgram {
private:
	const bool m_SingleFileShader;
	const ShaderPathList m_Paths;
	unsigned int m_ID;
	std::unordered_map<std::string, int> m_Uniforms;
	
	int getUniform(const char* name);
public:
	ShaderProgram(const char* shaderPath);
	ShaderProgram(const char* vertexPath, const char* fragmentPath);
	~ShaderProgram();

	void Bind();
	void Unbind();

	// Float Uniforms
	void setUniform1f(const char* name, float& val);
	void setUniform2f(const char* name, glm::vec2& vector);
	void setUniform3f(const char* name, glm::vec3& vector);
	void setUniform4f(const char* name, glm::vec4& vector);
	// Double Uniforms
	void setUniform1d(const char* name, double& val);
	void setUniform2d(const char* name, glm::dvec2& vec);
	void setUniform3d(const char* name, glm::dvec3& vec);
	void setUniform4d(const char* name, glm::dvec4& vec);
	// Integer Uniforms
	void setUniform1i(const char* name, int& val);
	void setUniform2i(const char* name, glm::ivec2& vec);
	void setUniform3i(const char* name, glm::ivec3& vec);
	void setUniform4i(const char* name, glm::ivec4& vec);
	// Unsigned Integer Uniforms
	void setUniform1u(const char* name, unsigned int& val);
	void setUniform2u(const char* name, glm::uvec2& val);
	void setUniform3u(const char* name, glm::uvec3& val);
	void setUniform4u(const char* name, glm::uvec4& val);
	// Square Matrix Uniforms
	void setUniformMat2(const char* name, glm::mat2& matrix);
	void setUniformMat3(const char* name, glm::mat3& matrix);
	void setUniformMat4(const char* name, glm::mat4& matrix);
};