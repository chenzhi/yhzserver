#ifndef _CPP_MYSQL_1_H_
#define _CPP_MYSQL_1_H_

/*******************************************
mysql ��������
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
	//��ִ�п������캯��������������Ѿ���Ч��������ʹ��
	//CppMySQLQuery(CppMySQLQuery& rQuery);
	//��ִ�и�ֵ���캯����=�ұߵ����Ѿ���Ч��������ʹ��
	//CppMySQLQuery& operator=(CppMySQLQuery& rQuery);
	virtual ~CppMySQLQuery();
	u_long numRow();//������

	int numFields();//������

	int fieldIndex(const char* szField);

	//0...n-1��
	const char* fieldName(int nCol);
	//   const char* fieldDeclType(int nCol);
	//   int fieldDataType(int nCol);
	u_long seekRow(u_long offerset);

	int getIntField(int nField, int nNullValue=0);

	int getIntField(const char* szField, int nNullValue=0);

	double getFloatField(int nField, double fNullValue=0.0);

	double getFloatField(const char* szField, double fNullValue=0.0);
	//0...n-1��
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

	/*�����ݿ⣬�ɹ������棬ʧ�ܷ��ؼ�
	*/
	bool open(const char* host, const char* user, const char* passwd, const char* db,
		unsigned int port = 0, unsigned long client_flag = 0);
	
	/**�ر����ݿ�*/
	void close();
	
	/* ���ؾ�� */
	MYSQL* getMysql();

	/* �����ض��еĲ�ѯ��
	*@param pQuery ���ز�ѯ���
	*@return �ɹ�������ʧ�ܷ��ؼ�
	*/
	bool  querySQL(const char *sql,CppMySQLQuery** pQuery);


	/* ִ�зǷ��ؽ����ѯ,������Ӱ������� */
	int execSQL(const char* sql);


	/**����һ���Ƿ��ؽ���Ĵ洢����*
	*
	*/
	bool  execProcedurce(const char*  procedurceName);


	/**ִ��һ���з��ؽ���Ĵ������
	*@param pQuery ע����һ��ָ��ָ��Ĳ���������������гɹ����ز�ѯ���
	*���гɹ������棬ʧ�ܷ��ؼ�
	*@������̵��ð��� ,"call querystudent (1,@ret,@ out_name,@ out_age)"
	*/
	bool  execProcedurce(const char* procedurceName,CppMySQLQuery** pQuery);


	/* ����mysql�������Ƿ��� */
	bool  ping();


	/* �ر�mysql ������ */
	bool shutDown();


	/* ��Ҫ����:��������mysql ������ */
	int reboot();


	/**
	* ˵��:����֧��InnoDB or BDB������
	*/
	/* ��Ҫ����:��ʼ���� */
	int startTransaction();

	/** ��Ҫ����:�ύ���� */
	int commit();


	/** ��Ҫ����:�ع����� */
	int rollback();


	/** �õ��ͻ���Ϣ */
	const char * getClientInfo();


	/** ��Ҫ����:�õ��ͻ��汾��Ϣ */
	const unsigned long  getClientVersion();


	/** ��Ҫ����:�õ�������Ϣ */
	const char * getHostInfo();


	/** ��Ҫ����:�õ���������Ϣ */
	const char * getServerInfo();


	/**��Ҫ����:�õ��������汾��Ϣ*/
	const unsigned long  getServerVersion();


	/**��Ҫ����:�õ� ��ǰ���ӵ�Ĭ���ַ���*/
	const char *  getCharacterSetName();


	/** �õ�ϵͳʱ�� */
	const char * getSysTime();


	/** ���������ݿ� */
	int createDB(const char* name);

	/** ɾ���ƶ������ݿ�*/
	int dropDB(const char* name);

	//bool tableExists(const char* table);

	//u_int lastRowId();


private:

	/* msyql ���Ӿ�� */
	MYSQL* _db_ptr;


	CppMySQLQuery _db_query;
};



#endif
