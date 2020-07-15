#include <glad\glad.h>
#include "ShaderManager.h"
#include "Config.h"
#include "FileLoader.h"

enum {
	INVALID = -2, NONE = -1, VERTEX_SOURCE = 0, FRAGMENT_SOURCE = 1
};

struct ShaderSourceCode {
	std::string vertSrc;
	std::string fragSrc;
};

unsigned int loadShader(const std::string& source, unsigned int type)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, NULL);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));

		glGetShaderInfoLog(id, length, &length, message);

		std::cout << "Error while compiling " << (type == GL_VERTEX_SHADER ? "Vertex Shader" : "Fragment Shader") << std::endl;
		std::cout << message << std::endl;

		glDeleteShader(id);
		return 0;
	}

	return id;
}
unsigned int createShader(ShaderSourceCode& sourceCode) {
	unsigned int program = glCreateProgram();
	unsigned int vs = loadShader(sourceCode.vertSrc, GL_VERTEX_SHADER);
	unsigned int fs = loadShader(sourceCode.fragSrc, GL_FRAGMENT_SHADER);

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}
/**
	Loads a shader from one file, the shaders must be separated by type using `$vert` and `$frag`
*/
ShaderSourceCode loadShaderFromOneFile(const char* shaderPath) {
	std::fstream shaderFile(shaderPath);
	std::array<std::stringstream, 2> shaderSource;
	std::string line;
	int type = NONE;

	if (shaderFile.is_open()) {
		while (std::getline(shaderFile, line)) {
			if (line.find(c().VERTEX_START_STRING)) {
				type = VERTEX_SOURCE;
			}
			else if (line.find(c().FRAGMENT_START_STRING)) {
				type = FRAGMENT_SOURCE;
			}
			else {
				if (type == INVALID) {
					std::cerr << "ERROR, INVALID SHADER STATE SELECTED" << std::endl;
				}
				else if (type != NONE) {
					shaderSource[type] << line << "\n";
				}
			}
		}
	}
	else {
		printf("SHADERMANAGER  ERROR: No file exists at path: %s", shaderPath);
	}

	shaderFile.close();
	return {
		shaderSource[0].str(), shaderSource[1].str()
	};
}

/**
	Loads a vertex and fragment shader from two separate files, the shaders are then read and the source code for both shaders is returned
*/
ShaderSourceCode loadShaderFromTwoFiles(const char* vertPath, const char* fragPath) {
	return {
		readFile(vertPath), readFile(fragPath)
	};
}


/**
	ShaderProgram Class
*/
ShaderProgram::ShaderProgram(const char* shaderPath)
	: m_SingleFileShader(true), m_Paths({shaderPath, "", "" }), m_Uniforms()
{
	ShaderSourceCode sourceCode = loadShaderFromOneFile(shaderPath);
	m_ID =  createShader(sourceCode);
}
ShaderProgram::ShaderProgram(const char* vertexPath, const char* fragmentPath)
	: m_SingleFileShader(false), m_Paths({ "", vertexPath, fragmentPath})
{
	ShaderSourceCode sourceCode = loadShaderFromTwoFiles(vertexPath, fragmentPath);
	m_ID = createShader(sourceCode);
}

ShaderProgram::~ShaderProgram() {
	glUseProgram(0);
	glDeleteProgram(m_ID);
}

int ShaderProgram::getUniform(const char* name) {
	if (int loc = m_Uniforms[name]) {
		return loc;
	}
	int loc = glGetUniformLocation(m_ID, name);
	m_Uniforms[name] = loc;
	return loc;
}

void ShaderProgram::Bind() {
	glUseProgram(m_ID);
}

void ShaderProgram::Unbind() {
	glUseProgram(0);
}

// Float Uniforms
void ShaderProgram::setUniform1f(const char* name, float& val) {
	glUniform1fv(getUniform(name), 1, &val);
}
void ShaderProgram::setUniform2f(const char* name, glm::vec2& vec) {
	glUniform2fv(getUniform(name), 2, glm::value_ptr(vec));
}
void ShaderProgram::setUniform3f(const char* name, glm::vec3& vec) {
	glUniform3fv(getUniform(name), 3, glm::value_ptr(vec));
}
void ShaderProgram::setUniform4f(const char* name, glm::vec4& vec) {
	glUniform4fv(getUniform(name), 4, glm::value_ptr(vec));
}
// Double Uniforms
void ShaderProgram::setUniform1d(const char* name, double& val) {
	glUniform1dv(getUniform(name), 1, &val);
}
void ShaderProgram::setUniform2d(const char* name, glm::dvec2& val) {
	glUniform2dv(getUniform(name), 2, glm::value_ptr(val));
}
void ShaderProgram::setUniform3d(const char* name, glm::dvec3& val) {
	glUniform3dv(getUniform(name), 2, glm::value_ptr(val));
}
void ShaderProgram::setUniform4d(const char* name, glm::dvec4& val) {
	glUniform4dv(getUniform(name), 2, glm::value_ptr(val));
}
// Integer Uniforms
void ShaderProgram::setUniform1i(const char* name, int& val) {
	glUniform1iv(getUniform(name), 1, &val);
}
void ShaderProgram::setUniform2i(const char* name, glm::ivec2& val) {
	glUniform2iv(getUniform(name), 3, glm::value_ptr(val));
}
void ShaderProgram::setUniform3i(const char* name, glm::ivec3& val) {
	glUniform3iv(getUniform(name), 3, glm::value_ptr(val));
}
void ShaderProgram::setUniform4i(const char* name, glm::ivec4& val) {
	glUniform4iv(getUniform(name), 4, glm::value_ptr(val));
}
// Unsigned Integer Uniforms
void ShaderProgram::setUniform1u(const char* name, unsigned int& val) {
	glUniform1uiv(getUniform(name), 1, &val);
}
void ShaderProgram::setUniform2u(const char* name, glm::uvec2& val) {
	glUniform2uiv(getUniform(name), 2, glm::value_ptr(val));
}
void ShaderProgram::setUniform3u(const char* name, glm::uvec3& val) {
	glUniform3uiv(getUniform(name), 3, glm::value_ptr(val));
}
void ShaderProgram::setUniform4u(const char* name, glm::uvec4& val) {
	glUniform4uiv(getUniform(name), 4, glm::value_ptr(val));
}
// Matrix Uniforms
void ShaderProgram::setUniformMat2(const char* name, glm::mat2& matrix) {
	glUniformMatrix2fv(getUniform(name), 1, GL_FALSE, glm::value_ptr(matrix));
}
void ShaderProgram::setUniformMat3(const char* name, glm::mat3& matrix) {
	glUniformMatrix3fv(getUniform(name), 1, GL_FALSE, glm::value_ptr(matrix));
}
void ShaderProgram::setUniformMat4(const char* name, glm::mat4& matrix) {
	glUniformMatrix4fv(getUniform(name), 1, GL_FALSE, glm::value_ptr(matrix));
}
