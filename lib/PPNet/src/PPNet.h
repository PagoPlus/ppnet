#ifndef _PPNET_H
#define _PPNET_H

#include <variant>
#include <iostream>
#include <string>

#include <MsgPack.h>
#include <Stream.h>

/**
 * @namespace PPNetwork
 * @brief PagoPlus Network Communication
 * 
 * This namespace contains the components for preparing and sending data over serial and GPS.
 */
namespace PPNetwork
{

  /**
   * @namespace Message
   * @brief Messages for PPNet
   * 
   * This namespace contains all of the messages available to be sent to PagoPlus.
   */
  namespace Message
  {
    struct SingleCounterMessage {
      /**
       * @brief The kind (identifier) of this counter.
       */
      MsgPack::str_t kind;
      /**
       * @brief The current value of this counter.
       * Optional. If not defined, then `1` is used.
       */
      uint32_t value;
      /**
       * @brief The quantity of pulses (internal events) needed to create this counter event.
       * Optional.
       */
      uint32_t pulses;
      /**
       * @brief The duration, in milliseconds, of this event.
       * Optional.
       */
      uint32_t duration_ms;

      MSGPACK_DEFINE(kind, value, pulses, duration_ms);
    };
  }

  /**
   * @brief A variant type that can hold all possible messages sent by the system.
   */
  using AnyMessage = std::variant<Message::SingleCounterMessage>;

  /**
   * @brief Enumeration for the types of messages.
   * 
   * Each enumerator represents a specific type of message and its associated code,
   * used internally within the PagoPlus Network Communication layer.
   */
  enum class MessageType : uint8_t {
    SingleCounterMessage = 0x01,
  };

  /**
   * @brief Main class for PPNet.
   */
  class PPNet {
    public:
      PPNet(Stream* output) {
        this->output = output;
      };
      ~PPNet() {};
      /**
       * @brief Write a message 
       */
      size_t WriteMessage(AnyMessage msg);
    private:
      Stream* output;
      MsgPack::Packer packer;
  };
}

#endif /* _PPNET_H */
