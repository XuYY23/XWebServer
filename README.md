# XWebServer
一个’个人‘学习道路上的webserver

Xwebserver1.0
1、使用 线程池 + 非阻塞socket + epoll(ET模式) + 事件处理(Reactor) 的并发模型
2、使用状态机解析HTTP请求报文，暂时只支持解析GET请求
3、利用IO复用进行压力测试

目前正在努力为这个服务器增加更多的内容，同时慢慢用c++改写，目前线程池使用了c++的线程库以及条件变量作为实现
