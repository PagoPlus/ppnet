#include <string>
#include <iostream>

#include <Arduino.h>

#include "hexdump.hpp"

class FakeSerial : public Stream
{
public:
  FakeSerial() : Stream()
  {
    _written = false;
  }

  virtual int available(void) override
  {
    return static_cast<int>(_transmittedData.size());
  }

  virtual int peek(void) override
  {
    if (available() > 0)
    {
      return _transmittedData[0];
    }
    return -1;
  }

  virtual int read(void) override
  {
    if (available() > 0)
    {
      char c = _transmittedData[0];
      _transmittedData.erase(_transmittedData.begin());
      return c;
    }
    return -1;
  }

  virtual size_t write(uint8_t data) override
  {
    _transmittedData.push_back(static_cast<uint8_t>(data));
    _written = true;
    return 1;
  }

  virtual size_t write(const uint8_t *buffer, size_t size) override
  {
    std::cout << "Writing ";
    std::cout << std::dec << size;
    std::cout << " bytes:" << std::endl << Hexdump(buffer, size) << std::endl;

    for (size_t i = 0; i < size; i++)
    {
      _transmittedData.push_back(static_cast<uint8_t>(buffer[i]));
    }
    _written = true;
    return size;
  }

  std::vector<uint8_t> getTransmittedData()
  {
    return _transmittedData;
  }

  void clearTransmittedData()
  {
    _transmittedData.clear();
  }

private:
  std::vector<uint8_t> _transmittedData;
  bool _written = false;
};