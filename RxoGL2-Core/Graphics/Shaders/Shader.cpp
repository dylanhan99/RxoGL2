#include "Shader.h"
#include <iostream>
#include "../../Utils/Utilities.h"

Shader::Shader(const std::string& vertPath, const std::string& fragPath)
	: m_VertPath(vertPath), m_FragPath(fragPath), m_RendererID(0)
{
	m_RendererID = CreateShader(vertPath, fragPath);
}

Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
}

RXOrendererID Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	RXOrendererID program = glCreateProgram();
	RXOrendererID vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	RXOrendererID fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
	glAttachShader(program, vs); glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);
	glDeleteShader(vs); glDeleteShader(fs);
	return program;
}

RXOrendererID Shader::CompileShader(unsigned int type, const std::string& source)
{
	RXOrendererID id = glCreateShader(type);
	std::string sourceStr = Utilities::ReadFile(source.c_str());
	const char* src = sourceStr.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		// Failed compilation
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		// Keeping message defined on the stack
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile " <<
			(type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << " shader!" << std::endl;
		std::cout << message << std::endl;

		glDeleteShader(id);
		return 0;
	}
	return id;
}

void Shader::Bind() const
{ glUseProgram(m_RendererID); }
void Shader::Unbind() const
{ glUseProgram(0); }

void Shader::SetUniform1i(const std::string& name, int v)
{ glUniform1i(GetUniformLocation(name), v); }
void Shader::SetUniform1iv(const std::string& name, int count, int* v)
{ glUniform1iv(GetUniformLocation(name), count, v); }
void Shader::SetUniform1f(const std::string& name, float v)
{ glUniform1f(GetUniformLocation(name), v); }
void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
{ glUniform3f(GetUniformLocation(name), v0, v1, v2);  }
void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{ glUniform4f(GetUniformLocation(name), v0, v1, v2, v3); }
void Shader::SetUniformMat4f(const std::string& name, glm::mat4& matrix)
{ glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]); }

int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];
	int location = glGetUniformLocation(m_RendererID, name.c_str());
	if (location == -1)
		std::cout << "Warning: uniform '" << name << "' does not exist!" << std::endl;
	m_UniformLocationCache[name] = location;
	return location;
}