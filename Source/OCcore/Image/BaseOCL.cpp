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

BayerPattern imagePattern;
unsigned int width = 0;
unsigned int height = 0;

cl_kernel imageFillKernel;

cl_kernel nearestTopLeftKernel;
cl_kernel nearestTopRightKernel;
cl_kernel nearestBottomLeftKernel;
cl_kernel nearestBottomRightKernel;
cl_kernel nearestGreen0Kernel;
cl_kernel nearestGreen1Kernel;

cl_kernel bilinearTopLeftKernel;
cl_kernel bilinearTopRightKernel;
cl_kernel bilinearBottomLeftKernel;
cl_kernel bilinearBottomRightKernel;
cl_kernel bilinearGreen0Kernel;
cl_kernel bilinearGreen1Kernel;

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

//    if (deviceInfo[9] != '2')
//    {
        queue = clCreateCommandQueue(context, devices[0], 0, nullptr);
//    }
//    else
//    {
//        isOpenCL2Device = true;
//        queue = clCreateCommandQueueWithProperties(context, devices[0], nullptr, nullptr);
//    }

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

    imageFillKernel = clCreateKernel(program, "imageFill", &result);

    nearestTopLeftKernel = clCreateKernel(program, "nearestTopLeft", &result);
    nearestTopRightKernel = clCreateKernel(program, "nearestTopRight", &result);
    nearestBottomLeftKernel = clCreateKernel(program, "nearestBottomLeft", &result);
    nearestBottomRightKernel = clCreateKernel(program, "nearestBottomRight", &result);
    nearestGreen0Kernel = clCreateKernel(program, "nearestGreen0", &result);
    nearestGreen1Kernel = clCreateKernel(program, "nearestGreen1", &result);

    bilinearTopLeftKernel = clCreateKernel(program, "bilinearTopLeft", &result);
    bilinearTopRightKernel = clCreateKernel(program, "bilinearTopRight", &result);
    bilinearBottomLeftKernel = clCreateKernel(program, "bilinearBottomLeft", &result);
    bilinearBottomRightKernel = clCreateKernel(program, "bilinearBottomRight", &result);
    bilinearGreen0Kernel = clCreateKernel(program, "bilinearGreen0", &result);
    bilinearGreen1Kernel = clCreateKernel(program, "bilinearGreen1", &result);

    return 0;
}

