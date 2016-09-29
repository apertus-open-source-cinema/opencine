#ifndef EVENTPPIMPL_H
#define EVENTPPIMPL_H

//Library: eventpp
#include <event.hpp>
#include <bus.hpp>

using namespace eventpp;

class EventA : public Event<EventA>
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

using eventppBus = Bus<EventA>;

#endif //EVENTPPIMPL_H
