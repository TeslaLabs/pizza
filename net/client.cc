#include <cstdio>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char** argv) {
  auto sock_id = socket(PF_INET, SOCK_DGRAM, 0);
  if (sock_id == -1) {
    perror("Could not create socket");
    return 1;
  }

  sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(26000);
  inet_aton("192.168.1.3", &addr.sin_addr);
  std::memset(&addr.sin_zero, 0, sizeof(addr.sin_zero));

  auto buf = new char[256];
  std::sprintf(buf, "Hello!\n");
  auto res = sendto(sock_id,
                    (void*) buf,
                    sizeof(char) * 256,
                    0,
                    (sockaddr*) &addr,
                    sizeof(sockaddr_in));
  if (res == -1) {
    perror("Could not send packet");
  }

  close(sock_id);
  return 0;
}
