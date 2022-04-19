1. TCP的流是指，两台主机通过套接字建立连接后进入可交换数据的状态，也称为“流形成的状态”。而对于UDP来说，UDP不存在连接。
2. 单方面断开连接是指，通信一方调用close或closesocket断开连接，如此就会同时断开输出流与输入流，如果对方主机还有输出的话，本方主机也无法再接收数据了。
3. 半关闭是指单独关闭输入流或输出流。针对输出流执行半关闭的主机则无法再调用输出数据相关的函数，但是还可以接收数据。半关闭会让对方主机接收到EOF。