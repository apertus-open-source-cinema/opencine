#ifndef FFMPEGDATAPROVIDER_H
#define FFMPEGDATAPROVIDER_H

#include <string>
#include <iostream>

#include <CL/cl.hpp>

#ifdef __cplusplus
extern "C"
{
//#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
//#include <libswscale/swscale.h>
}
#endif

static void TestFFMPEG()
{
  AVFormatContext* formatContext = nullptr;
  AVCodecContext* codecContext = nullptr;

  AVInputFormat* format = new AVInputFormat();
  format->name           = "mlv";
  format->long_name      = "Magic Lantern Video (MLV)";

  av_register_all();

  std::cout << LIBAVFORMAT_IDENT << std::endl;
  std::cout << LIBAVCODEC_IDENT << std::endl;
  std::cout << LIBAVUTIL_IDENT << std::endl;

  std::string videoFile = "test.mlv";

  int result = avformat_open_input(&formatContext, videoFile.c_str(), nullptr, nullptr);

  char* errorText = new char[256];
  av_strerror(result, errorText, 1024);

  result = avformat_find_stream_info(formatContext, NULL);

  // Dump information about file onto standard error
  av_dump_format(formatContext, 0, videoFile.c_str(), 0);

  //AVPacket* videoPacket = new AVPacket();

  //int frameFinished = 0;
  //if(videopacket!=0)
  //{
  //    avcodec_decode_video2(codecContext, _std_frame, &frameFinished, videoPacket);
  //}

  int i = 0;
}

static std::string trim(const std::string& str, const std::string& whitespace = " \t")
{
  const auto strBegin = str.find_first_not_of(whitespace);
  if (strBegin == std::string::npos)
    return ""; // no content

  const auto strEnd = str.find_last_not_of(whitespace);
  const auto strRange = strEnd - strBegin + 1;

  return str.substr(strBegin, strRange);
}

static void TestOpenCL()
{
  //get all platforms (drivers)
  std::vector<cl::Platform> all_platforms;
  cl::Platform::get(&all_platforms);
  if (all_platforms.size() == 0)
  {
    std::cout << " No platforms found. Check OpenCL installation!\n";
    exit(1);
  }

  cl::Platform default_platform = all_platforms[1];
  std::cout << "Using platform: " << trim(default_platform.getInfo<CL_PLATFORM_NAME>()) << "\n";

  //get default device of the default platform
  std::vector<cl::Device> all_devices;
  default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
  if (all_devices.size() == 0)
  {
    std::cout << " No devices found. Check OpenCL installation!\n";
    exit(1);
  }
  cl::Device default_device = all_devices[0];
  std::cout << "Using device: " << trim(default_device.getInfo<CL_DEVICE_NAME>()) << "\n";

  std::flush(std::cout);

  cl::Context context= { default_device };

  cl::Program::Sources sources;

  //kernel calculates for each element C=A+B
  std::string kernelCode =
    " void kernel simple_add(global const int* A, global const int* B, global int* C){ "
    " C[get_global_id(0)]=A[get_global_id(0)]+B[get_global_id(0)]; "
    " } ";

  //std::ifstream t("test1.cl");
  //std::string kernelCode((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
  sources.push_back({ kernelCode.c_str(), kernelCode.length() });

  cl::Program program(context, sources);
  if (program.build({ default_device }) != CL_SUCCESS){
    std::cout << " Error building: " << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device) << "\n";
    exit(1);
  }

  unsigned int SIZE = 1001;

  // create buffers on the device
  cl::Buffer buffer_A(context, CL_MEM_READ_WRITE, sizeof(int) * SIZE);
  cl::Buffer buffer_B(context, CL_MEM_READ_WRITE, sizeof(int) * SIZE);
  cl::Buffer buffer_C(context, CL_MEM_READ_WRITE, sizeof(int) * SIZE);

  int* A = new int[SIZE]; //[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  for(int i = 0; i < SIZE; i++)
  {
    A[i] = i;
  }

  int* B = new int[SIZE];
  for(int i = 0; i < SIZE; i++)
  {
    B[i] = i;
  }

  //int B[] = { 0, 1, 2, 0, 1, 2, 0, 1, 2, 0 };

  //create queue to which we will push commands for the device.
  cl::CommandQueue queue(context, default_device);

  //write arrays A and B to the device
  queue.enqueueWriteBuffer(buffer_A, CL_TRUE, 0, sizeof(int) * SIZE, A);
  queue.enqueueWriteBuffer(buffer_B, CL_TRUE, 0, sizeof(int) * SIZE, B);

  //run the kernel
  //cl::make_kernel<int, cl::Buffer, cl::Buffer, cl::Buffer> simple_add(cl::Kernel(program, "simple_add"), queue, cl::NullRange, cl::NDRange(10), cl::NullRange);
  //simple_add(buffer_A, buffer_B, buffer_C);

  //alternative way to run the kernel
  cl::Kernel kernel_add = cl::Kernel(program, "simple_add");
  kernel_add.setArg(0, buffer_A);
  kernel_add.setArg(1, buffer_B);
  kernel_add.setArg(2, buffer_C);
  int result = queue.enqueueNDRangeKernel(kernel_add, cl::NullRange, cl::NDRange(SIZE), cl::NullRange);
  result = queue.finish();

  int C[SIZE];
  //read result C from the device to array C
  queue.enqueueReadBuffer(buffer_C, CL_TRUE, 0, sizeof(int) * SIZE, C);

  std::cout << " result: \n";
  for (int i = 0; i < SIZE; i++)
  {
    std::cout << C[i] << " ";
  }
}

void TestCatch();
/*
//General includes
#include <memory>

//OpenCineAPI includes
#include "../API/IDataProvider.h"

//LibRaw includes
#include <libraw/libraw.h>

using namespace OpenCineAPI;

class LibRawDataProvider : public IDataProvider
{
    LibRaw* imageProcessor;

public:
    LibRawDataProvider();
    ~LibRawDataProvider();

    // IDataProvider interface
    OCImage* LoadFile(std::string filePath);
    OCImage* LoadFolder(std::string folderPath);

    // IPlugin interface
    std::string GetName();
};*/

#endif //FFMPEGDATAPROVIDER_H
