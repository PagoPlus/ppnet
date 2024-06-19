#ifndef _PPNET_UTILS_ADLER_H
#define _PPNET_UTILS_ADLER_H

#include <cstdint>

namespace PPNetwork::Utils
{
  uint32_t adler32(const uint8_t *data, size_t length);
  void split(uint32_t data, uint8_t* bytes);
} // namespace PPNetwork::Utils

#endif // _PPNET_UTILS_ADLER_H
