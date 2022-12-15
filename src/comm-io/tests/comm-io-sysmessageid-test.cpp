#define BOOST_TEST_MODULE SysMessageID Test
#include <boost/test/included/unit_test.hpp>
#include <boost/variant.hpp>

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <type_traits>

#include <comm-io-codec.hpp>

using namespace msg4r;
using namespace openmq;

BOOST_AUTO_TEST_CASE(SysMessageIDTest) {
  SysMessageID id1 {
    1,
    { { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 } },
    7676,
    9527
  };
  SysMessageID id2;
  
  std::stringstream ssm;
  write(ssm, id1);
  std::cout << "encoding id1: ";
  print_bytes(std::cout, ssm.str());

  ssm.seekg(0);
  SysMessageIDParser parse;
  decode_state state = parse(ssm, id2);

  BOOST_TEST(32 == ssm.tellg());
  BOOST_TEST(decode_state::DECODE_SUCCESS == state);
  std::cout << "id1 = " << id1<< std::endl;
  std::cout << "id2 = " << id2 << std::endl;
  std::cout << "(id1 == id2) => " << (id1 == id2) << std::endl;
  BOOST_TEST(id1 == id2);
}

