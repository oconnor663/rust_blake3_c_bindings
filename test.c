#include <stddef.h>
#include <stdio.h>

#include "blake3_bindings.h"

int main() {
  blake3_hasher *hasher = blake3_hasher_new();
  blake3_hasher_update(hasher, (const uint8_t *)"foo", 3);
  uint8_t out[32];
  blake3_hasher_finalize(hasher, &out);
  for (size_t i = 0; i < 32; i++) {
    printf("%02x", (int)out[i]);
  }
  printf("\n");
  blake3_hasher_free(hasher);
  return 0;
}
