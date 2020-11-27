#pragma once
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

namespace Event
{
	class IEvent
	{
	public:
		virtual const std::string& GetName() const = 0;
	};

	template <typename ..._args>
	class Event : public IEvent
	{
	public:
		using _callback = std::function<void(_args...)>;
	private:
		std::string m_Name;
		const _callback m_cbFunction;
	public:
		explicit Event(const std::string& name, const _callback& cb)
			: m_Name(name), m_cbFunction(cb) {}
		~Event() {}

		void Trigger(_args... a) { m_cbFunction(a...); }

		inline const std::string& GetName() const override { return m_Name; }
	};

	class EventDispatcher
	{
	private:
		//static EventDispatcher* m_Instance; // Singleton
		std::unordered_map<std::string, std::vector<IEvent*>> m_EventList;
	public:
		//EventDispatcher() {}
		~EventDispatcher()
		{
			for (auto el : m_EventList)
			{
				for (auto e : el.second)
					delete e;
			}
		}

		//static void DeleteInstance()
		//{
		//	if (m_Instance)
		//	{
		//		delete m_Instance;
		//		m_Instance = NULL;
		//	}
		//}

		void RegisterEvent(IEvent* event)
		{
			if (event)
				m_EventList[event->GetName()].push_back(event);
		}

		template<typename ..._args>
		void DispatchEvent(const std::string& eventName, _args... a)
		{
			auto el = m_EventList.find(eventName);
			if (el == m_EventList.end())
				return;
			for (auto e : el->second)
			{
				if (Event<_args...>* event = dynamic_cast<Event<_args...>*>(e))
					event->Trigger(a...);
			}
		}

		//static EventDispatcher* GetInstance()
		//{
		//	if (m_Instance == NULL)
		//		m_Instance = new EventDispatcher();
		//
		//	return m_Instance;
		//}
	};
}