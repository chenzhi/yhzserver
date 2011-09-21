//-----------------------------------------------------------------------
// Author: Tangbin
// Create Time: 2008.8.21
// Summary: Define ADO function
//-----------------------------------------------------------------------
#pragma  once 

//#include "TBADOInclude.h"

#define _DBGetRec(Rs, fieldName) (Rs->Fields->Item[_variant_t(fieldName)]->Value)

struct volumn
{
	char name[32];
	char type[30];
	char dvalue[20];
};

class TBADOConnection
{
//-------------------- Constructor and Destructor -------------------
public:
	TBADOConnection();
	virtual ~TBADOConnection();

//-------------------- Methods --------------------------------------
public:
	bool			OpenConnect(const char* szProvider, const char* szDataSource, 
								const char* szDB, const char* szUserID, const char* szPassword);

	bool			OnenConnect(const char* szDNSSource, const char* szUserID = NULL, const char* szPassword = NULL);

	bool			OpenConn(const char* szConn);

	void			CloseConnection(void);

	void			Init();

	void			UnInit();

	void			AddColumn( char* szTableName, volumn* pColumn, int nCnt );

	_RecordsetPtr	ExecuteRS( char* szFormat, ... );
	HRESULT			ExecuteNoRS( char* szFormat, ... );

//-------------------- Members --------------------------------------
protected:
	_ConnectionPtr	m_pConnection;
	_RecordsetPtr	m_pRecordset;
	_CommandPtr		m_pCommondPtr;

	bool			m_bInit;

	bool			m_bConnected;
};
