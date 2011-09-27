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
     
	const char* sendip=pPack->getSendGUID().ToString();
	unsigned len=strlen(sendip);
	UserAccount account;
	unsigned size=sizeof(UserAccount);
	::ZeroMemory(&account,sizeof(UserAccount));

	strcpy(account.m_account,pmessage->m_account);
	strcpy(account.m_password,pmessage->m_password);
	strcpy(account.m_ip,sendip);


	NetWork::getSingleton().send(GM_ACCOUNT_REQUEST,account,address);

	return ;

 //   NetByte netbyte;
	//netbyte.m_byte = 0;

	//RakNet::RakNetGUID netguid;
	//netguid.FromString(sendip);
	//NetWork::getSingleton().send(GM_ACCOUNT_RESPOND,netbyte,netguid);



	//return ;

}


//---------------------------------------------------------------------
void  PlayerManager::processAccountTest(NetPack* pdata)
{

	RespondAccount* prespond=reinterpret_cast<RespondAccount*>(pdata->getData());

	RakNet::RakNetGUID  address;
	address.FromString(prespond->m_userip);

	if(prespond->m_login==0)
	{
		NetByte netbyte;
		netbyte.m_byte=prespond->m_login;
		NetWork::getSingleton().send(GM_ACCOUNT_RESPOND_FAILED,netbyte,address);

	
	}else
	{
		///发送消息给游戏逻辑服务器，通知有客户端需要联接
		const GameServer* pGameserver=GameServerManager::getSingleton().getBestGameServer();
		if(pGameserver!=NULL)
		{
			///把游戏服务器的地址发给客户端，让客户端连接游戏服务器

			GameServerInfor gameserver;
			ZeroMemory(&gameserver,sizeof(GameServerInfor));
			strcpy(gameserver.m_GameServerIP,pGameserver->getIP().c_str());
			strcpy(gameserver.m_GameServerPassWord,pGameserver->getPassWord().c_str());
			gameserver.m_PortNumber=pGameserver->getPortNumber();
			NetWork::getSingleton().send(GM_ACCOUNT_RESPOND_SUCCEED,gameserver,address);
		}




	}


	return ;
}