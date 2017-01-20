#include <cstdio>
#include <cstring>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char** argv) {
  auto sock_id = socket(PF_INET, SOCK_DGRAM, 0);
  if (sock_id == -1) {
    std::printf("Could not create socket");
    return 1;
  }
  if (fcntl(sock_id, F_SETFL, O_NONBLOCK) == -1) {
    std::printf("Error setting nonblocking flag");
    return 1;
  }

  sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(26000);
  inet_aton("127.0.0.1", &addr.sin_addr);
  std::memset(&addr.sin_zero, 0, sizeof(addr.sin_zero));
  if (bind(sock_id, (sockaddr*) &addr, sizeof(sockaddr_in)) != 0) {
    perror("Could not bind socket");
    return 1;
  }

  auto buf = new char[256];
  for (;;) {
    sockaddr_in addr_in;
    socklen_t addr_len { sizeof(addr_in) };
    if (recvfrom(sock_id,
                 buf,
                 sizeof(char) * 256,
                 0,
                 (sockaddr*) &addr_in,
                 &addr_len) == -1) {
      if (errno == EAGAIN) {
        continue;
      } else {
        perror(NULL);
      }
    } else {
      printf("%s", buf);
      break;
    }
  }

  close(sock_id);

  return 0;
}
