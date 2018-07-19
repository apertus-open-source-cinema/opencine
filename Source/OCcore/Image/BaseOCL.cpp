// Copyright (c) 2018 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#include <iostream>

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
unsigned int width = 0;
unsigned int height = 0;

cl_kernel imageFillKernel;

// TODO (TofuLynx): Error Handler.

int initializeHost()
{
    devices = nullptr;

    return 0;
}

int initializeOCL()
{
    unsigned int numDevices = 0;
    char deviceInfo[128];

    // Get number of GPU devices.
    clGetDeviceIDs(nullptr, CL_DEVICE_TYPE_ALL, 0, nullptr, &numDevices);
    if (numDevices == 0)
    {
        OC_LOG_ERROR("No OpenCL capable GPUs found!");
        return -1;
    }

    // Get GPU devices.
    devices = static_cast<cl_device_id*>(malloc(sizeof(cl_device_id) * numDevices));
    clGetDeviceIDs(nullptr, CL_DEVICE_TYPE_ALL, numDevices, devices, nullptr);

    // Create Context.
    context = clCreateContext(nullptr, 1, devices, nullptr, nullptr, nullptr);

    // Get OpenCL C Version Support.
    clGetDeviceInfo(devices[0], CL_DEVICE_OPENCL_C_VERSION, 128 * sizeof(char), deviceInfo, nullptr);
    OC_LOG_INFO(deviceInfo);

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
    cl_int result;

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

    program = clCreateProgramWithSource(context, 1, (const char**) &kernelsBuffer, &sourceLen, &result);

    result = clBuildProgram(program, 1, devices, nullptr, nullptr, nullptr);

    if(result != 0)
    {
        size_t length;
        char buffer[2048];
        clGetProgramBuildInfo(program, devices[0], CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &length);
        std::cout<<"--- Build log ---\n "<<buffer<<std::endl;
    }

    // TODO (TofuLynx): Create Kernel Objects.
    imageFillKernel = clCreateKernel(program, "imageFill", &result);

    return 0;
}

int loadImageOCL(OCImage &image)
{
    width = image.Width();
    height = image.Height();

    cl_int result = 0;
    redChannel      = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(unsigned short) * width * height, static_cast<void*>(image.RedChannel()), &result);
    greenChannel    = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(unsigned short) * width * height, static_cast<void*>(image.GreenChannel()), &result);
    blueChannel     = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(unsigned short) * width * height, static_cast<void*>(image.BlueChannel()), &result);

    return 0;
}

int saveImageOCL(OCImage &image)
{
    cl_int result;

    uint16_t* newRedChannel = new uint16_t[width * height];
    uint16_t* newGreenChannel = new uint16_t[width * height];
    uint16_t* newBlueChannel = new uint16_t[width * height];

    result = clEnqueueReadBuffer(queue, redChannel, CL_TRUE, 0, sizeof(unsigned short) * width * height, newRedChannel, 0, nullptr, nullptr);
    result = clEnqueueReadBuffer(queue, greenChannel, CL_TRUE, 0, sizeof(unsigned short) * width * height, newGreenChannel, 0, nullptr, nullptr);
    result =clEnqueueReadBuffer(queue, blueChannel, CL_TRUE, 0, sizeof(unsigned short) * width * height, newBlueChannel, 0, nullptr, nullptr);
    clFinish(queue);

    OC_LOG_INFO("RGB>" + std::to_string(newRedChannel[1]) + " " + std::to_string(newGreenChannel[1]) + " " + std::to_string(newBlueChannel[1]));

    image.SetRedChannel(newRedChannel);
    image.SetGreenChannel(newGreenChannel);
    image.SetBlueChannel(newBlueChannel);

    return 0;
}

int runImageFillKernel(unsigned short value)
{
    cl_int result;

    size_t globalSizes[2] = {width, height};
    size_t localSizes[2] = {1, 1};

    clSetKernelArg(imageFillKernel, 1, sizeof(unsigned int), &width);
    clSetKernelArg(imageFillKernel, 2, sizeof(unsigned int), &height);
    clSetKernelArg(imageFillKernel, 3, sizeof(unsigned short), &value);

    clSetKernelArg(imageFillKernel, 0, sizeof(cl_mem), &redChannel);
    result = clEnqueueNDRangeKernel(queue, imageFillKernel, 2, nullptr, globalSizes, localSizes, 0, nullptr, nullptr);
    OC_LOG_INFO("clEnqueueNDRangeKernel Red Result>" + std::to_string(result));

    clSetKernelArg(imageFillKernel, 0, sizeof(cl_mem), &greenChannel);
    result = clEnqueueNDRangeKernel(queue, imageFillKernel, 2, nullptr, globalSizes, localSizes, 0, nullptr, nullptr);
    OC_LOG_INFO("clEnqueueNDRangeKernel Green Result>" + std::to_string(result));

    clSetKernelArg(imageFillKernel, 0, sizeof(cl_mem), &blueChannel);
    result = clEnqueueNDRangeKernel(queue, imageFillKernel, 2, nullptr, globalSizes, localSizes, 0, nullptr, nullptr);
    OC_LOG_INFO("clEnqueueNDRangeKernel Blue Result>" + std::to_string(result));

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
