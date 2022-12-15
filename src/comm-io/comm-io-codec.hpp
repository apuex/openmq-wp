#include "comm-io.hpp"
#include "msg4r.hpp"

namespace openmq {

  std::ostream& write(std::ostream& os, const IPAddress& v);

  class IPAddressParser {
  public:
    IPAddressParser();
    msg4r::decode_state operator()(std::istream& is, IPAddress& v);
    void reset();

  private:
    size_t index_;
    IPAddress t_;
  };

  std::ostream& write(std::ostream& os, const SysMessageID& v);

  class SysMessageIDParser {
    DECLARE_PARSER_FOR(SysMessageID)
  public:
    SysMessageIDParser();

  private:
    msg4r::number_parser<int64_t> parse_int64_;
    IPAddressParser parse_ipaddress_;
    msg4r::number_parser<int32_t> parse_int32_;
  };

  std::ostream& write(std::ostream& os, const PacketHeader& v);

  class PacketHeaderParser {
    DECLARE_PARSER_FOR(PacketHeader)
  public:
    PacketHeaderParser();

  private:
    msg4r::number_parser<int8_t> parse_int8_;
    msg4r::number_parser<int16_t> parse_int16_;
    msg4r::number_parser<int32_t> parse_int32_;
    msg4r::number_parser<int64_t> parse_int64_;
    SysMessageIDParser parse_sysMessageID_;
  };

}
