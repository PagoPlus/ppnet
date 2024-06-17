#include "PPNet.h"

#include <variant>

using namespace PPNetwork;
using namespace PPNetwork::Message;

template<typename... Ts> struct always_false : std::false_type {};

size_t PPNet::WriteMessage(AnyMessage msg)
{
  SyncMessage syncMsg;

  auto visitor = [&](auto &&arg)
  {
    using T = std::decay_t<decltype(arg)>;
    if constexpr (std::is_same_v<T, SingleCounterMessage>)
    {
      syncMsg.code = MessageType::SingleCounterMessage;
      syncMsg.data = std::forward<decltype(arg)>(arg);
    }
    else
    {
      static_assert(always_false<T>::value, "Unhandled type in WriteMessage");
    }

    return 0;
  };

  return std::visit(visitor, msg);
}
