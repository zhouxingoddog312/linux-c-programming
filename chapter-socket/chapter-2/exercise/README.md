1. 协议就是计算间对话必备的通信规则。能够让计算机正确对话，以此交换数据。
2. 
   - 传输过程中数据不会消失
   - 按序传输数据
   - 传输的数据不存在数据边界
3. - 传输数据可能丢失
   - 以快速传递为目标
   - 与面向连接的套接字不同，不存在连接的概念
4. - 面向消息的套接字，要求速度快，对数据丢失有一定容忍度
   - 面向连接的套接字，对可靠性要求较高
   - 面向连接的套接字，对可靠性要求高
5. 面向连接的套接字不存在数据边界，这类套接字只能与另外一个同样特性的套接字连接。
6. 见exercise目录