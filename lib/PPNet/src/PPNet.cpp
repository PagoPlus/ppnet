#include "PPNet.h"

#include <variant>

using namespace PPNetwork;
using namespace PPNetwork::Message;

#pragma GCC diagnostic error "-Wswitch-enum"

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
    return true;
  default:
    return false;
  }
}

size_t PPNet::WriteMessage(AnyMessage msg)
{
  this->packer.clear();

  MessageType type;

  auto visitor = [&](auto &&arg)
  {
    using T = std::decay_t<decltype(arg)>;
    if constexpr (std::is_same_v<T, SingleCounterMessage>)
    {
      type = MessageType::SingleCounterMessage;
      this->packer.pack(std::forward<decltype(arg)>(arg));
    }
    else
    {
      static_assert(always_false<T>::value, "Unhandled type in WriteMessage");
    }
  };
  std::visit(visitor, msg);

  // calculate package size
  auto totalSize = this->packer.size() + 3;
  assert(totalSize < 255);

  switch (this->targetType)
  {
  case WriteTargetType::RAW:
    this->output->write(static_cast<uint8_t>(MessageType::SingleCounterMessage));
    this->output->write(packer.data(), packer.size());
  case WriteTargetType::SUNTECH:
    this->output->write(static_cast<uint8_t>(MessageType::SingleCounterMessage));
    this->output->write(packer.data(), packer.size());
    this->output->write("\r\n");
  }

  return totalSize;
}
