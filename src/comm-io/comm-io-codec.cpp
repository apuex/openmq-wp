#include <comm-io-codec.hpp>

std::ostream& write(std::ostream& os, const IPAddress& v) {
  os.write(reinterpret_cast<const char*>(v.ip_), sizeof(v.ip_));
  return os;
}

IPAddressParser::IPAddressParser() : index_(0), t_() { }

msg4r::decode_state IPAddressParser::operator()(std::istream& is, IPAddress& v) {
  if(is.eof()) return msg4r::decode_state::DECODE_INPROGRESS;
  is.read((char*)&t_ + index_, sizeof(IPAddress) - index_);
  auto count = is.gcount();
  if(0 == count) return msg4r::decode_state::DECODE_INPROGRESS;
  index_ += count;
  if(index_ != sizeof(IPAddress)) {
    return msg4r::decode_state::DECODE_INPROGRESS;
  } else {
    v = t_;
    index_  = 0; // reset to initial state
    return msg4r::decode_state::DECODE_SUCCESS;
  }
}
  
void IPAddressParser::reset() { index_ = 0; }


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
