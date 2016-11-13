class OCEventBase
{

};

class OCEvent : public OCEventBase
{
protected:
	OCEvent() {}

public:
    virtual ~OCEvent() {}

    // TODO: Implement some meaningful structure, this here should just prevent instantiation
    //virtual void DummyMethod() = 0;
};
