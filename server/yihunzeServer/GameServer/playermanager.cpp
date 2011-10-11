#include "pch.h"
#include "playerManager.h"
#include "netWork.h"
#include "application.h"
#include "usermessage.h"
#include "GameServerManager.h"


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


	NetWorkServer* pNetWork=NetWorkServer::getSingletonPtr();
	pNetWork->registerMessageHandle(GM_CHATMESSAGE,&PlayerManager::processChatMessage,this);



	pNetWork->registerMessageHandle(GM_STATESERVER_CLIENT_CONNECT,&PlayerManager::processWillClientConnect,this);



	return true;

}


//--------------------------------------------------------
bool PlayerManager::unregisterNetWorkMessage()
{
	NetWorkServer* pNetWork=NetWorkServer::getSingletonPtr();
    pNetWork->unregisterMessageHandle(GM_CHATMESSAGE,this);

	return true;
}

///���������
void  PlayerManager::processChatMessage(NetPack* pPack)
{
	const char* pMessage= static_cast<const char*>(pPack->getData());


	std::string reMessage="recive__";
	reMessage+=pMessage;

	NetWorkServer::getSingletonPtr()->send(GM_CHATMESSAGE,reMessage.c_str(),reMessage.length(),pPack->getSendGUID());
	return ;

}


//-------------------------------------------------------------------------------
///�������пͻ�������֪ͨ
void  PlayerManager::processWillClientConnect(NetPack* pPack)
{
	NetIPAddress* paddress=static_cast<NetIPAddress*>( pPack->getData());

	MessageBox(NULL,"�ͻ��˽�Ҫ����֪ͨ",NULL,MB_OK);

	return ;


}