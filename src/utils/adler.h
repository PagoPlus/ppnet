#ifndef _PPNET_UTILS_ADLER_H
#define _PPNET_UTILS_ADLER_H

#include <vector>
#include <stdint.h>

namespace PPNetwork::Utils
{
  uint32_t adler32(const std::vector<uint8_t> &data)
  {
    constexpr uint32_t MOD_ADLER = 65521;
    uint32_t a = 1, b = 0;

    if (data.empty()) return 1;

    for (uint8_t byte : data)
    {
      a = (a + byte) % MOD_ADLER;
      b = (b + a) % MOD_ADLER;
    }

    return (b << 16) | a;
  }
} // ppnet::utils

#endif // _PPNET_UTILS_ADLER_H