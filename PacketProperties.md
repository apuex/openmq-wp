# PacketProperties

## Packet Property Type

```
wangxy@concerto:~/github/eclipse-ee4j/openmq$ head -54 ./mq/main/comm-io/src/main/java/com/sun/messaging/jmq/io/PacketProperties.java | tail -11 | sed -e "/^$/d" | sed -e "s/^\\s*public static final \w* /  /g" | sed -e "s/;$/,/g" 
  BOOLEAN = 1,
  BYTE = 2,
  SHORT = 3,
  INTEGER = 4,
  LONG = 5,
  FLOAT = 6,
  DOUBLE = 7,
  STRING = 8,
  OBJECT = 9,
  VERSION1 = 1,
wangxy@concerto:~/github/eclipse-ee4j/openmq$
```

source code reference:
```
wangxy@concerto:~/github/eclipse-ee4j/openmq$ cat -n ./mq/main/comm-io/src/main/java/com/sun/messaging/jmq/io/PacketProperties.java | head -54 | tail -22
    33	/*
    34	 * Only the follow property types are supported:
    35	 *    Boolean, Byte, Short, Integer, Long, Float, Double, and String
    36	 *
    37	 * Format:
    38	 *     [Name length][Name (UTF-8)][Value type][Value Length][Value]
    39	 *
    40	 *    Pad out to 32 bit boundry
    41	 *
    42	 */
    43	public class PacketProperties {
    44	    public static final short BOOLEAN = 1;
    45	    public static final short BYTE = 2;
    46	    public static final short SHORT = 3;
    47	    public static final short INTEGER = 4;
    48	    public static final short LONG = 5;
    49	    public static final short FLOAT = 6;
    50	    public static final short DOUBLE = 7;
    51	    public static final short STRING = 8;
    52	    public static final short OBJECT = 9;
    53	
    54	    public static final int VERSION1 = 1;
wangxy@concerto:~/github/eclipse-ee4j/openmq$
```
