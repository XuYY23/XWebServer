#include "./config/config.h"

int main(int argc, char *argv[])
{
   //需要修改的数据库信息,登录名,密码,库名
   std::string user = "root";
   std::string passwd = "root";
   std::string databasename = "X_server";

   //命令行解析
   Config config;
   config.parse_arg(argc, argv);

   WebServer server;

   //初始化
   server.init(config.PORT, user, passwd, databasename, config.LOGWrite, 
               config.OPT_LINGER, config.TRIGMode, config.sql_num, config.thread_num, 
               config.close_log);
   

   //日志
   server.set_log();
   printf("5...\n");

   //数据库
   server.set_sqlpool();
   printf("4...\n");

   //线程池
   server.set_threadpool();
   printf("3...\n");

   //触发模式
   server.set_trigmode();
   printf("2...\n");

   //监听
   server.eventListen();
   printf("start server...\n");

   //运行
   server.eventLoop();

   return 0;
}
