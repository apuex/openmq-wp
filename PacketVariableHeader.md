# PacketVariableHeader

## Variable Type Definition

```
wangxy@concerto:~/github/eclipse-ee4j/openmq$ cat ./mq/main/comm-io/src/main/java/com/sun/messaging/jmq/io/PacketString.java | head -36 | tail -13 | sed -e "s/^\\s*public static final int /  PVHDR_/g" | sed -e "s/;$/,/g"
  PVHDR_NULL = 0,
  PVHDR_DESTINATION = 1,
  PVHDR_MESSAGEID = 2,
  PVHDR_CORRELATIONID = 3,
  PVHDR_REPLYTO = 4,
  PVHDR_TYPE = 5,
  PVHDR_DESTINATION_CLASS = 6,
  PVHDR_REPLYTO_CLASS = 7,
  PVHDR_TRANSACTIONID = 8,
  PVHDR_PRODUCERID = 9,
  PVHDR_DELIVERY_TIME = 10,
  PVHDR_DELIVERY_COUNT = 11,
  PVHDR_LAST = 12,
wangxy@concerto:~/github/eclipse-ee4j/openmq$
```

