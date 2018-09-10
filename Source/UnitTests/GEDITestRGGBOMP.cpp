#include <Catch2/catch.hpp>

#include "../OCcore/Image/GEDIDebayerOMP.h"
#include "../OCcore/Log/Logger.h"

TEST_CASE("GEDI OMP Test RGGB", "[OC::Image]")
{
    const int inputDataLength = 64;
    const int outputDataLength = inputDataLength;

    // R = 1, G = 2, B = 3
    uint16_t inputData[inputDataLength] = {
        1,2,1,2,1,2,1,2,
        2,3,2,3,2,3,2,3,
        1,2,1,2,1,2,1,2,
        2,3,2,3,2,3,2,3,
        1,2,1,2,1,2,1,2,
        2,3,2,3,2,3,2,3,
        1,2,1,2,1,2,1,2,
        2,3,2,3,2,3,2,3
    };

    uint16_t inputRed[inputDataLength] = {
        1,0,1,0,1,0,1,0,
        0,0,0,0,0,0,0,0,
        1,0,1,0,1,0,1,0,
        0,0,0,0,0,0,0,0,
        1,0,1,0,1,0,1,0,
        0,0,0,0,0,0,0,0,
        1,0,1,0,1,0,1,0,
        0,0,0,0,0,0,0,0
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
        0,0,0,0,0,0,0,0,
        0,3,0,3,0,3,0,3,
        0,0,0,0,0,0,0,0,
        0,3,0,3,0,3,0,3,
        0,0,0,0,0,0,0,0,
        0,3,0,3,0,3,0,3,
        0,0,0,0,0,0,0,0,
        0,3,0,3,0,3,0,3
    };

    uint16_t expectedRed[outputDataLength] = {
        1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1
    };

    uint16_t expectedGreen[outputDataLength] = {
        2,2,2,2,2,2,2,2,
        2,2,2,2,2,2,2,2,
        2,2,2,2,2,2,2,2,
        2,2,2,2,2,2,2,2,
        2,2,2,2,2,2,2,2,
        2,2,2,2,2,2,2,2,
        2,2,2,2,2,2,2,2,
        2,2,2,2,2,2,2,2
    };

    uint16_t expectedBlue[outputDataLength] = {
        3,3,3,3,3,3,3,3,
        3,3,3,3,3,3,3,3,
        3,3,3,3,3,3,3,3,
        3,3,3,3,3,3,3,3,
        3,3,3,3,3,3,3,3,
        3,3,3,3,3,3,3,3,
        3,3,3,3,3,3,3,3,
        3,3,3,3,3,3,3,3
    };


    OCImage* outputImage = new OCImage();
    outputImage->SetWidth(8);
    outputImage->SetHeight(8);
    outputImage->SetBayerPattern(BayerPattern::RGGB);

    outputImage->SetRedChannel(inputRed);
    outputImage->SetGreenChannel(inputGreen);
    outputImage->SetBlueChannel(inputBlue);

    uint16_t* imageRed = (uint16_t*)outputImage->RedChannel();
    uint16_t* imageGreen = (uint16_t*)outputImage->GreenChannel();
    uint16_t* imageBlue = (uint16_t*)outputImage->BlueChannel();

    std::unique_ptr<GEDIDebayerOMP> debayer(new GEDIDebayerOMP(*outputImage));
    debayer.get()->Process();

    bool correctRed = true;
    bool correctGreen = true;
    bool correctBlue = true;

    for(int index = 0; index < outputDataLength; index++)
    {
        if(imageRed[index] != expectedRed[index])
        {
            correctRed = false;
            OC_LOG_INFO("index" + std::to_string(index) + " out:" + std::to_string(imageRed[index])+ " exp:" + std::to_string(expectedRed[index]));
            break;
        }
    }

    for(int index = 0; index < outputDataLength; index++)
    {
        if(imageGreen[index] != expectedGreen[index])
        {
            correctGreen = false;
            OC_LOG_INFO("index" + std::to_string(index) + " out:" + std::to_string(imageGreen[index])+ " exp:" + std::to_string(expectedGreen[index]));
            break;
        }
    }

    for(int index = 0; index < outputDataLength; index++)
    {
        if(imageBlue[index] != expectedBlue[index])
        {
            correctBlue = false;
            OC_LOG_INFO("index" + std::to_string(index) + " out:" + std::to_string(imageBlue[index])+ " exp:" + std::to_string(expectedBlue[index]));
            break;
        }
    }

    REQUIRE(correctRed == true);
    REQUIRE(correctGreen == true);
    REQUIRE(correctBlue == true);
}
