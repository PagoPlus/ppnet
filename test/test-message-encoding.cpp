#include <gtest/gtest.h>

#include <PPNet.h>
#include <Arduino.h>

#include "fake-serial.hpp"
#include "hexdump.hpp"

class MessageEncodingTest : public ::testing::Test
{
protected:
  void SetUp() override
  {
  }

  void TearDown() override
  {
  }
};

// std::cout << Hexdump(data.c_str(), data.size()) << std::endl;

#define ASSERT_DATA_EQUALS(value, ...) \
  do { \
    std::vector<uint8_t> expected(std::begin(__VA_ARGS__), std::end(__VA_ARGS__)); \
    ASSERT_GT(value.size(), 0); \
    auto val = value.c_str(); \
    for (size_t i = 0; i < value.size() && i < expected.size(); i++) { \
      ASSERT_EQ(static_cast<uint8_t>(val[i]), expected[i]); \
    } \
  } while (0)

TEST_F(MessageEncodingTest, encode_SingleCounterMessage)
{
  FakeSerial serial;
  PPNetwork::PPNet ppnet(&serial);
  PPNetwork::Message::SingleCounterMessage msg;

  msg.kind = "foo";
  msg.value = 1;
  ASSERT_EQ(ppnet.WriteMessage(msg), 10);
  ASSERT_DATA_EQUALS(serial.getTransmittedData(), {0x01, 0x94, 0xa3, 0x66, 0x6f, 0x6f, 0x01, 0x10, 0xcc, 0xf8});
  serial.clearTransmittedData();

  msg.kind = "bar";
  msg.value = 42;
  msg.duration_ms = 1500;
  ASSERT_EQ(ppnet.WriteMessage(msg), 11);
  ASSERT_DATA_EQUALS(serial.getTransmittedData(), {0x01, 0x94, 0xa3, 0x62, 0x61, 0x72, 0x2a, 0x10, 0xcd, 0x05, 0xdc});
  serial.clearTransmittedData();

  msg.kind = "zaz";
  msg.value = 42;
  msg.pulses = 42424242;
  msg.duration_ms = 1500;
  ASSERT_EQ(ppnet.WriteMessage(msg), 15);
  ASSERT_DATA_EQUALS(serial.getTransmittedData(), {0x01, 0x94, 0xa3, 0x7a, 0x61, 0x7a, 0x2a, 0xce, 0x02, 0x87, 0x57, 0xb2, 0xcd, 0x05, 0xdc});
  serial.clearTransmittedData();
}
