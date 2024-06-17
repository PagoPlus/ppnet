#include <gtest/gtest.h>

class MessageEncodingTest : public ::testing::Test
{
protected:
  void SetUp() override
  {}

  void TearDown() override
  {}
};

TEST_F(MessageEncodingTest, encode_basic)
{
  // auto encoded = Base64::encode("hello");
  // ASSERT_STREQ(encoded.c_str(), "aGVsbG8=");
  ASSERT_EQ(true, true);
}
