///.cpp
////////////////////////////////////////////////////////////////////////////////
// CppMysql - A C++ wrapper around the mysql database library.
//
// Copyright (c) 2009 Rob Groves. All Rights Reserved. 
//lizp.net@gmail.com
// 
// Permission to use, copy, modify, and distribute this software and its
// documentation for any purpose, without fee, and without a written
// agreement, is hereby granted, provided that the above copyright notice, 
// this paragraph and the following two paragraphs appear in all copies, 
// modifications, and distributions.
//
// IN NO EVENT SHALL THE AUTHOR BE LIABLE TO ANY PARTY FOR DIRECT,
// INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST
// PROFITS, ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION,
// EVEN IF THE AUTHOR HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// THE AUTHOR SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
// PARTICULAR PURPOSE. THE SOFTWARE AND ACCOMPANYING DOCUMENTATION, IF
// ANY, PROVIDED HEREUNDER IS PROVIDED "AS IS". THE AUTHOR HAS NO OBLIGATION
// TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
//
// u can use it for anything, but u must show the source
// frome 
//http://rainfish.cublog.cn
// by ben
// if u find some questions, please tell me with email
//
// V1.0  18/09/2009 -Initial Version for cppmysql
////////////////////////////////////////////////////////////////////////////////
#include "pch.h"
#include "databaseInstance.h"
#include "xLogManager.h"



//--------------------------------------------------------------------------------
CppMySQLQuery::CppMySQLQuery()
{
	_mysql_res = NULL;
	_field = NULL;
	_row = NULL;
}

////--------------------------------------------------------------------------------
//CppMySQLQuery::CppMySQLQuery(CppMySQLQuery& rQuery)
//{
//	*this = rQuery;
//}
//
////--------------------------------------------------------------------------------
//CppMySQLQuery& CppMySQLQuery::operator=(CppMySQLQuery& rQuery)
//{
//	if ( this == &rQuery )
//		return *this;
//	_mysql_res = rQuery._mysql_res;
//	_row = NULL;
//	_row_count = 0;
//	_field_count = 0;
//	_field = NULL;
//	if ( _mysql_res != NULL )
//	{
//		//��λ�α�λ�õ���һ��λ��
//		mysql_data_seek(_mysql_res, 0);
//		_row =  mysql_fetch_row( _mysql_res );
//		_row_count = mysql_num_rows( _mysql_res ); 
//		//�õ��ֶ�����
//		_field_count = mysql_num_fields( _mysql_res );
//	}
//	rQuery._mysql_res = NULL;
//	rQuery._field = NULL;
//	rQuery._row = NULL;
//	rQuery._row_count = 0;
//	rQuery._field_count = 0;
//	return *this;
//}

//--------------------------------------------------------------------------------
CppMySQLQuery::~CppMySQLQuery()
{
	freeRes();
}

//--------------------------------------------------------------------------------
void CppMySQLQuery::freeRes()
{
	if ( _mysql_res != NULL )
	{
		mysql_free_result(_mysql_res);
		_mysql_res = NULL;
	}
}

//--------------------------------------------------------------------------------
u_long CppMySQLQuery::numRow()
{
	if(_mysql_res==NULL)
		return 0;
	return _mysql_res->row_count;
}

//--------------------------------------------------------------------------------
int CppMySQLQuery::numFields()
{
	if(_mysql_res==NULL)
		return 0;
	return _mysql_res->field_count;
}
//--------------------------------------------------------------------------------
u_long CppMySQLQuery::seekRow(u_long offerset)
{
	if(_mysql_res==NULL)
		return 0;

	if ( offerset == numRow() )
	{
		offerset = numRow() -1;
	}

	mysql_data_seek(_mysql_res, offerset);
	_row = mysql_fetch_row(_mysql_res);
	return offerset;
}

//--------------------------------------------------------------------------------

int CppMySQLQuery::fieldIndex(const char* szField)
{
	if ( NULL == _mysql_res )
		return -1;
	if ( NULL == szField )
		return -1;
	mysql_field_seek(_mysql_res, 0);//��λ����0��
	u_int i = 0;
	while ( i < numFields() )
	{
		_field = mysql_fetch_field( _mysql_res );
		if ( _field != NULL && strcmp(_field->name, szField) == 0 )//�ҵ�
			return i;
		i++;
	}
	return -1;
}

//--------------------------------------------------------------------------------
const char* CppMySQLQuery::fieldName(int nCol)
{
	if ( _mysql_res == NULL )
		return NULL;
	mysql_field_seek(_mysql_res, nCol);
	_field = mysql_fetch_field(_mysql_res);
	if ( _field != NULL )
		return _field->name;
	else
		return  NULL;
}

