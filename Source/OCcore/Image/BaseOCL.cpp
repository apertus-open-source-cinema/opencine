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

bool isOpenCL2Device = false;
char* kernelsBuffer = nullptr;
cl_uint width = 0;
cl_uint height = 0;

cl_kernel imageFillKernel;

// TODO (TofuLynx): Error Handler.

int initializeHost()
{
    devices = nullptr;

    return 0;
}

int initializeOCL()
{
    cl_uint numDevices = 0;
    char deviceInfo[128];

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

    // Get OpenCL C Version Support.
    clGetDeviceInfo(devices[0], CL_DEVICE_OPENCL_C_VERSION, 128 * sizeof(char), deviceInfo, nullptr);
    OC_LOG_INFO(deviceInfo);

    // Create Queue.
    if (deviceInfo[9] != '2')
    {
        queue = clCreateCommandQueue(context, devices[0], 0, nullptr);
    }
    else
    {
        isOpenCL2Device = true;
        queue = clCreateCommandQueueWithProperties(context, devices[0], nullptr, nullptr);
    }

    if (loadKernels(KERNELS_FILE) != 0)
    {
        return -1;
    }

    return 0;
}

int loadKernels(const char *fileName)
{
    // Load Kernels File.
    FILE* fp = fopen(fileName, "r");
    if (fp == nullptr)
    {
        OC_LOG_ERROR("Error opening Kernels File!");
        return -1;
    }

    // Get source length.
    fseek(fp, 0, SEEK_END);
    unsigned long sourceLen = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    kernelsBuffer = (char*) calloc(sourceLen + 1, sizeof(char));
    fread(kernelsBuffer, sizeof(char), sourceLen, fp);

    fclose(fp);

    program = clCreateProgramWithSource(context, 1, (const char**) &kernelsBuffer, &sourceLen, nullptr);

    clBuildProgram(program, 1, devices, nullptr, nullptr, nullptr);

    // TODO (TofuLynx): Create Kernel Objects.

    imageFillKernel = clCreateKernel(program, "imageFill", nullptr);

    return 0;
}

int loadImageOCL(OCImage &image)
{
    // TODO (TofuLynx): Make this more readable.
    width = image.Width();
    height = image.Height();

    cl_image_format imgFormat = {
        CL_R,
        CL_UNSIGNED_INT16,
    };

    cl_image_desc imgDescriptor = {
        CL_MEM_OBJECT_IMAGE2D,
        width,
        height,
        1,
        0,
        0,
        0,
        0,
        0,
        {nullptr},
    };

    redChannel      = clCreateImage(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, &imgFormat, &imgDescriptor, (void*) image.RedChannel(), nullptr);
    greenChannel    = clCreateImage(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, &imgFormat, &imgDescriptor, (void*) image.GreenChannel(), nullptr);
    blueChannel     = clCreateImage(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, &imgFormat, &imgDescriptor, (void*) image.BlueChannel(), nullptr);

    return 0;
}

int saveImageOCL(OCImage &image)
{
    size_t origin[3] = {0, 0, 0};
    size_t region[3] = {width, height, 1};

    uint16_t newRedChannel[width * height];

    clEnqueueReadImage(queue, redChannel, CL_TRUE, origin, region, 0, 0, (void*) newRedChannel, 0, nullptr, nullptr);
    clFinish(queue);

    OC_LOG_INFO("GOT> " + std::to_string(newRedChannel[0]));

    image.SetRedChannel(newRedChannel);

    return 0;
}

int runImageFillKernel(cl_ushort value)
{
    clSetKernelArg(imageFillKernel, 0, sizeof(cl_ushort) * width * height, &redChannel);
    clSetKernelArg(imageFillKernel, 1, sizeof(cl_uint), &width);
    clSetKernelArg(imageFillKernel, 2, sizeof(cl_uint), &height);
    clSetKernelArg(imageFillKernel, 3, sizeof(cl_ushort), &value);

    size_t globalSizes[2] = {width, height};

    clEnqueueNDRangeKernel(queue, imageFillKernel, 2, nullptr, globalSizes, nullptr, 0, nullptr, nullptr);
    clFinish(queue);

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
