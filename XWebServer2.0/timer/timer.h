
/*
   定时器
   依据游双大佬的书写的时间堆
*/

#ifndef TIMER_H
#define TIMER_H

#include <netinet/in.h>
#include <time.h>
#include <vector>
using std::exception;
using std::swap;

#define BUFFER_SIZE 64

class heap_timer;

/*绑定 socket 和定时器*/
struct client_data
{
   sockaddr_in address;
   int         sockfd;
   heap_timer* timer;
};

/*定时器*/
class heap_timer
{
public:
   /*定时器生效的绝对时间*/
   time_t         expire;

   /*用户数据*/
   client_data*   user_data;

   /*回调函数*/
   void (*cb_func)(client_data*);

public:
   heap_timer(){}

   heap_timer(int delay)
   {
      expire = time(NULL) + delay;
   }
};

/*时间堆*/
class time_heap
{
private:
   /*堆数组容量*/
   int      capacity;

   /*堆数组当前包含的元素个数*/
   int      cur_size;

   /*堆数组*/
   std::vector<heap_timer*> 
            array;

private:
   /*最小堆的下滤操作，确保堆数组中以第 hole 个节点作为根的子树保持最小堆性质*/
   void percolate_down(int hole);

   /*将堆数组容量扩大一倍*/
   void resize();

public:
   time_heap(int cap = 10000);

   time_heap(std::vector<heap_timer*> init_array, int size, int cap);

   ~time_heap() = default;

public:
   /*添加目标定时器*/
   void add_timer(heap_timer* timer);

   /*删除目标定时器*/
   void del_timer(heap_timer* timer);

   /*获取堆顶定时器*/
   heap_timer* top() const;

   /*删除堆顶定时器*/
   void pop_timer();

   /*心搏函数*/
   void tick();

   bool empty() const { return cur_size == 0; }
};

class Utils
{
public:
    Utils(int cap = 10000) : m_timer_heap(cap) {}
    Utils(std::vector<heap_timer*> init_array, int size, int cap) : 
         m_timer_heap(init_array, size, cap)
      {}
    ~Utils() {}

    void init(int timeslot);

    //对文件描述符设置非阻塞
    int setnonblocking(int fd);

    //将内核事件表注册读事件，ET模式，选择开启EPOLLONESHOT
    void addfd(int epollfd, int fd, bool one_shot, int TRIGMode);

    //信号处理函数
    static void sig_handler(int sig);

    //设置信号函数
    void addsig(int sig, void(handler)(int), bool restart = true);

    //定时处理任务，重新定时以不断触发SIGALRM信号
    void timer_handler();

    void show_error(int connfd, const char* info);

public:
    static int*      u_pipefd;
    time_heap        m_timer_heap;
    static int       u_epollfd;
    int              m_TIMESLOT;
};

void cb_func(client_data *user_data);

#endif
