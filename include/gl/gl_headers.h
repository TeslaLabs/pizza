#ifndef GL_HEADERS_H
#define GL_HEADERS_H

#ifdef _WIN32
  #include <gl/glew.h>
  #include <gl/wglew.h>
  #include <gl/gl.h>
#elif __APPLE__
  // FIXME: We might need to fix this to <OpenGL/gl.h>
  // #include <gl/glew.h>
  #include <OpenGL/gl.h>
  #define glGenVertexArrays glGenVertexArraysAPPLE
  #define glDeleteVertexArrays glDeleteVertexArraysAPPLE
  #define glBindVertexArray glBindVertexArrayAPPLE
#elif __linux__
  #include <GL/glew.h>
  #include <GL/gl.h>
#endif

#endif
