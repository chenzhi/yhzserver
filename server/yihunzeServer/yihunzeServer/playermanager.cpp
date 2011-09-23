#include "pch.h"
#include "playerManager.h"
#include "netWork.h"
#include "application.h"
#include "usermessage.h"



template<> PlayerManager* Singleton<PlayerManager>::ms_Singleton=NULL;

//--------------------------------------------------------
PlayerManager::PlayerManager()
{

	registerNetWorkMessage();


}



//--------------------------------------------------------
PlayerManager::~PlayerManager()
{

	unregisterNetWorkMessage();
}


//--------------------------------------------------------
bool PlayerManager::registerNetWorkMessage()
{


	NetWork* pNetWork=NetWork::getSingletonPtr();

	pNetWork->registerMessageHandle(GM_ACCOUNT_REQUEST,&PlayerManager::processTestMessage,this);
	pNetWork->registerMessageHandle(GM_ACCOUNT_RESPOND,&PlayerManager::processAccountTest,this);

	return true;

}


//--------------------------------------------------------
bool PlayerManager::unregisterNetWorkMessage()
{
	NetWork* pNetWork=NetWork::getSingletonPtr();



	pNetWork->unregisterMessageHandle(GM_TEXT_MESSAGE,this);

	return true;
}



//--------------------------------------------------------
void PlayerManager::processTestMessage(NetPack* pPack)
{

	UserLogin* pmessage=(UserLogin*)pPack->getData();

	//Application::getSingletonPtr()->addPrintMessage(pmessage);

	const std::string& serverip=Application::getSingleton().getAccountServer();
	unsigned int port=Application::getSingleton().getAccountServerPort();
	RakNet::SystemAddress address(serverip.c_str(),port);
     
	const char* sendip=pPack->getSendIP();
	UserAccount account;
	unsigned size=sizeof(UserAccount);
	::ZeroMemory(&account,sizeof(UserAccount));

	memcpy(account.m_account,pmessage->m_account,sizeof(account.m_account));
	memcpy(account.m_password,pmessage->m_password,sizeof(account.m_password));
	memcpy(account.m_ip,sendip,strlen(sendip));
	NetWork::getSingleton().send(GM_ACCOUNT_REQUEST,account,address);

	return ;

}


//---------------------------------------------------------------------
void  PlayerManager::processAccountTest(NetPack* pdata)
{



	return ;
}