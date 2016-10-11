#ifndef EVENTPPADAPTER_H
#define EVENTPPADAPTER_H

#include <iostream>
#include <functional>
#include <memory>
#include <unordered_map>

#include "OCEvent.h"

class StartDriveTransferEvent : public OCEvent
{
    std::string _testMemeber = "123";

private:
    void DummyMethod() override {}
};

// E: event, C: receiver class
class OCEventBus
{
    //typedef void(*FuncDef)(const OCEvent &);
    typedef std::function<void(const OCEvent&)> FuncDef;
    std::unordered_map<size_t, int> eventMap;

    std::vector<FuncDef> handlerList;

    // Private for now as events should be registered automatically (if not already done) on handler registration, just for simplicity
    template<typename E>
    std::vector<int>& RegisterEvent()
    {
        std::string name = typeid(E).name();
        std::size_t hash = std::hash<std::string>()(name);

        eventMap.insert(std::make_pair(hash, 0));
    }

    template<typename E>
    std::vector<int> FindEvent()
    {
        size_t hash = typeid(E).hash_code();
        std::unordered_map<size_t, int>::const_iterator it = eventMap.find(hash);

        // TODO: Improve error handling
        if ( it == eventMap.end() )
        {
            // Create event
        }
        else
        {

        }
    }

    template <class Functor>
    FuncDef CreateDelegate(Functor f)
    {
        return FuncDef(new std::function<void(const OCEvent&)>(f));
    }

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

        //_bus.add<E, func>();
    }


    // TODO: Implementation
    void RemoveEventHandler()
    {
    }

    template<typename E>
    void FireEvent(E& event)
    {
        size_t hash = typeid(E).hash_code();


        //_bus.publish<E>();
        //_busImpl->FireEvent(event);
    }

    void FireTestEventA()
    {
        //StartDriveTransferEvent event;
        //_testFunc(event);
        //_bus.publish<EventA>(78);
    }

    template<typename E, typename C>
    void RegisterEventHandler(FuncDef&& event)
    {
        // Look up if event already exists, oterwise register it
        //FindEvent();

        // Push handler to handlerList and store index in std::vector of evetn handlers
        //funcDef f = CreateDelegate(func);
        handlerList.emplace_back(event);

        std::string name = typeid(E).name();
        std::size_t hash = std::hash<std::string>()(name);
        std::cout << "Hash:" << hash << std::endl;

        std::cout << "Hash2:" << typeid(E).hash_code() << std::endl;

        eventMap.insert(std::make_pair(hash, 0));
    }
};

#endif //EVENTPPADAPTER_H
