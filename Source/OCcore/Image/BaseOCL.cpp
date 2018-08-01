// Copyright (c) 2018 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#include <fstream>
#include <iostream>

#include "BaseOCL.h"

BaseOCL::BaseOCL() :
	_context(nullptr),
	_queue(nullptr),
	_program(nullptr),
	_numDevices(0)
{
}

BaseOCL::~BaseOCL()
{
}

int BaseOCL::SetupOCL()
{
	InitBase();

	_context = cl::Context({ _defaultDevice });
	_queue = cl::CommandQueue(_context, _defaultDevice);

	return 0;
}

cl::CommandQueue BaseOCL::GetQueue()
{
	return _queue;
}

cl::Context BaseOCL::GetContext()
{
	return _context;
}

void BaseOCL::RegisterProcessor(IProcessorOCL * processor, OCImage &image)
{
    std::cout << "Registering Processor\n";
	_processor = processor;

    // Get Kernel Source.
	std::string kernelSource = LoadKernelSource(_processor->GetKernelFilePath());

	_program = cl::Program(_context, kernelSource);
	if (_program.build({ _defaultDevice }) != CL_SUCCESS)
	{
		std::cout << " Error building: " << _program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(_defaultDevice) << "\n";
		exit(1);
	}

    // Get Kernels Strings.
    std::string kernelsStrings[6];
    processor->GetKernelsStrings(image.GetBayerPattern(), kernelsStrings);

    // Load Kernels.
    for (int i = 0; i < 6; i++)
    {
        std::cout << "Loading: " << kernelsStrings[i] << "\n";
        _kernels[i] = cl::Kernel(_program, kernelsStrings[i].c_str());
    }

    // Pass arguments to processor.
    _processor->GetArguments(_context, image, _kernels, _queue);
}

void BaseOCL::ExecuteProcessor()
{
	_queue.finish();
}

void BaseOCL::InitBase()
{
	//get all platforms (drivers)
	std::vector<cl::Platform> platformList;
	cl::Platform::get(&platformList);
	if (platformList.size() == 0)
	{
		std::cout << " No platforms found. Check OpenCL installation!\n";
		exit(1);
	}

	cl::Platform defaultPlatform = platformList[0];
	std::cout << "Using platform: " << defaultPlatform.getInfo<CL_PLATFORM_NAME>() << "\n";

	//get default device of the default platform
	defaultPlatform.getDevices(CL_DEVICE_TYPE_ALL, &_devices);
	if (_devices.size() == 0)
	{
		std::cout << " No devices found. Check OpenCL installation!\n";
		exit(1);
	}
	
	_defaultDevice = _devices[0];
	std::cout << "Using device: " << _defaultDevice.getInfo<CL_DEVICE_NAME>() << "\n";
}

std::string BaseOCL::LoadKernelSource(std::string kernelPath)
{
	std::ifstream in(kernelPath, std::ifstream::in | std::ifstream::ate);
	size_t sourceLen = in.tellg();
	in.seekg(0, in.beg);

	_fileBuffer = static_cast<char*>(calloc(sourceLen + 1, sizeof(char)));
	_fileBuffer = std::string((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

	return _fileBuffer;
}
