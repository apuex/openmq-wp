#define BOOST_TEST_MODULE Variant Test
#include <boost/test/included/unit_test.hpp>
#include <boost/variant.hpp>

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <type_traits>

#include <comm-io-codec.hpp>

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
  encoder(apuex::byte_buffer& buf) : buf_(buf) { }

  void operator()(bool v) const {
    int16_t type = static_cast<int16_t>(PACKET_PROPERTY_TYPE::BOOLEAN);
    buf_.writeBigEndian(type);
    buf_.writeBigEndian(reinterpret_cast<int8_t&>(v));   
  }

  void operator()(int8_t v) const {
    int16_t type = static_cast<int16_t>(PACKET_PROPERTY_TYPE::BYTE);
    buf_.writeBigEndian(type);
    buf_.writeBigEndian(v);
  }

  void operator()(int16_t v) const { 
    int16_t type = static_cast<int16_t>(PACKET_PROPERTY_TYPE::SHORT);
    buf_.writeBigEndian(type);
    buf_.writeBigEndian(v);
  }

  void operator()(int32_t v) const {
    int16_t type = static_cast<int16_t>(PACKET_PROPERTY_TYPE::INTEGER);
    buf_.writeBigEndian(type);
    buf_.writeBigEndian(v);
  }

  void operator()(int64_t v) const {
    int16_t type = static_cast<int16_t>(PACKET_PROPERTY_TYPE::LONG);
    buf_.writeBigEndian(type);
    buf_.writeBigEndian(v);
  }

  void operator()(float v) const {
    int16_t type = static_cast<int16_t>(PACKET_PROPERTY_TYPE::FLOAT);
    buf_.writeBigEndian(type);
    buf_.writeBigEndian(v);
  }

  void operator()(double v) const {
    int16_t type = static_cast<int16_t>(PACKET_PROPERTY_TYPE::DOUBLE);
    buf_.writeBigEndian(type);
    buf_.writeBigEndian(v);
  }

  void operator()(std::string v) const {
    int16_t type = static_cast<int16_t>(PACKET_PROPERTY_TYPE::STRING);
    buf_.writeBigEndian(type);
    writeUTF(buf_, v);
  }

 private:
  apuex::byte_buffer& buf_;
};

bool writeMyProp(apuex::byte_buffer& buf, const MyProp& v) {
  encoder theEncoder(buf);
  boost::apply_visitor(theEncoder, v);
  return true;
}

bool writeMyProps(apuex::byte_buffer& buf, const std::map<std::string, MyProp>& v) {
  uint32_t length = static_cast<uint32_t>(v.size());
  buf.writeBigEndian(length);
  std::for_each(v.begin(), v.end(), [&](const std::pair<std::string, MyProp>& e) {
      writeUTF(buf, e.first);
      writeMyProp(buf, e.second);
    });
  return true;
}

bool readMyProp(apuex::byte_buffer& buf, MyProp& v) {
  int16_t type_;
  if (!buf.readBigEndian(type_)) return false;
  switch(static_cast<PACKET_PROPERTY_TYPE>(type_)) {
    case PACKET_PROPERTY_TYPE::BOOLEAN:
    {
      int8_t b;
      if (!buf.readBigEndian(b)) return false;
      v = static_cast<bool>(b);
      return true;
    }
    case PACKET_PROPERTY_TYPE::BYTE:
    {
      int8_t b;
      if (!buf.readBigEndian(b)) return false;
      v = b;
      return true;
    }
    case PACKET_PROPERTY_TYPE::SHORT:
    {
      int16_t b;
      if (!buf.readBigEndian(b)) return false;
      v = b;
      return true;
    }
    case PACKET_PROPERTY_TYPE::INTEGER:
    {
      int32_t b;
      if (!buf.readBigEndian(b)) return false;
      v = b;
      return true;
    }
    case PACKET_PROPERTY_TYPE::LONG:
    {
      int64_t b;
      if (!buf.readBigEndian(b)) return false;
      v = b;
      return true;
    }
    case PACKET_PROPERTY_TYPE::FLOAT:
    {
      float b;
      if (!buf.readBigEndian(b)) return false;
      v = b;
      return true;
    }
    case PACKET_PROPERTY_TYPE::DOUBLE:
    {
      double b;
      if (!buf.readBigEndian(b)) return false;
      v = b;
      return true;
    }
    case PACKET_PROPERTY_TYPE::STRING:
    {
      std::string b;
      if (!readUTF(buf, b)) return false;
      v = b;
      return true;
    }
    default:
      return false;
  }
}


bool readMyProps(apuex::byte_buffer& buf, std::map<std::string, MyProp>& v) {
  uint32_t length;
  if(!buf.readBigEndian(length)) return false;
  for (uint32_t i = 0; i != length; ++i) {
    std::string key;
    MyProp value;
    if (!readUTF(buf, key)) return false;
    if (!readMyProp(buf, value)) return false;
    v.insert(std::make_pair(key, value));
  }
  return true;
}

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

  uint8_t buffer[0xFFFF];
  apuex::byte_buffer outbuf(buffer, 0, 0, sizeof(buffer));
  encoder theEncoder(outbuf);
  
  std::for_each(myProps1.begin(), myProps1.end(), [&](const std::pair<std::string, MyProp>& e) {
    std::cout << e.first << " => " << e.second << std::endl;
    boost::apply_visitor(output(), e.second);
    boost::apply_visitor(theEncoder, e.second);
  });

  std::cout << "\nencoded bytes: ";
  print_bytes(std::cout, buffer, buffer + outbuf.element_count());

  outbuf.clear();
  writeMyProps(outbuf, myProps1);
  std::cout << "\nMyProps encoded bytes: ";
  print_bytes(std::cout, buffer, buffer + outbuf.element_count());
  
  apuex::byte_buffer inbuf(buffer, 0, outbuf.element_count(), sizeof(buffer));
  bool state = readMyProps(inbuf, myProps2);

  std::cout << std::dec << std::setw(0); 
  std::cout << "\nMyProps decoded values: ";
  std::for_each(myProps2.begin(), myProps2.end(), [&](const std::pair<std::string, MyProp>& e) {
    std::cout << e.first << " => " << e.second << std::endl;
    boost::apply_visitor(output(), e.second);
    boost::apply_visitor(theEncoder, e.second);
  });

  BOOST_TEST(true == state);
  BOOST_TEST(myProps1 == myProps2);
  std::cout << "(myProps1 == myProps2) => " << (myProps1 == myProps2) << std::endl;
}

