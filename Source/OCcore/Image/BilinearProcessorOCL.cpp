#include "BilinearProcessorOCL.h"

using namespace OC::Image;

std::string BilinearProcessorOCL::GetKernelFilePath()
{
    return "Kernels.cl";
}

void BilinearProcessorOCL::GetArguments(cl::Context &context, OC::Image::OCImage &image, cl::Kernel kernels[])
{
    _kernels = kernels;
    OC::Image::BayerPattern imagePattern = image.GetBayerPattern();

    _redChannel = image.RedChannel();
    _greenChannel = image.GreenChannel();
    _blueChannel = image.BlueChannel();

    _width = image.Width();
    _height = image.Height();
    _size = _width * _height;

    _globalSizes = cl::NDRange((_width / 2) - 1, (_height / 2) - 1);
    _localSizes = cl::NDRange(1, 1);
    _verticalSize = cl::NDRange(1, _height / 2);
    _horizontalSize = cl::NDRange(_width / 2, 1);

    _greenOffsets = cl::NDRange(1, 1);
    _greenSizes = cl::NDRange((_width / 2) - 2, (_height / 2) - 2);

    // Create buffers on the device.
    _redBuffer = cl::Buffer(context, CL_MEM_COPY_HOST_PTR | CL_MEM_READ_WRITE, sizeof(short) * _size, _redChannel);
    _greenBuffer = cl::Buffer(context, CL_MEM_COPY_HOST_PTR | CL_MEM_READ_WRITE, sizeof(short) * _size, _greenChannel);
    _blueBuffer = cl::Buffer(context, CL_MEM_COPY_HOST_PTR | CL_MEM_READ_WRITE, sizeof(short) * _size, _blueChannel);

    switch(imagePattern)
    {
    case BayerPattern::RGGB:
        // Red Channel.
        _redOffsets = cl::NullRange;
        _redVerticalOffsets = cl::NDRange((_width / 2) - 1, 0);
        _redHorizontalOffsets = cl::NDRange(0, (_height / 2) - 1);

        // Blue Channel.
        _blueOffsets = cl::NDRange(1, 1);
        _blueVerticalOffsets = cl::NullRange;
        _blueHorizontalOffsets = cl::NullRange;
        break;
    case BayerPattern::BGGR:
        // Blue Channel.
        _blueOffsets = cl::NullRange;
        _blueVerticalOffsets = cl::NDRange((_width / 2) - 1, 0);
        _blueHorizontalOffsets = cl::NDRange(0, (_height / 2) - 1);

        // Red Channel.
        _redOffsets = cl::NDRange(1, 1);
        _redVerticalOffsets = cl::NullRange;
        _redHorizontalOffsets = cl::NullRange;
        break;
    case BayerPattern::GRBG:
        // Red Channel.
        _redOffsets = cl::NDRange(1, 0);
        _redVerticalOffsets = cl::NullRange;
        _redHorizontalOffsets = cl::NDRange(0, (_height / 2) - 1);

        // Blue Channel.
        _blueOffsets = cl::NDRange(0, 1);
        _blueVerticalOffsets = cl::NDRange((_width / 2) - 1, 0);
        _blueHorizontalOffsets = cl::NullRange;
        break;
    case BayerPattern::GBRG:
        // Blue Channel.
        _blueOffsets = cl::NDRange(1, 0);
        _blueVerticalOffsets = cl::NullRange;
        _blueHorizontalOffsets = cl::NDRange(0, (_height / 2) - 1);

        // Red Channel.
        _redOffsets = cl::NDRange(0, 1);
        _redVerticalOffsets = cl::NDRange((_width / 2) - 1, 0);
        _redHorizontalOffsets = cl::NullRange;
        break;
    }

    // Red Channel.
    _kernels[0].setArg(0, sizeof(cl::Buffer), &_redBuffer);
    _kernels[0].setArg(1, sizeof(int), &_width);
    _kernels[1].setArg(0, sizeof(cl::Buffer), &_redBuffer);
    _kernels[1].setArg(1, sizeof(int), &_width);

    // Green Channel.
    _kernels[2].setArg(0, sizeof(cl::Buffer), &_greenBuffer);
    _kernels[2].setArg(1, sizeof(int), &_width);
    _kernels[3].setArg(0, sizeof(cl::Buffer), &_greenBuffer);
    _kernels[3].setArg(1, sizeof(int), &_width);

    // Blue Channel.
    _kernels[4].setArg(0, sizeof(cl::Buffer), &_blueBuffer);
    _kernels[4].setArg(1, sizeof(int), &_width);
    _kernels[5].setArg(0, sizeof(cl::Buffer), &_blueBuffer);
    _kernels[5].setArg(1, sizeof(int), &_width);
}

