#include "sqlconn_pool.h"


connection_pool::connection_pool() : m_MaxConn(0), m_CurConn(0), m_FreeConn(0)
{
	
}

connection_pool::~connection_pool()
{
	DestroyPool();
}

connection_pool* connection_pool::GetInstance()
{
	static connection_pool connPool;
	return &connPool;
}

//构造初始化
void connection_pool::init(std::string Url, std::string User, std::string PassWord, 
						std::string DataBaseName, int Port, int MaxConn, int Close_Log)
{
   m_Url = Url;
   m_User = User;
   m_PassWord = PassWord;
   m_DatabaseName = DataBaseName;
   m_Port = Port;
   m_MaxConn = MaxConn;
   m_close_log = Close_Log;

   /*在连接池中放入 maxconn 个数据库连接*/
	for (int i = 0; i < MaxConn; i++)
	{
      /*初始化一个连接*/
		MYSQL* con = NULL;
		con = mysql_init(con);

		if ( con == NULL )
		{
			LOG_ERROR("MySQL Error");
			exit(1);
		}

      /*与数据库连接*/
		con = mysql_real_connect(con, Url.c_str(), User.c_str(), PassWord.c_str(), 
                                 DataBaseName.c_str(), Port, NULL, 0);

		if ( con == NULL )
		{
			LOG_ERROR("MySQL Error");
			exit(1);
		}

		conn_Queue.push(con);
		++m_FreeConn;
	}
}


//当有请求时，从数据库连接池中返回一个可用连接，更新使用和空闲连接数
MYSQL* connection_pool::GetConnection()
{
	MYSQL* con = NULL;

	if ( conn_Queue.empty() )
		return NULL;

	conn_Queue.wait_and_pop(con);

	--m_FreeConn;
	++m_CurConn;

	return con;
}

//释放当前使用的连接
bool connection_pool::ReleaseConnection(MYSQL* con)
{
	if ( con == NULL )
		return false;

   conn_Queue.push(con);

	++m_FreeConn;
	--m_CurConn;

	return true;
}

//销毁数据库连接池
void connection_pool::DestroyPool()
{

   while( !conn_Queue.empty() )
   {
      MYSQL* con = *(conn_Queue.wait_and_pop());
      mysql_close(con);
   }

   m_CurConn = 0;
   m_FreeConn = 0;
}

//当前空闲的连接数
int connection_pool::GetFreeConn()
{
	return m_FreeConn;
}

connectionRAII::connectionRAII(MYSQL** SQL, connection_pool* connPool)
{
	*SQL = connPool->GetConnection();
	conRAII = *SQL;
	poolRAII = connPool;
}

connectionRAII::~connectionRAII()
{
	poolRAII->ReleaseConnection(conRAII);
}