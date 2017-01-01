#include <cstdio>
#include <sstream>
#include <unordered_map>
#include <gl/gl_headers.h>
#include "mcomp.h"
#include "../engine/engine.h"
#include "../event/sdlevent.h"
#include "../log/termlog.h"
#include "../math/math.h"
#include "../math/matrix.h"
#include "../math/vec4.h"
#include "../render/glrender.h"
#include "../window/sdlwindow.h"

int main(int argc, char **argv)
{
    TermLog log;

    SDLWindow window { log };
    window.set_title("mcomp");

#ifdef __linux__
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        log.Error("Could not initialize glew");
    }

    if (!GLEW_ARB_vertex_array_object) log.Error("ARB_vertex_array_object unsupported");
    if (!GLEW_ARB_framebuffer_object) log.Error("ARB_framebuffer_object unsupported");
#endif

    SDLEvent event { log };

    GLRender render { log };

    Mcomp mcomp { event, log, render, window };

    Engine engine { event, log, mcomp };

    engine.Run();

    return 0;
}
