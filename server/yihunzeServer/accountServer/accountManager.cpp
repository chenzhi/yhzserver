
#include "pch.h"
#include "accountManager.h"
#include "usermessage.h"


//---------------------------------------------------------------------
AccountManager::AccountManager()
{

	init();
}


//---------------------------------------------------------------------
AccountManager::~AccountManager()
{

	destroy();
}


//---------------------------------------------------------------------
void AccountManager::init()
{
	NetWork* pNetWork=NetWork::getSingletonPtr();
	assert(pNetWork);

	pNetWork->registerMessageHandle(GM_ACCOUNT_REQUEST,&AccountManager::processAccountTest,this);

}


//---------------------------------------------------------------------
void AccountManager::destroy()
{


	NetWork* pNetWork=NetWork::getSingletonPtr();
	if(pNetWork!=NULL)
	{
      pNetWork->unregisterMessageHandle(GM_ACCOUNT_REQUEST,this);
	}

	


}


//---------------------------------------------------------------------
void AccountManager::processAccountTest(NetPack* pPack)
{
	
	UserAccount* puser=reinterpret_cast<UserAccount*>(pPack->getData());
	//const char* pSendaddess=pPack->getSendIP();
   // unsigned length=strlen(pSendaddess);
	RespondAccount respond;
	memset(&respond,0,sizeof(RespondAccount));

	memcpy(respond.m_userip,puser->m_ip,sizeof(respond.m_userip));

	respond.m_login=1;

	NetWork::getSingleton().send( GM_ACCOUNT_RESPOND,&respond,pPack->getAddress());
	return ;
}



