# portmapper

## primary workflow of portmapper

### client initiate portmapper connection 

### server accept client portmapper connection 

### client send version over portmapper connection

- 2.0 client does not send a version.
- 3.0 client does send version (101).

See [`PortMapper.java`](https://github.com/eclipse-ee4j/openmq/blob/master/mq/main/mq-broker/broker-core/src/main/java/com/sun/messaging/jmq/jmsserver/service/PortMapper.java)
 
### server read version from client over portmapper connection

Get version from client. 2.0 client does not send a version so we must set SoTimeout to timeout if there is nothing to read.
See [`PortMapper.java`](https://github.com/eclipse-ee4j/openmq/blob/master/mq/main/mq-broker/broker-core/src/main/java/com/sun/messaging/jmq/jmsserver/service/PortMapper.java)

### server send port mapper table to client over portmapper connection

The content encoding is in `ASCII` text format.

A MessageBroker5.1 port mapper table maybe like this:

```
$ telnet 192.168.0.120 7676
Trying 192.168.0.120...
Connected to repository.
Escape character is '^]'.
101 imqbroker 301
portmapper tcp PORTMAPPER 7676 [sessionid=1091423743631234048]
cluster_discovery tcp CLUSTER_DISCOVERY 0
jmxrmi rmi JMX 0 [url=service:jmx:rmi://192.168.0.120/stub/rO0ABXNyAC5qYXZheC5tYW5hZ2VtZW50LnJlbW90ZS5ybWkuUk1JU2VydmVySW1wbF9TdHViAAAAAAAAAAICAAB4cgAaamF2YS5ybWkuc2VydmVyLlJlbW90ZVN0dWLp/tzJi+FlGgIAAHhyABxqYXZhLnJtaS5zZXJ2ZXIuUmVtb3RlT2JqZWN002G0kQxhMx4DAAB4cHchAAtVbmljYXN0UmVmMgEADTE5Mi4xNjguMC4xMjAAAKzTc3IAOWNvbS5zdW4ubWVzc2FnaW5nLmptcS5tYW5hZ2VtZW50Lk1RUk1JQ2xpZW50U29ja2V0RmFjdG9yeWcwHqL7+bHOAgAEWgAFZGVidWdaABNpc0Jyb2tlckhvc3RUcnVzdGVkWgAGdXNlU1NMTAAIaG9zdG5hbWV0ABJMamF2YS9sYW5nL1N0cmluZzt4cgAnamF2YXgucm1pLnNzbC5Tc2xSTUlDbGllbnRTb2NrZXRGYWN0b3J5jKq0u4GFJQ8CAAB4cAAAAHQADTE5Mi4xNjguMC4xMjB3F+YL8UtfKA2nqtKMmQAAAYQcupPugAEAeA==]
admin tcp ADMIN 37659 [hostname=192.168.0.120]
jms tcp NORMAL 7677 [hostname=192.168.0.120]
ssljms tls NORMAL 7678 [hostname=192.168.0.120]
cluster tcp CLUSTER 37341 [hostname=repository,hostaddr=192.168.0.120]
.
Connection closed by foreign host.
$
```

And a MessageBroker4.3 version maybe like this:
```
$ telnet 192.168.0.72 7676
Trying 192.168.0.72...
Connected to 192.168.0.72.
Escape character is '^]'.
101 imqbroker 4.3
portmapper tcp PORTMAPPER 7676 [sessionid=1823258681239055616,imqhome=C:\MessageQueue\MessageQueue\mq,imqvarhome=C:\MessageQueue\MessageQueue\var\mq]
cluster_discovery tcp CLUSTER_DISCOVERY 49678
jmxrmi rmi JMX 0 [url=service:jmx:rmi://wangxy-w10/stub/rO0ABXNyAC5qYXZheC5tYW5hZ2VtZW50LnJlbW90ZS5ybWkuUk1JU2VydmVySW1wbF9TdHViAAAAAAAAAAICAAB4cgAaamF2YS5ybWkuc2VydmVyLlJlbW90ZVN0dWLp/tzJi+FlGgIAAHhyABxqYXZhLnJtaS5zZXJ2ZXIuUmVtb3RlT2JqZWN002G0kQxhMx4DAAB4cHc4AAtVbmljYXN0UmVmMgAADTE3Mi4xOC4zNC4xNzcAAMIPAAAAAAAAAADuhyWNAAABhBxM6qWAAAB4]
admin tcp ADMIN 49684
jms tcp NORMAL 7677
cluster tcp CLUSTER 49685
.
Connection closed by foreign host.
$
```

### client receive port mapper table over portmapper connection
 
### server wait for portmapper connection close

### client close portmapper connection

### client extract service(i.e, jms tcp) port from port mapper table

### client initiate service connection(service flow)

