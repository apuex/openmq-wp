#define BOOST_TEST_MODULE PacketHeader Test
#include <boost/test/included/unit_test.hpp>
#include <boost/variant.hpp>

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <type_traits>

#include <comm-io-codec.hpp>

using namespace openmq;

BOOST_AUTO_TEST_CASE(PacketHeaderTest) {
  PacketHeader hdr1 {
    469754818, // int32_t magic_;
    301, // int16_t version_;  // VERSION3, which is the DEFAULT_VERSION.
    2, // int16_t packetType_; // BYTES_MESSAGE
    72, // int32_t packetSize_;
    // int32_t transactionId_; // VERSION1 only
    5, // int64_t expiration_;
    {
      1,
      { { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 } },
      7676,
      9527
    }, // SysMessageID sysMessageID_;
    7, // int32_t propertyOffset_;
    8, // int32_t propertySize_;
    9, // int8_t priority_;
    10, // int8_t encryption_;
    11, // int16_t bitFlags_; // VERSION1: bitFlags = bitFlags & 0x00FF
    12 // int64_t consumerID_; // VERSION1: int
  };
  PacketHeader hdr2;
  
  uint8_t buffer[0xFFFF];
  apuex::byte_buffer outbuf(buffer, 0, 0, sizeof(buffer));
  write(outbuf, hdr1);
  std::cout << "encoding hdr1(" << outbuf.element_count() << "): ";
  print_bytes(std::cout, buffer, buffer + outbuf.element_count());

  apuex::byte_buffer inbuf(buffer, 0, outbuf.element_count(), sizeof(buffer));
  bool state = read(inbuf, hdr2);

  BOOST_TEST(72 == outbuf.element_count());
  BOOST_TEST(true == state);
  std::cout << "hdr1 = " << hdr1 << std::endl;
  std::cout << "hdr2 = " << hdr2 << std::endl;
  std::cout << "(hdr1 == hdr2) => " << (hdr1 == hdr2) << std::endl;
  BOOST_TEST(hdr1 == hdr2);
}

