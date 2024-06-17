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

#define ASSERT_DATA_EQUALS(value, ...)                                                           \
  do                                                                                             \
  {                                                                                              \
    std::vector<uint8_t> expected = {__VA_ARGS__};                                               \
    ASSERT_GT(value.size(), 0) << "Value size is zero";                                          \
    ASSERT_EQ(value.size(), expected.size()) << "Sizes do not match";                            \
    for (size_t i = 0; i < value.size() && i < expected.size(); i++)                             \
    {                                                                                            \
      std::cout << "Comparing value[" << i << "]=" << static_cast<int>(value[i])                 \
                << " with expected[" << i << "]=" << static_cast<int>(expected[i]) << std::endl; \
      ASSERT_EQ(static_cast<uint8_t>(value[i]), expected[i]);                                    \
    }                                                                                            \
  } while (0)

TEST_F(MessageEncodingTest, encode_HelloMessage)
{
  FakeSerial serial;
  PPNetwork::PPNet ppnet(&serial);
  PPNetwork::Message::HelloMessage msg;
  memset(&msg, 0x00, sizeof(msg));

  msg.uniqueId = "TestRunner";
  msg.boardIdentifier = "Tester";
  msg.version = 0x1234;
  msg.boardVersion = 0x4321;
  msg.bootId = 0x5353456;
  msg.ppnetVersion = 0x00;
  ASSERT_EQ(ppnet.WriteMessage(msg), 32);
  ASSERT_DATA_EQUALS(serial.getTransmittedData(), {0x01,
                                                   0x96, 0xaa, 0x54, 0x65, 0x73, 0x74, 0x52, 0x75, 0x6e, 0x6e, 0x65, 0x72, 0xa6, 0x54, 0x65, 0x73,
                                                   0x74, 0x65, 0x72, 0xcd, 0x12, 0x34, 0xcd, 0x43, 0x21, 0xce, 0x05, 0x35, 0x34, 0x56,
                                                   // NOTE! We've set this value to 0x00, but it is always overriden to the current version of ppnet
                                                   0x01});
  serial.clearTransmittedData();
}

TEST_F(MessageEncodingTest, encode_SingleCounterMessage)
{
  FakeSerial serial;
  PPNetwork::PPNet ppnet(&serial);
  PPNetwork::Message::SingleCounterMessage msg;
  memset(&msg, 0x00, sizeof(msg));

  msg.kind = "foo";
  msg.value = 1;
  ASSERT_EQ(ppnet.WriteMessage(msg), 9);
  ASSERT_DATA_EQUALS(serial.getTransmittedData(), {0x02, 0x94, 0xa3, 0x66, 0x6f, 0x6f, 0x01, 0x00, 0x00});
  serial.clearTransmittedData();

  msg.kind = "bar";
  msg.value = 42;
  msg.duration_ms = 1500;
  ASSERT_EQ(ppnet.WriteMessage(msg), 11);
  ASSERT_DATA_EQUALS(serial.getTransmittedData(), {0x02, 0x94, 0xa3, 0x62, 0x61, 0x72, 0x2a, 0x00, 0xcd, 0x05, 0xdc});
  serial.clearTransmittedData();

  msg.kind = "zaz";
  msg.value = 42;
  msg.pulses = 42424242;
  msg.duration_ms = 1500;
  ASSERT_EQ(ppnet.WriteMessage(msg), 15);
  ASSERT_DATA_EQUALS(serial.getTransmittedData(), {0x02, 0x94, 0xa3, 0x7a, 0x61, 0x7a, 0x2a, 0xce, 0x02, 0x87, 0x57, 0xb2, 0xcd, 0x05, 0xdc});
  serial.clearTransmittedData();
}
