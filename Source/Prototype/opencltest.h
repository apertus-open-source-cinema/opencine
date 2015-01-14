#ifndef OPENCLTEST
#define OPENCLTEST

#include <CL/cl.hpp>

#include <OpenImageIO/imageio.h>
OIIO_NAMESPACE_USING

unsigned short* imageDataFloat = nullptr;

static std::string trim(const std::string& str, const std::string& whitespace = " \t")
{
  const auto strBegin = str.find_first_not_of(whitespace);
  if (strBegin == std::string::npos)
    return ""; // no content

  const auto strEnd = str.find_last_not_of(whitespace);
  const auto strRange = strEnd - strBegin + 1;

  return str.substr(strBegin, strRange);
}

int OpenCLTest()
{
  unsigned int imageWidth = 4;
  unsigned int imageHeight = 4;


  /*for(unsigned int index = 0; index < 16; index++)
  {
    imageData[index] = 15 - index;
  }*/

  ImageInput *in = ImageInput::open ("000100.dng");
  if (! in)
  {
    return 0;
  }

  const ImageSpec &spec = in->spec();
  int xres = spec.width;
  int yres = spec.height;
  int channels = spec.nchannels;
  std::vector<unsigned short> pixels (xres*yres*channels);
  in->read_image (TypeDesc::UINT16, &pixels[0]);

  for (size_t i = 0; i < spec.extra_attribs.size(); ++i) //Printing all the extra attributes
  {
    const OpenImageIO::ParamValue &p(spec.extra_attribs[i]);
    std::cout << p.name() << " ";
    if (p.type() == OpenImageIO::TypeDesc::TypeString)
      printf("\"\%s\"", *(const char **)p.data());
    else if (p.type() == OpenImageIO::TypeDesc::TypeFloat)
      printf("\%g", *(const float *)p.data());
    else if (p.type() == OpenImageIO::TypeDesc::TypeInt)
      printf("\%d", *(const int *)p.data());
    else if (p.type() == OpenImageIO::TypeDesc::UINT)
      printf("\%u", *(const unsigned int *)p.data());
    else
      printf("<unknown data type>");
    printf("\n");
  }

  ImageOutput *out = ImageOutput::create("test.tif");
  if (! out)
  {
    return 0;
  }

  ImageSpec spec2 (1920, 1080, 3, TypeDesc::UINT16);
  out->open ("test.tif", spec2);
  out->write_image (TypeDesc::UINT16, imageDataFloat);
  out->close();
  delete out;

  in->close ();
  delete in;

  return 0;

  //unsigned short* imageData = new unsigned short[1920 * 1080 * 3];
  //cout << sizeof(imageData) * 1920 * 1080 * 3 << endl;
  //delete[] imageData;

  //vector<unsigned short> imageData2;
  //imageData2.assign(1920*1080*3, 0);

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

  unsigned int* A = new unsigned int[SIZE]; //[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  for(unsigned int i = 0; i < SIZE; i++)
  {
    A[i] = i;
  }

  unsigned int* B = new unsigned int[SIZE];
  for(unsigned int i = 0; i < SIZE; i++)
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

  unsigned int C[SIZE];
  //read result C from the device to array C
  queue.enqueueReadBuffer(buffer_C, CL_TRUE, 0, sizeof(unsigned int) * SIZE, C);

  std::cout << " result: \n";
  for (unsigned int i = 0; i < SIZE; i++)
  {
    std::cout << C[i] << " ";
  }

  delete[] A;
  delete[] B;
}

#endif // OPENCLTEST

