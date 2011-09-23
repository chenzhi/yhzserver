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


	pNetWork->registerMessageHandle(GM_TEXT_MESSAGE,&PlayerManager::processTestMessage,this);

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
void PlayerManager::processTestMessage(void* pdata)
{

	char* pmessage=(char*)pdata;

	Application::getSingletonPtr()->addPrintMessage(pmessage);

	return ;

}