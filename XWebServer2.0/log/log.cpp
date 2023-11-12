#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <stdarg.h>
#include <utility>
#include "log.h"

Log::Log() : m_count(0), m_is_async(false), m_stop(false)
{

}

Log::~Log()
{
   /*日志类被销毁时，需要等待异步写完成才能销毁*/
   if( async_write.joinable() )
   {
      m_stop = true;
      async_write.join();
   }

   if( m_log_queue != NULL )
   {
      delete m_log_queue;
   }

   if( m_buf != NULL )
   {
      delete [] m_buf;
   }

   if ( m_fp != NULL )
   {
      fclose(m_fp);
   }
}

//参数：日志文件、是否关闭日志、日志缓冲区大小、最大行数以及是否开启异步写日志
bool Log::init(const char* file_name, int close_log, int log_buf_size, 
               int split_lines, bool is_async)
{
   //如果设置了 is_async,则设置为异步
   if ( is_async )
   {
      m_is_async = is_async;
      m_log_queue = new thread_safe_queue<std::string>();

      //flush_log_thread为回调函数,这里表示创建线程异步写日志
      async_write = std::move(std::thread(flush_log_thread));
   }
   
   m_close_log = close_log;
   m_log_buf_size = log_buf_size;
   m_buf = new char[m_log_buf_size];
   memset(m_buf, '\0', m_log_buf_size);
   m_split_lines = split_lines;

   /*获取时间*/
   time_t t = time(NULL);
   struct tm* sys_tm = localtime(&t);
   struct tm my_tm = *sys_tm;


   const char* p = strrchr(file_name, '/');
   char log_full_name[256] = {0};

   if ( p == NULL )
   {
      snprintf(log_full_name, 255, "%d-%02d-%02d-%s", my_tm.tm_year + 1900, my_tm.tm_mon + 1, my_tm.tm_mday, file_name);
   }
   else
   {
      strcpy(log_name, p + 1);
      strncpy(dir_name, file_name, p - file_name + 1);
      snprintf(log_full_name, 255, "%s%d-%02d-%02d-%s", dir_name, my_tm.tm_year + 1900, my_tm.tm_mon + 1, my_tm.tm_mday, log_name);
   }

   m_today = my_tm.tm_mday;
   
   m_fp = fopen(log_full_name, "a");
   if ( m_fp == NULL ) 
   {
      return false;
   }

   return true;
}

/*写日志*/
void Log::write_log(int level, const char *format, ...)
{
   struct timeval now = {0, 0};
   gettimeofday(&now, NULL);
   time_t t = now.tv_sec;
   struct tm* sys_tm = localtime(&t);
   struct tm my_tm = *sys_tm;
   char s[16] = {0};

   switch (level)
   {
      case 0:
         strcpy(s, "[debug]:");
         break;
      case 1:
         strcpy(s, "[info]:");
         break;
      case 2:
         strcpy(s, "[warn]:");
         break;
      case 3:
         strcpy(s, "[erro]:");
         break;
      default:
         strcpy(s, "[info]:");
         break;
   }

   //写入一个log，对m_count++, m_split_lines最大行数
   std::unique_lock<std::mutex> lk(m_mutex);
   m_count++;

   /*如果调用这个函数时已经是新的一天，或者行数满了就新开一个日志*/
   if ( m_today != my_tm.tm_mday || m_count % m_split_lines == 0)  //everyday log
   {
      
      char new_log[256] = {0};
      fflush(m_fp);
      fclose(m_fp);
      char tail[16] = {0};
      
      snprintf(tail, 16, "%d-%02d-%02d-", my_tm.tm_year + 1900, my_tm.tm_mon + 1, my_tm.tm_mday);
      
      if ( m_today != my_tm.tm_mday )
      {
         snprintf(new_log, 255, "%s%s%s", dir_name, tail, log_name);
         m_today = my_tm.tm_mday;
         m_count = 0;
      }
      else
      {
         snprintf(new_log, 255, "%s%s%s.%lld", dir_name, tail, log_name, m_count / m_split_lines);
      }
      m_fp = fopen(new_log, "a");
   }

   lk.unlock();

   va_list valst;
   va_start(valst, format);

   std::string log_str;
   lk.lock();

   //写入的具体时间内容格式
   int n = snprintf(m_buf, 48, "%d-%02d-%02d %02d:%02d:%02d.%06ld %s ",
                  my_tm.tm_year + 1900, my_tm.tm_mon + 1, my_tm.tm_mday,
                  my_tm.tm_hour, my_tm.tm_min, my_tm.tm_sec, now.tv_usec, s);
   
   int m = vsnprintf(m_buf + n, m_log_buf_size - n - 1, format, valst);
   m_buf[n + m] = '\n';
   m_buf[n + m + 1] = '\0';
   log_str = m_buf;

   lk.unlock();

   /*如果设置了异步标志，则直接将任务放进队列中*/
   if ( m_is_async )
   {
      m_log_queue->push(log_str);
   }
   /*否则就在本线程将日志处理*/
   else
   {
      lk.lock();
      fputs(log_str.c_str(), m_fp);
      lk.unlock();
   }

   va_end(valst);
}

void Log::flush(void)
{
    std::lock_guard<std::mutex> lk(m_mutex);
    //强制刷新写入流缓冲区
    fflush(m_fp);
}
