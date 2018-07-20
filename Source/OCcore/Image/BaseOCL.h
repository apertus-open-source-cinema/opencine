// Copyright (c) 2018 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef BASEOCL_H
#define BASEOCL_H

#include <CL/cl.h>
#include "OCImage.h"

#define KERNELS_FILE "Kernels.cl"

#define RED_OFFSET_RGGB 0
#define GREEN0_OFFSET_RGGB 1
#define GREEN1_OFFSET_RGGB width
#define BLUE_OFFSET_RGGB width + 1

#define BLUE_OFFSET_BGGR 0
#define GREEN0_OFFSET_BGGR 1
#define GREEN1_OFFSET_BGGR width
#define RED_OFFSET_BGGR width + 1

#define GREEN0_OFFSET_GRBG 0
#define RED_OFFSET_GRBG 1
#define BLUE_OFFSET_GRBG width
#define GREEN1_OFFSET_GRBG width + 1

#define GREEN0_OFFSET_GBRG 0
#define BLUE_OFFSET_GBRG 1
#define RED_OFFSET_GBRG width
#define GREEN1_OFFSET_GBRG width + 1

using namespace OC::DataProvider;

extern cl_context context;
extern cl_device_id* devices;
extern cl_command_queue queue;
extern cl_program program;

extern cl_mem redChannel;
extern cl_mem greenChannel;
extern cl_mem blueChannel;

extern bool isOpenCL2Device;
extern char* kernelsBuffer;

extern BayerPattern imagePattern;
extern unsigned int width;
extern unsigned int height;

extern cl_kernel imageFillKernel;
extern cl_kernel nearestNeighborKernel;

int initializeHost();

int initializeOCL();

int loadKernels(const char* filename);

int runImageFillKernel(unsigned short value);
int runNearestNeighborKernel();

int loadImageOCL(OCImage &image);
int saveImageOCL(OCImage &image);

int cleanupOCL();

#endif //BASEOCL_H
