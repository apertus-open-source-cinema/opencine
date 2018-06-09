// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / ProcessingTest
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef IPROCESSINGPRESENTER_H
#define IPROCESSINGPRESENTER_H

#include <QObject>

class IProcessingPresenter : public QObject
{
public:
    virtual void Test() = 0;
};

#endif //IPROCESSINGPRESENTER_H
