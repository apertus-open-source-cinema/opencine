// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCBackup
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef OCSERVICE_H
#define OCSERVICE_H

// TODO: Refactor by moving to more suitable location and possibly renaming

class OCService : public QObject
{
	Q_OBJECT

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
