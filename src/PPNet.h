#ifndef _PPNET_H
#define _PPNET_H

#define __PPNET_VERSION__ static_cast<uint32_t>(0000001)

#include <variant>
#include <iostream>
#include <string>

#include <MsgPack.h>
#include <Stream.h>

static_assert(__cplusplus >= 201703L, "PPNet needs at least a C++17 compatible compiler.");

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
    struct HelloMessage
    {
      /**
       * @brief The unique ID of this device.
       */
      MsgPack::str_t uniqueId;
      /**
       * @brief The identifier for this kind of board. Example: "MedIO".
       *
       * Used internally to process data specifically for each kind of board.
       */
      MsgPack::str_t boardIdentifier;
      /**
       * @brief The current software version.
       *
       * Typically, git commit ID is used.
       */
      uint32_t version;
      /**
       * @brief The current board design version.
       *
       * Used by the server to identify different versions of boards and change its parsing accordingly.
       */
      uint32_t boardVersion;
      /**
       * @brief A random number, set at boot.
       * 
       * Used by the server to detect when the board was restarted.
       * 
       * @note On ESP32 platforms, it is recommended to turn ON the WiFi to feed the random number generator.
       *       Read more [here](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/random.html).
       */
      uint32_t bootId;
      /**
       * @brief The version of PPNet library.
       * 
       * This value is automatically set, and should not be manually set.
       */
      uint32_t ppnetVersion;

      MSGPACK_DEFINE(uniqueId, boardIdentifier, version, boardVersion, bootId, ppnetVersion);
    };

    /**
     * @brief Message for sending a single counter value.
     *
     * The value is expected to be the current value (and NOT the accumulative value).
     *
     * Since this message is sent several times, it is recommended to use a short `kind` value to not
     * occupy much data when transferring.
     */
    struct SingleCounterMessage
    {
      /**
       * @brief The kind (identifier) of this counter.
       *
       * Example: `"MIO/9D"`, meaning: MedIO namespace, 9D as the identifier (for 9D counter).
       *
       * It is recommended to prepend a namespace (no more than 3-5 chars), so messages can easily be
       * separated and aggrupated.
       *
       * The namespace is commonly divided by a `/` character.
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
  using AnyMessage = std::variant<Message::HelloMessage, Message::SingleCounterMessage>;

  /**
   * @brief Enumeration for the types of messages.
   *
   * Each enumerator represents a specific type of message and its associated code,
   * used internally within the PagoPlus Network Communication layer.
   */
  enum class MessageType : uint8_t
  {
    HelloMessage = 0x01,
    SingleCounterMessage = 0x02,
  };

  /**
   * @brief What kind of target to use.
   *
   * Depending on how the board is connected to the data provider,
   * it might be needed to change between how messages are encoded.
   */
  enum class WriteTargetType : uint8_t
  {
    RAW = 0x01,
    SUNTECH = 0x02
  };

  /**
   * @brief Main class for PPNet.
   */
  class PPNet
  {
  public:
    PPNet(Stream *output, WriteTargetType targetType = WriteTargetType::RAW)
    {
      this->output = output;
      this->targetType = targetType;
    };
    ~PPNet(){};
    /**
     * @brief Write a message
     */
    size_t WriteMessage(AnyMessage msg);

  private:
    Stream *output;
    WriteTargetType targetType;
    MsgPack::Packer packer;
  };
}

#endif /* _PPNET_H */
