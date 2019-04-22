#include <Catch2/catch.hpp>

#include "../OCcore/Image/GEDIDebayer.h"

#include "Helpers.h"

#include "TestData/BayerBGGRData.h"
#include "TestData/BayerGBRGData.h"
#include "TestData/BayerGRBGData.h"
#include "TestData/BayerRGGBData.h"

static OC::Image::OCImage* outputImage = nullptr;
static std::shared_ptr<GEDIDebayer> debayer;

inline void SetupTest()
{
    outputImage = new OC::Image::OCImage();
    outputImage->SetWidth(8);
    outputImage->SetHeight(8);

    debayer = std::make_shared<GEDIDebayer>(*outputImage);
}

TEST_CASE("GEDI Test BGGR", "[OC::Image]")
{
    unsigned int dataLength = 64;

    SetupTest();

    outputImage->SetBayerPattern(OC::Image::BayerPattern::BGGR);

    outputImage->SetRedChannel(inputRedBGGR);
    outputImage->SetGreenChannel(inputGreenBGGR);
    outputImage->SetBlueChannel(inputBlueBGGR);

    debayer.get()->Process();

    uint16_t* imageRed = static_cast<uint16_t*>(outputImage->RedChannel());
    uint16_t* imageGreen = static_cast<uint16_t*>(outputImage->GreenChannel());
    uint16_t* imageBlue = static_cast<uint16_t*>(outputImage->BlueChannel());

    REQUIRE(CompareArrays(imageRed, expectedRedBGGR, dataLength));
    REQUIRE(CompareArrays(imageGreen, expectedGreenBGGR, dataLength));
    REQUIRE(CompareArrays(imageBlue, expectedBlueBGGR, dataLength));
}

TEST_CASE("GEDI Test GBRG", "[OC::Image]")
{
    unsigned int dataLength = 64;

    SetupTest();

    outputImage->SetBayerPattern(OC::Image::BayerPattern::GBRG);

    outputImage->SetRedChannel(inputRedGBRG);
    outputImage->SetGreenChannel(inputGreenGBRG);
    outputImage->SetBlueChannel(inputBlueGBRG);

    debayer.get()->Process();

    uint16_t* imageRed = static_cast<uint16_t*>(outputImage->RedChannel());
    uint16_t* imageGreen = static_cast<uint16_t*>(outputImage->GreenChannel());
    uint16_t* imageBlue = static_cast<uint16_t*>(outputImage->BlueChannel());

    REQUIRE(CompareArrays(imageRed, expectedRedGBRG, dataLength));
    REQUIRE(CompareArrays(imageGreen, expectedGreenGBRG, dataLength));
    REQUIRE(CompareArrays(imageBlue, expectedBlueGBRG, dataLength));
}

TEST_CASE("GEDI Test GRBG", "[OC::Image]")
{
    unsigned int dataLength = 64;

    SetupTest();

    outputImage->SetBayerPattern(OC::Image::BayerPattern::GRBG);

    outputImage->SetRedChannel(inputRedGRBG);
    outputImage->SetGreenChannel(inputGreenGRBG);
    outputImage->SetBlueChannel(inputBlueGRBG);

    debayer.get()->Process();

    uint16_t* imageRed = static_cast<uint16_t*>(outputImage->RedChannel());
    uint16_t* imageGreen = static_cast<uint16_t*>(outputImage->GreenChannel());
    uint16_t* imageBlue = static_cast<uint16_t*>(outputImage->BlueChannel());

    REQUIRE(CompareArrays(imageRed, expectedRedGRBG, dataLength));
    REQUIRE(CompareArrays(imageGreen, expectedGreenGRBG, dataLength));
    REQUIRE(CompareArrays(imageBlue, expectedBlueGRBG, dataLength));
}

TEST_CASE("GEDI Test RGGB", "[OC::Image]")
{
    unsigned int dataLength = 64;

    SetupTest();

    outputImage->SetBayerPattern(OC::Image::BayerPattern::RGGB);

    outputImage->SetRedChannel(inputRedRGGB);
    outputImage->SetGreenChannel(inputGreenRGGB);
    outputImage->SetBlueChannel(inputBlueRGGB);

    debayer.get()->Process();

    uint16_t* imageRed = static_cast<uint16_t*>(outputImage->RedChannel());
    uint16_t* imageGreen = static_cast<uint16_t*>(outputImage->GreenChannel());
    uint16_t* imageBlue = static_cast<uint16_t*>(outputImage->BlueChannel());

    REQUIRE(CompareArrays(imageRed, expectedRedRGGB, dataLength));
    REQUIRE(CompareArrays(imageGreen, expectedGreenRGGB, dataLength));
    REQUIRE(CompareArrays(imageBlue, expectedBlueRGGB, dataLength));
}
