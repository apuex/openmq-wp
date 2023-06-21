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
    if (!buf.readBigEndian(v.magic_)) return false;
    if (!buf.readBigEndian(v.version_)) return false;
    if (!buf.readBigEndian(v.packetType_)) return false;
    if (!buf.readBigEndian(v.packetSize_)) return false;
    if (!buf.readBigEndian(v.expiration_)) return false;
    if (!read(buf, v.sysMessageID_)) return false;
    if (!buf.readBigEndian(v.propertyOffset_)) return false;
    if (!buf.readBigEndian(v.propertySize_)) return false;
    if (!buf.readBigEndian(v.priority_)) return false;
    if (!buf.readBigEndian(v.encryption_)) return false;
    if (!buf.readBigEndian(v.bitFlags_)) return false;
    if (!buf.readBigEndian(v.consumerID_)) return false;
    return true;
  }

  bool write(apuex::byte_buffer& buf, const PacketHeader& v) {
    if (!buf.writeBigEndian(v.magic_)) return false;
    if (!buf.writeBigEndian(v.version_)) return false;
    if (!buf.writeBigEndian(v.packetType_)) return false;
    if (!buf.writeBigEndian(v.packetSize_)) return false;
    if (!buf.writeBigEndian(v.expiration_)) return false;
    if (!write(buf, v.sysMessageID_)) return false;
    if (!buf.writeBigEndian(v.propertyOffset_)) return false;
    if (!buf.writeBigEndian(v.propertySize_)) return false;
    if (!buf.writeBigEndian(v.priority_)) return false;
    if (!buf.writeBigEndian(v.encryption_)) return false;
    if (!buf.writeBigEndian(v.bitFlags_)) return false;
    if (!buf.writeBigEndian(v.consumerID_)) return false;
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
