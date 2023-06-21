#define BOOST_TEST_MODULE Variant Test
#include <boost/test/included/unit_test.hpp>
#include <boost/variant.hpp>

#include <comm-io-codec.hpp>
#include <sstream>

using namespace openmq;

namespace comm_io {

struct Prop {
  Prop(PACKET_PROPERTY_TYPE t) : type_(t) {}
  virtual ~Prop() {}
  PACKET_PROPERTY_TYPE type_;
};

struct BoolProp : public Prop {
  BoolProp() : Prop(PACKET_PROPERTY_TYPE::BOOLEAN) {}
  virtual ~BoolProp() {}
};

struct ByteProp : public Prop {
  ByteProp() : Prop(PACKET_PROPERTY_TYPE::BYTE) {}
  virtual ~ByteProp() {}
};

struct ShortProp : public Prop {
  ShortProp() : Prop(PACKET_PROPERTY_TYPE::SHORT) {}
  virtual ~ShortProp() {}
};

struct IntProp : public Prop {
  IntProp() : Prop(PACKET_PROPERTY_TYPE::INTEGER) {}
  virtual ~IntProp() {}
};

struct LongProp : public Prop {
  LongProp() : Prop(PACKET_PROPERTY_TYPE::LONG) {}
  virtual ~LongProp() {}
};

struct FloatProp : public Prop {
  FloatProp() : Prop(PACKET_PROPERTY_TYPE::FLOAT) {}
  virtual ~FloatProp() {}
};

struct DoubleProp : public Prop {
  DoubleProp() : Prop(PACKET_PROPERTY_TYPE::DOUBLE) {}
  virtual ~DoubleProp() {}
};

struct StringProp : public Prop {
  StringProp() : Prop(PACKET_PROPERTY_TYPE::STRING) {}
  virtual ~StringProp() {}
};

struct ObjectProp : public Prop {
  ObjectProp() : Prop(PACKET_PROPERTY_TYPE::OBJECT) {}
  virtual ~ObjectProp() {}
};

} // namespace comm_io 

using namespace comm_io;

BOOST_AUTO_TEST_CASE(PropSerializeTest) {
}

