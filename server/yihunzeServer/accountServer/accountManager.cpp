
#include "pch.h"
#include "accountManager.h"
#include "usermessage.h"


//---------------------------------------------------------------------
AccountManager::AccountManager()
{

	init();


	//createAccount("插入中文试一下看能插几个","111");

	checkAccount("testplayer","11111");


}


//---------------------------------------------------------------------
AccountManager::~AccountManager()
{

	destroy();
}


//---------------------------------------------------------------------
void AccountManager::init()
{
	NetWorkServer* pNetWork=NetWorkServer::getSingletonPtr();
	assert(pNetWork);

	pNetWork->registerMessageHandle(GM_ACCOUNT_REQUEST,&AccountManager::processAccountTest,this);

}


//---------------------------------------------------------------------
void AccountManager::destroy()
{


	NetWorkServer* pNetWork=NetWorkServer::getSingletonPtr();
	if(pNetWork!=NULL)
	{
      pNetWork->unregisterMessageHandle(GM_ACCOUNT_REQUEST,this);
	}

	


}


//---------------------------------------------------------------------
void AccountManager::processAccountTest(NetPack* pPack)
{
	
	UserAccount* puser=reinterpret_cast<UserAccount*>(pPack->getData());
	RespondAccount respond;
	memset(&respond,0,sizeof(RespondAccount));
	strcpy(respond.m_userip,puser->m_ip);

	if(checkAccount(puser->m_account,puser->m_password))
	{
     	respond.m_login=1;
	}else
	{
       	respond.m_login=0;
	}
	NetWorkServer::getSingleton().send( GM_ACCOUNT_RESPOND,respond,pPack->getAddress());

	return ;
}


//---------------------------------------------------------------------
bool AccountManager:: createAccount(const std::string& accountName,const std::string& password)
{

	char Procedurce[512];
	::ZeroMemory(Procedurce,512);
	_snprintf(Procedurce,512,"call createaccount('%s','%s',@ret)",accountName.c_str(),password.c_str());
     
	if(DatabaseInstace::getSingleton().execProcedurce(Procedurce)==false)
	{
		return false;
	}

	CppMySQLQuery* pQuery=NULL;

	if(DatabaseInstace::getSingleton().querySQL("SELECT @ret",&pQuery)==false)
		return false;

	unsigned int result=pQuery->getIntField("@ret",0);
	if(result==0)
		return false;


	return  true;

}


//---------------------------------------------------------------------
bool AccountManager::checkAccount(const std::string& accountName,const std::string& password)
{

	char Procedurce[512];
	::ZeroMemory(Procedurce,512);
	_snprintf(Procedurce,512,"call hasaccount('%s','%s',@ret)",accountName.c_str(),password.c_str());

	if(DatabaseInstace::getSingleton().execProcedurce(Procedurce)==false)
	{
		return false;
	}

	CppMySQLQuery* pQuery=NULL;
	if(DatabaseInstace::getSingleton().querySQL("SELECT @ret",&pQuery)==false)
		return false;

	unsigned int result=pQuery->getIntField("@ret",0);
	if(result==0)
		return false;

	return true;
}