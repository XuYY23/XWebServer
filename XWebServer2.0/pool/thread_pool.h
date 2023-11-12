#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <exception>
#include <thread>
#include <vector>
#include <utility>
#include <iostream>

#include "../thread_safe_queue/thread_safe_queue.h"
#include "sqlconn_pool.h"

template <typename T>
class thread_pool
{
private:
    /*线程数量*/
    int                         m_thread_number;        

    /*线程池*/
    std::vector<std::thread>    m_threads;       

    /*工作队列*/
    thread_safe_queue<T*>       m_workqueue;

    /*标志工作线程是否结束运行*/
    bool m_stop;

    /*数据库*/
    connection_pool*            m_connPool; 

private:

    /*工作线程运行的函数，它不断从工作队列中取出任务并执行之*/
    static  void run(thread_pool<T>* arg);

public:
    /*
        thread_number是线程池中线程的数量
        max_requests是请求队列中最多允许的、等待处理的请求的数量
    */
    thread_pool(connection_pool* connPool, int thread_number = 8);

    ~thread_pool()
    {
        m_stop = true;
    }

    /*向线程池中添加任务*/
    void append(T* request);

};

/*-----------------------------------实现---------------------------------------------*/

template <typename T>
thread_pool<T>::thread_pool(connection_pool* connPool, int thread_number) : 
    m_thread_number(thread_number), 
    m_threads(m_thread_number),
    m_stop(false),
    m_connPool(connPool)
{
    if ( thread_number <= 0 )
        throw std::exception();

    for (int i = 0; i < thread_number; ++i)
    {
        m_threads[i] = std::move(std::thread(run, this));
        m_threads[i].detach();
    }
}

template <typename T>
void thread_pool<T>::run(thread_pool<T>* arg)
{
    while ( !arg->m_stop ) 
    {
       T* request = NULL;
       if( arg->m_workqueue.try_pop(request) == true)
       {
            /*
                每次处理一个http请求之前，先初始化数据库信息，
                该http请求结束后会自动归还数据库连接
            */
            connectionRAII mysqlcon(&request->mysql, arg->m_connPool);
            request->initmysql_result(arg->m_connPool);
            request->process();
       }
    }
}

template <typename T>
void thread_pool<T>::append(T* request)
{
    m_workqueue.push(request);
}

#endif
