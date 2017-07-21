// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

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
