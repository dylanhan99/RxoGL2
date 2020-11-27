#pragma once
#include <unordered_map>

#include "../../Constants.h"

class Shader
{
private:
	RXOrendererID m_RendererID;
	const std::string& m_VertPath;
	const std::string& m_FragPath;
	std::unordered_map <std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& vertPath, const std::string& fragPath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform1i(const std::string& name, int v);
	void SetUniform1iv(const std::string& name, int count, int* v);
	void SetUniform1f(const std::string& name, float v);
	void SetUniform3f(const std::string& name, float v0, float v1, float v2);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, glm::mat4& matrix);
private:
	RXOrendererID CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	RXOrendererID CompileShader(unsigned int type, const std::string& source);
	int GetUniformLocation(const std::string& name);
};