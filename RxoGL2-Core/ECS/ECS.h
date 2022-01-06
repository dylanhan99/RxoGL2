#pragma once
#include <functional>

#include "../Constants.h"
#include "../MonoBehaviour.h"

namespace ECS
{
	inline ComponentID GetComponentID()
	{
		static ComponentID lastID = 0;
		return lastID++;
	}
	template <typename T> 
	inline ComponentID GetComponentTypeID() noexcept
	{
		static ComponentID typeID = GetComponentID();
		return typeID;
	}
	
	class Entity : public MonoBehaviour
	{
	private:
		friend class EntityList;

		inline EntityID NewEntityID()
		{ static EntityID lastID = 0; return lastID++; }

		EntityID	m_EntID = NewEntityID();
		std::string m_Name;
		std::string m_Tag;
		sPtrEntity m_sPtrThis;
		mutable sPtrLayer	m_Layer;
		std::vector<sPtrComponent> m_Components;
		ComponentArray	 m_ComponentArray;
		ComponentBitSet	 m_ComponentBitSet;

		//Singletons::EventDispatcher m_LocalEventDispatcher;
		// Flags
		bool m_Active;
		bool m_CollisionEnter;
		bool m_CollisionStay;
		bool m_CollisionExit;

	public:
		Entity(std::string name = "");
		void OnAwake() override;
		void OnStart() override;
		void OnStop() override;
		void OnUpdate(float deltatime) override;
		void OnDraw() override;

		void OnCollisionEnter(sPtrCollidableComponent component) override;
		void OnCollisionStay(sPtrCollidableComponent component) override;
		void OnCollisionExit(sPtrCollidableComponent component) override;
		
		template <typename T>
		bool HasComponent() const
		{ return m_ComponentBitSet[GetComponentTypeID<T>()]; }

		template <typename T, typename... TArgs>
		std::shared_ptr<T> AddComponent(TArgs&&... mArgs)//std::shared_ptr<Component> AddComponent(TArgs&&... mArgs)
		{
			T* c(new T(std::forward<TArgs>(mArgs)...));
			std::shared_ptr<T> sPtr{ c };
			sPtr->m_Entity = m_sPtrThis;
			sPtr->m_sPtrThis = sPtr;

			m_ComponentArray[GetComponentTypeID<T>()] = sPtr;
			m_ComponentBitSet[GetComponentTypeID<T>()] = true;
			//m_Collidables.emplace_back(sPtr);

			//sPtr->OnAwake(); // Removed this line because entity calls all OnAwake in its on OnAwake
			//m_Components.emplace_back(std::move(sPtr)); pls use this in future
			m_Components.push_back(sPtr);
			return sPtr;
		}

		// Getters/Setters
		inline const	EntityID& ID()			const	{ return m_EntID; }
		inline const	std::string	Name()		const	{ return m_Name; }
		inline const	bool Active()			const	{ return m_Active; }
		inline			void Active(bool state)			{ m_Active = state; }
		inline const	std::string Tag()		const	{ return m_Tag; }
		inline			void Tag(std::string tag)		{ m_Tag = tag; }
		inline			sPtrLayer Layer()		const	{ return m_Layer; }
		inline			void SetLayer(sPtrLayer layer)			{ m_Layer = layer; }

		template <typename T>
		std::shared_ptr<T> GetComponent() const
		{
			//auto ptr(m_Components[GetComponentTypeID<T>()]);
			//return *static_cast<T*>(ptr);
			//auto sPtr = m_Components[GetComponentTypeID<T>()];
			//return sPtr;
			return std::static_pointer_cast<T>(m_ComponentArray[GetComponentTypeID<T>()]);
		}
	};

	class Component : public MonoBehaviour
	{
	private:
		friend class Entity;
	protected:
		sPtrEntity m_Entity; // Reference to the entity it is attached to
		std::shared_ptr<Component> m_sPtrThis;
	public:
		virtual ~Component() {}
		//void OnAwake() override {}
		//void OnStart() override {}
		//void OnStop() override {}
		//void OnUpdate(float deltatime) override {}
		//void OnDraw() override {}

		// Getters/Setters
		inline const sPtrEntity Entity() const { return m_Entity; }
	};

	class EntityList : public MonoBehaviour
	{
	private:
		std::vector<sPtrEntity> m_Entities;
		std::unordered_map<std::string, std::vector<sPtrEntity>> m_Entities_Tags;
	public:
		~EntityList() {}
		void OnAwake() override;
		void OnStart() override;
		void OnStop() override;
		void OnUpdate(float deltatime) override;
		void OnDraw() override;
		sPtrEntity AddEntity(Entity& e);
		void Refresh();

		// Getters/Setters
		inline sPtrEntity GetEntity(std::string name) 
		{ 
			for (auto e : m_Entities) 
				if (e->Name() == name) 
					return e;
			return NULL;
		}
		inline std::vector<std::shared_ptr<ECS::Entity>> GetEntitiesTag(std::string tag) { return m_Entities_Tags[tag]; }
	};

	class RenderableComponent : public Component
	{
	};

	class CollidableComponent : public Component
	{
	protected:
		struct RB
		{
			// If IsKinematic is True, the Entity WILL NOT
			// be affected by Engine physics.
			// Rather, the transform will be affected by scripts/animation instead.
			bool m_IsKinematic;
			float m_Mass, m_Roatation, m_Velocity;
		};
	public:
		static enum class pType
		{ Static, Kinematic, Dynamic };
	protected:
		pType m_PhysicsType;
		RXOposition* m_Position;
		bool m_IsColliding;
		virtual void AddToPhysicsManager() = 0;
	public:
		CollidableComponent(RXOposition* position);
		/* Get the vector projection (range of the dot product in float) 
		  of this component by parsing an edge in. */
		virtual std::pair<float, float> Project(glm::vec3 plane) = 0;
		virtual bool CheckCollision(sPtrCollidableComponent other) { return false; }
		virtual void DrawOutline() = 0;

		void OnDraw() override;
		void OnCollisionEnter(sPtrCollidableComponent component) override{}
		void OnCollisionStay(sPtrCollidableComponent component)  override{}
		void OnCollisionExit(sPtrCollidableComponent component)  override{}

		// Getters/Setters
		inline const pType&			GetPType() const { return m_PhysicsType; }
		inline		 void			SetPType(pType type) { m_PhysicsType = type; }
		inline		 RXOposition&	GetPosition() { return *m_Position; }
		inline const bool& IsColliding() const { return m_IsColliding; }
		inline		 void  IsColliding(bool colliding) { m_IsColliding = colliding; }
	};
}