#pragma once
#include <unordered_map>
#include <vector>

#include "../Constants.h"
#include "../Event/Event.h"

namespace Singletons
{
	class EventDispatcher
	{
	private:
		static sPtrEventDispatcher m_Instance;
		std::unordered_map<std::string, std::vector<Event::IEvent*>> m_EventList;
	public:
		EventDispatcher();
		~EventDispatcher();

		static inline sPtrEventDispatcher Instance()
		{
			if (m_Instance == NULL)
				m_Instance = std::make_shared<EventDispatcher>();
			return m_Instance;
		}

		void RegisterEvent(Event::IEvent* event);

		template<typename ..._args>
		void DispatchEvent(const std::string& eventName, _args... a)
		{
			auto el = m_EventList.find(eventName);
			if (el == m_EventList.end())
				return;
			for (auto e : el->second)
			{
				if (Event::Event<_args...>* event = dynamic_cast<Event::Event<_args...>*>(e))
					event->Trigger(a...);
			}
		}
	};
}