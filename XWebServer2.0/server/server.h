#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <cassert>
#include <vector>
#include <sys/epoll.h>

#include "../pool/thread_pool.h"
#include "../http/http.h"
#include "../timer/timer.h"

const int MAX_FD           = 65536;           //最大文件描述符
const int MAX_EVENT_NUMBER = 10000;          //最大事件数
const int TIMESLOT         = 5;              //最小超时单位
const int LOG_BUF_SIZE     = 2000;           //日志缓冲区大小
const int LOG_MAX_LINES    = 800000;         //日志行数

class WebServer
{
public:
   /*基本数据信息*/
   int                        m_port;
   char*                      m_root;
   bool                       m_async;
   int                        m_close_log;
   int                        m_pipefd[2];
   int                        m_epollfd;
   http*                      users;

   /*数据库相关信息*/
   connection_pool*           m_connPool;
   std::string                m_user;        
   std::string                m_passWord;     
   std::string                m_databaseName; 
   int                        m_sql_num;

   /*线程池相关信息*/
   thread_pool<http>*         m_pool;
   int                        m_thread_num;

   /*epoll_event相关信息*/
   epoll_event                events[MAX_EVENT_NUMBER];
   int                        m_listenfd;
   int                        m_OPT_LINGER;
   int                        m_TRIGMode;
   int                        m_LISTENTrigmode;
   int                        m_CONNTrigmode;

   //定时器相关
   client_data*               users_timer;
   Utils                      utils;

public:
   /*参数是给时间堆数组设置容量*/
   WebServer(int cap = 100);
   WebServer(std::vector<heap_timer*> init_array, int size, int cap);
   ~WebServer();

   /*
      初始化数据
      参数：
         1、端口号
         2、用户名
         3、密码
         4、数据库名称
         5、是否开启异步写日志
         6、是否优雅关闭连接
         7、触发模式（ ET/LT）
         8、数据库连接数量
         9、线程数量
         10、是否关闭日志
   */
   void init(int port, std::string user, std::string passWord, std::string databaseName,
             bool async, int opt_linger, int trigmode, 
             int sql_num, int thread_num, int close_log);

   void set_threadpool();
   void set_sqlpool();
   void set_log();
   void set_trigmode();

   void eventListen();
   void eventLoop();

   void add_timer(int connfd, struct sockaddr_in client_address);
   void adjust_timer(heap_timer* timer);
   void deal_timer(heap_timer* timer, int sockfd);

   bool deal_clinetdata();
   bool deal_signal(bool& timeout, bool& stop_server);
   void deal_read(int sockfd);
   void deal_write(int sockfd);

};

#endif
