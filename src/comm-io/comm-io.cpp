#include <comm-io.hpp>

namespace openmq {

  bool operator==(const IPAddress& lhs, const IPAddress& rhs) {
    for (size_t i = 0; i != sizeof(IPAddress::ip_); ++i) {
      if (lhs.ip_[i] != rhs.ip_[i]) return false;
    }
    return true;
  }

  std::ostream& operator<<(std::ostream& os, const IPAddress& v) {
    os
      << "IPAddress { ip: ["
      << std::hex
      << std::uppercase;
    for (size_t i = 0; i != sizeof(IPAddress::ip_); ++i) {
      os
        << "0x"
        << std::setw(2)
        << std::setfill('0')
        << (0xFF & v.ip_[i]);
      if ((i + 1) != sizeof(IPAddress::ip_)) os
        << ", ";
    }
    os
      << std::dec // switch back to default std::dec.
      << "] }";
    return os;
  }

  bool operator==(const SysMessageID& lhs, const SysMessageID& rhs) {
    return (lhs.timestamp_ == rhs.timestamp_
      && lhs.sourceIP_ == rhs.sourceIP_
      && lhs.sourcePort_ == rhs.sourcePort_
      && lhs.sequenceNo_ == rhs.sequenceNo_
      );
  }

  std::ostream& operator<<(std::ostream& os, const SysMessageID& v) {
    os << "SysMessageID { ";
    os << "timestamp: " << v.timestamp_ << ", ";
    os << "sourceIP: " << v.sourceIP_ << ", ";
    os << "sourcePort: " << v.sourcePort_ << ", ";
    os << "sequenceNo: " << v.sequenceNo_ << " }";
    return os;
  }

  bool operator==(const PacketHeader& lhs, const PacketHeader& rhs) {
    return (lhs.magic_ == rhs.magic_
      && lhs.version_ == rhs.version_
      && lhs.packetType_ == rhs.packetType_
      && lhs.packetSize_ == rhs.packetSize_
      // && lhs.transactionId_ == rhs.transactionId_
      && lhs.expiration_ == rhs.expiration_
      && lhs.sysMessageID_ == rhs.sysMessageID_
      && lhs.propertyOffset_ == rhs.propertyOffset_
      && lhs.propertySize_ == rhs.propertySize_
      && lhs.priority_ == rhs.priority_
      && lhs.encryption_ == rhs.encryption_
      && lhs.bitFlags_ == rhs.bitFlags_
      && lhs.consumerID_ == rhs.consumerID_
      );
  }

  std::ostream& operator<<(std::ostream& os, const PacketHeader& v) {
    os << "PacketHeader { ";
    os << "magic: " << v.magic_ << ", ";
    os << "version: " << v.version_ << ", ";
    os << "packetType: " << v.packetType_ << ", ";
    os << "packetSize: " << v.packetSize_ << ", ";
    // os << "transactionId: " << v.transactionId_ << ", ";
    os << "expiration: " << v.expiration_ << ", ";
    os << "sysMessageID: " << v.sysMessageID_ << ", ";
    os << "propertyOffset: " << v.propertyOffset_ << ", ";
    os << "propertySize: " << v.propertySize_ << ", ";
    os << "priority: " << (0xff & v.priority_) << ", ";
    os << "encryption: " << (0xff & v.encryption_) << ", ";
    os << "bitFlags: " << v.bitFlags_ << ", ";
    os << "consumerID: " << v.consumerID_ << " }";
    return os;
  }
}
