#pragma once
#include <array>
#include <bitset>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

#define ASSERT(x) if (!(x)) __debugbreak();

// [Independent][Class Declaration]
class Application;
class BatchRenderer2D;
class Font;
class Group;
class Layer;
class Scene;
class SceneMenu;
class Shader;
class TextureData;
class VertexBuffer;
class Window;

namespace ECS
{
	class Component;
	class Entity;
	class EntityList;
	class Sprite;
	class Label;
}

namespace Singletons
{
	class TextureCache;
	class FontCache;
}

// [Independent][Typedefs][General][GLFW][GLEW][GLM]
typedef GLFWwindow RXOwindow;
typedef GLuint RXOrendererID;
typedef glm::vec4 RXOposition;
typedef glm::vec4 RXOcolor;
typedef glm::vec2 RXOtexCoords;
typedef glm::vec2 RXOsize;

// [General]
struct Vertex
{
	RXOposition		Position; // Vec4 because Homogeneous coordinates. The fourth element = 1
	RXOcolor		Color;
	RXOtexCoords	TexCoords;
	float			TexIndex;
	float			IsText;
};

struct Character {
	unsigned int TextureID;  // ID handle of the glyph texture
	glm::ivec2   Size;       // Size of glyph
	glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
	unsigned int Advance;    // Offset to advance to next glyph
};

// [Event Names]
constexpr char EVENT_NAME_OnPosChange[] = "OnPosChange";

// [Unique Pointers]

// [Shared Pointers]
typedef std::shared_ptr<Application> sPtrApplication;
typedef std::shared_ptr<BatchRenderer2D> sPtrBatchRenderer2D;
typedef std::shared_ptr<Font> sPtrFont;
typedef std::shared_ptr<Group> sPtrGroup;
typedef std::shared_ptr<Layer> sPtrLayer;
typedef std::shared_ptr<Scene> sPtrScene;
typedef std::shared_ptr<SceneMenu> sPtrSceneMenu;
typedef std::shared_ptr<Shader> sPtrShader;
typedef std::shared_ptr<TextureData> sPtrTextureData;
typedef std::shared_ptr<VertexBuffer> sPtrVBO;
typedef std::shared_ptr<Window> sPtrWindow;

namespace ECS
{
	typedef std::shared_ptr<Component>	sPtrComponent;
	typedef std::shared_ptr<Entity>		sPtrEntity;
	typedef std::shared_ptr<EntityList>	sPtrEntityList;
	typedef std::shared_ptr<Sprite>		sPtrSprite;
	typedef std::shared_ptr<Label>		sPtrLabel;
}

namespace Singletons
{
	typedef std::shared_ptr<TextureCache> sPtrTextureCache;
	typedef std::shared_ptr<FontCache> sPtrFontCache;
}

// [ECS]
namespace ECS
{
	constexpr std::size_t ENTITY_MAX_COMPONENTS = 32;
	typedef std::size_t	EntityID;
	typedef std::size_t	ComponentID;
	typedef std::bitset<ENTITY_MAX_COMPONENTS> ComponentBitSet;
	typedef std::array<std::shared_ptr<Component>, ENTITY_MAX_COMPONENTS> ComponentArray;
}