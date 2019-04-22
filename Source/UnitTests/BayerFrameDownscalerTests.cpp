#include <Catch2/catch.hpp>

#include "../OCcore/Image/BayerFrameDownscaler.h"

TEST_CASE("Downscaler Extraction", "[OC::Image]")
{
    const int inputDataLength = 64;
    const int outputDataLength = inputDataLength / 4;

    // R = 1, G = 2, B = 3
    uint16_t inputData[inputDataLength] = {1, 2, 1, 2, 1, 2, 1, 2,  //
                                           2, 3, 2, 3, 2, 3, 2, 3,  //
                                           1, 2, 1, 2, 1, 2, 1, 2,  //
                                           2, 3, 2, 3, 2, 3, 2, 3,  //
                                           1, 2, 1, 2, 1, 2, 1, 2,  //
                                           2, 3, 2, 3, 2, 3, 2, 3,  //
                                           1, 2, 1, 2, 1, 2, 1, 2,  //
                                           2, 3, 2, 3, 2, 3, 2, 3}; //

    uint16_t expectedRed[outputDataLength] = {1, 1, 1, 1,  //
                                              1, 1, 1, 1,  //
                                              1, 1, 1, 1,  //
                                              1, 1, 1, 1}; //

    uint16_t expectedGreen[outputDataLength] = {2, 2, 2, 2,  //
                                                2, 2, 2, 2,  //
                                                2, 2, 2, 2,  //
                                                2, 2, 2, 2}; //

    uint16_t expectedBlue[outputDataLength] = {3, 3, 3, 3,  //
                                               3, 3, 3, 3,  //
                                               3, 3, 3, 3,  //
                                               3, 3, 3, 3}; //

    std::unique_ptr<BayerFrameDownscaler> downscaler(new BayerFrameDownscaler);
    OC::Image::OCImage* outputImage = new OC::Image::OCImage();
    outputImage->SetWidth(8);
    outputImage->SetHeight(8);
    outputImage->SetBayerPattern(OC::Image::BayerPattern::RGGB);

    outputImage->SetRedChannel(new uint16_t[inputDataLength]);
    memset(outputImage->RedChannel(), 0, 64 * sizeof(uint16_t));
    outputImage->SetGreenChannel(new uint16_t[inputDataLength]);
    memset(outputImage->GreenChannel(), 0, 64 * sizeof(uint16_t));
    outputImage->SetBlueChannel(new uint16_t[inputDataLength]);
    memset(outputImage->BlueChannel(), 0, 64 * sizeof(uint16_t));

    downscaler.get()->SetData(inputData, *outputImage);
    downscaler.get()->Process();

    bool correctRed = true;
    bool correctGreen = true;
    bool correctBlue = true;

    uint16_t* imageRed = (uint16_t*)outputImage->RedChannel();
    for(int index = 0; index < outputDataLength; index++)
    {
        if(imageRed[index] != expectedRed[index])
        {
            correctRed = false;
            break;
        }
    }

    uint16_t* imageGreen = (uint16_t*)outputImage->GreenChannel();
    for(int index = 0; index < outputDataLength; index++)
    {
        if(imageGreen[index] != expectedGreen[index])
        {
            correctGreen = false;
            break;
        }
    }

    uint16_t* imageBlue = (uint16_t*)outputImage->BlueChannel();
    for(int index = 0; index < outputDataLength; index++)
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
