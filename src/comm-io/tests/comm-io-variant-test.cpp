#define BOOST_TEST_MODULE Variant Test
#include <boost/test/included/unit_test.hpp>
#include <boost/variant.hpp>

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <type_traits>

#include <comm-io.hpp>
#include <msg4r.hpp>

using namespace openmq;

typedef boost::variant
  < bool
  , int8_t 
  , int16_t 
  , int32_t 
  , int64_t 
  , float 
  , double 
  , std::string
  > MyProp;

struct output : public boost::static_visitor<>
{
  void operator()(bool c) const { std::cout << "  => " << c << '\n'; }
  void operator()(int8_t c) const { std::cout << "  => \'" << c << "\'" << '\n'; }
  void operator()(int16_t c) const { std::cout << "  => "<< c << '\n'; }
  void operator()(int32_t c) const { std::cout << "  => "<< c << '\n'; }
  void operator()(int64_t c) const { std::cout << "  => "<< c << '\n'; }
  void operator()(float d) const { std::cout << "  => "<< d << '\n'; }
  void operator()(double d) const { std::cout << "  => "<< d << '\n'; }
  void operator()(std::string s) const { std::cout << "  => \"" << s << "\"\n"; }
};

struct encoder: public boost::static_visitor<>
{
  encoder(std::ostream& os) : os_(os) { }

  void operator()(bool v) const {
    PACKET_PROPERTY_TYPE type = PACKET_PROPERTY_TYPE::BOOLEAN;
    msg4r::write(os_, type);   
    msg4r::write(os_, reinterpret_cast<int8_t&>(v));   
  }

  void operator()(int8_t v) const {
    PACKET_PROPERTY_TYPE type = PACKET_PROPERTY_TYPE::BYTE;
    msg4r::write(os_, type);   
    msg4r::write(os_, v);   
  }

  void operator()(int16_t v) const {
    PACKET_PROPERTY_TYPE type = PACKET_PROPERTY_TYPE::SHORT;
    msg4r::write(os_, type);   
    msg4r::write(os_, v);   
  }

  void operator()(int32_t v) const {
    PACKET_PROPERTY_TYPE type = PACKET_PROPERTY_TYPE::INTEGER;
    msg4r::write(os_, type);   
    msg4r::write(os_, v);   
  }

  void operator()(int64_t v) const {
    PACKET_PROPERTY_TYPE type = PACKET_PROPERTY_TYPE::LONG;
    msg4r::write(os_, type);   
    msg4r::write(os_, v);   
  }

  void operator()(float v) const {
    PACKET_PROPERTY_TYPE type = PACKET_PROPERTY_TYPE::FLOAT;
    msg4r::write(os_, type);   
    msg4r::write(os_, v);   
  }

  void operator()(double v) const {
    PACKET_PROPERTY_TYPE type = PACKET_PROPERTY_TYPE::DOUBLE;
    msg4r::write(os_, type);   
    msg4r::write(os_, v);   
  }

  void operator()(std::string v) const {
    PACKET_PROPERTY_TYPE type = PACKET_PROPERTY_TYPE::STRING;
    msg4r::write(os_, type);   
    msg4r::write(os_, v);   
  }

 private:
  std::ostream& os_;
};

msg4r::encode_state writeMyProp(std::ostream& os, const MyProp& v) {
  encoder theEncoder(os);
  boost::apply_visitor(theEncoder, v);
  return msg4r::encode_state::ENCODE_SUCCESS;
}

msg4r::encode_state writeMyProps(std::ostream& os, const std::map<std::string, MyProp>& v) {
  MSG4R_SIZE_T length = static_cast<MSG4R_SIZE_T>(v.size());
  msg4r::write(os, length);
  std::for_each(v.begin(), v.end(), [&](const std::pair<std::string, MyProp>& e) {
      msg4r::write(os, e.first);
      writeMyProp(os, e.second);
    });
  return msg4r::encode_state::ENCODE_SUCCESS;
}

struct decoder {
public:
  typedef MyProp value_type;
  msg4r::decode_state operator()(std::istream& is, value_type& v);
  void reset();
      
private:
  msg4r::decode_state parseValue(std::istream& is, value_type& v);
  // intemediate values
  int16_t type_;
  int8_t int8Value_;
  int16_t int16Value_;
  int32_t int32Value_;
  int64_t int64Value_;
  float floatValue_;
  double doubleValue_;
  std::string stringValue_;
  // parsers 
  msg4r::number_parser<int8_t> parse_int8_;
  msg4r::number_parser<int16_t> parse_int16_;
  msg4r::number_parser<int32_t> parse_int32_;
  msg4r::number_parser<int64_t> parse_int64_;
  msg4r::number_parser<float32_t> parse_float32_;
  msg4r::number_parser<float64_t> parse_float64_;
  msg4r::string_parser parse_string_;
  int state_;
};

BEGIN_IMPLEMENT_PARSER(decoder)
  PARSE_FIELD(parse_int16_, is, type_)
  PARSE_FIELD(parseValue, is, v)