void BilinearProcessorOCL::GetKernelsStrings(BayerPattern pattern, std::string kernelsStrings[])
{
    switch(pattern)
    {
    case BayerPattern::RGGB:
        kernelsStrings[0] = "bilinearBottomRight";
        kernelsStrings[1] = "nearestBottomRight";
        kernelsStrings[2] = "bilinearGreen0";
        kernelsStrings[3] = "nearestGreen0";
        kernelsStrings[4] = "bilinearTopLeft";
        kernelsStrings[5] = "nearestTopLeft";
        break;
    case BayerPattern::BGGR:
        kernelsStrings[0] = "bilinearTopLeft";
        kernelsStrings[1] = "nearestTopLeft";
        kernelsStrings[2] = "bilinearGreen0";
        kernelsStrings[3] = "nearestGreen0";
        kernelsStrings[4] = "bilinearBottomRight";
        kernelsStrings[5] = "nearestBottomRight";
        break;
    case BayerPattern::GRBG:
        kernelsStrings[0] = "bilinearBottomLeft";
        kernelsStrings[1] = "nearestBottomLeft";
        kernelsStrings[2] = "bilinearGreen1";
        kernelsStrings[3] = "nearestGreen1";
        kernelsStrings[4] = "bilinearTopRight";
        kernelsStrings[5] = "nearestTopRight";
        break;
    case BayerPattern::GBRG:
        kernelsStrings[0] = "bilinearTopRight";
        kernelsStrings[1] = "nearestTopRight";
        kernelsStrings[2] = "bilinearGreen1";
        kernelsStrings[3] = "nearestGreen1";
        kernelsStrings[4] = "bilinearBottomLeft";
        kernelsStrings[5] = "nearestBottomLeft";
        break;
    }
    return;
}

void BilinearProcessorOCL::Process(cl::CommandQueue &queue)
{
    // Run _kernels.
    queue.enqueueNDRangeKernel(_kernels[0], _redOffsets, _globalSizes, _localSizes);
    queue.enqueueNDRangeKernel(_kernels[1], _redVerticalOffsets, _verticalSize, _localSizes);
    queue.enqueueNDRangeKernel(_kernels[1], _redHorizontalOffsets, _horizontalSize, _localSizes);

    queue.enqueueNDRangeKernel(_kernels[2], _greenOffsets, _greenSizes, _localSizes);
    queue.enqueueNDRangeKernel(_kernels[3], cl::NullRange, _verticalSize, _localSizes);
    queue.enqueueNDRangeKernel(_kernels[3], cl::NullRange, _horizontalSize, _localSizes);
    queue.enqueueNDRangeKernel(_kernels[3], cl::NDRange((_width / 2) - 1, 0), _verticalSize, _localSizes);
    queue.enqueueNDRangeKernel(_kernels[3], cl::NDRange(0, (_height / 2) - 1), _horizontalSize, _localSizes);

    queue.enqueueNDRangeKernel(_kernels[4], _blueOffsets, _globalSizes, _localSizes);
    queue.enqueueNDRangeKernel(_kernels[5], _blueVerticalOffsets, _verticalSize, _localSizes);
    queue.enqueueNDRangeKernel(_kernels[5], _blueHorizontalOffsets, _horizontalSize, _localSizes);

    // Read buffers from device to host.
    queue.enqueueReadBuffer(_redBuffer, CL_TRUE, 0, sizeof(short) * _size, _redChannel);
    queue.enqueueReadBuffer(_greenBuffer, CL_TRUE, 0, sizeof(short) * _size, _greenChannel);
    queue.enqueueReadBuffer(_blueBuffer, CL_TRUE, 0, sizeof(short) * _size, _blueChannel);
}

void *BilinearProcessorOCL::GetRedChannel()
{
    return _redChannel;
}

void *BilinearProcessorOCL::GetGreenChannel()
{
    return _greenChannel;
}

void *BilinearProcessorOCL::GetBlueChannel()
{
    return _blueChannel;
}
