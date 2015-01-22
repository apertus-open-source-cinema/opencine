#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <streambuf>

#include "gl3w.h"
#include "timer.h"
#include <SDL2/SDL.h>

#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>
#include <oglplus/bound/texture.hpp>
#include <oglplus/bound/framebuffer.hpp>

#include <OpenImageIO/imageio.h>
OIIO_NAMESPACE_USING

using namespace oglplus;

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
  Timer timer(true);

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

  Context gl;

  int majorVersion = gl.MajorVersion();
  int minorVersion = gl.MinorVersion();

  std::string shadingLanguageVersion = std::string(gl.ShadingLanguageVersion());

  // Notes
  // Get image data
  // Setup chain of plugins with GLSL first
  // Let them process the data
  // Output processed image data with OIIO (simple to use for such things)

  VertexShader vs;
  FragmentShader fs;

  try
  {
    std::string vertexShaderSource = LoadTextFile("basicShader.vert");
    vs.Source(vertexShaderSource);
    vs.Compile();
  }
  catch(Error& err)
  {
    std::cout << err.Log() << std::endl;
  }

  try
  {
    std::string fragmentShaderSource = LoadTextFile("basicShader.frag");
    fs.Source(fragmentShaderSource);
    fs.Compile();
  }
  catch(Error& err)
  {
    std::cout << err.Log() << std::endl;
  }

  Program prog;

  prog.AttachShader(vs);
  prog.AttachShader(fs);

  try
  {
    prog.Link();
    prog.Use();
  }
  catch(Error& err)
  {
    std::cout << err.Log() << std::endl;
  }

  const std::unique_ptr<IProcessingPlugin> pluginA = std::unique_ptr<IProcessingPlugin>(new SimpleProcessingPlugin("PluginA"));

  //unsigned short* imageData = nullptr;
  //unsigned int dataSize = 0;
  Frame* frame = new Frame();
  LoadImage("test.jpg", frame);

  SaveImage("test2.jpg", frame/*, frame->dataSize*/);

  // Processing here
  VertexArray rectangle;
  Buffer verts;
  Buffer texCoords;

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

  verts.Bind(Buffer::Target::Array);
  Buffer::Data(Buffer::Target::Array, rectangleVertices);
  (prog | "Position").Setup<Vec2f>().Enable();

  texCoords.Bind(Buffer::Target::Array);
  Buffer::Data(Buffer::Target::Array, rectangleTexCoords);
  (prog | "vertTexCoord").Setup<Vec2f>().Enable();

  //gl.Disable(Capability::DepthTest);

  int maxTexSize = -1;
  glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTexSize);

  Texture tex;
  tex.Bind(Texture::Target::_2D);

  //Texture::Active(0);
  gl.Bind(TextureTarget::_2D, tex);
  gl.PixelStore(PixelParameter::UnpackAlignment, 1);
  Texture::Image2D(TextureTarget::_2D, 0, PixelDataInternalFormat::RGB, frame->Width, frame->Height, 0, PixelDataFormat::RGB, PixelDataType::UnsignedByte, frame->imageData);
  //Texture::SubImage2D(TextureTarget::_2D, 0, 0, 0, frame->Width, frame->Height, PixelDataFormat::RGB, PixelDataType::UnsignedByte, frame->imageData);

  ErrorCode errorCode = gl.GetError();

  Texture::MinFilter(TextureTarget::_2D, TextureMinFilter::Linear);
  Texture::MagFilter(TextureTarget::_2D, TextureMagFilter::Linear);
  Texture::WrapS(TextureTarget::_2D, TextureWrap::ClampToEdge);
  Texture::WrapT(TextureTarget::_2D, TextureWrap::ClampToEdge);
  Texture::GenerateMipmap(TextureTarget::_2D);
  //UniformSampler(prog, "mainTexture").Set(0);

  Framebuffer fbo;
  DefaultFramebuffer dfb;
  Texture color_tex;

  gl.Bind(TextureTarget::_2D, color_tex);
  //gl.PixelStore(PixelParameter::UnpackAlignment, 1);
  Texture::Image2D(TextureTarget::_2D, 0, PixelDataInternalFormat::RGB, 640, 480, 0, PixelDataFormat::RGB, PixelDataType::UnsignedByte, nullptr);
  Texture::MinFilter(TextureTarget::_2D, TextureMinFilter::Linear);
  Texture::MagFilter(TextureTarget::_2D, TextureMagFilter::Linear);
  Texture::WrapS(TextureTarget::_2D, TextureWrap::ClampToEdge);
  Texture::WrapT(TextureTarget::_2D, TextureWrap::ClampToEdge);
  //Texture::GenerateMipmap(TextureTarget::_2D);

  //Texture::Image2D(TextureTarget::_2D, 0, PixelDataInternalFormat::RGB, frame->Width, frame->Height, 0, PixelDataFormat::RGB, PixelDataType::UnsignedByte, frame->imageData);

//  Texture::Active(1);
// UniformSampler(prog, "mainTexture").Set(0);
// gl.Bound(Texture::Target::Rectangle, color_tex)
// .MinFilter(TextureMinFilter::Linear)
// .MagFilter(TextureMagFilter::Linear)
// .WrapS(TextureWrap::ClampToEdge)
// .WrapT(TextureWrap::ClampToEdge)
// .Image2D(0, PixelDataInternalFormat::RGB, width, height, 0, PixelDataFormat::RGB, PixelDataType::UnsignedByte, nullptr);

  gl.Bind(Framebuffer::Target::Draw, fbo);
  fbo.AttachTexture(Framebuffer::Target::Draw, FramebufferAttachment::Color, color_tex, 0);
  fbo.Complete(Framebuffer::Target::Draw);

  std::cout << "GL setup: " << timer.Elapsed().count() << "ms" << std::endl;

  for(;;)
  {
    //timer.Reset();

    gl.ClearColor(0.0f, 0.3f, 0.5f, 1.0f);
    gl.Bind(Framebuffer::Target::Draw, fbo);
    gl.Clear().ColorBuffer().DepthBuffer();

    //UniformSampler(prog, "mainTexture").Set(0);
    rectangle.Bind();
    tex.Bind(Texture::Target::_2D);
    gl.DrawArrays(PrimitiveType::TriangleStrip, 0, 4);

    gl.Bind(Framebuffer::Target::Draw, dfb);
    gl.ClearColor(0.0f, 0.5f, 0.3f, 1.0f);
    gl.Clear().ColorBuffer().DepthBuffer();

    rectangle.Bind();
    color_tex.Bind(Texture::Target::_2D);
    gl.DrawArrays(PrimitiveType::TriangleStrip, 0, 4);

    SDL_GL_SwapWindow(window);
    //std::cout << "Elapsed: " << timer.Elapsed().count() << "ms" << std::endl;
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

