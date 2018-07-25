// Copyright (c) 2018 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef BASEOCL_H
#define BASEOCL_H

#include <CL/cl.h>
#include "OCImage.h"

#define KERNELS_FILE "Kernels.cl"

using namespace OC::DataProvider;

class BaseOCL
{
private:
    cl_context _context;
    cl_device_id* _devices;
    cl_command_queue _queue;
    cl_program _program;

    cl_uint _numDevices;

    char* _fileBuffer;

    cl_int _result;

public:
    BaseOCL();

    ~BaseOCL();

    int SetupOCL();

    cl_command_queue GetQueue();

};

#endif //BASEOCL_H
