#include <Catch2/catch.hpp>

#include "../OCcore/Image/BaseOCL.h"
#include "../OCcore/Log/Logger.h"

#include <iostream>
#include "../OCcore/Image/SumProcessorOCL.h"

TEST_CASE("Initialization of OpenCL Test", "[OC::Image]")
{
    const int inputDataLength = 64;
    const int outputDataLength = inputDataLength;

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

    BaseOCL* ocl = new BaseOCL();
    ocl->SetupOCL();

    cl::Context context = ocl->GetContext();

    SumProcessorOCL sumProc;
    ocl->RegisterProcessor(&sumProc);

    // TODO: Extend for multiple processors
    // TODO: Evaluate which id to use to call
    ocl->ExecuteProcessor();

    int* C = sumProc.GetResult();

    std::cout << " result: \n";
    for (int i = 0; i < 10; i++)
    {
        std::cout << C[i] << " ";
    }

    std::cout << std::endl;
    delete ocl;
}

