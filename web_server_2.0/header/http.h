#ifndef HTTP_H
#define HTTP_H

#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <sys/stat.h>
#include <string.h>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <stdarg.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/uio.h>
#include <map>
#include <mutex>

#include "sqlconn_pool.h"
#include "log.h"

class http
{
public:
   static const int FILENAME_LEN       = 200;
   static const int READ_BUFFER_SIZE   = 2048;
   static const int WRITE_BUFFER_SIZE  = 1024;

   enum METHOD
   {
      GET = 0,
      POST,
      HEAD,
      PUT,
      DELETE,
      TRACE,
      OPTIONS,
      CONNECT,
      PATH
   };

   enum CHECK_STATE
   {
      CHECK_STATE_REQUESTLINE = 0,
      CHECK_STATE_HEADER,
      CHECK_STATE_CONTENT
   };

   enum HTTP_CODE
   {
      NO_REQUEST,
      GET_REQUEST,
      BAD_REQUEST,
      NO_RESOURCE,
      FORBIDDEN_REQUEST,
      FILE_REQUEST,
      INTERNAL_ERROR,
      CLOSED_CONNECTION
   };


   enum LINE_STATUS
   {
      LINE_OK = 0,
      LINE_BAD,
      LINE_OPEN
   };

private:
   /*socket 连接描述符*/
   int            m_sockfd;

   /*客户端地址*/
   sockaddr_in    m_address;

   /*读缓冲区*/
   char           m_read_buf[READ_BUFFER_SIZE];

   /*开始读的位置*/
   long           m_read_idx;

   /*已经检查了的位置*/
   long           m_checked_idx;

   /*下一行开始位置*/
   int            m_start_line;

   /*写缓冲区*/
   char           m_write_buf[WRITE_BUFFER_SIZE];

   /*写开始的位置*/
   int            m_write_idx;

   /*检查状态*/
   CHECK_STATE    m_check_state;

   /*请求方法*/
   METHOD         m_method;

   /*请求的文件名*/
   char           m_real_file[FILENAME_LEN];

   /*
      请求文件的路径
      m_url 有如下8种情况
      1、/
      GET请求，跳转到judge.html，即欢迎访问页面   

      2、/0
      POST请求，跳转到register.html，即注册页面

      3、/1
      POST请求，跳转到log.html，即登录页面

      4、/2CGISQL.cgi
      POST请求，进行登录校验
      验证成功跳转到welcome.html，即资源请求成功页面
      验证失败跳转到logError.html，即登录失败页面

      5、/3CGISQL.cgi
      POST请求，进行注册校验
      注册成功跳转到log.html，即登录页面
      注册失败跳转到registerError.html，即注册失败页面

      6、/5
      POST请求，跳转到picture.html，即图片请求页面

      7、/6
      POST请求，跳转到video.html，即视频请求页面

      8、/7
      POST请求，跳转到fans.html，即关注页面
   */
   char*          m_url;

   /*HTTP版本信息*/
   char*          m_version;

   /*主机信息*/
   char*          m_host;

   /*内容长度*/
   long           m_content_length;

   /*是否开启TCP长连接*/
   bool           m_linger;

   /*文件信息*/
   char*          m_file_address;
   struct stat    m_file_stat;
   struct iovec   m_iv[2];
   int            m_iv_count;

   /*是否启用POST*/
   int            cgi;        

   /*请求头数据*/
   char*          m_string;

   /*需要发送的字节*/
   int            bytes_to_send;

   /*已经发送的字节*/
   int            bytes_have_send;

   /*网站根目录*/
   char*          doc_root;

   /*数据库用户信息*/
   std::map<std::string, std::string> 
                  m_users;

   /*选择 LT 模式还是 ET 模式*/
   int            m_TRIGMode;

   /*是否关闭日志*/
   int            m_close_log;

   /*用户名*/
   char           sql_user[100];

   /*用户密码*/
   char           sql_passwd[100];

   /*数据库名字*/
   char           sql_name[100];

   /*互斥锁*/
   std::mutex     m_mutex;

public:
   /*epoll 标识符*/
   static int     m_epollfd;

   /*用户数量*/
   static int     m_user_count;

   /*数据库连接*/
   MYSQL*         mysql;

public:
   http() {}
   ~http() {}

public:
   /*
      初始化连接
      参数：
         1、socket连接描述符
         2、socket连接地址
         3、根目录
         4、是否开启 ET 模式
         5、是否关闭日志
         6、用户名称
         7、用户密码
         8、数据库名称
   */
   void           init(int sockfd, const sockaddr_in& addr, char* root, int TRIGMode, 
                       int close_log, std::string user, std::string passwd, 
                       std::string sqlname);

   void           close_conn(bool real_close = true);

   void           process();

   bool           read();

   bool           write();

   sockaddr_in*   get_address(){ return &m_address; }

   void           initmysql_result(connection_pool* connPool);

private:
   void           init();

   /*以下函数分别是解析对应的字段*/
   LINE_STATUS    parse_line();
   HTTP_CODE      parse_request_line(char* text);
   HTTP_CODE      parse_headers(char* text);
   HTTP_CODE      parse_content(char* text);

   /*处理读*/
   HTTP_CODE      process_read();

   /*处理请求*/
   HTTP_CODE      do_request();

   void           unmap();

   /*构造响应*/
   bool           add_response(const char* format, ...);

   bool           add_status_line(int status, const char* title);

   bool           add_headers(int content_length);

   bool           add_content_length(int content_length);

   bool           add_content_type();

   bool           add_linger();

    bool           add_blank_line();

   bool           add_content(const char* content);

   /*处理写*/
   bool           process_write(HTTP_CODE ret);

   char*          get_line() { return m_read_buf + m_start_line; };
};

#endif