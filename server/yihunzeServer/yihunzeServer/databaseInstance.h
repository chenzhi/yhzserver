#ifndef _CPP_MYSQL_1_H_
#define _CPP_MYSQL_1_H_

/*******************************************
mysql 的连接类
**********************************************************/
#include "mysql.h"
#include "Singleton.h"




typedef unsigned int u_int;
typedef unsigned long u_long;
typedef MYSQL*  DB_HANDLE;


class DatabaseInstace;


class CppMySQLQuery
{
	friend class DatabaseInstace;
public:
	CppMySQLQuery();
	//当执行拷贝构造函数后，括号里的类已经无效，不能再使用
	//CppMySQLQuery(CppMySQLQuery& rQuery);
	//当执行赋值构造函数后，=右边的类已经无效，不能再使用
	//CppMySQLQuery& operator=(CppMySQLQuery& rQuery);
	virtual ~CppMySQLQuery();
	u_long numRow();//多少行

	int numFields();//多少列

	int fieldIndex(const char* szField);

	//0...n-1列
	const char* fieldName(int nCol);
	//   const char* fieldDeclType(int nCol);
	//   int fieldDataType(int nCol);
	u_long seekRow(u_long offerset);

	int getIntField(int nField, int nNullValue=0);

	int getIntField(const char* szField, int nNullValue=0);

	double getFloatField(int nField, double fNullValue=0.0);

	double getFloatField(const char* szField, double fNullValue=0.0);
	//0...n-1列
	const char* getStringField(int nField, const char* szNullValue="");
	const char* getStringField(const char* szField, const char* szNullValue="");
	const unsigned char* getBlobField(int nField, int& nLen);
	const unsigned char* getBlobField(const char* szField, int& nLen);
	bool fieldIsNull(int nField);
	bool fieldIsNull(const char* szField);
	bool eof();
	void nextRow();
	void finalize();
private:
	void freeRes();
	void checkVM();
private:
	MYSQL_RES*  _mysql_res;
	MYSQL_FIELD* _field;
	MYSQL_ROW  _row;
	//u_long   _row_count;
	//u_int   _field_count;
};



class DatabaseInstace :public Singleton<DatabaseInstace>
{
public:

	DatabaseInstace();

	virtual ~DatabaseInstace();

	/*打开数据库，成功返回真，失败返回假
	*/
	bool open(const char* host, const char* user, const char* passwd, const char* db,
		unsigned int port = 0, unsigned long client_flag = 0);
	
	/**关闭数据库*/
	void close();
	
	/* 返回句柄 */
	MYSQL* getMysql();

	/* 处理返回多行的查询，
	*@param pQuery 返回查询结果
	*@return 成功返回真失败返回假
	*/
	bool  querySQL(const char *sql,CppMySQLQuery** pQuery);


	/* 执行非返回结果查询,返回受影响的行数 */
	int execSQL(const char* sql);


	/**运行一个非返回结果的存储过程*
	*
	*/
	bool  execProcedurce(const char*  procedurceName);


	/**执行一个有返回结果的储存过程
	*@param pQuery 注意是一个指向指针的参数。如果函数运行成功返回查询结果
	*运行成功返回真，失败返回假
	*@储存过程调用案例 ,"call querystudent (1,@ret,@ out_name,@ out_age)"
	*/
	bool  execProcedurce(const char* procedurceName,CppMySQLQuery** pQuery);


	/* 测试mysql服务器是否存活 */
	bool  ping();


	/* 关闭mysql 服务器 */
	bool shutDown();


	/* 主要功能:重新启动mysql 服务器 */
	int reboot();


	/**
	* 说明:事务支持InnoDB or BDB表类型
	*/
	/* 主要功能:开始事务 */
	int startTransaction();

	/** 主要功能:提交事务 */
	int commit();


	/** 主要功能:回滚事务 */
	int rollback();


	/** 得到客户信息 */
	const char * getClientInfo();


	/** 主要功能:得到客户版本信息 */
	const unsigned long  getClientVersion();


	/** 主要功能:得到主机信息 */
	const char * getHostInfo();


	/** 主要功能:得到服务器信息 */
	const char * getServerInfo();


	/**主要功能:得到服务器版本信息*/
	const unsigned long  getServerVersion();


	/**主要功能:得到 当前连接的默认字符集*/
	const char *  getCharacterSetName();


	/** 得到系统时间 */
	const char * getSysTime();


	/** 建立新数据库 */
	int createDB(const char* name);

	/** 删除制定的数据库*/
	int dropDB(const char* name);

	//bool tableExists(const char* table);

	//u_int lastRowId();


private:

	/* msyql 连接句柄 */
	MYSQL* _db_ptr;


	CppMySQLQuery _db_query;
};



#endif
