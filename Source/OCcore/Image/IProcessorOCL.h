#ifndef IPROCESSOROCL_H
#define IPROCESSOROCL_H

#include <CL/cl.hpp>
#include <string>

class IProcessorOCL
{
public:
	virtual std::string GetKernelFilePath() = 0;

	virtual void GetArguments(cl::Context& context, cl::Kernel& kernel, cl::CommandQueue& queue) = 0;
};

#endif //IPROCESSOROCL_H