//--------------------------------------------------------------------------------
int CppMySQLQuery::getIntField(int nField, int nNullValue/*=0*/)
{
	if ( NULL == _mysql_res )
		return nNullValue;

	if ( nField + 1 > (int)numFields() )
		return nNullValue;

	if ( NULL == _row )
		return nNullValue;

	return atoi(_row[nField]);
}


//--------------------------------------------------------------------------------
int CppMySQLQuery::getIntField(const char* szField, int nNullValue/*=0*/)
{
	if ( NULL == _mysql_res || NULL == szField )
		return nNullValue;

	if ( NULL == _row )
		return nNullValue;
	const char* filed = getStringField(szField);
	if ( NULL == filed )
		return nNullValue;
	return atoi(filed);
}

//--------------------------------------------------------------------------------
const char* CppMySQLQuery::getStringField(int nField, const char* szNullValue/*=""*/)
{
	if ( NULL == _mysql_res )
		return szNullValue;
	if ( nField + 1 > (int)numFields() )
		return szNullValue;
	if ( NULL == _row )
		return szNullValue;
	return _row[nField];
}


//-----------------------------------------------------------------------------------------
const char* CppMySQLQuery::getStringField(const char* szField, const char* szNullValue/*=""*/)
{
	if ( NULL == _mysql_res )
		return szNullValue;
	int nField = fieldIndex(szField);
	if ( nField == -1 )
		return szNullValue;

	return getStringField(nField);
}

//-----------------------------------------------------------------------------------------
double CppMySQLQuery::getFloatField(int nField, double fNullValue/*=0.0*/)
{
	const char* field = getStringField(nField);
	if ( NULL == field )
		return fNullValue;
	return atol(field);
}


//-----------------------------------------------------------------------------------------
double CppMySQLQuery::getFloatField(const char* szField, double fNullValue/*=0.0*/)
{
	const char* field = getStringField(szField);
	if ( NULL == field )
		return fNullValue;
	return atol(field);
}

//----------------------------------------------------------------------
void CppMySQLQuery::nextRow()
{
	if ( NULL == _mysql_res )
		return;
	_row = mysql_fetch_row(_mysql_res);
}

//----------------------------------------------------------------------
bool CppMySQLQuery::eof()
{
	if ( _row == NULL )
		return true;
	return false;
}


//----------------------------------------------------------------------

template<>DatabaseInstace* Singleton<DatabaseInstace>::ms_Singleton=NULL;

//----------------------------------------------------------------------
DatabaseInstace::DatabaseInstace()
{
	_db_ptr = NULL;
}

//----------------------------------------------------------------------
DatabaseInstace::~DatabaseInstace()
{
	close();

}

//----------------------------------------------------------------------
bool  DatabaseInstace::open(const char* host, const char* user, const char* passwd, const char* db,
					unsigned int port /*= 0*/, unsigned long client_flag /*= 0*/)
{

	_db_ptr = mysql_init(NULL);
	if( NULL == _db_ptr ) 
		return false;

	//�������ʧ�ܣ�����NULL�����ڳɹ������ӣ�����ֵ���1��������ֵ��ͬ��
	if ( NULL == mysql_real_connect( _db_ptr, host, user, passwd, db,port, NULL, client_flag) )
		return false;
	//ѡ���ƶ������ݿ�ʧ��
	//0��ʾ�ɹ�����0ֵ��ʾ���ִ���
	if ( mysql_select_db( _db_ptr, db ) != 0 ) 
	{
		mysql_close(_db_ptr);
		_db_ptr = NULL;
		return false;
	}

	return true;
}

//----------------------------------------------------------------------
void DatabaseInstace::close()
{
	if ( _db_ptr != NULL )
	{
		mysql_close( _db_ptr );
		_db_ptr = NULL;
	}
}

//----------------------------------------------------------------------
MYSQL* DatabaseInstace::getMysql()
{
	return _db_ptr;
}


/* �����ض��еĲ�ѯ������Ӱ������� */
CppMySQLQuery& DatabaseInstace::querySQL(const char *sql)
{
	if ( !mysql_real_query( _db_ptr, sql, strlen(sql) ) )
	{
		_db_query._mysql_res = mysql_store_result( _db_ptr );
		_db_query.seekRow(0);
		//   _db_query._row =  mysql_fetch_row( _db_query._mysql_res );
		//   _db_query._row_count = mysql_num_rows( _db_query._mysql_res ); 
		//   //�õ��ֶ�����
		//   _db_query._field_count = mysql_num_fields( _db_query._mysql_res );
	}else
	{
		const char* perror=mysql_error(_db_ptr);
		xLogMessager::getSingleton().logMessage(std::string("DatabaseInstace::querySQL failed ,")+perror);
	}
	return _db_query;
}


