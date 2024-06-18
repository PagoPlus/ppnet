#include <Arduino.h>

#include "utils/adler.h"

uint32_t PPNetwork::Utils::adler32(const uint8_t *data, size_t length)
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

void PPNetwork::Utils::split(uint32_t data, uint8_t* bytes)
{
  bytes[0] = (data >> 24) & 0xFF; // Most significant byte
  bytes[1] = (data >> 16) & 0xFF;
  bytes[2] = (data >> 8) & 0xFF;
  bytes[3] = data & 0xFF; // Least significant byte
}