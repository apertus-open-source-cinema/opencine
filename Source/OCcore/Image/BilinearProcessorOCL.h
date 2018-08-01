#ifndef BILINEARPROCESSOROCL_H
#define BILINEARPROCESSOROCL_H

#include "IProcessorOCL.h"

class BilinearProcessorOCL : public IProcessorOCL
{
private:
    void* _redChannel;
    void* _greenChannel;
    void* _blueChannel;
public:
	virtual std::string GetKernelFilePath() override
	{
        return "Kernels.cl";
	}

    virtual void GetArguments(cl::Context& context, OCImage& image, cl::Kernel kernels[6], cl::CommandQueue& queue) override
	{
        _redChannel = image.RedChannel();
        _greenChannel = image.GreenChannel();
        _blueChannel = image.BlueChannel();

        unsigned int width = image.Width();
        unsigned int height = image.Height();
        unsigned long size = width * height;

        cl::NDRange globalSizes((width / 2) - 1, (height / 2) - 1);
        cl::NDRange localSizes(1,1);
        cl::NDRange verticalSize(1, height / 2);
        cl::NDRange horizontalSize(width / 2, 1);

        cl::NDRange greenOffsets(1, 1);
        cl::NDRange greenSizes((width / 2) - 2, (height / 2) - 2);

        // Varies accordingly to pattern.
        cl::NDRange redOffsets, redVerticalOffsets, redHorizontalOffsets;
        cl::NDRange blueOffsets, blueVerticalOffsets, blueHorizontalOffsets;

        BayerPattern imagePattern = image.GetBayerPattern();

        // Create buffers on the device.
        cl::Buffer redBuffer(context, CL_MEM_COPY_HOST_PTR | CL_MEM_READ_WRITE, sizeof(short) * size, _redChannel);
        cl::Buffer greenBuffer(context, CL_MEM_COPY_HOST_PTR | CL_MEM_READ_WRITE, sizeof(short) * size, _greenChannel);
        cl::Buffer blueBuffer(context, CL_MEM_COPY_HOST_PTR | CL_MEM_READ_WRITE, sizeof(short) * size, _blueChannel);

        switch (imagePattern) {
        case BayerPattern::RGGB:
            // Red Channel.
            kernels[0].setArg(0, sizeof(cl::Buffer), &redBuffer);
            kernels[0].setArg(1, sizeof(int), &width);
            redOffsets = cl::NullRange;

            kernels[1].setArg(0, sizeof(cl::Buffer), &redBuffer);
            kernels[1].setArg(1, sizeof(int), &width);
            redVerticalOffsets = cl::NDRange((width / 2) - 1, 0);
            redHorizontalOffsets = cl::NDRange(0, (height / 2) - 1);

            // Green Channel.
            kernels[2].setArg(0, sizeof(cl::Buffer), &greenBuffer);
            kernels[2].setArg(1, sizeof(int), &width);
            kernels[3].setArg(0, sizeof(cl::Buffer), &greenBuffer);
            kernels[3].setArg(1, sizeof(int), &width);

            // Blue Channel.
            kernels[4].setArg(0, sizeof(cl::Buffer), &blueBuffer);
            kernels[4].setArg(1, sizeof(int), &width);
            blueOffsets = cl::NDRange(1,1);

            kernels[5].setArg(0, sizeof(cl::Buffer), &blueBuffer);
            kernels[5].setArg(1, sizeof(int), &width);
            blueVerticalOffsets = cl::NullRange;
            blueHorizontalOffsets = cl::NullRange;
            break;
        case BayerPattern::BGGR:
            // Blue Channel.
            kernels[4].setArg(0, sizeof(cl::Buffer), &blueBuffer);
            kernels[4].setArg(1, sizeof(int), &width);
            blueOffsets = cl::NullRange;

            kernels[5].setArg(0, sizeof(cl::Buffer), &blueBuffer);
            kernels[5].setArg(1, sizeof(int), &width);
            blueVerticalOffsets = cl::NDRange((width / 2) - 1, 0);
            blueHorizontalOffsets = cl::NDRange(0, (height / 2) - 1);

            // Red Channel.
            kernels[0].setArg(0, sizeof(cl::Buffer), &redBuffer);
            kernels[0].setArg(1, sizeof(int), &width);
            redOffsets = cl::NDRange(1,1);

            kernels[1].setArg(0, sizeof(cl::Buffer), &redBuffer);
            kernels[1].setArg(1, sizeof(int), &width);
            redVerticalOffsets = cl::NullRange;
            redHorizontalOffsets = cl::NullRange;
            break;
        case BayerPattern::GRBG:
            // Red Channel.
            kernels[0].setArg(0, sizeof(cl::Buffer), &redBuffer);
            kernels[0].setArg(1, sizeof(int), &width);
            redOffsets = cl::NDRange(1,0);

            kernels[1].setArg(0, sizeof(cl::Buffer), &redBuffer);
            kernels[1].setArg(1, sizeof(int), &width);
            redVerticalOffsets = cl::NullRange;
            redHorizontalOffsets = cl::NDRange(0, (height / 2) - 1);

            // Blue Channel.
            kernels[4].setArg(0, sizeof(cl::Buffer), &blueBuffer);
            kernels[4].setArg(1, sizeof(int), &width);
            blueOffsets = cl::NDRange(0,1);

            kernels[5].setArg(0, sizeof(cl::Buffer), &blueBuffer);
            kernels[5].setArg(1, sizeof(int), &width);
            blueVerticalOffsets = cl::NDRange((width / 2) - 1, 0);
            blueHorizontalOffsets = cl::NullRange;
            break;
        case BayerPattern::GBRG:
            // Blue Channel.
            kernels[4].setArg(0, sizeof(cl::Buffer), &blueBuffer);
            kernels[4].setArg(1, sizeof(int), &width);
            blueOffsets = cl::NDRange(1,0);

            kernels[5].setArg(0, sizeof(cl::Buffer), &blueBuffer);
            kernels[5].setArg(1, sizeof(int), &width);
            blueVerticalOffsets = cl::NullRange;
            blueHorizontalOffsets = cl::NDRange(0, (height / 2) - 1);

            // Red Channel.
            kernels[0].setArg(0, sizeof(cl::Buffer), &redBuffer);
            kernels[0].setArg(1, sizeof(int), &width);
            redOffsets = cl::NDRange(0,1);

            kernels[1].setArg(0, sizeof(cl::Buffer), &redBuffer);
            kernels[1].setArg(1, sizeof(int), &width);
            redVerticalOffsets = cl::NDRange((width / 2) - 1, 0);
            redHorizontalOffsets = cl::NullRange;
            break;
        }

        // Green Channel.
        kernels[2].setArg(0, sizeof(cl::Buffer), &greenBuffer);
        kernels[2].setArg(1, sizeof(int), &width);
        kernels[3].setArg(0, sizeof(cl::Buffer), &greenBuffer);
        kernels[3].setArg(1, sizeof(int), &width);

        // Run kernels.
        queue.enqueueNDRangeKernel(kernels[0], redOffsets, globalSizes, localSizes);
        queue.enqueueNDRangeKernel(kernels[1], redVerticalOffsets, verticalSize, localSizes);
        queue.enqueueNDRangeKernel(kernels[1], redHorizontalOffsets, horizontalSize, localSizes);

        queue.enqueueNDRangeKernel(kernels[2], greenOffsets, greenSizes, localSizes);
        queue.enqueueNDRangeKernel(kernels[3], cl::NullRange, verticalSize, localSizes);
        queue.enqueueNDRangeKernel(kernels[3], cl::NullRange, horizontalSize, localSizes);
        queue.enqueueNDRangeKernel(kernels[3], cl::NDRange((width / 2) - 1, 0), verticalSize, localSizes);
        queue.enqueueNDRangeKernel(kernels[3], cl::NDRange(0, (height / 2) - 1), horizontalSize, localSizes);

        queue.enqueueNDRangeKernel(kernels[4], blueOffsets, globalSizes, localSizes);
        queue.enqueueNDRangeKernel(kernels[5], blueVerticalOffsets, verticalSize, localSizes);
        queue.enqueueNDRangeKernel(kernels[5], blueHorizontalOffsets, horizontalSize, localSizes);

        // Read buffers from device to host.
        queue.enqueueReadBuffer(redBuffer, CL_TRUE, 0, sizeof(short) * size, _redChannel);
        queue.enqueueReadBuffer(greenBuffer, CL_TRUE, 0, sizeof(short) * size, _greenChannel);
        queue.enqueueReadBuffer(blueBuffer, CL_TRUE, 0, sizeof(short) * size, _blueChannel);
	}

    void GetKernelsStrings(BayerPattern pattern, std::string kernelsStrings[6]) override
    {
        switch (pattern) {
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
            kernelsStrings[2] = "bilinearGreen0";
            kernelsStrings[3] = "nearestGreen0";
            kernelsStrings[4] = "bilinearTopRight";
            kernelsStrings[5] = "nearestTopRight";
            break;
        case BayerPattern::GBRG:
            kernelsStrings[0] = "bilinearTopRight";
            kernelsStrings[1] = "nearestTopRight";
            kernelsStrings[2] = "bilinearGreen0";
            kernelsStrings[3] = "nearestGreen0";
            kernelsStrings[4] = "bilinearBottomLeft";
            kernelsStrings[5] = "nearestBottomLeft";
            break;
        }
        return;
    }

    void* GetRedChannel() override
	{
        return _redChannel;
	}

    void* GetGreenChannel() override
    {
        return _greenChannel;
    }

    void* GetBlueChannel() override
    {
        return _blueChannel;
    }
};

#endif //BILINEARPROCESSOROCL_H
