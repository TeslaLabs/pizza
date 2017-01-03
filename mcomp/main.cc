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

  GLRender render { log };

  Mcomp mcomp { event, log, render, window };

  Engine engine { event, log, mcomp };
  engine.Run();

  return 0;
}
