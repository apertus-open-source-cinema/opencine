#ifndef EVENTPPADAPTER_H
#define EVENTPPADAPTER_H

#include <iostream>
#include <functional>
#include <memory>
#include <unordered_map>

#include "OCEvent.h"
#include <winerror.h>

class StartDriveTransferEvent : public OCEvent
{
	std::string _testMemeber = "123";

private:
	void DummyMethod() override
	{
	}
};

// E: event, C: receiver class
class OCEventBus
{
	//typedef void(*FuncDef)(const OCEvent &);
	typedef std::function<void(const OCEvent&)> FuncDef;
	
	std::unordered_map<size_t, std::vector<int>*> eventMap;
	std::vector<FuncDef> handlerList;

	// Private for now as events should be registered automatically (if not already done) on handler registration, just for simplicity
	template <typename E>
	std::vector<int>* RegisterEvent()
	{
		std::string name = typeid(E).name();
		std::size_t hash = std::hash<std::string>()(name);

		std::vector<int>* eventHandlers = new std::vector<int>();
		eventMap.insert(std::make_pair(hash, eventHandlers));

		return eventHandlers;
	}

	template <typename E>
	bool FindEvent(std::vector<int>& handlers)
	{
		bool eventFound = false;
		std::string name = typeid(E).name();
		std::size_t hash = std::hash<std::string>()(name);
		std::unordered_map<size_t, std::vector<int>*>::const_iterator it = eventMap.find(hash);

		// TODO: Improve error handling
		if (it != eventMap.end())
		{
			handlers = *(*it).second;
			eventFound = true;
		}

		return eventFound;
	}

public:
	OCEventBus()
	{
	}

	std::function<void(const OCEventBase&)> _testFunc = nullptr;
	void* funcPtr = nullptr;

	template <typename E, typename F>
	void AddEventHandler(F func)
	{
	}


	// TODO: Implementation
	void RemoveEventHandler()
	{
	}

	template <typename E>
	void FireEvent(E& event)
	{
		std::vector<int> eventHandlers;
		bool eventFound = FindEvent<E>(eventHandlers);

		if(!eventFound)
		{
			return;
		}

		for(int handlerIndex : eventHandlers)
		{
			handlerList.at(handlerIndex)(event);
		}
	}

	template <typename E, typename C>
	void RegisterEventHandler(FuncDef&& event)
	{
		// Look up if event already exists, oterwise register it
		std::vector<int>* eventHandlers = nullptr;
		bool eventFound = FindEvent<E>(*eventHandlers);

		if(!eventFound)
		{
			eventHandlers = RegisterEvent<E>();
		}

		handlerList.push_back(event);
		eventHandlers->push_back(handlerList.size() - 1);
	}
};

#endif //EVENTPPADAPTER_H
