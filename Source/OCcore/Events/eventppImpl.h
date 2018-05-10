// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef EVENTPPIMPL_H
#define EVENTPPIMPL_H

//Library: eventpp
#include <event.hpp>
#include <bus.hpp>

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

#endif //EVENTPPIMPL_H
