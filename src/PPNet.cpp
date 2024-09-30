#include "PPNet.h"
#include "utils/adler.h"

#include <variant>

using namespace PPNetwork;
using namespace PPNetwork::Message;

#pragma GCC diagnostic error "-Wswitch-enum"
#pragma GCC diagnostic error "-Wswitch"

template <typename... Ts>
struct always_false : std::false_type
{
};

constexpr bool validateWriteTargetType(WriteTargetType type)
{
  switch (type)
  {
  case WriteTargetType::RAW:
  case WriteTargetType::SUNTECH:
  case WriteTargetType::AOVX:
    return true;
  default:
    return false;
  }
}

size_t PPNet::WriteMessage(AnyMessage msg)
{
  MessageType type;
  this->packer.clear();

  auto visitor = [&](auto &&arg)
  {
    using T = std::decay_t<decltype(arg)>;
    if constexpr (std::is_same_v<T, HelloMessage>)
    {
      type = MessageType::HelloMessage;
      HelloMessage newMsg = std::forward<decltype(arg)>(arg);
      newMsg.ppnetVersion = __PPNET_VERSION__;

      assert(strlen(newMsg.uniqueId.c_str()) > 0);
      assert(strlen(newMsg.boardIdentifier.c_str()) > 0);
      assert(newMsg.version > 0);
      assert(newMsg.boardVersion > 0);
      assert(newMsg.ppnetVersion == __PPNET_VERSION__);
      
      this->packer.pack(newMsg);
    }
    else if constexpr (std::is_same_v<T, SingleCounterMessage>)
    {
      type = MessageType::SingleCounterMessage;
      SingleCounterMessage newMsg = std::forward<decltype(arg)>(arg);
      assert(strlen(newMsg.kind.c_str()) > 0);
      if (newMsg.value == 0) {
        newMsg.value = 1;
      }
      
      this->packer.pack(newMsg);
    }
    else
    {
      static_assert(always_false<T>::value, "Unhandled Message type in WriteMessage");
    }
  };
  std::visit(visitor, msg);

  // calculate package size (1=code, 4=checksum, rest=payload)
  auto totalSize = 1 + 4 + this->packer.size();
  assert(totalSize < 255);

  auto checksum = PPNetwork::Utils::adler32(packer.data(), packer.size());
  uint8_t checksum_arr[4] = {0};
  PPNetwork::Utils::split(checksum, checksum_arr);

  switch (this->targetType)
  {
  case WriteTargetType::RAW:
    this->output->write(static_cast<uint8_t>(type));
    this->output->write(checksum_arr, 4);
    this->output->write(packer.data(), packer.size());
    this->output->flush();
    break;
  case WriteTargetType::SUNTECH:
    this->output->write(static_cast<uint8_t>(type));
    this->output->write(checksum_arr, 4);
    this->output->write(packer.data(), packer.size());
    this->output->write("\r\n");
    this->output->flush();
    break;
  case WriteTargetType::AOVX:
    this->output->write(static_cast<uint8_t>(type));
    this->output->write(checksum_arr, 4);
    this->output->write(packer.data(), packer.size());
    this->output->write("\n");
    this->output->flush();
    break;
  }

  return totalSize;
}
