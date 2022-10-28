# PacketType

## All PacketTypes

```
wangxy@concerto:~/github/eclipse-ee4j/openmq/mq/main$ head -144 ./comm-io/src/main/java/com/sun/messaging/jmq/io/PacketType.java | tail -97 | sed -e "/^\s*$/d"
    public static final int NULL = 0;
    public static final int TEXT_MESSAGE = 1;
    public static final int BYTES_MESSAGE = 2;
    public static final int MAP_MESSAGE = 3;
    public static final int STREAM_MESSAGE = 4;
    public static final int OBJECT_MESSAGE = 5;
    public static final int MESSAGE = 6;
    public static final int SEND_REPLY = 9;
    public static final int HELLO = 10;
    public static final int HELLO_REPLY = 11;
    public static final int AUTHENTICATE = 12;
    public static final int AUTHENTICATE_REPLY = 13;
    public static final int ADD_CONSUMER = 14;
    public static final int ADD_CONSUMER_REPLY = 15;
    public static final int DELETE_CONSUMER = 16;
    public static final int DELETE_CONSUMER_REPLY = 17;
    public static final int ADD_PRODUCER = 18;
    public static final int ADD_PRODUCER_REPLY = 19;
    public static final int START = 20;
    public static final int STOP = 22;
    public static final int STOP_REPLY = 23;
    public static final int ACKNOWLEDGE = 24;
    public static final int ACKNOWLEDGE_REPLY = 25;
    public static final int BROWSE = 26;
    public static final int BROWSE_REPLY = 27;
    public static final int MESSAGE_SET = 27; // for bkwds compat
    public static final int GOODBYE = 28;
    public static final int GOODBYE_REPLY = 29;
    public static final int ERROR = 30;
    public static final int REDELIVER = 32;
    public static final int CREATE_DESTINATION = 34;
    public static final int CREATE_DESTINATION_REPLY = 35;
    public static final int DESTROY_DESTINATION = 36;
    public static final int DESTROY_DESTINATION_REPLY = 37;
    public static final int AUTHENTICATE_REQUEST = 38;
    public static final int VERIFY_DESTINATION = 40;
    public static final int VERIFY_DESTINATION_REPLY = 41;
    public static final int DELIVER = 42;
    public static final int DELIVER_REPLY = 43;
    public static final int START_TRANSACTION = 44;
    public static final int START_TRANSACTION_REPLY = 45;
    public static final int COMMIT_TRANSACTION = 46;
    public static final int COMMIT_TRANSACTION_REPLY = 47;
    public static final int ROLLBACK_TRANSACTION = 48;
    public static final int ROLLBACK_TRANSACTION_REPLY = 49;
    public static final int SET_CLIENTID = 50;
    public static final int SET_CLIENTID_REPLY = 51;
    public static final int RESUME_FLOW = 52;
    public static final int PING = 54;
    public static final int PING_REPLY = 55;
    public static final int PREPARE_TRANSACTION = 56;
    public static final int PREPARE_TRANSACTION_REPLY = 57;
    public static final int END_TRANSACTION = 58;
    public static final int END_TRANSACTION_REPLY = 59;
    public static final int RECOVER_TRANSACTION = 60;
    public static final int RECOVER_TRANSACTION_REPLY = 61;
    public static final int GENERATE_UID = 62;
    public static final int GENERATE_UID_REPLY = 63;
    public static final int FLOW_PAUSED = 64;
    public static final int DELETE_PRODUCER = 66;
    public static final int DELETE_PRODUCER_REPLY = 67;
    public static final int CREATE_SESSION = 68;
    public static final int CREATE_SESSION_REPLY = 69;
    public static final int DESTROY_SESSION = 70;
    public static final int DESTROY_SESSION_REPLY = 71;
    public static final int INFO_REQUEST = 72;
    public static final int INFO = 73;
    public static final int DEBUG = 74;
    public static final int GET_LICENSE = 76;
    public static final int GET_LICENSE_REPLY = 77;
    public static final int VERIFY_TRANSACTION = 78;
    public static final int VERIFY_TRANSACTION_REPLY = 79;
    public static final int LAST = 80;
wangxy@concerto:~/github/eclipse-ee4j/openmq/mq/main$ head -144 ./comm-io/src/main/java/com/sun/messaging/jmq/io/PacketType.java | tail -97 | sed -e "/^\s*$/d" | wc -l
73
```

