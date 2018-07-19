#include <Catch2/catch.hpp>

#include "../OCcore/Image/BaseOCL.h"
#include "../OCcore/Log/Logger.h"

TEST_CASE("Initialization of OpenCL Test", "[OC::Image]")
{
    const int inputDataLength = 64;

    uint16_t inputRed[inputDataLength] = {
        9,9,9,9,9,9,9,9,
        9,9,9,9,9,9,9,9,
        9,9,9,9,9,9,9,9,
        9,9,9,9,9,9,9,9,
        9,9,9,9,9,9,9,9,
        9,9,9,9,9,9,9,9,
        9,9,9,9,9,9,9,9,
        9,9,9,9,9,9,9,9
    };

    uint16_t inputGreen[inputDataLength] = {
        1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1
    };

    uint16_t inputBlue[inputDataLength] = {
        4,4,4,4,4,4,4,4,
        4,4,4,4,4,4,4,4,
        4,4,4,4,4,4,4,4,
        4,4,4,4,4,4,4,4,
        4,4,4,4,4,4,4,4,
        4,4,4,4,4,4,4,4,
        4,4,4,4,4,4,4,4,
        4,4,4,4,4,4,4,4
    };

    uint16_t expectedValues[inputDataLength] = {
        7,7,7,7,7,7,7,7,
        7,7,7,7,7,7,7,7,
        7,7,7,7,7,7,7,7,
        7,7,7,7,7,7,7,7,
        7,7,7,7,7,7,7,7,
        7,7,7,7,7,7,7,7,
        7,7,7,7,7,7,7,7,
        7,7,7,7,7,7,7,7
    };

    OCImage* inputImage = new OCImage();
    inputImage->SetWidth(8);
    inputImage->SetHeight(8);
    inputImage->SetBayerPattern(BayerPattern::BGGR);

    inputImage->SetRedChannel(inputRed);
    inputImage->SetGreenChannel(inputGreen);
    inputImage->SetBlueChannel(inputBlue);

    bool status = 0;

    status = initializeHost();

    status = initializeOCL();

    status = loadImageOCL(*inputImage);

    status = runImageFillKernel(7);

    OCImage* outputImage = new OCImage();
    outputImage->SetWidth(8);
    outputImage->SetHeight(8);
    outputImage->SetBayerPattern(BayerPattern::BGGR);

    status = saveImageOCL(*outputImage);

    status = cleanupOCL();

    uint16_t* imageRed = (uint16_t*)outputImage->RedChannel();
    uint16_t* imageGreen = (uint16_t*)outputImage->GreenChannel();
    uint16_t* imageBlue = (uint16_t*)outputImage->BlueChannel();

    bool correctRed = true;
    bool correctGreen = true;
    bool correctBlue = true;

    for(int index = 0; index < inputDataLength; index++)
    {
        if(imageRed[index] != expectedValues[index])
        {
            correctRed = false;
            OC_LOG_INFO("index" + std::to_string(index) + " out:" + std::to_string(imageRed[index])+ " exp:" + std::to_string(expectedValues[index]));
            break;
        }
    }

    for(int index = 0; index < inputDataLength; index++)
    {
        if(imageGreen[index] != expectedValues[index])
        {
            correctGreen = false;
            OC_LOG_INFO("index" + std::to_string(index) + " out:" + std::to_string(imageGreen[index])+ " exp:" + std::to_string(expectedValues[index]));
            break;
        }
    }

    for(int index = 0; index < inputDataLength; index++)
    {
        if(imageBlue[index] != expectedValues[index])
        {
            correctBlue = false;
            OC_LOG_INFO("index" + std::to_string(index) + " out:" + std::to_string(imageBlue[index])+ " exp:" + std::to_string(expectedValues[index]));
            break;
        }
    }

    REQUIRE(status == 0);
    REQUIRE(correctRed == true);
    REQUIRE(correctGreen == true);
    REQUIRE(correctBlue == true);
}

