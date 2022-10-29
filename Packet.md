# Packet

## Packet Header

Type name in java.

```
magic          :: int  // 468754818 = 0x1BFFE3C2
version        :: short
packetType     :: short
packetSize     :: int

if(version == VERSION1) {
  tractionId   :: int
}

expiration     :: long
sysMessageID   :: SysMessageID
propertyOffset :: int
propertySize   :: int
priority       :: byte
encryption     :: byte
bitFlags       :: short

if(version == VERSION1) {
  consumerID   :: int
  bitFlags = bitFlags & 0x00FF
} else {
  consumerID   :: long
}

```

## SysMessageID

```
timestamp :: long
sourceIP  :: IPAddress
sourcePort :: int
sequenceNo :: int
```

source code reference:

```
wangxy@concerto:~/github/eclipse-ee4j/openmq/mq$ head -349 main/comm-io/src/main/java/com/sun/messaging/jmq/io/SysMessageID.java | tail -43
    /**
     * Write the ID to the specified DataOutput. The format of the written data will be:
     *
     * <PRE>
     *    0                   1                   2                   3
     *   |0 1 2 3 4 5 6 7|8 9 0 1 2 3 4 5|6 7 8 9 0 1 2 3|4 5 6 7 8 9 0 1|
     *   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     *   |                                                               |
     *   +                        timestamp                              +
     *   |                                                               |
     *   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     *   |                                                               |
     *   +                                                               +
     *   |                     source IP                                 |
     *   +                                                               +
     *   |                                                               |
     *   +                                                               +
     *   |                                                               |
     *   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     *   |                      source port                              |
     *   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     *   |                     sequence number                           |
     *   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     * </PRE>
     *
     * This format matches the format specified in the ACKNOWLEDGE message of the JMQ protocol spec.
     *
     * We don't use ObjectSerialization to do this because we don't want the class version cruft that would be prefixed to
     * the data.
     *
     * @param out DataOutput to write ID to
     */
    public void writeID(DataOutput out) throws IOException {

        out.writeLong(timestamp);
        ip.writeAddress(out);
        out.writeInt(port);
        out.writeInt(sequence);

        if (out instanceof DataOutputStream) {
            ((DataOutputStream) out).flush();
        }
    }
wangxy@concerto:~/github/eclipse-ee4j/openmq/mq$ 
```

## IPAddress

```
ip :: byte[16]
```

source code reference:

```
wangxy@concerto:~/github/eclipse-ee4j/openmq/mq$ head -51 main/comm-util/src/main/java/com/sun/messaging/jmq/util/net/IPAddress.java | tail -26
/**
 * This class encapsulates an IP address which may be either IPv4 (32 bit) or IPv6 (128 bit). The JDK does not yet
 * support IPv6 addresses, but the Swift packet format uses 128 bit addresses (in preparation for IPv6) and therefore we
 * need this class. Internally everything is kept as an IPv6 address. If an IPv4 address is set (which will be the
 * typical case until IPv6 is adopted), then it is converted to an IPv4-mapped IPv6 address. See RFC 2373 for more info
 * on IPv6.
 *
 * Additionally we have added a third format called IPv4+MAC. In iMQ IP addresses are simply used as a unique identifier
 * for clients. Since an IPv4 address is not suitably unique (for example when NAT is used) we add the ability to
 * embedded a 40 bit MAC address (or psuedo MAC address) along with an IPv4 address in the 128 bits an IPv6 address
 * gives us. The format is:
 *
 * +--------+--------+--------+--------+
 * |11111111|00000000|00000000|00000000|
 * +--------+--------+--------+--------+
 * |      48 bit MAC address . . .
 * +--------+--------+--------+--------+
 *        . . .      |11111111|11111111|
 * +--------+--------+--------+--------+
 * |      32 bit IPv4 address          |
 * +--------+--------+--------+--------+
 *
 * The leading 11111111 is used in IPv6 to signify an IPv6 multicast address. Since a client will never be assigned a
 * multicast address we can use this prefix to indicate an IPv4+MAC address.
 */
public class IPAddress implements Cloneable, Serializable {
wangxy@concerto:~/github/eclipse-ee4j/openmq/mq$ 
```

## PacketVariableHeader

length:
```
size = propertyOffset - HEADER_SIZE
```

source code reference:
```
wangxy@concerto:~/github/eclipse-ee4j/openmq/mq$ cat -n main/comm-io/src/main/java/com/sun/messaging/jmq/io/PacketVariableHeader.java | head -322 | tail -80
   243	    /**
   244	     * Parse buffer and populate class with values
   245	     */
   246	    void parseBuffer() {
   247	
   248	        int type, len = 0;
   249	
   250	        if (buffer == null) {
   251	            bufferParsed = true;
   252	            return;
   253	        }
   254	
   255	        buffer.rewind();
   256	
   257	        type = buffer.getShort();
   258	        while (type != PacketString.NULL) {
   259	            switch (type) {
   260	
   261	            case PacketString.TRANSACTIONID:
   262	                // Skip length. TransactinID is a long
   263	                len = buffer.getShort();
   264	                transactionID = buffer.getLong();
   265	                break;
   266	
   267	            case PacketString.PRODUCERID:
   268	                // Skip length. ProducerID is a long
   269	                len = buffer.getShort();
   270	                producerID = buffer.getLong();
   271	                break;
   272	
   273	            case PacketString.DELIVERY_TIME:
   274	                // Skip length. deliveryTime is a long
   275	                len = buffer.getShort();
   276	                deliveryTime = buffer.getLong();
   277	                break;
   278	
   279	            case PacketString.DELIVERY_COUNT:
   280	                // Skip length. deliveryCount is a int
   281	                len = buffer.getShort();
   282	                deliveryCount = buffer.getInt();
   283	                break;
   284	
   285	            case PacketString.DESTINATION:
   286	            case PacketString.MESSAGEID:
   287	            case PacketString.CORRELATIONID:
   288	            case PacketString.REPLYTO:
   289	            case PacketString.TYPE:
   290	            case PacketString.DESTINATION_CLASS:
   291	            case PacketString.REPLYTO_CLASS:
   292	                len = buffer.getShort();
   293	
   294	                int currentLimit = buffer.limit();
   295	                int currentPosition = buffer.position();
   296	
   297	                // Set limit so we can decode
   298	                buffer.limit(currentPosition + len);
   299	                try {
   300	                    stringItems[type] = decoder.get().decode(buffer).toString();
   301	                } catch (CharacterCodingException e) {
   302	                    // Should never get
   303	                    System.out.println("Could not decode string " + e);
   304	                }
   305	
   306	                // reset limit
   307	                buffer.limit(currentLimit);
   308	                break;
   309	
   310	            default:
   311	                // Skip unknown field
   312	                len = buffer.getShort();
   313	                buffer.position(buffer.position() + len);
   314	                break;
   315	            }
   316	            type = buffer.getShort();
   317	        }
   318	
   319	        bufferParsed = true;
   320	        return;
   321	    }
   322	
wangxy@concerto:~/github/eclipse-ee4j/openmq/mq$
```

## PacketPayload

### PacketPayload.Property

```
size = propertySize
```

### PacketPayload.Body

```
size = packetSize - propertyOffset - propertySize
```




