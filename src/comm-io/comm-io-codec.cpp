#include <comm-io-codec.hpp>

namespace openmq {
  // IPAddress
  std::ostream& write(std::ostream& os, const IPAddress& v) {
    os.write(reinterpret_cast<const char*>(v.ip_), sizeof(v.ip_));
    return os;
  }

  IPAddressParser::IPAddressParser() : index_(0), t_() { }

  msg4r::decode_state IPAddressParser::operator()(std::istream& is, IPAddress& v) {
    if (is.eof()) return msg4r::decode_state::DECODE_INPROGRESS;
    is.read((char*)&t_ + index_, sizeof(IPAddress) - index_);
    auto count = is.gcount();
    if (0 == count) return msg4r::decode_state::DECODE_INPROGRESS;
    index_ += count;
    if (index_ != sizeof(IPAddress)) {
      return msg4r::decode_state::DECODE_INPROGRESS;
    }
    else {
      v = t_;
      index_ = 0; // reset to initial state
      return msg4r::decode_state::DECODE_SUCCESS;
    }
  }

  void IPAddressParser::reset() { index_ = 0; }

  // SysMessageID
  std::ostream& write(std::ostream& os, const SysMessageID& v) {
    msg4r::write(os, v.timestamp_);
    write(os, v.sourceIP_);
    msg4r::write(os, v.sourcePort_);
    msg4r::write(os, v.sequenceNo_);
    return os;
  }

  BEGIN_IMPLEMENT_PARSER(SysMessageIDParser)
    PARSE_FIELD(parse_int64_, is, v.timestamp_)
    PARSE_FIELD(parse_ipaddress_, is, v.sourceIP_)
    PARSE_FIELD(parse_int32_, is, v.sourcePort_)
    PARSE_FIELD(parse_int32_, is, v.sequenceNo_)
    END_IMPLEMENT_PARSER()

    SysMessageIDParser::SysMessageIDParser()
    : state_()
    , parse_int64_()
    , parse_ipaddress_()
    , parse_int32_()
  {}

  void SysMessageIDParser::reset() {
    parse_int64_.reset();
    parse_ipaddress_.reset();
    parse_int32_.reset();
  }

  // PacketHeader
  
  std::ostream& write(std::ostream& os, const PacketHeader& v) {
    msg4r::write(os, v.magic_);
    msg4r::write(os, v.version_);
    msg4r::write(os, v.packetType_);
    msg4r::write(os, v.packetSize_);
    msg4r::write(os, v.expiration_);
    write(os, v.sysMessageID_);
    msg4r::write(os, v.propertyOffset_);
    msg4r::write(os, v.propertySize_);
    msg4r::write(os, v.priority_);
    msg4r::write(os, v.encryption_);
    msg4r::write(os, v.bitFlags_);
    msg4r::write(os, v.consumerID_);
    return os;
  }

  BEGIN_IMPLEMENT_PARSER(PacketHeaderParser)
    PARSE_FIELD(parse_int32_, is, v.magic_)
    PARSE_FIELD(parse_int16_, is, v.version_)
    PARSE_FIELD(parse_int16_, is, v.packetType_)
    PARSE_FIELD(parse_int32_, is, v.packetSize_)
    PARSE_FIELD(parse_int64_, is, v.expiration_)
    PARSE_FIELD(parse_sysMessageID_, is, v.sysMessageID_)
    PARSE_FIELD(parse_int32_, is, v.propertyOffset_)
    PARSE_FIELD(parse_int32_, is, v.propertySize_)
    PARSE_FIELD(parse_int8_, is, v.priority_)
    PARSE_FIELD(parse_int8_, is, v.encryption_)
    PARSE_FIELD(parse_int16_, is, v.bitFlags_)
    PARSE_FIELD(parse_int64_, is, v.consumerID_)
  END_IMPLEMENT_PARSER()

    PacketHeaderParser::PacketHeaderParser()
    : state_()
    , parse_int8_()
    , parse_int16_()
    , parse_int32_()
    , parse_int64_()
    , parse_sysMessageID_()
  {}

  void PacketHeaderParser::reset() {
    parse_int8_.reset();
    parse_int16_.reset();
    parse_int32_.reset();
    parse_int64_.reset();
    parse_sysMessageID_.reset();
  }
 

}
