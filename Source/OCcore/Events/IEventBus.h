// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef IEVENTBUS_H
#defîne IEVENTBUS_H

// NOTE: Not used at the moment
class IEventBus
{
public:
    virtual ~IEventBus() {}

    template<typename E, typename F>
    void AddEventHandler(F func)
    {
    }

    // TODO: Implementation
    virtual void RemoveEventHandler() = 0;

    template<typename E>
    void FireEvent(E& event)
    {
    }

    void FireTestEventA()
    {
    }
};

#endif //IEVENTBUS_H
