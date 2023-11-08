#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <list>
#include <cstdio>
#include <exception>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>

template<typename T>
class thread_pool
{
private:
	int m_thread_number;							/*线程池中的线程数*/
	int m_max_requests;							/*请求队列中允许的最大请求数*/
	std::vector<std::thread> m_threads;		/*线程池数组*/
	std::list<T*> m_workqueue;					/*请求队列*/
	std::mutex m_queuelocker;					/*保护请求队列的互斥锁*/
	std::condition_variable m_queuestat;	/*是否有任务需要处理*/
	bool m_stop;								/*是否结束线程*/

public:
	thread_pool(int thread_number = 8, int max_requests = 10000);
	~thread_pool();
	bool append(T* request);	/*往队列里添加任务*/

private:
	static void* worker(void*);	/*工作线程运行的函数，它不断从工作队列中取出任务并执行*/
	void run();
};

template<typename T>
thread_pool<T>::thread_pool(int thread_number, int max_requests) :
	m_thread_number(thread_number), m_max_requests(max_requests),
	m_stop(false)
{
	if ( ( thread_number <= 0 ) || ( max_requests <= 0 ) )
	{
		throw std::exception();
	}

	try
	{
		for (int i = 0; i < thread_number; ++i)
		{
			printf("create the %dth thread\n", i);
			std::thread t(worker, this);
			m_threads.push_back(std::move(t));
			m_threads[i].detach();
		}
	}
	catch (...)
	{
		throw std::exception();
	}
}

template<typename T>
thread_pool<T>::~thread_pool()
{
	m_stop = true;
	m_queuestat.notify_all();
}

template<typename T>
bool thread_pool<T>::append(T* request)
{
	std::unique_lock<std::mutex> lk(m_queuelocker);
	if (m_workqueue.size() > m_max_requests)
	{
		lk.unlock();
		return false;
	}
	m_workqueue.push_back(request);
	lk.unlock();
	m_queuestat.notify_one();	/*一旦有任务就唤醒一个正在等待的工作线程*/
	return true;
}

template<typename T>
void* thread_pool<T>::worker(void* arg)
{
	thread_pool* pool = (thread_pool*)arg;
	pool->run();
	return pool;
}

template<typename T>
void thread_pool<T>::run()
{
	while (!m_stop)
	{
		std::unique_lock<std::mutex> lk(m_queuelocker);
      /*
         这里我改变了书中的代码，使用了c++的条件变量
         但是这样就必须在线程池中的析构函数中将所有等待的条件变量唤醒，并让m_stop也成为等待条件
         否则工作线程会一直阻塞在这里
         c++的信号量在c++20才引入，这里没有使用
      */
		m_queuestat.wait(lk, [this] {return m_stop || !m_workqueue.empty(); });
		if (m_stop)break;
		T* request = m_workqueue.front();
		m_workqueue.pop_front();
		lk.unlock();
		if (!request)
		{
			continue;
		}
		request->process();	/*该函数需要模板参数类自行完成*/
	}
}

#endif
