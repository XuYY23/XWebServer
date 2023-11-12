#include "timer.h"
#include "../http/http.h"

time_heap::time_heap(int cap) :
   capacity(cap),
   cur_size(0),
   array(cap, NULL)
{

}

time_heap::time_heap(std::vector<heap_timer*> init_array, int size, int cap) :
   capacity(cap),
   cur_size(size),
   array(init_array)
{
   if( capacity < size )throw std::exception();

   if( size != 0 )
   {
      for(int i = (cur_size - 1) / 2; i >= 0; --i)
      {
         percolate_down(i);
      }
   }
}

void time_heap::add_timer(heap_timer* timer)
{
   if( !timer )return;

   if( cur_size >= capacity )
   {
      resize();
   }

   /*新插入一个元素，当前堆大小加1，hole 是新建空穴的位置*/
   int hole = cur_size++;
   int parent = 0;

   /*对从空穴到根节点的路径上的所有节点执行上滤操作*/
   for(; hole > 0; hole = parent)
   {
      parent = (hole - 1) / 2;

      if( array[parent]->expire <= timer->expire )
      {
         break;
      }
      array[hole] = array[parent];
   }
   array[hole] = timer;
}

void time_heap::del_timer(heap_timer* timer)
{
   /*
      原本是想直接copy游双大佬的定时器，但是出了bug
      原始版本是不删除定时器在这个函数中，只是单纯将回调函数设置为空（延迟删除）
      但是这样会导致数组彭转太快，出现内存问题
      所以只能在这里删除了
   */
   if( !timer )return;
   int index = -1;
   for(int i = 0; i < cur_size; i++)
   {
      if( array[i] == timer )
      {
         index = i;
         break;
      }
   }
   assert( index != -1 );
   array[index] = array[--cur_size];
   percolate_down(index);
}

heap_timer* time_heap::top() const
{
   if( empty() )
      return NULL;
   return array[0];
}

void time_heap::pop_timer()
{
   if( empty() )return;
   if( array[0] )
   {
      delete array[0];
      /*将原来的堆顶元素替换为堆数组最后一个元素*/
      array[0] = array[--cur_size];
      /*对堆顶元素执行下滤操作*/
      percolate_down(0);
   }
}

void time_heap::tick()
{
   heap_timer* tmp = array[0];
   /*获取当前时间，然后循环处理到期的定时器*/
   time_t cur = time(NULL);
   while( !empty() )
   {
      if( !tmp )break;

      /*如果堆顶的定时器没到期，则退出循环*/
      if( tmp->expire > cur )break;

      /*否则执行回调函数*/
      if( array[0]->cb_func )array[0]->cb_func(array[0]->user_data);

      pop_timer();
      tmp = array[0];
   }
}

void time_heap::percolate_down(int hole)
{
   heap_timer* tmp = array[hole];
   int child = 0;
   for(; ((hole * 2 + 1) <= (cur_size - 1)); hole = child)
   {
      child = hole * 2 + 1;

      /*找到左右孩子中的较小值*/
      if( (child < (cur_size - 1)) && (array[child + 1]->expire < array[child]->expire) )
      {
         ++child;
      }

      if( array[child]->expire < tmp->expire )
      {
         array[hole] = array[child];
      }
      else break;
   }
   array[hole] = tmp;
}

void time_heap::resize()
{
   std::vector<heap_timer*> tmp(capacity * 2, NULL);
   for(int i = 0; i < cur_size; ++i)
   {
      tmp[i] = array[i];
   }
   std::swap(array, tmp);
}

int* Utils::u_pipefd = 0;
int Utils::u_epollfd = 0;

void Utils::init(int timeslot)
{
   m_TIMESLOT = timeslot;
}

//对文件描述符设置非阻塞
int Utils::setnonblocking(int fd)
{
   int old_option = fcntl(fd, F_GETFL);
   int new_option = old_option | O_NONBLOCK;
   fcntl(fd, F_SETFL, new_option);
   return old_option;
}

//将内核事件表注册读事件，ET模式，选择开启EPOLLONESHOT
void Utils::addfd(int epollfd, int fd, bool one_shot, int TRIGMode)
{
   epoll_event event;
   event.data.fd = fd;

   if ( TRIGMode == 1 )
      event.events = EPOLLIN | EPOLLET | EPOLLRDHUP;
   else
      event.events = EPOLLIN | EPOLLRDHUP;

   if ( one_shot )
      event.events |= EPOLLONESHOT;
   epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
   setnonblocking(fd);
}

//信号处理函数
void Utils::sig_handler(int sig)
{
   //为保证函数的可重入性，保留原来的errno
   int save_errno = errno;
   int msg = sig;
   send(u_pipefd[1], (char *)&msg, 1, 0);
   errno = save_errno;
}

//设置信号函数
void Utils::addsig(int sig, void(handler)(int), bool restart)
{
   struct sigaction sa;
   memset(&sa, '\0', sizeof(sa));
   sa.sa_handler = handler;
   if ( restart )
      sa.sa_flags |= SA_RESTART;
   sigfillset(&sa.sa_mask);
   assert(sigaction(sig, &sa, NULL) != -1);
}

//定时处理任务，重新定时以不断触发SIGALRM信号
void Utils::timer_handler()
{
   m_timer_heap.tick();
   alarm(m_TIMESLOT);
}

void Utils::show_error(int connfd, const char *info)
{
   send(connfd, info, strlen(info), 0);
   close(connfd);
}

class Utils;
void cb_func(client_data* user_data)
{
   epoll_ctl(Utils::u_epollfd, EPOLL_CTL_DEL, user_data->sockfd, 0);
   assert(user_data);
   close(user_data->sockfd);
   http::m_user_count--;
}
