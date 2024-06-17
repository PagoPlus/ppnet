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
  PPNetwork::Message::SingleCounterMessage msg {
    .kind = "foo",
    .value = 1,
  };

  ASSERT_GT(ppnet.WriteMessage(msg), 5);
}
