#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include "blake3_bindings.h"

void bail(const char *message) {
  printf("%s\n", message);
  exit(1);
}

int main(int argc, char **argv) {
  if (argc != 2) {
    bail("usage:  ./test <FILE>");
  }

  int fd = open(argv[1], O_RDONLY);
  if (fd == -1) {
    bail("failed to open file");
  }

  struct stat stat_out;
  if (fstat(fd, &stat_out) == -1) {
    bail("failed to stat file");
  }

  uint8_t *mmap_addr =
      mmap(NULL, stat_out.st_size, PROT_READ, MAP_SHARED, fd, 0);
  if (mmap_addr == MAP_FAILED) {
    bail("failed to mmap file");
  }

  blake3_hasher *hasher = blake3_hasher_new();
  blake3_hasher_update(hasher, mmap_addr, stat_out.st_size);
  uint8_t out[32];
  blake3_hasher_finalize(hasher, &out);
  for (size_t i = 0; i < 32; i++) {
    printf("%02x", (int)out[i]);
  }
  printf("\n");
  blake3_hasher_free(hasher);

  if (munmap(mmap_addr, stat_out.st_size) != 0) {
    bail("munmap failed");
  }
  if (close(fd)) {
    bail("close failed");
  }

  return 0;
}
