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
		Entity(std::string tag = "") : m_Tag(tag) {}
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
		inline std::vector<std::shared_ptr<ECS::Entity>> GetEntitiesTag(std::string tag) { return m_Entities_Tags[tag]; }
	};

	class RenderableComponent : public Component
	{

	};

	class CollidableComponent : public Component
	{
	protected:
		RXOposition* m_Position;
		bool m_IsColliding;
		virtual void AddToPhysicsManager() = 0;
	public:
		CollidableComponent(RXOposition* position);
		/* Get the vector projection (range of the dot product in float) 
		  of this component by parsing an edge in. */
		virtual std::pair<float, float> Project(glm::vec3 plane) = 0;
		virtual bool CheckCollision(sPtrCollidableComponent other) { return false; }

		void OnCollisionEnter(sPtrCollidableComponent component) override{}
		void OnCollisionStay(sPtrCollidableComponent component)  override{}
		void OnCollisionExit(sPtrCollidableComponent component)  override{}

		// Getters/Setters
		inline		 RXOposition& GetPosition() { return *m_Position; }
		inline const bool& IsColliding() const { return m_IsColliding; }
		inline		 void  IsColliding(bool colliding) { m_IsColliding = colliding; }
	};

	// T meaning Script Type
	//template <typename T, typename... TArgs>
	class NativeScriptComponent : public Component
	{
	public:
		NativeScript* Instance = nullptr;

		// InstantiateFunction & DestroyInstanceFunction are belonging to NativeScriptComponent.
		std::function<void()> InstantiateFunction;
		std::function<void()> DestroyInstanceFunction;

		// The rest are lambdas for the script
		//std::function<void()> OnPlayFunction;
		//std::function<void()> OnStopFunction;
		//std::function<void()> OnCreateFunction;
		//std::function<void()> OnDestroyFunction;
		//std::function<void(float)> OnUpdateFunction;

		//NativeScriptComponent(TArgs&&... mArgs)
		//{
		//	InstantiateFunction = [&]() {
		//		if (!m_Instance)
		//		{
		//			m_Instance = new T(std::forward<TArgs>(mArgs)...);
		//			((T*)m_Instance)->m_Entity = m_Entity;
		//		}
		//	};
		//	DestroyInstanceFunction = [&]() { delete (T*)m_Instance; m_Instance = nullptr; };
		//
		//	OnCreateFunction = [&]() { ((T*)m_Instance)->OnCreate(); };
		//	OnDestroyFunction = [&]() { ((T*)m_Instance)->OnDestroy(); };
		//	OnUpdateFunction = [&](float deltatime) { ((T*)m_Instance)->OnUpdate(deltatime); };
		//
		//	//NativeScriptManager::GetInstance()->AddScript(std::static_pointer_cast<NativeScriptComponent>(m_SptThis));
		//}

		template <typename T, typename... TArgs>
		T* Bind(TArgs&&... mArgs)
		{
			InstantiateFunction = [&]() {
				if (!Instance)
				{
					//Instance = std::make_shared<T>(new T(std::forward<TArgs>(mArgs)...));
					//Instance->m_Entity = m_Entity;
					Instance = new T(std::forward<TArgs>(mArgs)...);
					((T*)Instance)->m_Entity = m_Entity;
				}
			};
			DestroyInstanceFunction = [&]() { delete (T*)Instance; Instance = nullptr; };
			
			//OnPlayFunction		= [&]() { ((T*)Instance)->OnPlay(); };
			//OnStopFunction		= [&]() { ((T*)Instance)->OnStop(); };
			//OnCreateFunction	= [&]() { ((T*)Instance)->OnCreate(); };
			//OnDestroyFunction	= [&]() { ((T*)Instance)->OnDestroy(); };
			//OnUpdateFunction	= [&](float deltatime) { ((T*)Instance)->OnUpdate(deltatime); };
		
			//NativeScriptManager::GetInstance()->AddScript(std::static_pointer_cast<NativeScriptComponent>(m_SptThis));
			InstantiateFunction();
			m_Entity->Layer()->AddScript(std::static_pointer_cast<NativeScriptComponent>(m_sPtrThis));
			return static_cast<T*>(Instance);
		}

		// Getters/Setters
		//inline NativeScript* GetInstance() { return m_ScriptInstance; }
	};

	// To be a child of MonoBehaviour in the future.
	class NativeScript 
	{
	private:
		friend class NativeScriptComponent;
	protected:
		sPtrEntity m_Entity;
	public:
		virtual void OnAwake() {}
		virtual void OnStart() {}
		virtual void OnStop() {}
		virtual void OnUpdate(float deltatime) {}
		virtual void OnDestroy() {}
	};
}