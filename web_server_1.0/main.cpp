#include "config.h"

int main(int argc, char *argv[])
{
    //需要修改的数据库信息,登录名,密码,库名
    string user = "root";
    string passwd = "root";
    string databasename = "X_server";

    //命令行解析
    Config config;
    config.parse_arg(argc, argv);

    WebServer server;

    //初始化
    server.init(config.PORT, user, passwd, databasename, config.LOGWrite, 
                config.OPT_LINGER, config.TRIGMode,  config.sql_num,  config.thread_num, 
                config.close_log, config.actor_model);
    

    //日志
    server.log_write();
    printf("1...\n");

    //数据库
    server.sql_pool();
    printf("2...\n");

    //线程池
    server.thread_pool();
    printf("3...\n");

    //触发模式
    server.trig_mode();
    printf("4...\n");

    //监听
    server.eventListen();
    printf("5...\n");

    //运行
    server.eventLoop();

    return 0;
}