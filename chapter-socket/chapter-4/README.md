1. 链路层-->IP层-->TCP/UDP层-->应用层。
2. 链路层是物理链接领域标准化的结果，专门定义LAN、WAN、MAN等网络标准。IP层主要解决路径选择的问题。IP层以链路层为基础进行数据传输。
3. 层级结构使协议设计更容易，也可以通过标准化操作设计开放式系统，引导更多人遵守规范。
4. 服务器端调用listen函数进入等待请求状态后，客户端就可以调用connect函数。
5. 调用listen函数的时候创建连接请求等待队列，用于存放客户端连接请求，accept函数则在该队列中依序受理连接请求。
6. 客户端套接字是在调用connect函数的时候，由操作系统自动分配的计算机的IP和随机端口的。