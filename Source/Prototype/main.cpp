#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <streambuf>

#include "gl3w.h"
#include <SDL2/SDL.h>

#include <oglplus/gl.hpp>

#include <oglplus/all.hpp>

#include <OpenImageIO/imageio.h>
OIIO_NAMESPACE_USING

class IPlugin
{
  std::string _name;

public:
  IPlugin(std::string name) :
  _name(name)
  {
  }

  std::string GetName()
  {
    return _name;
  }
};

// Dummy struct for now
struct Frame
{

};

class IProcessingPlugin : public IPlugin
{
public:
  IProcessingPlugin(std::string name) : IPlugin(name)
  {

  }

  virtual void Process(Frame* input, Frame* output) = 0;
};

class SimpleProcessingPlugin : public IProcessingPlugin
{
public:
  SimpleProcessingPlugin(std::string name) : IProcessingPlugin(name)
  {

  }

  virtual void Process(Frame* input, Frame* output)
  {
    // Do something
  }
};


bool LoadImage(std::string fileName, unsigned short* imageData, unsigned int dataSize)
{
  ImageInput *image = ImageInput::open ("000100.dng");
  if (! image)
  {
    return false;
  }

  const ImageSpec &spec = image->spec();
  int width = spec.width;
  int height = spec.height;
  int channelCount = spec.nchannels;
  //std::vector<unsigned short> imageData(width * height * channelCount);
  image->read_image (TypeDesc::UINT16, &imageData[0]);

  image->close();
  delete image;

  return true;
}

bool SaveImage(std::string fileName, unsigned short* imageData, unsigned int dataSize)
{
  ImageOutput *image = ImageOutput::create(fileName);
  if (!image)
  {
    return false;
  }

  ImageSpec spec (1920, 1080, 3, TypeDesc::UINT16);
  image->open ("test.tif", spec);
  image->write_image (TypeDesc::UINT16, imageData);

  image->close();
  delete image;

  return true;
}

std::string LoadTextFile(std::string fileName)
{
  /*std::ifstream in(filename, std::ios::in | std::ios::binary);
   if (in)
   {
     std::string contents;
     in.seekg(0, std::ios::end);
     contents.resize(in.tellg());
     in.seekg(0, std::ios::beg);
     in.read(&contents[0], contents.size());
     in.close();
     return(contents);
   }
   throw(errno);*/

  //Slow for large files, according to: http://insanecoding.blogspot.de/2011/11/how-to-read-in-file-in-c.html
  std::ifstream file(fileName);
  std::string str((std::istreambuf_iterator<char>(file)),
  std::istreambuf_iterator<char>());

  return str  ;
}

int OGLPlusTest()
{
  int width = 640, height = 480;
  int status = SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *window = SDL_CreateWindow( "Grapics Application", 0, 0, width, height, SDL_WINDOW_OPENGL);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GLContext glcontext = SDL_GL_CreateContext(window);

  gl3wInit();

  if (!gl3wIsSupported(3, 3))
  {
    fprintf(stderr, "OpenGL 3.2 not supported\n");
    return 0;
  }

  oglplus::Context gl;

  int majorVersion = gl.MajorVersion();
  int minorVersion = gl.MinorVersion();

  std::string shadingLanguageVersion = std::string(gl.ShadingLanguageVersion());

  // Notes
  // Get image data
  // Setup chain of plugins with GLSL first
  // Let them process the data
  // Output processed image data with OIIO (simple to use for such things)

  oglplus::VertexShader vs;
  oglplus::FragmentShader fs;

  try
  {
    std::string vertexShaderSource = LoadTextFile("basicShader.vert");
    vs.Source(vertexShaderSource);
    vs.Compile();
  }
  catch(oglplus::Error& err)
  {
    std::cout << err.Log() << std::endl;
  }

  try
  {
    std::string fragmentShaderSource = LoadTextFile("basicShader.frag");
    fs.Source(fragmentShaderSource);
    fs.Compile();
  }
  catch(oglplus::Error& err)
  {
    std::cout << err.Log() << std::endl;
  }

  oglplus::Program prog;

  prog.AttachShader(vs);
  prog.AttachShader(fs);

  try
  {
    prog.Link();
    prog.Use();
  }
  catch(oglplus::Error& err)
  {
    std::cout << err.Log() << std::endl;
  }

  const std::unique_ptr<IProcessingPlugin> pluginA = std::unique_ptr<IProcessingPlugin>(new SimpleProcessingPlugin("PluginA"));

  int i = 0; // For breakpoint
}

int main()
{
  //LibRawTest();

  //OpenCLTest();

  OGLPlusTest();

  return 0;
}