int runImageFillKernel(unsigned short value)
{
    cl_int result;

    size_t globalSizes[2] = {width, height};
    size_t localSizes[2] = {1, 1};

    clSetKernelArg(imageFillKernel, 1, sizeof(unsigned int), &width);
    clSetKernelArg(imageFillKernel, 2, sizeof(unsigned short), &value);

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

int runNearestNeighborKernel()
{
    cl_int result;

    size_t globalSizes[2] = {(width / 2), (height / 2)};
    size_t globalOffsets[2] = {0, 0};
    size_t localSizes[2] = {1, 1};

    switch (imagePattern) {
    case BayerPattern::RGGB:
        // Red.
        clSetKernelArg(nearestBottomRightKernel, 0, sizeof(cl_mem), &redChannel);
        clSetKernelArg(nearestBottomRightKernel, 1, sizeof(unsigned int), &width);
        clEnqueueNDRangeKernel(queue, nearestBottomRightKernel, 2, globalOffsets, globalSizes, localSizes, 0, nullptr, nullptr);

        // Green.
        clSetKernelArg(nearestGreen0Kernel, 0, sizeof(cl_mem), &greenChannel);
        clSetKernelArg(nearestGreen0Kernel, 1, sizeof(unsigned int), &width);
        clEnqueueNDRangeKernel(queue, nearestGreen0Kernel, 2, globalOffsets, globalSizes, localSizes, 0, nullptr, nullptr);

        // Blue.
        clSetKernelArg(nearestTopLeftKernel, 0, sizeof(cl_mem), &blueChannel);
        clSetKernelArg(nearestTopLeftKernel, 1, sizeof(unsigned int), &width);
        clEnqueueNDRangeKernel(queue, nearestTopLeftKernel, 2, globalOffsets, globalSizes, localSizes, 0, nullptr, nullptr);
        break;
    case BayerPattern::BGGR:
        // Red.
        clSetKernelArg(nearestBottomRightKernel, 0, sizeof(cl_mem), &blueChannel);
        clSetKernelArg(nearestBottomRightKernel, 1, sizeof(unsigned int), &width);
        result = clEnqueueNDRangeKernel(queue, nearestBottomRightKernel, 2, globalOffsets, globalSizes, localSizes, 0, nullptr, nullptr);

        // Green.
        clSetKernelArg(nearestGreen0Kernel, 0, sizeof(cl_mem), &greenChannel);
        clSetKernelArg(nearestGreen0Kernel, 1, sizeof(unsigned int), &width);
        clEnqueueNDRangeKernel(queue, nearestGreen0Kernel, 2, globalOffsets, globalSizes, localSizes, 0, nullptr, nullptr);

        // Blue.
        clSetKernelArg(nearestTopLeftKernel, 0, sizeof(cl_mem), &redChannel);
        clSetKernelArg(nearestTopLeftKernel, 1, sizeof(unsigned int), &width);
        clEnqueueNDRangeKernel(queue, nearestTopLeftKernel, 2, globalOffsets, globalSizes, localSizes, 0, nullptr, nullptr);
        break;
    case BayerPattern::GRBG:
        // Red.
        clSetKernelArg(nearestBottomLeftKernel, 0, sizeof(cl_mem), &redChannel);
        clSetKernelArg(nearestBottomLeftKernel, 1, sizeof(unsigned int), &width);
        clEnqueueNDRangeKernel(queue, nearestBottomLeftKernel, 2, globalOffsets, globalSizes, localSizes, 0, nullptr, nullptr);

        // Green.
        clSetKernelArg(nearestGreen1Kernel, 0, sizeof(cl_mem), &greenChannel);
        clSetKernelArg(nearestGreen1Kernel, 1, sizeof(unsigned int), &width);
        clEnqueueNDRangeKernel(queue, nearestGreen1Kernel, 2, globalOffsets, globalSizes, localSizes, 0, nullptr, nullptr);

        // Blue.
        clSetKernelArg(nearestTopRightKernel, 0, sizeof(cl_mem), &blueChannel);
        clSetKernelArg(nearestTopRightKernel, 1, sizeof(unsigned int), &width);
        clEnqueueNDRangeKernel(queue, nearestTopRightKernel, 2, globalOffsets, globalSizes, localSizes, 0, nullptr, nullptr);
        break;
    case BayerPattern::GBRG:
        // Red.
        clSetKernelArg(nearestBottomLeftKernel, 0, sizeof(cl_mem), &blueChannel);
        clSetKernelArg(nearestBottomLeftKernel, 1, sizeof(unsigned int), &width);
        clEnqueueNDRangeKernel(queue, nearestBottomLeftKernel, 2, globalOffsets, globalSizes, localSizes, 0, nullptr, nullptr);

        // Green.
        clSetKernelArg(nearestGreen1Kernel, 0, sizeof(cl_mem), &greenChannel);
        clSetKernelArg(nearestGreen1Kernel, 1, sizeof(unsigned int), &width);
        clEnqueueNDRangeKernel(queue, nearestGreen1Kernel, 2, globalOffsets, globalSizes, localSizes, 0, nullptr, nullptr);

        // Blue.
        clSetKernelArg(nearestTopRightKernel, 0, sizeof(cl_mem), &redChannel);
        clSetKernelArg(nearestTopRightKernel, 1, sizeof(unsigned int), &width);
        clEnqueueNDRangeKernel(queue, nearestTopRightKernel, 2, globalOffsets, globalSizes, localSizes, 0, nullptr, nullptr);
        break;
    }

    clFinish(queue);

    return 0;
}

int runBilinearKernel()
{
    cl_int result;

    size_t globalSizes[2] = {(width / 2) - 1, (height / 2) - 1};
    size_t bottomRightOffsets[2]    = {0, 0};
    size_t bottomLeftOffsets[2]     = {1, 0};
    size_t topRightOffsets[2]       = {0, 1};
    size_t topLeftOffsets[2]        = {1, 1};

    size_t greenSizes[2] = {(width / 2) - 2, (height / 2) - 2};
    size_t greenOffsets[2] = {1, 1};

    size_t verticalBorderSizes[2]   = {1, height / 2};
    size_t horizontalBorderSizes[2] = {width / 2, 1};
    size_t rightOffsets[2] = {(width / 2) - 1, 0};
    size_t bottomOffsets[2] = {0, (height / 2) - 1};

    size_t localSizes[2] = {1, 1};

    switch (imagePattern) {
    case BayerPattern::RGGB:
        // Red.
        clSetKernelArg(bilinearBottomRightKernel, 0, sizeof(cl_mem), &redChannel);
        clSetKernelArg(bilinearBottomRightKernel, 1, sizeof(unsigned int), &width);
        clEnqueueNDRangeKernel(queue, bilinearBottomRightKernel, 2, bottomRightOffsets, globalSizes, localSizes, 0, nullptr, nullptr);

        clSetKernelArg(nearestBottomRightKernel, 0, sizeof(cl_mem), &redChannel);
        clSetKernelArg(nearestBottomRightKernel, 1, sizeof(unsigned int), &width);
        clEnqueueNDRangeKernel(queue, nearestBottomRightKernel, 2, rightOffsets, verticalBorderSizes, localSizes, 0, nullptr, nullptr);
        clEnqueueNDRangeKernel(queue, nearestBottomRightKernel, 2, bottomOffsets, horizontalBorderSizes, localSizes, 0, nullptr, nullptr);

        // Green.
        clSetKernelArg(bilinearGreen0Kernel, 0, sizeof(cl_mem), &greenChannel);
        clSetKernelArg(bilinearGreen0Kernel, 1, sizeof(unsigned int), &width);
        clEnqueueNDRangeKernel(queue, bilinearGreen0Kernel, 2, greenOffsets, greenSizes, localSizes, 0, nullptr, nullptr);

        clSetKernelArg(nearestGreen0Kernel, 0, sizeof(cl_mem), &greenChannel);
        clSetKernelArg(nearestGreen0Kernel, 1, sizeof(unsigned int), &width);
        clEnqueueNDRangeKernel(queue, nearestGreen0Kernel, 2, bottomRightOffsets, verticalBorderSizes, localSizes, 0, nullptr, nullptr);
        clEnqueueNDRangeKernel(queue, nearestGreen0Kernel, 2, bottomRightOffsets, horizontalBorderSizes, localSizes, 0, nullptr, nullptr);
        clEnqueueNDRangeKernel(queue, nearestGreen0Kernel, 2, rightOffsets, verticalBorderSizes, localSizes, 0, nullptr, nullptr);
        clEnqueueNDRangeKernel(queue, nearestGreen0Kernel, 2, bottomOffsets, horizontalBorderSizes, localSizes, 0, nullptr, nullptr);

        // Blue.
        clSetKernelArg(bilinearTopLeftKernel, 0, sizeof(cl_mem), &blueChannel);
        clSetKernelArg(bilinearTopLeftKernel, 1, sizeof(unsigned int), &width);
        clEnqueueNDRangeKernel(queue, bilinearTopLeftKernel, 2, topLeftOffsets, globalSizes, localSizes, 0, nullptr, nullptr);

        clSetKernelArg(nearestTopLeftKernel, 0, sizeof(cl_mem), &blueChannel);
        clSetKernelArg(nearestTopLeftKernel, 1, sizeof(unsigned int), &width);
        clEnqueueNDRangeKernel(queue, nearestTopLeftKernel, 2, bottomRightOffsets, verticalBorderSizes, localSizes, 0, nullptr, nullptr);
        clEnqueueNDRangeKernel(queue, nearestTopLeftKernel, 2, bottomRightOffsets, horizontalBorderSizes, localSizes, 0, nullptr, nullptr);
        break;
    case BayerPattern::BGGR:
        // Blue.
        clSetKernelArg(bilinearBottomRightKernel, 0, sizeof(cl_mem), &blueChannel);
        clSetKernelArg(bilinearBottomRightKernel, 1, sizeof(unsigned int), &width);
        clEnqueueNDRangeKernel(queue, bilinearBottomRightKernel, 2, bottomRightOffsets, globalSizes, localSizes, 0, nullptr, nullptr);

        clSetKernelArg(nearestBottomRightKernel, 0, sizeof(cl_mem), &blueChannel);
        clSetKernelArg(nearestBottomRightKernel, 1, sizeof(unsigned int), &width);
        clEnqueueNDRangeKernel(queue, nearestBottomRightKernel, 2, rightOffsets, verticalBorderSizes, localSizes, 0, nullptr, nullptr);
        clEnqueueNDRangeKernel(queue, nearestBottomRightKernel, 2, bottomOffsets, horizontalBorderSizes, localSizes, 0, nullptr, nullptr);

        // Green.
        clSetKernelArg(bilinearGreen0Kernel, 0, sizeof(cl_mem), &greenChannel);
        clSetKernelArg(bilinearGreen0Kernel, 1, sizeof(unsigned int), &width);
        clEnqueueNDRangeKernel(queue, bilinearGreen0Kernel, 2, greenOffsets, greenSizes, localSizes, 0, nullptr, nullptr);

        clSetKernelArg(nearestGreen0Kernel, 0, sizeof(cl_mem), &greenChannel);
        clSetKernelArg(nearestGreen0Kernel, 1, sizeof(unsigned int), &width);
        clEnqueueNDRangeKernel(queue, nearestGreen0Kernel, 2, bottomRightOffsets, verticalBorderSizes, localSizes, 0, nullptr, nullptr);
        clEnqueueNDRangeKernel(queue, nearestGreen0Kernel, 2, bottomRightOffsets, horizontalBorderSizes, localSizes, 0, nullptr, nullptr);
        clEnqueueNDRangeKernel(queue, nearestGreen0Kernel, 2, rightOffsets, verticalBorderSizes, localSizes, 0, nullptr, nullptr);
        clEnqueueNDRangeKernel(queue, nearestGreen0Kernel, 2, bottomOffsets, horizontalBorderSizes, localSizes, 0, nullptr, nullptr);

        // Red.
        clSetKernelArg(bilinearTopLeftKernel, 0, sizeof(cl_mem), &redChannel);
        clSetKernelArg(bilinearTopLeftKernel, 1, sizeof(unsigned int), &width);
        clEnqueueNDRangeKernel(queue, bilinearTopLeftKernel, 2, topLeftOffsets, globalSizes, localSizes, 0, nullptr, nullptr);

        clSetKernelArg(nearestTopLeftKernel, 0, sizeof(cl_mem), &redChannel);
        clSetKernelArg(nearestTopLeftKernel, 1, sizeof(unsigned int), &width);
        clEnqueueNDRangeKernel(queue, nearestTopLeftKernel, 2, bottomRightOffsets, verticalBorderSizes, localSizes, 0, nullptr, nullptr);
        clEnqueueNDRangeKernel(queue, nearestTopLeftKernel, 2, bottomRightOffsets, horizontalBorderSizes, localSizes, 0, nullptr, nullptr);
        break;
    case BayerPattern::GRBG:
        // Red.
        clSetKernelArg(bilinearBottomLeftKernel, 0, sizeof(cl_mem), &redChannel);
        clSetKernelArg(bilinearBottomLeftKernel, 1, sizeof(unsigned int), &width);
        clEnqueueNDRangeKernel(queue, bilinearBottomLeftKernel, 2, bottomLeftOffsets, globalSizes, localSizes, 0, nullptr, nullptr);

        clSetKernelArg(nearestTopRightKernel, 0, sizeof(cl_mem), &redChannel);
        clSetKernelArg(nearestTopRightKernel, 1, sizeof(unsigned int), &width);
        clEnqueueNDRangeKernel(queue, nearestTopRightKernel, 2, bottomRightOffsets, verticalBorderSizes, localSizes, 0, nullptr, nullptr);
        clEnqueueNDRangeKernel(queue, nearestTopRightKernel, 2, bottomOffsets, horizontalBorderSizes, localSizes, 0, nullptr, nullptr);

        // Green.
        clSetKernelArg(bilinearGreen1Kernel, 0, sizeof(cl_mem), &greenChannel);
        clSetKernelArg(bilinearGreen1Kernel, 1, sizeof(unsigned int), &width);
        clEnqueueNDRangeKernel(queue, bilinearGreen1Kernel, 2, greenOffsets, greenSizes, localSizes, 0, nullptr, nullptr);

        clSetKernelArg(bilinearGreen1Kernel, 0, sizeof(cl_mem), &greenChannel);
        clSetKernelArg(bilinearGreen1Kernel, 1, sizeof(unsigned int), &width);
        clEnqueueNDRangeKernel(queue, bilinearGreen1Kernel, 2, bottomRightOffsets, verticalBorderSizes, localSizes, 0, nullptr, nullptr);
        clEnqueueNDRangeKernel(queue, bilinearGreen1Kernel, 2, bottomRightOffsets, horizontalBorderSizes, localSizes, 0, nullptr, nullptr);
        clEnqueueNDRangeKernel(queue, bilinearGreen1Kernel, 2, rightOffsets, verticalBorderSizes, localSizes, 0, nullptr, nullptr);
        clEnqueueNDRangeKernel(queue, bilinearGreen1Kernel, 2, bottomOffsets, horizontalBorderSizes, localSizes, 0, nullptr, nullptr);

        // Blue.
        clSetKernelArg(bilinearTopRightKernel, 0, sizeof(cl_mem), &blueChannel);
        clSetKernelArg(bilinearTopRightKernel, 1, sizeof(unsigned int), &width);
        clEnqueueNDRangeKernel(queue, bilinearTopRightKernel, 2, topRightOffsets, globalSizes, localSizes, 0, nullptr, nullptr);

        clSetKernelArg(nearestTopRightKernel, 0, sizeof(cl_mem), &blueChannel);
        clSetKernelArg(nearestTopRightKernel, 1, sizeof(unsigned int), &width);
        clEnqueueNDRangeKernel(queue, nearestTopRightKernel, 2, rightOffsets, verticalBorderSizes, localSizes, 0, nullptr, nullptr);
        clEnqueueNDRangeKernel(queue, nearestTopRightKernel, 2, bottomRightOffsets, horizontalBorderSizes, localSizes, 0, nullptr, nullptr);
        break;
    case BayerPattern::GBRG:
        // Blue.
        clSetKernelArg(bilinearBottomLeftKernel, 0, sizeof(cl_mem), &blueChannel);
        clSetKernelArg(bilinearBottomLeftKernel, 1, sizeof(unsigned int), &width);
        clEnqueueNDRangeKernel(queue, bilinearBottomLeftKernel, 2, bottomLeftOffsets, globalSizes, localSizes, 0, nullptr, nullptr);

        clSetKernelArg(nearestTopRightKernel, 0, sizeof(cl_mem), &blueChannel);
        clSetKernelArg(nearestTopRightKernel, 1, sizeof(unsigned int), &width);
        clEnqueueNDRangeKernel(queue, nearestTopRightKernel, 2, bottomRightOffsets, verticalBorderSizes, localSizes, 0, nullptr, nullptr);
        clEnqueueNDRangeKernel(queue, nearestTopRightKernel, 2, bottomOffsets, horizontalBorderSizes, localSizes, 0, nullptr, nullptr);

        // Green.
        clSetKernelArg(bilinearGreen1Kernel, 0, sizeof(cl_mem), &greenChannel);
        clSetKernelArg(bilinearGreen1Kernel, 1, sizeof(unsigned int), &width);
        clEnqueueNDRangeKernel(queue, bilinearGreen1Kernel, 2, greenOffsets, greenSizes, localSizes, 0, nullptr, nullptr);

        clSetKernelArg(bilinearGreen1Kernel, 0, sizeof(cl_mem), &greenChannel);
        clSetKernelArg(bilinearGreen1Kernel, 1, sizeof(unsigned int), &width);
        clEnqueueNDRangeKernel(queue, bilinearGreen1Kernel, 2, bottomRightOffsets, verticalBorderSizes, localSizes, 0, nullptr, nullptr);
        clEnqueueNDRangeKernel(queue, bilinearGreen1Kernel, 2, bottomRightOffsets, horizontalBorderSizes, localSizes, 0, nullptr, nullptr);
        clEnqueueNDRangeKernel(queue, bilinearGreen1Kernel, 2, rightOffsets, verticalBorderSizes, localSizes, 0, nullptr, nullptr);
        clEnqueueNDRangeKernel(queue, bilinearGreen1Kernel, 2, bottomOffsets, horizontalBorderSizes, localSizes, 0, nullptr, nullptr);

        // Red.
        clSetKernelArg(bilinearTopRightKernel, 0, sizeof(cl_mem), &redChannel);
        clSetKernelArg(bilinearTopRightKernel, 1, sizeof(unsigned int), &width);
        clEnqueueNDRangeKernel(queue, bilinearTopRightKernel, 2, topRightOffsets, globalSizes, localSizes, 0, nullptr, nullptr);

        clSetKernelArg(nearestTopRightKernel, 0, sizeof(cl_mem), &redChannel);
        clSetKernelArg(nearestTopRightKernel, 1, sizeof(unsigned int), &width);
        clEnqueueNDRangeKernel(queue, nearestTopRightKernel, 2, rightOffsets, verticalBorderSizes, localSizes, 0, nullptr, nullptr);
        clEnqueueNDRangeKernel(queue, nearestTopRightKernel, 2, bottomRightOffsets, horizontalBorderSizes, localSizes, 0, nullptr, nullptr);
        break;
    }

    // TODO (TofuLynx): Demosaic Borders.

    clFinish(queue);

    return 0;
}

int loadImageOCL(OCImage &image)
{
    width = image.Width();
    height = image.Height();
    imagePattern = image.GetBayerPattern();

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

    result = clEnqueueReadBuffer(queue, redChannel, CL_FALSE    , 0, sizeof(unsigned short) * width * height, newRedChannel, 0, nullptr, nullptr);
    result = clEnqueueReadBuffer(queue, greenChannel, CL_FALSE, 0, sizeof(unsigned short) * width * height, newGreenChannel, 0, nullptr, nullptr);
    result =clEnqueueReadBuffer(queue, blueChannel, CL_FALSE, 0, sizeof(unsigned short) * width * height, newBlueChannel, 0, nullptr, nullptr);
    clFinish(queue);

    OC_LOG_INFO("RGB>" + std::to_string(newRedChannel[1]) + " " + std::to_string(newGreenChannel[1]) + " " + std::to_string(newBlueChannel[1]));

    image.SetRedChannel(newRedChannel);
    image.SetGreenChannel(newGreenChannel);
    image.SetBlueChannel(newBlueChannel);

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
