#include "BatchRenderer.h"
#include "../../ECS/StandardComponents.h"
#include "../../Singletons/FontCache.h"
#include "../../Singletons/TextureCache.h"

BatchRenderer2D::BatchRenderer2D()
	: Renderer2D(),
	m_Buffer(NULL), m_IndexCount(0), 
	m_VAO(std::make_unique<VertexArray>()), 
	m_VBO(std::make_shared<VertexBuffer>(RENDERER_BUFFER_SIZE))
{
	BufferLayout layout;
	layout.Push<RXOposition>(1);	// vec4 Pos, 4th element = 1
	layout.Push<RXOcolor>(1);		// vec4 Color
	layout.Push<RXOtexCoords>(1);	// Texture
	layout.Push<float>(1);			// Texture ID
	layout.Push<float>(1);			// IsText

	m_VAO->AddBuffer(m_VBO, layout);

	unsigned int indeces[RENDERER_INDICES_SIZE];
	unsigned int offset = 0;
	for (size_t i = 0; i < RENDERER_INDICES_SIZE; i += 6)
	{
		indeces[i + 0] = 0 + offset;
		indeces[i + 1] = 1 + offset;
		indeces[i + 2] = 2 + offset;

		indeces[i + 3] = 2 + offset;
		indeces[i + 4] = 3 + offset;
		indeces[i + 5] = 0 + offset;

		offset += 4;
	}
	m_IBO = std::make_unique<IndexBuffer>(indeces, RENDERER_INDICES_SIZE);
}

BatchRenderer2D::~BatchRenderer2D()
{

}

