#include "comm-io.hpp"
#include "apuex/byte_buffer.hpp"

namespace openmq {

  bool readUTF(apuex::byte_buffer& buf, std::string& v);
  bool writeUTF(apuex::byte_buffer& buf, const std::string& v);

  bool read(apuex::byte_buffer& buf, IPAddress& v);
  bool write(apuex::byte_buffer& buf, const IPAddress& v);

  bool read(apuex::byte_buffer& buf, SysMessageID& v);
  bool write(apuex::byte_buffer& buf, const SysMessageID& v);

  bool read(apuex::byte_buffer& buf, PacketHeader& v);
  bool write(apuex::byte_buffer& buf, const PacketHeader& v);


  template<typename T>
  void print_bytes(std::ostream& os, const T& str) {
    os << "[ ";
    std::for_each(str.begin(), str.end(), [&](const typename T::value_type& e) {
      os << std::hex << std::uppercase << std::setw(2) << std::setfill('0')
        << (static_cast<uint32_t>(e) & 0xff) << " ";
      });
    os << "]" << std::endl;
  }

  void print_bytes(std::ostream& os, const char* buff, const size_t length);
  template <typename Iterator>
  void print_bytes(std::ostream& os, const Iterator begin, const Iterator end) {
    os << "[ ";
    std::for_each(begin, end, [&](const char& e) {
      os << std::hex << std::uppercase << std::setw(2) << std::setfill('0')
        << (static_cast<uint32_t>(e) & 0xff) << " ";
      });
    os << "]" << std::endl;
  }

}
