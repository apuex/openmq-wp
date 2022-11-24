#define BOOST_TEST_MODULE IPAddress Test
#include <boost/test/included/unit_test.hpp>
#include <boost/variant.hpp>

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <type_traits>

#include <comm-io-codec.hpp>

BOOST_AUTO_TEST_CASE(IPAddressTest) {
  IPAddress ipaddr1 {
    { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }
  };
  IPAddress ipaddr2;
  std::cout << "sizeof(IPAddress) = " << sizeof(IPAddress) << std::endl;
  std::cout << "sizeof(IPAddress::ip_) = " << sizeof(IPAddress::ip_) << std::endl;
  BOOST_TEST(sizeof(IPAddress) == 16);
  
  std::stringstream ssm;
  write(ssm, ipaddr1);
  
  ssm.seekg(0);
  IPAddressParser parse;
  parse(ssm, ipaddr2);
  std::cout << "ipaddr1 = " << ipaddr1 << std::endl;
  std::cout << "ipaddr2 = " << ipaddr2 << std::endl;
  std::cout << "(ipaddr1 == ipaddr2) => " << (ipaddr1 == ipaddr2) << std::endl;
  BOOST_TEST(ipaddr1 == ipaddr2);
}
