#include <gtest/gtest.h>

#include <string>
#include <variant>
#include <iostream>
#include <sstream>

#include "Base64.h"

using namespace PPNetwork::Utils;

class Base64Test : public ::testing::Test
{
protected:
  void SetUp() override
  {}

  void TearDown() override
  {}
};

TEST_F(Base64Test, encode)
{
  auto encoded = Base64::encode("hello");
  ASSERT_STREQ(encoded.c_str(), "aGVsbG8=");
}

TEST_F(Base64Test, decode)
{
  MsgPack::str_t out;
  bool isDecoded = Base64::decode("aGVsbG8=", out);

  ASSERT_TRUE(isDecoded);
  ASSERT_STREQ(out.c_str(), "hello");
}

TEST_F(Base64Test, encoded_size)
{
  ASSERT_EQ(Base64::encoded_size("hello"), 8);
}