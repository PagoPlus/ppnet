#include <gtest/gtest.h>

#include "utils/adler.h"

#include "hexdump.hpp"

class AdlerTest : public ::testing::Test
{
protected:
  void SetUp() override
  {
  }

  void TearDown() override
  {
  }
};

TEST_F(AdlerTest, calculate)
{
  std::vector<uint8_t> data = {0x01, 0x02, 0x03, 0x04, 0x05};
  uint32_t checksum = ppnet::utils::adler32(data);
  ASSERT_EQ(checksum, 2621456);
}

TEST_F(AdlerTest, calculate_reverse)
{
  std::vector<uint8_t> data = {0x05, 0x04, 0x03, 0x02, 0x01};
  uint32_t checksum = ppnet::utils::adler32(data);
  ASSERT_EQ(checksum, 3932176);
}