#ifndef EVENTPPIMPL_H
#define EVENTPPIMPL_H

//Library: eventpp
#include <event.hpp>
#include <bus.hpp>

//using namespace eventpp;

/* ------------------------------- */
// TODO: Temporarily here, move the block to separate file later

//class EventBusBase
//{
//public:
//    virtual void RegisterEvent(OCEvent& event) = 0;

//    virtual void FireEvent(OCEvent& event) = 0;
//};

//// Empty base implementation
//template<typename T>
//class IEventBus : public EventBusBase
//{
//public:
//    virtual void RegisterEvent(OCEvent& event) = 0;

//    void FireEvent(OCEvent& event)
//    {
//        static_cast<T*>(this)->FireEvent(event);
//    }
//};
/* ------------------------------- */

class EventA : public eventpp::Event<EventA>
{
    int _value;

public:
    EventA(int value) :
        _value(value)
    {
        int i = 0;
    }
};

class TestListener
{
public:
    void receive(const EventA &)
    {
        std::cout << "received EventA" << std::endl;
    }

    void listen(const EventA &)
    {
        std::cout << "listened EventA" << std::endl;
    }
};

class TestListener2
{
public:
    void receive(const EventA &)
    {
        std::cout << "M2 received EventA" << std::endl;
    }

    void listen(const EventA &)
    {
        std::cout << "M2 listened EventA" << std::endl;
    }
};

//using eventppBus = Bus<EventA>;

//class eventppImpl : public IEventBus<eventppImpl>
//{
//    eventpp::Bus<> _eventBus;

//public:
//    template<typename E>
//    void FireEvent(E& event)
//    {
//        int i = 0;
//    }

//    void RegisterEvent(OCEvent &event)
//    {
//        //_eventBus.add<event>()
//    }
//};

#endif //EVENTPPIMPL_H