/* ִ�зǷ��ؽ����ѯ */
int DatabaseInstace::execSQL(const char* sql)
{
	if( !mysql_real_query( _db_ptr, sql, strlen(sql) ) )
	{
		//�õ���Ӱ�������
		return (int)mysql_affected_rows(_db_ptr) ;
	}
	else
	{
		//ִ�в�ѯʧ��
		return -1;
	}
}


/* ����mysql�������Ƿ��� */
int DatabaseInstace::ping()
{
	if( mysql_ping(_db_ptr) == 0 )
		return 0;
	else 
		return -1; 
}


/* �ر�mysql ������ */
int DatabaseInstace::shutDown()
{
	if( mysql_shutdown(_db_ptr,SHUTDOWN_DEFAULT) == 0 )
		return 0;
	else 
		return -1;
}


/* ��Ҫ����:��������mysql ������ */
int DatabaseInstace::reboot()
{
	if(!mysql_reload(_db_ptr))
		return 0;
	else
		return -1;
}


/*
* ˵��:����֧��InnoDB or BDB������
*/
/* ��Ҫ����:��ʼ���� */
int DatabaseInstace::startTransaction()
{
	if(!mysql_real_query(_db_ptr, "START TRANSACTION" ,(unsigned long)strlen("START TRANSACTION" )))
	{
		return 0;
	}
	else
	{
		//ִ�в�ѯʧ��
		return -1;
	}

}


/* ��Ҫ����:�ύ���� */
int DatabaseInstace::commit()
{
	if(!mysql_real_query( _db_ptr, "COMMIT",(unsigned long)strlen("COMMIT" ) ))
	{
		return 0;
	}
	else    
	{
		//ִ�в�ѯʧ��
		return -1;
	}
}


/* ��Ҫ����:�ع����� */
int DatabaseInstace::rollback()
{
	if(!mysql_real_query(_db_ptr, "ROLLBACK",(unsigned long)strlen("ROLLBACK" )) )
		return 0;
	else  
		//ִ�в�ѯʧ��
		return -1; 
}


/* �õ��ͻ���Ϣ */
const char * DatabaseInstace::getClientInfo()
{
	return mysql_get_client_info();
}


/* ��Ҫ����:�õ��ͻ��汾��Ϣ */
const unsigned long  DatabaseInstace::getClientVersion()
{
	return mysql_get_client_version();
}


/* ��Ҫ����:�õ�������Ϣ */
const char * DatabaseInstace::getHostInfo()
{
	return mysql_get_host_info(_db_ptr);
}


/* ��Ҫ����:�õ���������Ϣ */
const char * DatabaseInstace::getServerInfo()
{
	return mysql_get_server_info( _db_ptr ); 
}


/*��Ҫ����:�õ��������汾��Ϣ*/
const unsigned long  DatabaseInstace::getServerVersion()
{
	return mysql_get_server_version(_db_ptr);
}


/*��Ҫ����:�õ� ��ǰ���ӵ�Ĭ���ַ���*/
const char *  DatabaseInstace::getCharacterSetName()
{
	return mysql_character_set_name(_db_ptr);
}


/* �õ�ϵͳʱ�� */
const char * DatabaseInstace::getSysTime()
{
	//return ExecQueryGetSingValue("select now()";
	return NULL;
}


/* ���������ݿ� */
int DatabaseInstace::createDB(const char* name)
{
	char temp[1024];
	sprintf(temp, "CREATE DATABASE %s", name);
	if(!mysql_real_query( _db_ptr, temp, strlen(temp)) )
		return 0;

	else
		//ִ�в�ѯʧ��
		return -1;
}


/* ɾ���ƶ������ݿ�*/
int DatabaseInstace::dropDB(const char*  name)
{
	char temp[1024];

	sprintf(temp, "DROP DATABASE %s", name);
	if(!mysql_real_query( _db_ptr, temp, strlen(temp)) )
		return 0;
	else
		//ִ�в�ѯʧ��
		return -1;
}

//-------------------------------------------------------------------
//bool DatabaseInstace::tableExists(const char* table)
//{
//	return false;
//}
//
////-------------------------------------------------------------------
//u_int DatabaseInstace::lastRowId()
//{
//	return 0;
//}
