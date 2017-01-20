#include "mcomp.h"
#include "../engine/engine.h"
#include "../event/sdlevent.h"
#include "../log/termlog.h"
#include "../render/glrender.h"
#include "../timer/timer.h"
#include "../window/sdlwindow.h"

#include <cstdio>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

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

  Timer timer;

  Engine engine { event, log, mcomp, timer };
  // engine.Run();

  // sleep(2);

  auto sock_id = socket(PF_INET, SOCK_DGRAM, 0);
  if (sock_id == -1) {
    log.Error("Could not create socket");
    return 1;
  }

  sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(26000);
  inet_aton("192.168.1.3", &addr.sin_addr);
  std::memset(&addr.sin_zero, 0, sizeof(addr.sin_zero));

  auto buf = new char[256];
  std::sprintf(buf, "Hello!\n");
  if (sendto(sock_id,
             (void*) buf,
             sizeof(char) * 256,
             0,
             (sockaddr*) &addr,
             sizeof(sockaddr_in)) == -1) {
    perror("Could not send");
  }

  close(sock_id);

  return 0;
}
