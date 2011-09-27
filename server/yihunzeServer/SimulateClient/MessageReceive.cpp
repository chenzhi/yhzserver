
#include "pch.h"
#include "MessageReceive.h"
#include "usermessage.h"
#include "NetWorkListener.h"

template<>
MessageReceive* Singleton<MessageReceive>::ms_Singleton=NULL;



MessageReceive::MessageReceive()
{
	NetWorkClient::getSingleton().registerMessageHandle(GM_ACCEPTCOME,&MessageReceive::processConnectRemoteServer,this);
	NetWorkClient::getSingleton().registerMessageHandle(GM_ACCOUNT_RESPOND_FAILED,&MessageReceive::processAccountFaild,this);
	NetWorkClient::getSingleton().registerMessageHandle(GM_ACCOUNT_RESPOND_SUCCEED,&MessageReceive::processAccountSucceed,this);

}


MessageReceive::~MessageReceive()
{

	NetWorkClient::getSingleton().unregisterMessageHandle(GM_ACCOUNT_RESPOND_FAILED,this);
	NetWorkClient::getSingleton().unregisterMessageHandle(GM_ACCOUNT_RESPOND_SUCCEED,this);

}


///处理登入消息
void MessageReceive::processAccountFaild(NetPack* pPack)
{
	NetByte* puser=reinterpret_cast<NetByte*>(pPack->getData());
	if(puser->m_byte==0)
	{
		MessageBox(NULL,"用户名密码错误!","错误",MB_OK);
	}else
	{
         MessageBox(NULL,"用户名正确","正确",MB_OK);
	}

	return ;
}



///处理登入成功消息
void MessageReceive::processAccountSucceed(NetPack* pPack)
{

	GameServerInfor* pGameserver=(GameServerInfor*) pPack->getData();

	NetWorkClient::getSingleton().close(pPack->getAddress());

	NetWorkClient::getSingleton(). connect(pGameserver->m_GameServerIP,pGameserver->m_PortNumber,pGameserver->m_GameServerPassWord); 

	

	///记录游戏服务器地址
	RakNet::SystemAddress  tem(pGameserver->m_GameServerIP,pGameserver->m_PortNumber);
	m_GameServerAdderss=tem;
    m_GameServerPassWord=pGameserver->m_GameServerPassWord;


}

///成功连接远程计算机
void MessageReceive::processConnectRemoteServer(NetPack* pPack)
{
	if(pPack->getAddress()==m_GameServerAdderss)
	{
		::MessageBox(NULL,"登入游戏服务器成功","",MB_OK);
	}

	ServerListener::getSingleton().onConnect(pPack->getRakNetPack());


}