#pragma once
#include "../../Constants.h"
#include <vector>
//#include <typeinfo>

struct BufferElement
{
	//constants::Type type; // This doubles both as type name and size of type
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:			return 4;
		case GL_UNSIGNED_INT:	return 4;
		case GL_UNSIGNED_BYTE:	return 1;
		}
		ASSERT(false);
		return 0;
	}
};

class BufferLayout
{
private:
	std::vector<BufferElement> m_Elements;
	unsigned int m_Stride;
public:
	BufferLayout()
		: m_Stride(0) {}
	inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }

	template<typename T>
	void Push(unsigned int count)
	{ static_assert(false); }

	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += count * BufferElement::GetSizeOfType(GL_FLOAT);
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += count * BufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void Push<glm::vec2>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT, (unsigned int)glm::vec2::length(), GL_TRUE });
		m_Stride += count * sizeof(glm::vec2);
	}

	template<>
	void Push<glm::vec3>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT, (unsigned int)glm::vec3::length(), GL_TRUE });
		m_Stride += count * sizeof(glm::vec3);
	}

	template<>
	void Push<glm::vec4>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT, (unsigned int)glm::vec4::length(), GL_TRUE });
		m_Stride += count * sizeof(glm::vec4);
	}
};

class VertexBuffer
{
private:
	RXOrendererID m_RendererID;
public:
	VertexBuffer(unsigned int size);
	//VertexBuffer(const void* data, unsigned int size);
	//VertexBuffer();
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	//void SetData(const void* data, unsigned int size);
};

class IndexBuffer
{
private:
	RXOrendererID m_RendererID;
	unsigned int m_Count;
public:
	IndexBuffer() {}
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_Count; }

};