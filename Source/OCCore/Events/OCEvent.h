class OCEventBase
{

};

class OCEvent : public OCEventBase
{
protected:
	OCEvent() {}

public:
    virtual ~OCEvent() {}
};
