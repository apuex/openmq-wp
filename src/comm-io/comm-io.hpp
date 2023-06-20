#pragma once

#include <cstdint>
#include <string>
#include <iostream>
#include <iomanip>
#include <map>
#include <boost/chrono.hpp>
#ifdef _WIN32
#include <windows.h>
#endif
#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/variant.hpp>

namespace openmq {
  enum struct PACKET_VERSION : int16_t
  {
    VERSION1 = 103,
    VERSION2 = 200,
    VERSION3 = 301,
  };

  struct IPAddress
  {
    uint8_t ip_[16];
  };

  bool operator==(const IPAddress& lhs, const IPAddress& rhs);
  std::ostream& operator<<(std::ostream& os, const IPAddress& v);

  struct SysMessageID
  {
  public:
    int64_t timestamp_;
    IPAddress sourceIP_;
    int32_t sourcePort_;
    int32_t sequenceNo_;
  };

  bool operator==(const SysMessageID& lhs, const SysMessageID& rhs);
  std::ostream& operator<<(std::ostream& os, const SysMessageID& v);

  enum PacketType {
    NULL_MESSAGE = 0,
    TEXT_MESSAGE = 1,
    BYTES_MESSAGE = 2,
    MAP_MESSAGE = 3,
    STREAM_MESSAGE = 4,
    OBJECT_MESSAGE = 5,
    MESSAGE = 6,
    SEND_REPLY = 9,
    HELLO = 10,
    HELLO_REPLY = 11,
    AUTHENTICATE = 12,
    AUTHENTICATE_REPLY = 13,
    ADD_CONSUMER = 14,
    ADD_CONSUMER_REPLY = 15,
    DELETE_CONSUMER = 16,
    DELETE_CONSUMER_REPLY = 17,
    ADD_PRODUCER = 18,
    ADD_PRODUCER_REPLY = 19,
    START = 20,
    STOP = 22,
    STOP_REPLY = 23,
    ACKNOWLEDGE = 24,
    ACKNOWLEDGE_REPLY = 25,
    BROWSE = 26,
    BROWSE_REPLY = 27,
    MESSAGE_SET = 27, // for bkwds compat
    GOODBYE = 28,
    GOODBYE_REPLY = 29,
    ERROR = 30,
    REDELIVER = 32,
    CREATE_DESTINATION = 34,
    CREATE_DESTINATION_REPLY = 35,
    DESTROY_DESTINATION = 36,
    DESTROY_DESTINATION_REPLY = 37,
    AUTHENTICATE_REQUEST = 38,
    VERIFY_DESTINATION = 40,
    VERIFY_DESTINATION_REPLY = 41,
    DELIVER = 42,
    DELIVER_REPLY = 43,
    START_TRANSACTION = 44,
    START_TRANSACTION_REPLY = 45,
    COMMIT_TRANSACTION = 46,
    COMMIT_TRANSACTION_REPLY = 47,
    ROLLBACK_TRANSACTION = 48,
    ROLLBACK_TRANSACTION_REPLY = 49,
    SET_CLIENTID = 50,
    SET_CLIENTID_REPLY = 51,
    RESUME_FLOW = 52,
    PING = 54,
    PING_REPLY = 55,
    PREPARE_TRANSACTION = 56,
    PREPARE_TRANSACTION_REPLY = 57,
    END_TRANSACTION = 58,
    END_TRANSACTION_REPLY = 59,
    RECOVER_TRANSACTION = 60,
    RECOVER_TRANSACTION_REPLY = 61,
    GENERATE_UID = 62,
    GENERATE_UID_REPLY = 63,
    FLOW_PAUSED = 64,
    DELETE_PRODUCER = 66,
    DELETE_PRODUCER_REPLY = 67,
    CREATE_SESSION = 68,
    CREATE_SESSION_REPLY = 69,
    DESTROY_SESSION = 70,
    DESTROY_SESSION_REPLY = 71,
    INFO_REQUEST = 72,
    INFO = 73,
    DEBUG = 74,
    GET_LICENSE = 76,
    GET_LICENSE_REPLY = 77,
    VERIFY_TRANSACTION = 78,
    VERIFY_TRANSACTION_REPLY = 79,
    LAST = 80
  };

  struct PacketHeader
  {
  public:
    int32_t magic_;
    int16_t version_;
    int16_t packetType_;
    int32_t packetSize_;
    // int32_t transactionId_; // VERSION1 only
    int64_t expiration_;
    SysMessageID sysMessageID_;
    int32_t propertyOffset_;
    int32_t propertySize_;
    int8_t priority_;
    int8_t encryption_;
    int16_t bitFlags_; // VERSION1: bitFlags = bitFlags & 0x00FF
    int64_t consumerID_; // VERSION1: int
  };

  bool operator==(const PacketHeader& lhs, const PacketHeader& rhs);
  std::ostream& operator<<(std::ostream& os, const PacketHeader& v);

  enum struct PVHDR_TYPE : int16_t
  {
    PVHDR_NULL = 0, // NULL cause name clash.
    PVHDR_DESTINATION = 1,
    PVHDR_MESSAGEID = 2,
    PVHDR_CORRELATIONID = 3,
    PVHDR_REPLYTO = 4,
    PVHDR_TYPE = 5,
    PVHDR_DESTINATION_CLASS = 6,
    PVHDR_REPLYTO_CLASS = 7,
    PVHDR_TRANSACTIONID = 8,
    PVHDR_PRODUCERID = 9,
    PVHDR_DELIVERY_TIME = 10,
    PVHDR_DELIVERY_COUNT = 11,
    PVHDR_LAST = 12
  };

  static const std::string _packetHeaderNames[]
    =
  { "NULL"
  , "JMSDestination"
  , "JMSMessageID"
  , "JMSCorrelationID"
  , "JMSReplyTo"
  , "JMSType"
  , "DestinationClass"
  , "ReplyToClass"
  , "TransacionID"
  , "ProducerID"
  , "DeliveryTime"
  };

  struct PacketVariableHeader
  {
    int64_t transactionID = 0L;
    int64_t producerID = 0L;
    int64_t deliveryTime = 0L;
    int32_t deliveryCount = 0;
    std::string stringItems_[static_cast<size_t>(PVHDR_TYPE::PVHDR_LAST)];
  };

  inline const std::string& packetHeaderNames(PVHDR_TYPE type) {
    size_t theType = static_cast<size_t>(type);
    if (0 > theType || static_cast<size_t>(PVHDR_TYPE::PVHDR_LAST) > theType) theType = 0;

    return _packetHeaderNames[theType];
  }

  enum struct PACKET_PROPERTY_VERSION : int16_t
  {
    VERSION1 = 101,
    VERSION2 = 201,
    VERSION3 = 300 
  };

  enum class PACKET_PROPERTY_TYPE : int16_t
  {
    BOOLEAN = 1,
    BYTE = 2,
    SHORT = 3,
    INTEGER = 4,
    LONG = 5,
    FLOAT = 6,
    DOUBLE = 7,
    STRING = 8,
    OBJECT = 9
  };

  typedef boost::variant
    < bool
    , int8_t
    , int16_t
    , int32_t
    , int64_t
    , float
    , double
    , std::string
    > PacketProperty;

  struct PacketPayload
  {
    std::map<std::string, PacketProperty> properties_;
  };

  class Packet
    : public boost::enable_shared_from_this<Packet>
    , private boost::noncopyable
  {
  public:
    PacketHeader packetHeader_;
    PacketVariableHeader packetVariableHeader_;
    PacketPayload packetPayload_;
  };

}
