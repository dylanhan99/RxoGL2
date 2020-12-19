#include "EventCache.h"

namespace Singletons {
	sPtrEventDispatcher EventDispatcher::m_Instance = NULL;

	EventDispatcher::EventDispatcher()
	{

	}

	EventDispatcher::~EventDispatcher()
	{
		for (auto el : m_EventList)
		{
			for (auto e : el.second)
				delete e;
		}
	}

	void EventDispatcher::RegisterEvent(Event::IEvent* event)
	{
		if (event)
			m_EventList[event->GetName()].push_back(event);
	}
}