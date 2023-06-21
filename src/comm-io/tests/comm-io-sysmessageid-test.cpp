#define BOOST_TEST_MODULE SysMessageID Test
#include <boost/test/included/unit_test.hpp>
#include <boost/variant.hpp>

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <type_traits>

#include <comm-io-codec.hpp>

using namespace openmq;

BOOST_AUTO_TEST_CASE(SysMessageIDTest) {
  SysMessageID id1 {
    1,
    { { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 } },
    7676,
    9527
  };
  SysMessageID id2;
  
  uint8_t buffer[256];
  apuex::byte_buffer outbuf(buffer, 0, 0, sizeof(buffer));
  BOOST_TEST(true == write(outbuf, id1));

  apuex::byte_buffer inbuf(buffer, 0, outbuf.element_count(), sizeof(buffer));
  const bool decodeResult = read(inbuf, id2);

  BOOST_TEST(32 == outbuf.element_count());
  BOOST_TEST(true == decodeResult);
  std::cout << "id1 = " << id1<< std::endl;
  std::cout << "id2 = " << id2 << std::endl;
  std::cout << "(id1 == id2) => " << (id1 == id2) << std::endl;
  BOOST_TEST(id1 == id2);
}

