#include <cstdint>
#include <vector>
#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

/************************************************************************************
 These two functions are copied from https://gist.github.com/barrysteyn/7308212

   - calcDecodeLength
   - Base64Decode

 https://gist.github.com/barrysteyn/7308212#license
 ************************************************************************************/

size_t calcDecodeLength(
    const char *b64input) { // Calculates the length of a decoded string
  size_t len = strlen(b64input), padding = 0;

  if (b64input[len - 1] == '=' &&
      b64input[len - 2] == '=') // last two chars are =
    padding = 2;
  else if (b64input[len - 1] == '=') // last char is =
    padding = 1;

  return (len * 3) / 4 - padding;
}

int Base64Decode(char *b64message, unsigned char **buffer,
                 size_t *length) { // Decodes a base64 encoded string
  BIO *bio, *b64;

  int decodeLen = calcDecodeLength(b64message);
  *buffer = (unsigned char *)malloc(decodeLen + 1);
  (*buffer)[decodeLen] = '\0';

  bio = BIO_new_mem_buf(b64message, -1);
  b64 = BIO_new(BIO_f_base64());
  bio = BIO_push(b64, bio);

  BIO_set_flags(bio,
                BIO_FLAGS_BASE64_NO_NL); // Do not use newlines to flush buffer
  *length = BIO_read(bio, *buffer, strlen(b64message));
  assert(*length == decodeLen); // length should equal decodeLen, else something
                                // went horribly wrong
  BIO_free_all(bio);

  return (0); // success
}

/************************************************************************************
 The implementation of the following logic is inspired by

   - http://blog.tenhou.net/article/30503297.html
   - http://integral001.blog.fc2.com/blog-entry-29.html
   - http://integral001.blog.fc2.com/blog-entry-42.html
   - https://github.com/tomohxx/tenhou-tile-wall

 ************************************************************************************/

#include "mt19937ar.c"

std::vector<std::pair<std::vector<int>, std::vector<int>>> reproduce(char *seed,
                                                                     int num) {
  unsigned long rt_seed[624];
  unsigned char *decoded; std::size_t s;
  Base64Decode(seed, &decoded, &s);
  for (int i = 0; i < 624; i++)
    rt_seed[i] = (decoded[4 * i] << 24) | (decoded[4 * i + 1] << 16) |
                 (decoded[4 * i + 2] << 8) | decoded[4 * i + 3];
  for (unsigned long &i : rt_seed) i = __builtin_bswap32(i);
  init_by_array(rt_seed, sizeof(rt_seed) / sizeof(*rt_seed));

  std::vector<std::pair<std::vector<int>, std::vector<int>>> results;
  for (int n = 0; n < num; ++n) {
    std::uint32_t rnd[SHA512_DIGEST_LENGTH / sizeof(std::uint32_t) * 9];
    std::uint32_t src[sizeof(rnd) / sizeof(*rnd) * 2];

    for (int i = 0; i < sizeof(src) / sizeof(*src); ++i) src[i] = genrand_int32();
    for (int i = 0; i < sizeof(rnd) / SHA512_DIGEST_LENGTH; ++i) {
      SHA512_CTX ctx;
      SHA512_Init(&ctx);
      SHA512_Update(&ctx, (std::uint8_t *)src + i * SHA512_DIGEST_LENGTH * 2,
                    SHA512_DIGEST_LENGTH * 2);
      SHA512_Final((std::uint8_t *)rnd + i * SHA512_DIGEST_LENGTH, &ctx);
    }

    int wall[136];
    for (int i = 0; i < 136; ++i) wall[i] = i;
    for (int i = 0; i < 136 - 1; ++i) std::swap(wall[i], wall[i + (rnd[i] % (136 - i))]);

    std::vector<int> tiles;
    for (int i : wall) tiles.emplace_back(i);
    std::vector<int> dices = {(int)(rnd[135] % 6 + 1), (int)(rnd[136] % 6 + 1)};
    results.emplace_back(tiles, dices);
  }

  return results;
}

PYBIND11_MODULE(tenhou_wall_reproducer, m) {
  m.doc() = "tenhou_wall_reproducer";
  m.def("reproduce", &reproduce, "Reproduce wall and dices from seed.");
}
