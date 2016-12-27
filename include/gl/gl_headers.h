#ifndef GL_HEADERS_H
#define GL_HEADERS_H

#ifdef _WIN32
    #include <gl/glew.h>
    #include <gl/wglew.h>
    #include <gl/gl.h>
#elif __APPLE__
    #include <OpenGL/gl3.h>
#endif

#endif
