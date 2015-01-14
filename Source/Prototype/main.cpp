#include <iostream>
#include <vector>

#include "gl3w.h"
#include <SDL2/SDL.h>

#include <oglplus/gl.hpp>
//#include <oglplus/lib.hpp>

#include <oglplus/context.hpp>

//#include <oglplus/all.hpp>

//#define GLCOREARB_PROTOTYPES 1
//#include <GL/glcorearb.h>
//#include <GL/gl.h>

//#include "opencltest.h"
//#include "librawtest.h"

using namespace std;

class IPlugin
{
  string _name;

public:
  IPlugin(string name)
  {
    _name = name;
  }

  string GetName()
  {
    return _name;
  }
};

// Dummy struct for now
struct Frame
{

};

class IProcessingPlugin : IPlugin
{
public:
  virtual void Process(Frame* input, Frame* output) = 0;
};

class SimnplProcessingPlugin : IPlugin
{
public:
  virtual void Process(/*Frame* input, Frame* output*/)
  {
    // Do something
  }
};

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

  string s = string(gl.ShadingLanguageVersion());

  // Notes
  // Get image data
  // Setup chain of plugins with GLSL first
  // Let them process the data
  // Output processed image data with OIIO (simple to use for such things)

  int i = 0; // For breakpoint
}

int main()
{
  //LibRawTest();

  //OpenCLTest();

  OGLPlusTest();

  return 0;
}

