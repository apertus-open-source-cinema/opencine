#include <Catch2/catch.hpp>

#include "../OCcore/Image/BayerFramePreProcessor.h"

TEST_CASE("Known pixel extraction", "[OC::Image]")
{
    const int dataLength = 64;

    // R = 1, G = 2, B = 3
    uint16_t inputData[dataLength] = {
        1,2,1,2,1,2,1,2,
        2,3,2,3,2,3,2,3,
        1,2,1,2,1,2,1,2,
        2,3,2,3,2,3,2,3,
        1,2,1,2,1,2,1,2,
        2,3,2,3,2,3,2,3,
        1,2,1,2,1,2,1,2,
        2,3,2,3,2,3,2,3
    };

    uint16_t expectedRed[dataLength] = {
        1,0,1,0,1,0,1,0,
        0,0,0,0,0,0,0,0,
        1,0,1,0,1,0,1,0,
        0,0,0,0,0,0,0,0,
        1,0,1,0,1,0,1,0,
        0,0,0,0,0,0,0,0,
        1,0,1,0,1,0,1,0,
        0,0,0,0,0,0,0,0
    };

    uint16_t expectedGreen[dataLength] = {
        0,2,0,2,0,2,0,2,
        2,0,2,0,2,0,2,0,
        0,2,0,2,0,2,0,2,
        2,0,2,0,2,0,2,0,
        0,2,0,2,0,2,0,2,
        2,0,2,0,2,0,2,0,
        0,2,0,2,0,2,0,2,
        2,0,2,0,2,0,2,0
    };

    uint16_t expectedBlue[dataLength] = {
        0,0,0,0,0,0,0,0,
        0,3,0,3,0,3,0,3,
        0,0,0,0,0,0,0,0,
        0,3,0,3,0,3,0,3,
        0,0,0,0,0,0,0,0,
        0,3,0,3,0,3,0,3,
        0,0,0,0,0,0,0,0,
        0,3,0,3,0,3,0,3
    };

    std::unique_ptr<BayerFramePreProcessor> framePreProcessor(new BayerFramePreProcessor);// = std::make_shared<BayerFramePreProcessor>();
    OCImage* outputImage = new OCImage();
    outputImage->SetWidth(8);
    outputImage->SetHeight(8);
    outputImage->SetBayerPattern(BayerPattern::RGGB);

    outputImage->SetRedChannel(new uint16_t[dataLength]);
    memset(outputImage->RedChannel(), 0, 64 * sizeof(uint16_t));
    outputImage->SetGreenChannel(new uint16_t[dataLength]);
    memset(outputImage->GreenChannel(), 0, 64 * sizeof(uint16_t));
    outputImage->SetBlueChannel(new uint16_t[dataLength]);
    memset(outputImage->BlueChannel(), 0, 64 * sizeof(uint16_t));

    framePreProcessor.get()->SetData(inputData, *outputImage);
    framePreProcessor.get()->Process();

    bool correctRed = true;
    bool correctGreen = true;
    bool correctBlue = true;

    uint16_t* imageRed = (uint16_t*)outputImage->RedChannel();
    for(int index = 0; index < dataLength - 1; index++)
    {
        if(imageRed[index] != expectedRed[index])
        {
            correctRed = false;
            break;
        }
    }

    uint16_t* imageGreen = (uint16_t*)outputImage->GreenChannel();
    for(int index = 0; index < dataLength - 1; index++)
    {
        if(imageGreen[index] != expectedGreen[index])
        {
            correctGreen = false;
            break;
        }
    }

    uint16_t* imageBlue = (uint16_t*)outputImage->BlueChannel();
    for(int index = 0; index < dataLength - 1; index++)
    {
        if(imageBlue[index] != expectedBlue[index])
        {
            correctBlue = false;
            break;
        }
    }

    REQUIRE(correctRed == true);
    REQUIRE(correctGreen == true);
    REQUIRE(correctBlue == true);
}
