#include <cstdio>
#include <string>
#include "mcomp.h"
#include "../args/args.h"
#include "../engine/engine.h"
#include "../event/sdlevent.h"
#include "../log/termlog.h"
#include "../render/glrender.h"
#include "../timer/timer.h"
#include "../window/sdlwindow.h"

int main(int argc, char** argv) {
  Args args { argc, argv };

  TermLog log;

  int i;
  if (args.Has("-port", &i)) {
    auto port_num = args[i + 1];
    if (port_num) std::printf("port_num: %d\n", std::stoi(port_num));
  }

  SdlWindow window { log };

  SdlEvent event { log };

  GLRender render { log, window };
  if (!render.Initialize()) {
    log.Error("Could not initialize renderer");
    return 1;
  }

  window.set_resize_func(render.GetResizeFunction());

  Mcomp mcomp { event, log, render, window };

  Timer timer;

  Engine engine { event, log, mcomp, timer };
  engine.Run();

  // sleep(2);

  return 0;
}
