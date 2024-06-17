#include <gtest/gtest.h>

#include <PPNet.h>
#include <Arduino.h>

class MessageEncodingTest : public ::testing::Test
{
protected:
  void SetUp() override
  {}

  void TearDown() override
  {}
};

TEST_F(MessageEncodingTest, encode_SingleCounterMessage)
{
  PPNetwork::PPNet ppnet(&Serial);
  PPNetwork::Message::SingleCounterMessage msg1 {
    .kind = "foo",
    .value = 1,
  };
  ASSERT_EQ(ppnet.WriteMessage(msg1), 11);

  PPNetwork::Message::SingleCounterMessage msg2 {
    .kind = "bar",
    .value = 42,
    .duration_ms = 1500,
  };
  ASSERT_EQ(ppnet.WriteMessage(msg2), 13);

  PPNetwork::Message::SingleCounterMessage msg3 {
    .kind = "bar",
    .value = 42,
    .pulses = 42424242,
    .duration_ms = 1500,
  };
  ASSERT_EQ(ppnet.WriteMessage(msg3), 17);
}
