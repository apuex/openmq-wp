#include <comm-io-codec.hpp>

namespace openmq {
  // String, UTF
  bool readUTF(apuex::byte_buffer& buf, std::string& v) {
    uint16_t ssize;
    if (!buf.readBigEndian(ssize)) return false;

    for (uint16_t i = 0; i != ssize; ++i) {
      uint8_t b;
      if (!buf.readBigEndian(b)) return false;
      v.push_back(b);
    }
    return true;
  }

  bool writeUTF(apuex::byte_buffer& buf, const std::string& v) {
    size_t size = v.length();
    if (0xFFFF < size) return false;
    uint16_t ssize = static_cast<uint16_t>(size);
    if (!buf.writeBigEndian(ssize)) return false;

    for (auto it = v.begin(); it != v.end(); ++it) {
      uint8_t b = static_cast<uint8_t>(*it);
      if (!buf.writeBigEndian(b)) return false;
    }
    return true;
  }

  // IPAddress
  bool read(apuex::byte_buffer& buf, IPAddress& v) {
    for (size_t i = 0; i != sizeof(v.ip_); ++i) {
      if (!buf.readBigEndian(v.ip_[i])) return false;
    }
    return true;
  }

  bool write(apuex::byte_buffer& buf, const IPAddress& v) {
    for (size_t i = 0; i != sizeof(v.ip_); ++i) {
      if (!buf.writeBigEndian(v.ip_[i])) return false;
    }
    return true;
  }

  // SysMessageID
  bool read(apuex::byte_buffer& buf, SysMessageID& v) {
    if (!buf.readBigEndian(v.timestamp_)) return false;
    if (!read(buf, v.sourceIP_)) return false;
    if (!buf.readBigEndian(v.sourcePort_)) return false;
    if (!buf.readBigEndian(v.sequenceNo_)) return false;
    return true;
  }

  bool write(apuex::byte_buffer& buf, const SysMessageID& v) {
    if (!buf.writeBigEndian(v.timestamp_)) return false;
    if (!write(buf, v.sourceIP_)) return false;
    if (!buf.writeBigEndian(v.sourcePort_)) return false;
    if (!buf.writeBigEndian(v.sequenceNo_)) return false;
    return true;
  }

  // PacketHeader
  bool read(apuex::byte_buffer& buf, PacketHeader& v) {
    buf.readBigEndian(v.magic_);
    buf.readBigEndian(v.version_);
    buf.readBigEndian(v.packetType_);
    buf.readBigEndian(v.packetSize_);
    buf.readBigEndian(v.expiration_);
    read(buf, v.sysMessageID_);
    buf.readBigEndian(v.propertyOffset_);
    buf.readBigEndian(v.propertySize_);
    buf.readBigEndian(v.priority_);
    buf.readBigEndian(v.encryption_);
    buf.readBigEndian(v.bitFlags_);
    buf.readBigEndian(v.consumerID_);
    return true;
  }

  bool write(apuex::byte_buffer& buf, const PacketHeader& v) {
    buf.writeBigEndian(v.magic_);
    buf.writeBigEndian(v.version_);
    buf.writeBigEndian(v.packetType_);
    buf.writeBigEndian(v.packetSize_);
    buf.writeBigEndian(v.expiration_);
    write(buf, v.sysMessageID_);
    buf.writeBigEndian(v.propertyOffset_);
    buf.writeBigEndian(v.propertySize_);
    buf.writeBigEndian(v.priority_);
    buf.writeBigEndian(v.encryption_);
    buf.writeBigEndian(v.bitFlags_);
    buf.writeBigEndian(v.consumerID_);
    return true;
  }


  void print_bytes(std::ostream& os, const char* buff, const size_t length) {
    os << "[ ";
    for (size_t i = 0; i != length; ++i) {
      os << std::hex << std::uppercase << std::setw(2) << std::setfill('0')
        << (static_cast<uint32_t>(buff[i]) & 0xff) << " ";
    }
    os << "]" << std::endl;
  }

}
