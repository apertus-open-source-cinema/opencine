#ifndef SUMPROCESSOROCL_H
#define SUMPROCESSOROCL_H

#include "IProcessorOCL.h"

class SumProcessorOCL : public IProcessorOCL
{
	int C[10];
public:
	virtual std::string GetKernelFilePath() override
	{
		return "test_kernel.cl";
	}

	virtual void GetArguments(cl::Context& context, cl::Kernel& kernel, cl::CommandQueue& queue) override
	{
		// create buffers on the device
		cl::Buffer buffer_A(context, CL_MEM_READ_WRITE, sizeof(int) * 10);
		cl::Buffer buffer_B(context, CL_MEM_READ_WRITE, sizeof(int) * 10);
		cl::Buffer buffer_C(context, CL_MEM_READ_WRITE, sizeof(int) * 10);

		int A[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		int B[] = { 0, 1, 2, 0, 1, 2, 0, 1, 2, 0 };

		//write arrays A and B to the device
		queue.enqueueWriteBuffer(buffer_A, CL_TRUE, 0, sizeof(int) * 10, A);
		queue.enqueueWriteBuffer(buffer_B, CL_TRUE, 0, sizeof(int) * 10, B);

		kernel.setArg(0, buffer_A);
		kernel.setArg(1, buffer_B);
		kernel.setArg(2, buffer_C);

		queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(10), cl::NullRange);

		//read result C from the device to array C
		queue.enqueueReadBuffer(buffer_C, CL_TRUE, 0, sizeof(int) * 10, C);
	}

	int* GetResult()
	{
		return C;
	}
};

#endif //SUMPROCESSOROCL_H
