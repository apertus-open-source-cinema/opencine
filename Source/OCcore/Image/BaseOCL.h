// Copyright (c) 2018 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef BASEOCL_H
#define BASEOCL_H

#include <vector>

#include <CL/cl.hpp>
//#include "OCImage.h"

#include "IProcessorOCL.h"

//#define KERNELS_FILE "Kernels.cl"

//using namespace OC::DataProvider;

class BaseOCL
{
private:
    cl::Context _context;
    
	std::vector<cl::Device> _devices;
	cl::Device _defaultDevice;

	cl::CommandQueue _queue;
    cl::Program _program;

	cl::Kernel _kernel;

    cl_uint _numDevices;

    std::string _fileBuffer;

    cl_int _result;

	// TODO: Extend for multiple
	IProcessorOCL* _processor;

public:
    BaseOCL();

    ~BaseOCL();

    int SetupOCL();

    cl::CommandQueue GetQueue();
	cl::Context GetContext();

	void RegisterProcessor(IProcessorOCL* processor);

	void ExecuteProcessor();

private:
	void InitBase();

	std::string LoadKernelSource(std::string kernelPath);
};

#endif //BASEOCL_H