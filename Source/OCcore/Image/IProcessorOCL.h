#ifndef IPROCESSOROCL_H
#define IPROCESSOROCL_H

#include "OCImage.h"
#include <CL/cl.hpp>
#include <string>

using namespace OC::DataProvider;

class IProcessorOCL
{
public:
	virtual std::string GetKernelFilePath() = 0;

    virtual void GetArguments(cl::Context& context, OCImage& image, cl::Kernel kernels[6], cl::CommandQueue& queue) = 0;

    virtual void GetKernelsStrings(BayerPattern pattern, std::string kernelsStrings[6]) = 0;

    virtual void* GetRedChannel() = 0;

    virtual void* GetGreenChannel() = 0;

    virtual void* GetBlueChannel() = 0;
};

#endif //IPROCESSOROCL_H
