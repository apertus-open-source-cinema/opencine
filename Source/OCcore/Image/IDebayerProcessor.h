#ifndef DEBAYERPROCESSOR_H
#define DEBAYERPROCESSOR_H

#include "OCImage.h"

class IDebayerProcessor
{
public:
    virtual ~IDebayerProcessor() {}

     virtual void Process(OC::DataProvider::OCImage &image) = 0;
};

#endif // DEBAYERPROCESSOR_H
