#include "pch.h"
#include "MessageReceive.h"
#include "usermessage.h"
#include "NetWorkClient.h"

template<>
MessageReceive* Singleton<MessageReceive>::ms_Singleton=NULL;



MessageReceive::MessageReceive(yhzIphoneClientViewController* pController)
:m_pController(pController)
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
        
	}else
	{
        
    }
    
     [m_pController printMessage:@"用户名验证错误"];
    
	return ;
}



///处理登入成功消息
void MessageReceive::processAccountSucceed(NetPack* pPack)
{
    
	//GameServerInfor* pGameserver=(GameServerInfor*) pPack->getData();
    
    [m_pController printMessage:@"用户名验证正确"];
    return ;
    
	//NetWorkClient::getSingleton().close(pPack->getAddress());
	//NetWorkClient::getSingleton(). connect(pGameserver->m_GameServerIP,pGameserver->m_PortNumber,pGameserver->m_GameServerPassWord); 
    
	///记录游戏服务器地址
	//RakNet::SystemAddress  tem(pGameserver->m_GameServerIP,pGameserver->m_PortNumber);
	//m_GameServerAdderss=tem;
   // m_GameServerPassWord=pGameserver->m_GameServerPassWord;
    
    
	//MyApp* pApp=static_cast<MyApp*>(&wxGetApp());
	//wxString receiveMessage;
	//receiveMessage=receiveMessage.Format("帐号服务器验证成功，返回帐号id: %d ", (pGameserver->m_accountid));
	//pApp->m_pframe->addSendMessage(receiveMessage);
    
    
    
    
}

///成功连接远程计算机
void MessageReceive::processConnectRemoteServer(NetPack* pPack)
{
	if(pPack->getAddress()==m_GameServerAdderss)
	{
	//	MyApp* pApp=static_cast<MyApp*>(&wxGetApp());
	//	wxString receiveMessage;
	//	receiveMessage=receiveMessage.Format("登入远程游戏服务器成功:%s",pPack->getAddress().ToString());
	//	pApp->m_pframe->addSendMessage(receiveMessage);
        
	}
    
	//ServerListener::getSingleton().onConnect(pPack->getRakNetPack());
    
    NSString*pIP=[NSString stringWithFormat:@"%s",pPack->getAddress().ToString()];
    [m_pController setRemoteServerIP:pIP];
    
}

///**玩家离开*/
void MessageReceive::onDisconnect(RakNet::Packet* p)
{
   
    
    [m_pController setRemoteServerIP:@"掉线"];
    
}

///**玩家掉线*/
void  MessageReceive::onConnectlost(RakNet::Packet* p)
{
  [m_pController setRemoteServerIP:@"掉线"];
}