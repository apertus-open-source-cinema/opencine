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
#include <oglplus/detail/program.hpp>

#include <OpenImageIO/imageio.h>
OIIO_NAMESPACE_USING

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

using namespace oglplus;

class IPlugin
{
public:
  IPlugin()
  {
  }
};

template<typename Interface>
class Factory {
  virtual Interface *create() = 0;
};

/*class Renderer {
  virtual void beginScene() = 0;
  virtual void endScene() = 0;
};
typedef Factory<Renderer> RendererFactory;
*/

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
  IProcessingPlugin()
  {
  }

  virtual void Process(Frame input, Frame* output) = 0;
};

class SimpleProcessingPlugin : public IProcessingPlugin
{
public:
  SimpleProcessingPlugin()
  {
  }

  virtual void Process(Frame input, Frame* output)
  {
    // Do something
  }

  // IPlugin interface
private:
  IPlugin *Create()
  {
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

std::vector<float> GenerateRectangle(float width, float height)
{
  std::vector<float> vertices =
  {
  -width / 2.0f, -height / 2.0f,
  width / 2.0f, -height / 2.0f,
  -width / 2.0f,  height / 2.0f,
  width / 2.0f,  height / 2.0f
  };

  return vertices;
}

typedef Factory<IProcessingPlugin> ProcessingPluginFactory;

#include <type_traits>

template <typename RealType>
class A
{
  static_assert(std::is_same<RealType, double>::value || std::is_same<RealType, float>::value, "Wrong type supplied. Only \"double\" or \"float\" accepted.");
};

enum class ClipType
{
  Test1,
  Test2
};

template<class BaseType> class GenericFactory
{
public:
  template <class T>
  void Register(ClipType type)
  {
    std::function<T*()> func = []() { return new T(); };
    registeredDataProviders.emplace(std::make_pair(type, func));
  }

  BaseType* Get(ClipType type)
  {
    auto it = registeredDataProviders.find(type);

    if (it != registeredDataProviders.end())
    {
      return (*it).second();
    }

    return nullptr;
  }

private:
  std::map<ClipType, std::function<BaseType*()>> registeredDataProviders;
};

TEST_CASE( "PluginFactory test", "[General]" )
{
  REQUIRE(1 == 2);
}

int OGLPlusTest()
{
  GenericFactory<IPlugin> pluginFactory;
  pluginFactory.Register<SimpleProcessingPlugin>(ClipType::Test1);
  pluginFactory.Register<SimpleProcessingPlugin>(ClipType::Test1);

  Catch::Session session;
  session.configData().processName = "Prototype";
  session.run();

  //pluginFactory.Register<A>(ClipType::Test2);
  //ProcessingPluginFactory<SimpleProcessingPlugin> plugin;

  A<float> a;


  Timer timer(true);

  int width = 640, height = 480;
  int status = SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *window = SDL_CreateWindow( "Grapics Application", 0, 0, width, height, SDL_WINDOW_OPENGL);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GLContext glcontext = SDL_GL_CreateContext(window);
  SDL_GL_SetSwapInterval(0);

  gl3wInit();

  if (!gl3wIsSupported(3, 3))
  {
    fprintf(stderr, "OpenGL 3.3 not supported\n");
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

  const std::unique_ptr<IProcessingPlugin> pluginA = std::unique_ptr<IProcessingPlugin>(new SimpleProcessingPlugin());

  //unsigned short* imageData = nullptr;
  //unsigned int dataSize = 0;
  Frame* frame = new Frame();
  LoadImage("color-test-file.jpg", frame);

  //SaveImage("test2.jpg", frame/*, frame->dataSize*/);

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

  //  GLfloat rectangleVertices[8] =
  //  {
  //    -frame->Width / 2.0, -frame->Height / 2.0,
  //     frame->Width / 2.0, -frame->Height / 2.0,
  //    -frame->Width / 2.0,  frame->Height / 2.0,
  //     frame->Width / 2.0,  frame->Height / 2.0
  //  };

  std::vector<float> rectangleVertices = GenerateRectangle(frame->Width / 1000.0f, frame->Height / 1000.0f);

  /*GLfloat rectangleVertices[8] =
  {
  -1.0f, -1.0f,
  1.0f, -1.0f,
  -1.0f,  1.0f,
  1.0f,  1.0f
  };*/

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
  gl.PixelStore(PixelParameter::UnpackAlignment, 1);
  Texture::Image2D(TextureTarget::_2D, 0, PixelDataInternalFormat::RGB, frame->Width, frame->Height, 0, PixelDataFormat::RGB, PixelDataType::UnsignedByte, nullptr);
  Texture::MinFilter(TextureTarget::_2D, TextureMinFilter::Linear);
  Texture::MagFilter(TextureTarget::_2D, TextureMagFilter::Nearest);
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

  //Lazy<ProgramUniform<Mat4f>> projection_matrix, camera_matrix, model_matrix;
  //ProgramUniform<Mat4f> projectionMatrix(prog, "ProjectionMatrix");
  ProgramUniform<Mat4f> cameraMatrix(prog, "CameraMatrix");
  ProgramUniform<Mat4f> modelMatrix(prog, "ModelMatrix");

  float aspectRatio = frame->Width / frame->Height;

  bool imageSaved = false;
  unsigned char* imData = new unsigned char[frame->Width * frame->Height * 3];
  int imageSize = -1;
  //projectionMatrix.Set(CamMatrixf::PerspectiveX(Degrees(60), aspectRatio, 0.1, 100.0));
  //cameraMatrix.Set(CamMatrixf::Ortho(-2  * aspectRatio, 2 * aspectRatio, -2, 2, 0.1, 100.0));
  //modelMatrix.Set(ModelMatrixf::Translation(0.0, 0.0, -12.0));

  float angle = 0.0f;

  gl.Disable(Capability::DepthTest);


  std::vector<IProcessingPlugin> pluginList;

  for(;;)
  {
    //timer.Reset();

    //Render off-screen
    gl.ClearColor(0.0f, 0.3f, 0.5f, 1.0f);
    //gl.Bind(Framebuffer::Target::Draw, fbo);
    gl.Clear().ColorBuffer().DepthBuffer();

    gl.Viewport(frame->Width, frame->Height);

    //projectionMatrix.Set(CamMatrixf::Ortho(-3  * aspectRatio, 3 * aspectRatio, -3, 3, 0.1, 100.0)/*CamMatrixf::PerspectiveX(Degrees(60), aspectRatio, 0.1, 100.0)*/);
    cameraMatrix.Set(CamMatrixf::Ortho(-(frame->Width / 1000.0f) / 2, (frame->Width / 1000.0f) / 2, -(frame->Height / 1000.0f) / 2, (frame->Height / 1000.0f) / 2, -20.0, 20.0));
    modelMatrix.Set(/*ModelMatrixf::RotationZ(Degrees(angle)) * */ ModelMatrixf::Translation(0.0, 0.0, 0.0));

    //UniformSampler(prog, "mainTexture").Set(0);
    rectangle.Bind();
    tex.Bind(Texture::Target::_2D);
    gl.DrawArrays(PrimitiveType::TriangleStrip, 0, 4);

    //Render to screen
    gl.Bind(Framebuffer::Target::Draw, dfb);
    gl.ClearColor(0.0f, 0.5f, 0.3f, 1.0f);
    gl.Clear().ColorBuffer().DepthBuffer();
    gl.Viewport(640, 480);

    //cameraMatrix.Set(CamMatrixf::Ortho(-1  * aspectRatio, 1 * aspectRatio, -1, 1, -1.0, 1.0));
    //modelMatrix.Set(/*ModelMatrixf::RotationZ(Degrees(angle)) * */ ModelMatrixf::Translation(0.0, 0.0, 0.0));

    //Flip drawing to correct FBO direction
    cameraMatrix.Set(CamMatrixf::Ortho(-(frame->Width / 1000.0f) / 2, (frame->Width / 1000.0f) / 2, (frame->Height / 1000.0f) / 2, -(frame->Height / 1000.0f) / 2, -20.0, 20.0));
    modelMatrix.Set(/*ModelMatrixf::RotationZ(Degrees(angle)) * */ ModelMatrixf::Translation(0.0, 0.0, 0.0));

    rectangle.Bind();
    color_tex.Bind(Texture::Target::_2D);

    if(!imageSaved)
    {
      gl.PixelStore(PixelParameter::PackAlignment, 1);
      Texture::GetImage(TextureTarget::_2D, 0, PixelDataFormat::RGB, oglplus::PixelDataType::UnsignedByte, imageSize, imData);
      Frame f;
      f.imageData = imData;
      f.dataSize = imageSize;
      f.Width = frame->Width;
      f.Height = frame->Height;

      SaveImage("fbo_output.png", &f);
      imageSaved = true;

      /*int total = -1;
      glGetProgramiv(3, GL_ACTIVE_UNIFORMS, &total );
      for(int i=0; i<total; ++i)
      {
          int name_len=-1, num=-1;
          GLenum type = GL_ZERO;
          char name[100];
          glGetActiveUniform( 3, GLuint(i), sizeof(name)-1, &name_len, &num, &type, name );
          name[name_len] = 0;
          //GLuint location = glGetUniformLocation( program_id, name );
          std::cout << "Uniform: " << name << " Type: " << type << std::endl;
      }*/

      int uniformCount = prog.ActiveUniforms().Size();

      //aux::ActiveVariableInfo uniform = prog.ActiveUniforms().At(0);

      for(unsigned int uniformIndex = 0; uniformIndex < uniformCount; uniformIndex++)
      {
        aux::ActiveVariableInfo uniform = prog.ActiveUniforms().At(uniformIndex);
        std::cout << "Uniform: " << uniform.Name() << " Type: " << (int)uniform.Type() << std::endl;
      }

      uniformCount = prog.ActiveAttribs().Size();

      //aux::ActiveVariableInfo uniform = prog.ActiveUniforms().At(0);

      for(unsigned int uniformIndex = 0; uniformIndex < uniformCount; uniformIndex++)
      {
        aux::ActiveVariableInfo uniform = prog.ActiveAttribs().At(uniformIndex);
        std::cout << "Uniform: " << uniform.Name() << " Type: " << (int)uniform.Type() << std::endl;
      }


      int i = 0;
    }

    gl.DrawArrays(PrimitiveType::TriangleStrip, 0, 4);


    SDL_GL_SwapWindow(window);
    angle += 0.01;
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

