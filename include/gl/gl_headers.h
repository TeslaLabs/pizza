#ifndef GL_HEADERS_H
#define GL_HEADERS_H

#ifdef _WIN32
    #include <gl/glew.h>
    #include <gl/wglew.h>
    #include <gl/gl.h>
#elif __APPLE__
    #include <OpenGL/gl3.h>
#elif __linux__
#include <GL/glew.h>
#include <GL/gl.h>
#endif

#endif
