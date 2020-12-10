#pragma once
#include "Renderer.h"
#include "../Buffers/VertexArray.h"

constexpr std::size_t RENDERER_MAX_SPRITES = 42500;
constexpr std::size_t RENDERER_VERTEX_SIZE = sizeof(Vertex);
constexpr std::size_t RENDERER_SPRITE_SIZE = RENDERER_VERTEX_SIZE * 4;
constexpr std::size_t RENDERER_BUFFER_SIZE = RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES;
constexpr std::size_t RENDERER_INDICES_SIZE = RENDERER_MAX_SPRITES * 6;

typedef std::unique_ptr<VertexArray> uPtrVAO;
typedef std::unique_ptr<IndexBuffer> uPtrIBO;

class BatchRenderer2D : public Renderer2D
{
private:
	uPtrVAO m_VAO;
	sPtrVBO m_VBO;
	uPtrIBO m_IBO;
	GLsizei m_IndexCount;
	Vertex* m_Buffer;

	std::vector<unsigned int> m_TextureSlots;

public:
	BatchRenderer2D();
	~BatchRenderer2D();

	void Begin() override;
	void Submit(const ECS::PtrSprite component) override;
	void Submit(const ECS::PtrLabel component) override;
	void End() override;
	void Flush() override;
};
