#ifndef LOG_H
#define LOG_H

/*
   日志类（全局只允许一个实例）
   利用线程安全的队列将日志写入文件中
   支持同步写和异步写
*/

#include <stdio.h>
#include <string>
#include <stdarg.h>
#include <thread>
#include "thread_safe_queue.h"

class Log
{
private:
   char        dir_name[128];             //路径名
   char        log_name[128];             //log文件名
   long        m_split_lines;             //日志最大行数
   long        m_log_buf_size;            //日志缓冲区大小
   long long   m_count;                   //日志行数记录
   int         m_today;                   //因为按天分类,记录当前时间是那一天
   FILE*       m_fp;                      //打开log的文件指针
   char*       m_buf;                     //日志缓冲区
   std::mutex  m_mutex;                   //互斥锁

   thread_safe_queue<std::string>*        
               m_log_queue;               //阻塞队列
   std::thread async_write;               //开启异步操作后的线程
   bool        m_stop;                    //是否关闭异步写线程

   bool        m_is_async;                //是否开启异步写日志操作
   int         m_close_log;               //是否关闭日志

public:
   //C++11以后,使用局部变量懒汉不用加锁
   static Log *get_instance()
   {
      static Log instance;
      return &instance;
   }

   /*异步线程的工作函数*/
   static void flush_log_thread()
   {
      Log::get_instance()->async_write_log();
   }

   //可选择的参数有日志文件、是否关闭日志、日志缓冲区大小、最大行数以及是否开启异步写日志
   bool        init(const char* file_name, int close_log, int log_buf_size = 8192, 
            int split_lines = 5000000, bool is_async = false);


   /*写日志*/
   void        write_log(int level, const char *format, ...);

   /*强制刷新缓冲区*/
   void        flush(void);

private:
   Log();
   virtual ~Log();

   /*异步写操作*/
   void async_write_log()
   {
      std::string single_log;
      /*
         从阻塞队列中取出一个日志string，写入文件
         如果日志实例还存在并且队列里还有任务要写，就全部写完再关闭线程
      */
      while ( !m_stop || !m_log_queue->empty() )
      {
         /*
            这里的判断非常重要，如果没有这个判断可能会导致死锁
            死锁原因：
               如果m_stop进了，同时调用了m_log_queue->wait_and_pop(single_log);
               这个时候外面的 write 没办法获得锁向队列添加任务，导致死锁
         */
         if( !m_log_queue->empty() )
            m_log_queue->wait_and_pop(single_log);
         else 
            continue;

         {
            std::lock_guard<std::mutex> lk(m_mutex);
            fputs(single_log.c_str(), m_fp);
         }

      }
   }

};

/*
   以下四个宏分别用于写对应的日志级别的日志
*/

#define LOG_DEBUG(format, ...) \
if(0 == m_close_log)\
{\
   Log::get_instance()->write_log(0, format, ##__VA_ARGS__);\
   Log::get_instance()->flush();\
}

#define LOG_INFO(format, ...) \
if(0 == m_close_log)\
{\
   Log::get_instance()->write_log(1, format, ##__VA_ARGS__);\
   Log::get_instance()->flush();\
}

#define LOG_WARN(format, ...) \
if(0 == m_close_log)\
{\
   Log::get_instance()->write_log(2, format, ##__VA_ARGS__);\
   Log::get_instance()->flush();\
}

#define LOG_ERROR(format, ...) \
if(0 == m_close_log)\
{\
   Log::get_instance()->write_log(3, format, ##__VA_ARGS__);\
   Log::get_instance()->flush();\
}

#endif