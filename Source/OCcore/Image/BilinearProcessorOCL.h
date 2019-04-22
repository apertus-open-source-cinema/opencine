#ifndef BILINEARPROCESSOROCL_H
#define BILINEARPROCESSOROCL_H

#include "IProcessorOCL.h"

class BilinearProcessorOCL : public IProcessorOCL
{
private:
    void* _redChannel;
    void* _greenChannel;
    void* _blueChannel;

    unsigned int _width;
    unsigned int _height;
    unsigned long _size;

    cl::Kernel* _kernels;

    cl::NDRange _globalSizes;
    cl::NDRange _localSizes;
    cl::NDRange _verticalSize;
    cl::NDRange _horizontalSize;

    cl::NDRange _greenOffsets;
    cl::NDRange _greenSizes;

    // Varies accordingly to pattern.
    cl::NDRange _redOffsets, _redVerticalOffsets, _redHorizontalOffsets;
    cl::NDRange _blueOffsets, _blueVerticalOffsets, _blueHorizontalOffsets;

    cl::Buffer _redBuffer;
    cl::Buffer _greenBuffer;
    cl::Buffer _blueBuffer;

public:
    virtual std::string GetKernelFilePath() override;

    virtual void GetArguments(cl::Context& context, OC::Image::OCImage& image, cl::Kernel kernels[6]) override;

    void GetKernelsStrings(OC::Image::BayerPattern pattern, std::string kernelsStrings[6]) override;

    void Process(cl::CommandQueue& queue) override;

    void* GetRedChannel() override;

    void* GetGreenChannel() override;

    void* GetBlueChannel() override;
};

#endif // BILINEARPROCESSOROCL_H