void BatchRenderer2D::Begin()
{
	m_VBO->Bind();
	m_Buffer = (Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
}

void BatchRenderer2D::Submit(const ECS::PtrSprite component)
{
	const auto& entity		= component->Entity();
	const auto& transform	= entity->GetComponent<ECS::Transform>();
	const auto& sprite		= entity->GetComponent<ECS::Sprite>();

	const auto& position	= transform->GetPosition();
	const auto& size		= transform->GetSize();

	const auto& color		= sprite->GetColor();
	const auto& texCoords	= sprite->GetCoords();
	const auto& texID		= sprite->GetTexture()->ID();
	const bool& isText		= false;
	float texSlot = 0.f;
	bool found = false;
	if (sprite->GetTexture())
	{
		for (int i = 0; i < m_TextureSlots.size(); i++)
		{
			if (m_TextureSlots[i] == texID)
			{
				texSlot = (float)(i + 1);
				found = true;
				break;
			}
		}

		if (!found)
		{
			if (m_TextureSlots.size() >= 32)
			{
				End();
				Flush();
				Begin();
			}
			m_TextureSlots.push_back(texID);
			texSlot = (float)(m_TextureSlots.size());// -1);
		}
	}
	m_Buffer->Position = *m_TransformationStackBack * position;
	m_Buffer->Color = color;
	m_Buffer->TexCoords = texCoords.bl;
	m_Buffer->TexIndex = texSlot;
	m_Buffer->IsText = isText;
	m_Buffer++;

	m_Buffer->Position = *m_TransformationStackBack * glm::vec4(position.x + size.x, position.y, position.z, 1);
	m_Buffer->Color = color;
	m_Buffer->TexCoords = texCoords.br;
	m_Buffer->TexIndex = texSlot;
	m_Buffer->IsText = isText;
	m_Buffer++;

	m_Buffer->Position = *m_TransformationStackBack * glm::vec4(position.x + size.x, position.y + size.y, position.z, 1);
	m_Buffer->Color = color;
	m_Buffer->TexCoords = texCoords.tr;
	m_Buffer->TexIndex = texSlot;
	m_Buffer->IsText = isText;
	m_Buffer++;

	m_Buffer->Position = *m_TransformationStackBack * glm::vec4(position.x, position.y + size.y, position.z, 1);
	m_Buffer->Color = color;
	m_Buffer->TexCoords = texCoords.tl;
	m_Buffer->TexIndex = texSlot;
	m_Buffer->IsText = isText;
	m_Buffer++;

	m_IndexCount += 6;
	return;
}

void BatchRenderer2D::Submit(const ECS::PtrLabel component)
{
	const auto& entity		= component->Entity();
	const auto& transform	= entity->GetComponent<ECS::Transform>();

	const auto& position	= transform->GetPosition();
	const auto& size		= transform->GetSize();

	const auto& color	= component->GetColor();
	const auto& text	= component->GetText();

	float x_Offset = transform->GetPosition().x;
	const auto& font = Singletons::FontCache::Instance()->GetFont(component->GetFontName());

	for (const char& c : text)
	{
		//const constants::rxoPosition&	position	= transform.GetPosition();
		const RXOcolor& color = component->GetColor();
		const Character& ch = font->GetChar(c);
		const unsigned int& texID = ch.TextureID;
		const float& scale = component->GetScale();
		const bool& isText = true;

		float xpos = x_Offset + ch.Bearing.x * scale;
		float ypos = position.y - (ch.Size.y - ch.Bearing.y) * scale;
		float w = ch.Size.x * scale;
		float h = ch.Size.y * scale;

		float texSlot = 0.f;
		bool found = false;
		for (int i = 0; i < m_TextureSlots.size(); i++)
		{
			if (m_TextureSlots[i] == texID)
			{
				texSlot = (float)(i + 1);
				found = true;
				break;
			}
		}

		if (!found)
		{
			if (m_TextureSlots.size() >= 32)
			{
				End();
				Flush();
				Begin();
			}
			m_TextureSlots.push_back(texID);
			texSlot = (float)(m_TextureSlots.size());// -1);
		}

		m_Buffer->Position = *m_TransformationStackBack * RXOposition(xpos, ypos, 0, 1);
		m_Buffer->Color = color;
		m_Buffer->TexCoords = glm::vec2(0.0f, 1.0f);
		m_Buffer->TexIndex = texSlot;
		m_Buffer->IsText = isText;
		m_Buffer++;

		m_Buffer->Position = *m_TransformationStackBack * RXOposition(xpos + w, ypos, 0, 1);
		m_Buffer->Color = color;
		m_Buffer->TexCoords = glm::vec2(1.0f, 1.0f);
		m_Buffer->TexIndex = texSlot;
		m_Buffer->IsText = isText;
		m_Buffer++;

		m_Buffer->Position = *m_TransformationStackBack * RXOposition(xpos + w, ypos + h, 0, 1);
		m_Buffer->Color = color;
		m_Buffer->TexCoords = glm::vec2(1.0f, 0.0f);
		m_Buffer->TexIndex = texSlot;
		m_Buffer->IsText = isText;
		m_Buffer++;

		m_Buffer->Position = *m_TransformationStackBack * RXOposition(xpos, ypos + h, 0, 1);
		m_Buffer->Color = color;
		m_Buffer->TexCoords = glm::vec2(0.0f, 0.0f);
		m_Buffer->TexIndex = texSlot;
		m_Buffer->IsText = isText;
		m_Buffer++;

		m_IndexCount += 6;
		x_Offset += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
	}
}

void BatchRenderer2D::Submit(const ECS::PtrCollidableComponent component)
{
	glVertex2f(10, 10);
	glVertex2f(20, 20);
}

void BatchRenderer2D::End()
{
	glUnmapBuffer(GL_ARRAY_BUFFER);
	m_VBO->Unbind();
}

void BatchRenderer2D::Flush()
{
	for (int i = 0; i < m_TextureSlots.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, m_TextureSlots[i]);
		//GLCall(glBindTextureUnit(i, m_TextureSlots[i]));
	}
	m_VAO->Bind();
	m_IBO->Bind();
	glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, nullptr);
	m_IBO->Unbind();
	m_VAO->Unbind();
	m_TextureSlots.clear(); // An O(n) operation in this case.
	m_IndexCount = 0;
}