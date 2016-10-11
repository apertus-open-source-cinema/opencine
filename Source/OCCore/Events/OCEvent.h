class OCEventBase
{

};

class OCEvent : public OCEventBase
{
public:
    virtual ~OCEvent() {}

    // TODO: Implement some meningful structure, this here should just prevent instantiation
    virtual void DummyMethod() = 0;
};
