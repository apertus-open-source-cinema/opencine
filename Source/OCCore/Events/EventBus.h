#ifndef EVENTPPADAPTER_H
#define EVENTPPADAPTER_H

#include <iostream>
#include <functional>

#include "OCEvent.h"
#include "eventppImpl.h"

//class TestEvent : public OCEvent<TestEvent>
//{
//    std::string _testMemeber = "456";

//private:
//    void DummyMethod() override {}
//};

class StartDriveTransferEvent : public OCEvent<StartDriveTransferEvent>
{
    std::string _testMemeber = "123";

private:
    void DummyMethod() override {}
};

//class StartDriveTransferEvent2 : public OCEvent<TestEvent>
//{
//    std::string _testMemeber = "123";

//private:
//    void DummyMethod() override {}
//};

// E: event, C: receiver class
class OCEventBus
{
    //EventBusBase* _busImpl;
    eventpp::Bus<StartDriveTransferEvent> _bus;
    std::shared_ptr<TestListener> _listener;
    std::shared_ptr<TestListener2> _listener2;

public:
    OCEventBus()
    {
    }

    //    template<class C>
    //    void RegisterListener(C* presenter)
    //    {
    //        std::shared_ptr<C> ptr = std::shared_ptr<C>(presenter);

    //        bus.reg(ptr);
    //    }

//    template<typename E, typename C, void (C::*func)(const E&)>
//    void AddEventHandler(C* presenter)
//    {
//        std::shared_ptr<C> ptr = std::shared_ptr<C>(presenter);

//        //_bus.add<E, C, func>(ptr);
//    }

    std::function<void(const OCEventBase&)> _testFunc = nullptr;
    void* funcPtr = nullptr;

    template<typename E, typename F>
    void AddEventHandler(F func)
    {
        //_testFunc = func;

        //funcPtr = _testFunc.target<std::function<void(const OCEventBase&)>>();
        //std::bind(func, C);
        //std::shared_ptr<C> ptr = std::shared_ptr<C>(presenter);

        _bus.add<E, func>();
    }


    // TODO: Implementation
    void RemoveEventHandler()
    {
    }

    template<typename E>
    void FireEvent(E& event)
    {
        _bus.publish<E>();
        //_busImpl->FireEvent(event);
    }

    void FireTestEventA()
    {
        //StartDriveTransferEvent event;
        //_testFunc(event);
        //_bus.publish<EventA>(78);
    }
};

#endif //EVENTPPADAPTER_H
