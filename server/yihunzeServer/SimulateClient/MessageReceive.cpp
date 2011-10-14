
#include "pch.h"
#include "MessageReceive.h"
#include "usermessage.h"
#include "NetWorkListener.h"
#include "App.h"
#include "SimulateClientMainFrame.h"


template<>
MessageReceive* Singleton<MessageReceive>::ms_Singleton=NULL;



MessageReceive::MessageReceive()
:m_NeedConectGameServer(false)
{

	NetWorkClientInstance* pInstance=NetWorkClient::getSingleton().getConnectInstance("statserver");

	pInstance->registerMessageHandle(GM_ACCEPTCOME,&MessageReceive::processConnectRemoteServer,this);
	pInstance->registerMessageHandle(GM_ACCOUNT_RESPOND_FAILED,&MessageReceive::processAccountFaild,this);
	pInstance->registerMessageHandle(GM_ACCOUNT_RESPOND_SUCCEED,&MessageReceive::processAccountSucceed,this);

	//pInstance->registerMessageHandle(GM_CHATMESSAGE,&MessageReceive::processChatMessage,this);


}


MessageReceive::~MessageReceive()
{
	NetWorkClientInstance* pInstance=NetWorkClient::getSingleton().getConnectInstance("statserver");
	if(pInstance!=NULL)
	{
		pInstance->unregisterMessageHandle(GM_ACCOUNT_RESPOND_FAILED,this);
		pInstance->unregisterMessageHandle(GM_ACCOUNT_RESPOND_SUCCEED,this);

	}
}


void  MessageReceive::initGameserverMessage()
{
	NetWorkClientInstance*pInstance=NetWorkClient::getSingleton().getConnectInstance(GAMESERVER);
	assert(pInstance);
	pInstance->registerMessageHandle(GM_CHATMESSAGE,&MessageReceive::processChatMessage,this);
	pInstance->registerMessageHandle(GM_REQUEST_PLAYERS,&MessageReceive::processAccountPlayers,this);


}


void MessageReceive::update()
{
	if(m_NeedConectGameServer==true)
	{
		//if(NetWorkClient::getSingletonPtr()->hasConnect()==false)
		//{
        //  NetWorkClient::getSingletonPtr()->connect(m_GameServerIp,m_GameServerPortNumber,m_GameServerPassWord);
		//  m_NeedConectGameServer=false;

		//}else
		//{
		//	m_NeedConectGameServer=false;
		//}

	}

}


///处理登入消息
void MessageReceive::processAccountFaild(NetPack* pPack)
{
	NetByte* puser=reinterpret_cast<NetByte*>(pPack->getData());
	
	MyApp* pApp=static_cast<MyApp*>(&wxGetApp());
	pApp->m_pframe->addReceiveMessage("帐号密码错误",pPack->getAddress());
	return ;
}



///处理登入成功消息
void MessageReceive::processAccountSucceed(NetPack* pPack)
{

	GameServerInfor* pGameserver=(GameServerInfor*) pPack->getData();


	//NetWorkClient::getSingleton().closeConnect();
	NetWorkClient::getSingletonPtr()->createConnect(GAMESERVER,pGameserver->m_GameServerIP,pGameserver->m_PortNumber,pGameserver->m_GameServerPassWord);

	///注册游戏逻辑服务器消息
	initGameserverMessage();

    NetWorkClient::getSingletonPtr()->getConnectInstance("statserver")->closeConnect();
	NetWorkClient::getSingletonPtr()->destroyInstance("statserver");
	//::sleep(1000);
	m_NeedConectGameServer = true;
	//NetWorkClient::getSingleton(). connect(pGameserver->m_GameServerIP,pGameserver->m_PortNumber,pGameserver->m_GameServerPassWord); 

	///记录游戏服务器地址
	RakNet::SystemAddress  tem(pGameserver->m_GameServerIP,pGameserver->m_PortNumber);
    m_GameServerPassWord=pGameserver->m_GameServerPassWord;
     m_GameServerIp=pGameserver->m_GameServerIP;
	 m_GameServerPortNumber=pGameserver->m_PortNumber;

	MyApp* pApp=static_cast<MyApp*>(&wxGetApp());
	wxString receiveMessage;
	receiveMessage=receiveMessage.Format("帐号服务器验证成功，返回帐号id: %d ", (pGameserver->m_accountid));
	pApp->m_pframe->addReceiveMessage(receiveMessage.c_str(),pPack->getAddress());




}

///成功连接远程计算机
void MessageReceive::processConnectRemoteServer(NetPack* pPack)
{
	if(pPack->getAddress().ToString(false)==m_GameServerIp)
	{
		MyApp* pApp=static_cast<MyApp*>(&wxGetApp());
		wxString receiveMessage;
		receiveMessage=receiveMessage.Format("登入远程游戏服务器成功:%s",pPack->getAddress().ToString());
		pApp->m_pframe->addSendMessage(receiveMessage);

	}

	ServerListener::getSingleton().onConnect(pPack->getRakNetPack());


}

///处理游戏逻辑服务器聊天消息
void MessageReceive::processChatMessage(NetPack* pPack)
{
	const char* pMessage= static_cast<const char*>(pPack->getData());

	MyApp* pApp=static_cast<MyApp*>(&wxGetApp());
	wxString receiveMessage;
	receiveMessage=receiveMessage.Format("%s",pMessage);
	pApp->m_pframe->addReceiveMessage(receiveMessage.c_str(),pPack->getAddress());


}

///处理帐号有多少个玩家
void  MessageReceive::processAccountPlayers(NetPack* pPack)
{
	Tag_PlayerCollect* players=static_cast<Tag_PlayerCollect*>(pPack->getData());

	char message[256];
	memset(message,0,256);

	sprintf(message,"帐号：%d 共有%d个角色",players->m_Account,players->m_Count);
	MyApp* pApp=static_cast<MyApp*>(&wxGetApp());
	pApp->m_pframe->addReceiveMessage(message,pPack->getAddress());

	for(UINT i=0;i<players->m_Count;++i)
	{
		Tag_Player* player = (&(players->m_pPlayer))+i;

		sprintf(message,"角色信息：%s, hp：%d,mp:%d",player->m_Name,player->m_hp,player->m_mp);
		pApp->m_pframe->addReceiveMessage(message,pPack->getAddress());
	}
	
	return ;

}