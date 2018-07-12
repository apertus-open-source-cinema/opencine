// Copyright (c) 2018 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef BASEOCL_H
#define BASEOCL_H

#include <CL/cl.h>
#include "OCImage.h"

using namespace OC::DataProvider;

extern cl_context context;
extern cl_device_id* devices;
extern cl_command_queue queue;
extern cl_program program;

extern cl_mem redChannel;
extern cl_mem greenChannel;
extern cl_mem blueChannel;

int initializeHost();

int initializeOCL();

int loadImageOCL(OCImage &image);

int cleanupOCL();

#endif //BASEOCL_H
