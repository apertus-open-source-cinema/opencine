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
  int Width;
  int Height;

  void* imageData;
  unsigned int dataSize;
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


bool LoadImage(std::string fileName, Frame* frame)
{
  ImageInput *image = ImageInput::open (fileName);
  if (! image)
  {
    return false;
  }

  const ImageSpec &spec = image->spec();
  frame->Width = spec.width;
  frame->Height = spec.height;
  int channelCount = spec.nchannels;

  frame->dataSize = frame->Width * frame->Height * channelCount;
  frame->imageData = new unsigned char[frame->dataSize];
  //std::vector<unsigned short> imageData(width * height * channelCount);
  image->read_image(TypeDesc::UINT8, frame->imageData);

  image->close();
  delete image;

  return true;
}

bool SaveImage(std::string fileName, Frame* frame /*unsigned short* imageData, unsigned int dataSize*/)
{
  ImageOutput *image = ImageOutput::create(fileName);
  if (!image)
  {
    return false;
  }

  ImageSpec spec (frame->Width, frame->Height, 3, TypeDesc::UINT8);
  image->open (fileName, spec);
  image->write_image (TypeDesc::UINT8, frame->imageData);

  image->close();
  delete image;

  return true;
}

std::string LoadTextFile(std::string fileName)
{
  /*std::ifstream in(filename, std::ios::in | std::ios::binary);
   if (in)b
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

  //unsigned short* imageData = nullptr;
  //unsigned int dataSize = 0;
  Frame* frame = new Frame();
  LoadImage("test_light.jpg", frame);

  SaveImage("test_light2.jpg", frame/*, frame->dataSize*/);

  // Processing here
  oglplus::VertexArray rectangle;
  oglplus::Buffer verts;
  oglplus::Buffer texCoords;

  rectangle.Bind();
  /*GLfloat rectangle_verts[8] =
  {
  -1.0f, -1.0f,
  -1.0f, 1.0f,
  1.0f, -1.0f,
  1.0f, 1.0f
  };*/

  GLfloat rectangleVertices[8] =
  {
   -0.9f, -0.9f,
    0.9f, -0.9f,
   -0.9f,  0.9f,
    0.9f,  0.9f
  };

  GLfloat rectangleTexCoords[8] =
  {
   0.0f, 1.0f,
   1.0f, 1.0f,
   0.0f, 0.0f,
   1.0f, 0.0f
  };

  verts.Bind(oglplus::Buffer::Target::Array);
  oglplus::Buffer::Data(oglplus::Buffer::Target::Array, rectangleVertices);
  (prog | "Position").Setup<oglplus::Vec2f>().Enable();

  texCoords.Bind(oglplus::Buffer::Target::Array);
  oglplus::Buffer::Data(oglplus::Buffer::Target::Array, rectangleTexCoords);
  (prog | "vertTexCoord").Setup<oglplus::Vec2f>().Enable();

  //gl.Disable(oglplus::Capability::DepthTest);

  int maxTexSize = -1;
  glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTexSize);

  oglplus::Texture tex;
  tex.Bind(oglplus::Texture::Target::_2D);

  //oglplus::Texture::Active(0);
  gl.Bind(oglplus::TextureTarget::_2D, tex);
  gl.PixelStore(oglplus::PixelParameter::UnpackAlignment, 1);
  oglplus::Texture::Image2D(oglplus::TextureTarget::_2D, 0, oglplus::PixelDataInternalFormat::RGB, frame->Width, frame->Height, 0, oglplus::PixelDataFormat::RGB, oglplus::PixelDataType::UnsignedByte, frame->imageData);
  //oglplus::Texture::SubImage2D(oglplus::TextureTarget::_2D, 0, 0, 0, frame->Width, frame->Height, oglplus::PixelDataFormat::RGB, oglplus::PixelDataType::UnsignedByte, frame->imageData);

  oglplus::ErrorCode errorCode = gl.GetError();

  oglplus::Texture::MinFilter(oglplus::TextureTarget::_2D, oglplus::TextureMinFilter::Linear);
  oglplus::Texture::MagFilter(oglplus::TextureTarget::_2D, oglplus::TextureMagFilter::Linear);
  oglplus::Texture::WrapS(oglplus::TextureTarget::_2D, oglplus::TextureWrap::ClampToEdge);
  oglplus::Texture::WrapT(oglplus::TextureTarget::_2D, oglplus::TextureWrap::ClampToEdge);
  oglplus::Texture::GenerateMipmap(oglplus::TextureTarget::_2D);
  oglplus::UniformSampler(prog, "mainTexture").Set(0);

  gl.ClearColor(0.0f, 0.3f, 0.5f, 1.0f);

  for(;;)
  {
    gl.Clear().ColorBuffer();

    rectangle.Bind();
    tex.Bind(oglplus::Texture::Target::_2D);
    gl.DrawArrays(oglplus::PrimitiveType::TriangleStrip, 0, 4);

    SDL_GL_SwapWindow(window);
  }

  delete frame; //[] imageData;

  int i = 0; // For breakpoint
}

int main()
{
  //LibRawTest();

  //OpenCLTest();

  OGLPlusTest();

  return 0;
}

