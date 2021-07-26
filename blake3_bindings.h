#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct blake3_hasher blake3_hasher;

struct blake3_hasher *blake3_hasher_new(void);

void blake3_hasher_update(struct blake3_hasher *hasher, const uint8_t *buf, uintptr_t len);

void blake3_hasher_finalize(const struct blake3_hasher *hasher, uint8_t (*out)[32]);

void blake3_hasher_free(struct blake3_hasher *hasher);
