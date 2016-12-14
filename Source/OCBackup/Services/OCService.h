#ifndef OCSERVICE_H
#define OCSERVICE_H

// TODO: Refactor by moving to more suitable location and possibly renaming

class OCService
{
	OCEventBus* _eventBus;


public:
	OCService(OCEventBus* bus)
	{
		_eventBus = bus;
	}

	OCService() = delete;

	virtual ~OCService()
	{
	}

	OCEventBus* GetEventBus()
	{
		return _eventBus;
	}

	virtual bool Execute() = 0;
};

#endif //OCSERVICE_H
