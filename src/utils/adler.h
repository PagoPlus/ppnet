#ifndef _PPNET_UTILS_ADLER_H
#define _PPNET_UTILS_ADLER_H

#include <cstdint>

namespace PPNetwork::Utils
{
  uint32_t adler32(const uint8_t *data, size_t length)
  {
    constexpr uint32_t MOD_ADLER = 65521;
    uint32_t a = 1, b = 0;

    if (data == nullptr || length == 0)
      return 1;

    for (size_t i = 0; i < length; ++i)
    {
      a = (a + data[i]) % MOD_ADLER;
      b = (b + a) % MOD_ADLER;
    }

    return (b << 16) | a;
  }
} // namespace PPNetwork::Utils

#endif // _PPNET_UTILS_ADLER_H
