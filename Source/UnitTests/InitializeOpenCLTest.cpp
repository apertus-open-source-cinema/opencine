#include <Catch2/catch.hpp>

#include "../OCcore/Image/BaseOCL.h"
#include "../OCcore/Log/Logger.h"

TEST_CASE("Initialization of OpenCL Test", "[OC::Image]")
{
    const int inputDataLength = 64;

    // R = 1, G = 2, B = 3
    uint16_t inputData[inputDataLength] = {
        3,2,3,2,3,2,3,2,
        2,1,2,1,2,1,2,1,
        3,2,3,2,3,2,3,2,
        2,1,2,1,2,1,2,1,
        3,2,3,2,3,2,3,2,
        2,1,2,1,2,1,2,1,
        3,2,3,2,3,2,3,2,
        2,1,2,1,2,1,2,1
    };

    uint16_t inputRed[inputDataLength] = {
        0,0,0,0,0,0,0,0,
        0,1,0,1,0,1,0,1,
        0,0,0,0,0,0,0,0,
        0,1,0,1,0,1,0,1,
        0,0,0,0,0,0,0,0,
        0,1,0,1,0,1,0,1,
        0,0,0,0,0,0,0,0,
        0,1,0,1,0,1,0,1
    };

    uint16_t inputGreen[inputDataLength] = {
        0,2,0,2,0,2,0,2,
        2,0,2,0,2,0,2,0,
        0,2,0,2,0,2,0,2,
        2,0,2,0,2,0,2,0,
        0,2,0,2,0,2,0,2,
        2,0,2,0,2,0,2,0,
        0,2,0,2,0,2,0,2,
        2,0,2,0,2,0,2,0
    };

    uint16_t inputBlue[inputDataLength] = {
        3,0,3,0,3,0,3,0,
        0,0,0,0,0,0,0,0,
        3,0,3,0,3,0,3,0,
        0,0,0,0,0,0,0,0,
        3,0,3,0,3,0,3,0,
        0,0,0,0,0,0,0,0,
        3,0,3,0,3,0,3,0,
        0,0,0,0,0,0,0,0
    };

    OCImage* inputImage = new OCImage();
    inputImage->SetWidth(8);
    inputImage->SetHeight(8);
    inputImage->SetBayerPattern(BayerPattern::BGGR);

    inputImage->SetRedChannel(inputRed);
    inputImage->SetGreenChannel(inputGreen);
    inputImage->SetBlueChannel(inputBlue);

    uint16_t* imageRed = (uint16_t*)inputImage->RedChannel();
    uint16_t* imageGreen = (uint16_t*)inputImage->GreenChannel();
    uint16_t* imageBlue = (uint16_t*)inputImage->BlueChannel();

    bool status = 0;

    status = initializeHost();

    status = initializeOCL();

    status = loadImageOCL(*inputImage);

    status = cleanupOCL();

    REQUIRE(status == 0);
}

