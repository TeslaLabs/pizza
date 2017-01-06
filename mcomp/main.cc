#include "mcomp.h"
#include "../engine/engine.h"
#include "../event/sdlevent.h"
#include "../log/termlog.h"
#include "../render/glrender.h"
#include "../window/sdlwindow.h"

int main(int argc, char** argv) {
  TermLog log;

  SdlWindow window { log };
  window.set_title("mcomp");

  SdlEvent event { log };

  GLRender render { log, window };
  if (!render.Initialize()) {
    log.Error("Could not initialize renderer");
    return 1;
  }

  Mcomp mcomp { event, log, render, window };

  Timer timer;

  Engine engine { event, log, mcomp, timer };
  engine.Run();

  return 0;
}
