#pragma once
#include "Buffer.h"

class VertexArray
{
private:
	unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const sPtrVBO vb, const BufferLayout& layout);

	void Bind() const;
	void Unbind() const;
};