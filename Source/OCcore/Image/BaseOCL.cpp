// Copyright (c) 2018 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#include "BaseOCL.h"
#include <Log/Logger.h>

cl_context context;
cl_device_id* devices = nullptr;
cl_command_queue queue;
cl_program program;

cl_mem redChannel;
cl_mem greenChannel;
cl_mem blueChannel;

// TODO (TofuLynx): Error Handler.

int initializeHost()
{
    devices = nullptr;

    return 0;
}

int initializeOCL()
{
    cl_uint numDevices = 0;

    // Get number of GPU devices.
    clGetDeviceIDs(nullptr, CL_DEVICE_TYPE_GPU, 0, nullptr, &numDevices);
    if (numDevices == 0)
    {
        OC_LOG_ERROR("No OpenCL capable GPUs found!");
        return -1;
    }

    // Get GPU devices.
    devices = (cl_device_id*) malloc(sizeof(cl_device_id) * numDevices);
    clGetDeviceIDs(nullptr, CL_DEVICE_TYPE_GPU, numDevices, devices, nullptr);

    // Create Context.
    context = clCreateContext(nullptr, 1, devices, nullptr, nullptr, nullptr);

    // Create Queue.
    queue = clCreateCommandQueueWithProperties(context, devices[0], nullptr, nullptr);

    // TODO (TofuLynx): Kernel load.
    // TODO (TofuLynx: Memory.

    return 0;
}

int loadImageOCL(OCImage &image)
{
    // TODO (TofuLynx): Make this more readable.

    cl_image_format imgFormat = {
        CL_A,
        CL_UNSIGNED_INT16,
    };

    cl_image_desc imgDescriptor = {
        CL_MEM_OBJECT_IMAGE2D,
        image.Width(),
        image.Height(),
        0,
        0,
        0,
        0,
        0,
        0,
        {nullptr},
    };

    redChannel      = clCreateImage(context, CL_MEM_READ_WRITE, &imgFormat, &imgDescriptor, image.RedChannel(), nullptr);
    greenChannel    = clCreateImage(context, CL_MEM_READ_WRITE, &imgFormat, &imgDescriptor, image.GreenChannel(), nullptr);
    blueChannel     = clCreateImage(context, CL_MEM_READ_WRITE, &imgFormat, &imgDescriptor, image.BlueChannel(), nullptr);

    return 0;
}

int cleanupOCL()
{
    // TODO (TofuLynx): Release Kernel.

    clReleaseProgram(program);

    clReleaseMemObject(redChannel);
    clReleaseMemObject(greenChannel);
    clReleaseMemObject(blueChannel);

    clReleaseCommandQueue(queue);

    clReleaseContext(context);

    return 0;
}
