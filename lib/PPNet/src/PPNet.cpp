#include "PPNet.h"

using namespace PPNetwork;
using namespace PPNetwork::Message;

size_t PPNet::WriteMessage(AnyMessage msg)
{
  std::visit([](auto&& arg) {
    // std::cout << "Writing message: " << arg << std::endl;
  }, msg);
  return 0;
}
