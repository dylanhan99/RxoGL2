#include "Buffer.h"

/////////////////////////////////////////////////////////////////////////////
// VertexBuffer /////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

// Dynamic batch rendering
VertexBuffer::VertexBuffer(unsigned int size)
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

// Static batch rendering
//VertexBuffer::VertexBuffer(const void* data, unsigned int size)
//{
//	glGenBuffers(1, &m_RendererID);
//	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
//	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
//}

//VertexBuffer::VertexBuffer()
//{
//	glGenBuffers(1, &m_RendererID);
//	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
//}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//void VertexBuffer::SetData(const void* data, unsigned int size)
//{
//	Bind();
//	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
//}

/////////////////////////////////////////////////////////////////////////////
// IndexBuffer //////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
	: m_Count(count)
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
