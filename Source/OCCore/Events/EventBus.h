#ifndef EVENTPPADAPTER_H
#define EVENTPPADAPTER_H

#include <iostream>
#include <functional>

#include "eventppImpl.h"

class OCEvent
{

};

class OCSignal
{

};

// Empty base implementation
class IEventBus
{
public:
    virtual void RegisterEvent(OCEvent event) {}

    template<typename E, typename... A>
    void FireEvent(A&&... args)
    {
        int i = 0;
    }
};

class eventppImpl : public IEventBus
{

};

class OCEventBus
{
    IEventBus* _busImpl;
    std::shared_ptr<TestListener> _listener;
    std::shared_ptr<TestListener2> _listener2;

public:
    OCEventBus()
    {
        std::cout << "EventManager constructor" << std::endl;

        _busImpl = new eventppImpl();


        _busImpl->FireEvent<OCEvent>(32);
    }

    //    template<class C>
    //    void RegisterListener(C* presenter)
    //    {
    //        std::shared_ptr<C> ptr = std::shared_ptr<C>(presenter);

    //        bus.reg(ptr);
    //    }

    //E: event, C: receiver class
    template<typename E, typename C, void (C::*func)(const E&)>
    void AddEventHandler(C* presenter)
    {
        std::shared_ptr<C> ptr = std::shared_ptr<C>(presenter);

        //_bus.add<E, C, func>(ptr);
    }

    template<typename E>
    void FireEvent()
    {
        _busImpl->FireEvent<E>();
    }

    void FireTestEventA()
    {
        //_bus.publish<EventA>(78);
    }
};

#endif //EVENTPPADAPTER_H
