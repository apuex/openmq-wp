#define BOOST_TEST_MODULE Variant Test
#include <boost/test/included/unit_test.hpp>
#include <boost/variant.hpp>

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <type_traits>

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
  void operator()(int8_t c) const { std::cout << "  => \'" << c << "\'\n" << '\n'; }
  void operator()(int16_t c) const { std::cout << "  => "<< c << '\n'; }
  void operator()(int32_t c) const { std::cout << "  => "<< c << '\n'; }
  void operator()(int64_t c) const { std::cout << "  => "<< c << '\n'; }
  void operator()(float d) const { std::cout << "  => "<< d << '\n'; }
  void operator()(double d) const { std::cout << "  => "<< d << '\n'; }
  void operator()(std::string s) const { std::cout << "  => \"" << s << "\"\n"; }
};

BOOST_AUTO_TEST_CASE(VariantTest) {
  std::map<std::string, MyProp> myProps
  =
  { { "a bool",  true }
  , { "an int8_t",  static_cast<int8_t>(0x41) }
  , { "an int16_t",  static_cast<int16_t>(0x41) }
  , { "an int32_t",  static_cast<int32_t>(0x41) }
  , { "an int64_t",  static_cast<int64_t>(0x41) }
  , { "a float",  static_cast<float>(1.234) }
  , { "a double",  static_cast<double>(1.234) }
  , { "a string",  std::string("Hello, World!") }
  };

  std::for_each(myProps.begin(), myProps.end(), [](const std::pair<std::string, MyProp>& e) {
    std::cout << e.first << " => " << e.second << std::endl;
    boost::apply_visitor(output(), e.second);
  });
}

