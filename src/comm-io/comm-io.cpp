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

}
