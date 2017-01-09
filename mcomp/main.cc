#include "mcomp.h"
#include "../engine/engine.h"
#include "../event/sdlevent.h"
#include "../log/termlog.h"
#include "../render/glrender.h"
#include "../window/sdlwindow.h"

#ifdef __APPLE__
  #include "../timer/appletimer.h"
#elif __linux__
  #include "../timer/linuxtimer.h"
#endif

int main(int argc, char** argv) {
  TermLog log;

  SdlWindow window { log };

  SdlEvent event { log };

  GLRender render { log, window };
  if (!render.Initialize()) {
    log.Error("Could not initialize renderer");
    return 1;
  }

  window.set_resize_func(render.GetResizeFunction());

  Mcomp mcomp { event, log, render, window };

#ifdef __APPLE__
  AppleTimer timer;
#elif __linux__
  LinuxTimer timer;
#endif

  Engine engine { event, log, mcomp, timer };
  engine.Run();

  return 0;
}