END_IMPLEMENT_PARSER()

msg4r::decode_state decoder::parseValue(std::istream& is, value_type& v) {
  msg4r::decode_state state;
  switch(static_cast<PACKET_PROPERTY_TYPE>(type_)) {
    case PACKET_PROPERTY_TYPE::BOOLEAN:
      state = parse_int8_(is, int8Value_);
      if(msg4r::decode_state::DECODE_SUCCESS == state) {
        v = static_cast<bool>(int8Value_);
      }
      return state;
    case PACKET_PROPERTY_TYPE::BYTE:
      state = parse_int8_(is, int8Value_);
      if(msg4r::decode_state::DECODE_SUCCESS == state) {
        v = int8Value_;
      }
      return state;
    case PACKET_PROPERTY_TYPE::SHORT:
      state = parse_int16_(is, int16Value_);
      if(msg4r::decode_state::DECODE_SUCCESS == state) {
        v = int16Value_;
      }
      return state;
    case PACKET_PROPERTY_TYPE::INTEGER:
      state = parse_int32_(is, int32Value_);
      if(msg4r::decode_state::DECODE_SUCCESS == state) {
        v = int32Value_;
      }
      return state;
    case PACKET_PROPERTY_TYPE::LONG:
      state = parse_int64_(is, int64Value_);
      if(msg4r::decode_state::DECODE_SUCCESS == state) {
        v = int64Value_;
      }
      return state;
    case PACKET_PROPERTY_TYPE::FLOAT:
      state = parse_float32_(is, floatValue_);
      if(msg4r::decode_state::DECODE_SUCCESS == state) {
        v = floatValue_;
      }
      return state;
    case PACKET_PROPERTY_TYPE::DOUBLE:
      state = parse_float64_(is, doubleValue_);
      if(msg4r::decode_state::DECODE_SUCCESS == state) {
        v = doubleValue_;
      }
      return state;
    case PACKET_PROPERTY_TYPE::STRING:
      state = parse_string_(is, stringValue_);
      if(msg4r::decode_state::DECODE_SUCCESS == state) {
        v = stringValue_;
      }
      return state;
    default:
      return msg4r::decode_state::DECODE_FAILURE;
  }
}

void decoder::reset() {
  type_ = 0;
  int8Value_ = 0;
  int16Value_ = 0;
  int32Value_ = 0;
  int64Value_ = 0;
  floatValue_ = 0;
  doubleValue_ = 0;
  stringValue_ = "";
  parse_int8_.reset();
  parse_int16_.reset();
  parse_int32_.reset();
  parse_int64_.reset();
  parse_float32_.reset();
  parse_float64_.reset();
  parse_string_.reset();
  state_ = 0;
}

typedef msg4r::map_parser<msg4r::string_parser, decoder> PropsDecoder;

BOOST_AUTO_TEST_CASE(VariantTest) {
  std::map<std::string, MyProp> myProps1
  =
  { { "a bool",  true }
  , { "anther bool",  false }
  , { "an int8_t",  static_cast<int8_t>(0x41) }
  , { "an int16_t",  static_cast<int16_t>(0x41) }
  , { "an int32_t",  static_cast<int32_t>(0x41) }
  , { "an int64_t",  static_cast<int64_t>(0x41) }
  , { "a float",  static_cast<float>(1.234) }
  , { "a double",  static_cast<double>(1.234) }
  , { "a string",  std::string("Hello, World!") }
  };

  std::map<std::string, MyProp> myProps2;

  std::stringstream ssm;
  encoder theEncoder(ssm);
  
  std::for_each(myProps1.begin(), myProps1.end(), [&](const std::pair<std::string, MyProp>& e) {
    std::cout << e.first << " => " << e.second << std::endl;
    boost::apply_visitor(output(), e.second);
    boost::apply_visitor(theEncoder, e.second);
  });

  std::cout << "\nencoded bytes: ";
  msg4r::print_bytes(std::cout, ssm.str());

  std::stringstream ssmProps;
  writeMyProps(ssmProps, myProps1);
  std::cout << "\nMyProps encoded bytes: ";
  msg4r::print_bytes(std::cout, ssmProps.str());
  
  ssm.seekg(0);
  PropsDecoder decodeProps;
  msg4r::decode_state state = decodeProps(ssmProps, myProps2);

  std::cout << std::dec << std::setw(0); 
  std::cout << "\nMyProps decoded values: ";
  std::for_each(myProps2.begin(), myProps2.end(), [&](const std::pair<std::string, MyProp>& e) {
    std::cout << e.first << " => " << e.second << std::endl;
    boost::apply_visitor(output(), e.second);
    boost::apply_visitor(theEncoder, e.second);
  });

  BOOST_TEST(msg4r::decode_state::DECODE_SUCCESS == state);
  BOOST_TEST(myProps1 == myProps2);
  std::cout << "(myProps1 == myProps2) => " << (myProps1 == myProps2) << std::endl;
}

