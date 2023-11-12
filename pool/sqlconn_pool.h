
/*
	数据库连接池
	1、利用线程安全的队列管理连接池
	2、单例模式
	3、RAII手法管理每一个使用的连接
*/

#ifndef SQLCONN_POOL_
#define SQLCONN_POOL_

#include <mysql/mysql.h>
#include <string>

#include "../thread_safe_queue/thread_safe_queue.h"
#include "../log/log.h"

class connection_pool
{
private:
	connection_pool();
	~connection_pool();

	int 				m_MaxConn;  									//最大连接数
	int 				m_CurConn;  									//当前已使用的连接数
	int 				m_FreeConn; 									//当前空闲的连接数
	thread_safe_queue<MYSQL*> 	
						conn_Queue;										//连接池
	
public:
	std::string 	m_Url;			 								//主机地址
	std::string 	m_Port;											//数据库端口号
	std::string 	m_User;		 									//登陆数据库用户名
	std::string 	m_PassWord;	 									//登陆数据库密码
	std::string 	m_DatabaseName; 								//使用数据库名
	int 				m_close_log;									//日志开关

public:
	MYSQL* 			GetConnection();				 				//获取数据库连接
	bool 				ReleaseConnection(MYSQL* conn); 			//释放连接
	int 				GetFreeConn();					 				//获取连接
	void 				DestroyPool();					 				//销毁所有连接

	static connection_pool* 
						GetInstance();									//单例模式

	void 				init(std::string Url, std::string User, std::string PassWord, 
							  std::string DataBaseName, int Port, int MaxConn, int Close_Log); 
};


/*
	该类用于自动管理获取的数据库连接，如果其他地方需要获取一个数据库连接可以使用这个类，
	然后不需要做任何回收资源的操作
*/
class connectionRAII
{
private:
	MYSQL* 					conRAII;			//MySQL句柄	
	connection_pool*		poolRAII;		//数据库池

public:
	connectionRAII(MYSQL** con, connection_pool* connPool);
	~connectionRAII();

};

#endif