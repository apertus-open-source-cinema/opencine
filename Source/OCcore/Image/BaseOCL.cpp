// Copyright (c) 2018 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#include <iostream>

#include "BaseOCL.h"
#include <Log/Logger.h>


BaseOCL::BaseOCL()
{
    _context = nullptr;
    _devices = nullptr;
    _queue = nullptr;
    _program = nullptr;

    _numDevices = 0;

    _fileBuffer = nullptr;
}

BaseOCL::~BaseOCL()
{
}

int BaseOCL::SetupOCL()
{
    // Get number of OpenCL capable devices.
    clGetDeviceIDs(nullptr, CL_DEVICE_TYPE_ALL, 0, nullptr, &_numDevices);
    if (_numDevices == 0)
    {
        OC_LOG_ERROR("No OpenCL capable devices found!");
        return -1;
    }

    // Store OpenCL capable devices.
    _devices = static_cast<cl_device_id*>(malloc(sizeof(cl_device_id) * _numDevices));
    if (_devices != nullptr)
    {
        OC_LOG_ERROR("Error allocating memory for _devices!");
        return -1;
    }
    _result = clGetDeviceIDs(nullptr, CL_DEVICE_TYPE_ALL, _numDevices, _devices, nullptr);
    if (_result != 0)
    {
        OC_LOG_ERROR("Error storing the devices into _devices!");
        return -1;
    }

    // Create Context.
    _context = clCreateContext(nullptr, 1, _devices, nullptr, nullptr, &_result);
    if (_result != 0)
    {
        OC_LOG_ERROR("Error creating _context!");
        return -1;
    }

    // Create Queue.
    // TODO: Choose best device.
    _queue = clCreateCommandQueue(_context, _devices[0], 0, &_result);
    if (_result != 0)
    {
        OC_LOG_ERROR("Error creating _queue!");
        return -1;
    }

    // Creating file pointer to "Kernels.cl".
    FILE* fp = fopen(KERNELS_FILE, "r");
    if (fp == nullptr)
    {
        OC_LOG_ERROR("Error opening \"Kernels.cl\" file!");
        return -1;
    }

    // Get "Kernels.cl" file length.
    fseek(fp, 0, SEEK_END);
    unsigned long sourceLen = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    if (sourceLen == 0)
    {
        OC_LOG_ERROR("\"Kernels.cl\" file appears to be empty!");
        return -1;
    }

    // Read "Kernels.cl" file into buffer.
    _fileBuffer = static_cast<char*>(calloc(sourceLen + 1, sizeof(char)));
    fread(_fileBuffer, sizeof(char), sourceLen, fp);

    // Close the File Pointer.
    fclose(fp);

    // Create program.
    _program = clCreateProgramWithSource(_context, 1, (const char**)&_fileBuffer, &sourceLen, &_result);
    if (_result == 0)
    {
        OC_LOG_ERROR("Error creating program!");
        return -1;
    }

    // Build program.
    _result = clBuildProgram(_program, 1, _devices, nullptr, nullptr, nullptr);
    if(_result != 0)
    {
        OC_LOG_ERROR("Error building program!");
        size_t length;
        char buffer[2048];
        clGetProgramBuildInfo(_program, _devices[0], CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &length);
        std::cout << "--- Build log ---\n " << buffer << std::endl;
        return -1;
    }

    return 0;
}

cl_command_queue BaseOCL::GetQueue()
{
    return _queue;
}
