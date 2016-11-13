#ifndef EVENTPPADAPTER_H
#define EVENTPPADAPTER_H

#include <iostream>
#include <functional>
#include <memory>
#include <unordered_map>

#include "OCEvent.h"
#include "Task/ITask.h"

class RegisterNewTaskEvent : public OCEvent
{
	ITask* _task;

public:
	explicit RegisterNewTaskEvent(ITask* task)
		: _task(task)
	{
	}

	~RegisterNewTaskEvent() override 
	{
	}
};

class StartDriveTransferEvent : public OCEvent
{
	std::string _sourcePath;
	std::vector<std::string> _destinationPaths;

	std::string _testMember = "123";

	//	void DummyMethod() override
	//	{
	//	}

public:
	void SetSourcePath(const std::string sourcePath)
	{
		_sourcePath = sourcePath;
	}

	std::string GetSourcePath() const
	{
		return _sourcePath;
	}


	void SetDestinationsPaths(const std::vector<std::string> destinationsList)
	{
		_destinationPaths = destinationsList;
	}

	std::vector<std::string> GetDestinationPaths() const
	{
		return _destinationPaths;
	}
};

// TODO: Implement better error handling
// E: event, C: receiver class
class OCEventBus
{
	//typedef void(*FuncDef)(const OCEvent &);
	typedef std::function<void(const OCEvent&)> FuncDef;

	std::unordered_map<size_t, std::shared_ptr<std::vector<int>>> eventMap;
	std::vector<FuncDef> handlerList;

	// Private for now as events should be registered automatically (if not already done) on handler registration, just for simplicity
	template <typename E>
	std::vector<int>* RegisterEvent()
	{
		std::string name = typeid(E).name();
		std::size_t hash = std::hash<std::string>()(name);

		std::shared_ptr<std::vector<int>> eventHandlers = std::make_shared<std::vector<int>>();
		eventMap.insert(std::make_pair(hash, eventHandlers));

		return eventHandlers.get();
	}

	template <typename E>
	std::vector<int>* FindEvent()
	{
		std::vector<int>* handlers = nullptr;

		std::string name = typeid(E).name();
		std::size_t hash = std::hash<std::string>()(name);
		std::unordered_map<size_t, std::shared_ptr<std::vector<int>>>::const_iterator it = eventMap.find(hash);

		// TODO: Improve error handling
		if (it == eventMap.end())
		{
			//Not Found
		}
		else
		{
			handlers = (it->second).get();
		}

		return handlers;
	}

public:
	OCEventBus()
	{
	}

	// TODO: Implementation
	void RemoveEventHandler()
	{
	}

	template <typename E>
	void FireEvent(E& event)
	{
		std::vector<int>* eventHandlers = FindEvent<E>();

		if (eventHandlers == nullptr)
		{
			return;
		}

		for (int handlerIndex : *eventHandlers)
		{
			handlerList.at(handlerIndex)(event);
		}
	}

	template <typename E, typename C>
	void RegisterEventHandler(FuncDef&& event)
	{
		// Look up if event already exists, oterwise register it
		std::vector<int>* eventHandlers = FindEvent<E>();

		if (eventHandlers == nullptr)
		{
			eventHandlers = RegisterEvent<E>();
		}

		handlerList.push_back(event);
		eventHandlers->push_back(handlerList.size() - 1);
	}
};

#endif //EVENTPPADAPTER_H
