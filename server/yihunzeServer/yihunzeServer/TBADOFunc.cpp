#pragma once
#include "pch.h"
#include "TBADOInclude.h"


TBADOConnection::TBADOConnection()
{
	m_pConnection = NULL;
	m_pRecordset = NULL;
	m_pCommondPtr = NULL;

	CoInitialize(NULL);

	m_bInit = false;
	m_bConnected = false;
}

TBADOConnection::~TBADOConnection()
{
	CoUninitialize();
}

bool TBADOConnection::OpenConnect(const char* szProvider, const char* szDataSource, const char* szDB,
								  const char* szUserID, const char* szPassword)
{
	char szConn[MAX_PATH];
	sprintf(szConn, "Provider=%s;Data Source=%s;Initial Catalog=%s;User Id=%s;Password=%s;", 
						szProvider, 
						szDataSource,
						szDB,
						szUserID,
						szPassword);
	return OpenConn(szConn);
}

bool TBADOConnection::OnenConnect( const char* szDNSSource, const char* szUserID /*= NULL*/, 
								   const char* szPassword /*= NULL*/ )
{
	char szConn[MAX_PATH];
	//sprintf(szConn, "Data Source=%s;UID=%s;PWD=%s;", szDNSSource, szUserID, szPassword);
	sprintf(szConn, "Data Source=%s;UID=;PWD=;", szDNSSource);

	return OpenConn(szConn);
}

bool TBADOConnection::OpenConn(const char* szConn)
{
	try
	{
		HRESULT hRet;
		//if ( !bool( m_pConnection ) )
		//{
		//	hRet = m_pConnection.CreateInstance( /*__uuidof(_Connection)*/"ADODB.Connection" );
		//	if ( !SUCCEEDED(hRet) )
		//	{
		//		//TBDebugOut(  TEXT("CreateInstance error.") );
		//		return false;
		//	}
		//}

		Init();

		//m_pConnection->CursorLocation = adUseClient;

		if ( ( hRet = m_pConnection->Open( szConn,  "",  "" , adModeUnknown ) ) < 0 )
		{
			//TBDebugOut( TEXT("Open[%s] error!"), szConn );
			return false;
		}

		m_bConnected = true;
		//m_strConnection = szConn;

		//TBDebugOut(  TEXT("Open[%s] connected."), szConn );
	}
	catch( _com_error e )
	{
		//TT_DEBUG_OUT_COM_ERROR( e );
		int nError = GetLastError();
		//_bstr_t strt  = e.Description;
		//std::string errormessage;

		//errormessage.Format("Warning: 连接数据库发生异常. 错误信息: %s; 文件: %s; 行: %dn", e.ErrorMessage(), __FILE__, __LINE__);
//
		return false;
	}
	return true;
}

void TBADOConnection::CloseConnection(void)
{
	HRESULT hRet;
	
	if( m_pRecordset )
	{
		m_pRecordset->Update();
		m_pRecordset->Close();
	}

	if ( m_pConnection )
	{
		if( ( hRet = m_pConnection->Close() ) < 0 )
		{
			//TBDebugOut(  TEXT("Connection close failed!")  );
		}
		else
		{
			//TBDebugOut(  TEXT("Connection closed.")  );
		}
	}
}

void TBADOConnection::Init( )
{
	if ( !m_bInit )
	{
		m_pConnection.CreateInstance( "ADODB.Connection" );
		//m_pCommondPtr.CreateInstance( );
		m_pCommondPtr.CreateInstance(__uuidof(Command)); 
		m_bInit = true;
	}
}

void TBADOConnection::UnInit()
{
	if ( m_pConnection )
	{
		if ( m_pConnection->State == adStateOpen )
		{
			m_pConnection->Close();
			m_pConnection.Release();
		}
		m_pConnection = NULL;
	}

	if ( m_pCommondPtr )
	{
		m_pCommondPtr.Release();
		m_pCommondPtr = NULL;
	}

	m_bInit = false;
}

HRESULT	TBADOConnection::ExecuteNoRS( char* szFormat, ... )
{
	try 
	{
		char szSQL[1024*10];
		int nMaxBufSize = sizeof(szSQL)-1;
		_vsnprintf( szSQL, nMaxBufSize, szFormat, (char*)(&szFormat+1));

		m_pConnection->Execute( szSQL, NULL, adExecuteNoRecords );

		return S_OK;
	}
	catch( _com_error e )
	{
		//std::string errormessage;

		//errormessage.Format("Warning: 错误信息: %s; ", (char*)e.Description() );
	}
	
	return E_FAIL;
}

_RecordsetPtr TBADOConnection::ExecuteRS( char* szFormat, ... )
{
	try 
	{
		char szSQL[1024*10];
		int nMaxBufSize = sizeof(szSQL)-1;
		_vsnprintf( szSQL, nMaxBufSize, szFormat, (char*)(&szFormat+1));

		_RecordsetPtr pRecordset;
		pRecordset.CreateInstance( __uuidof(Recordset) );

		m_pCommondPtr->ActiveConnection = m_pConnection;
		m_pCommondPtr->CommandType = adCmdText;
		m_pCommondPtr->CommandText = szSQL;
		
		_variant_t vNull;
		vNull.vt = VT_ERROR;
		vNull.scode = DISP_E_PARAMNOTFOUND;
		pRecordset = m_pCommondPtr->Execute( &vNull, &vNull, adCmdText );

		return pRecordset;
	}
	catch( _com_error e )
	{
	    //wxString errormessage;

		//errormessage.Format("Warning: 错误信息: %s; ", (char*)e.Description() );
	}
	
	return NULL;
}

void TBADOConnection::AddColumn( char* szTableName, volumn* pColumn, int nCnt )
{
	if ( nCnt <= 0 ) return;

	for ( int i = 0; i < nCnt; ++i )
	{
		ExecuteRS( "ALTER TABLE %s ADD %s %s NOT NULL DEFAULT %s", szTableName, pColumn[i].name, pColumn[i].type, pColumn[i].dvalue );
	}
}