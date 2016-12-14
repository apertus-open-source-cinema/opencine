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
