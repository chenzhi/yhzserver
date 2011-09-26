#include "pch.h"
#include "NetWorkListener.h"
#include "application.h"
#include "GameServerManager.h"



//----------------------------------------------------------------
void ServerListener::onConnect(RakNet::Packet* p)
{
	std::string tem=p->systemAddress.ToString(false);
	tem+=": 登入";
	Application::getSingleton().addPrintMessage(tem);

	return ;
}

//----------------------------------------------------------------
void ServerListener::onDisconnect(RakNet::Packet* p)
{

	std::string tem=p->systemAddress.ToString(false);;
	tem+=": 退出";
	Application::getSingleton().addPrintMessage(tem);


	///通知有游戏服务器管理员
	GameServerManager::getSingleton().removeGameServerByIP(p->systemAddress.ToString(false));
	
	return ;
}

//----------------------------------------------------------------
void  ServerListener::onConnectlost(RakNet::Packet* p)
{
	std::string tem=p->systemAddress.ToString(false);
	tem+=": 掉线";
	Application::getSingleton().addPrintMessage(tem);


	///通知有游戏服务器管理员
	GameServerManager::getSingleton().removeGameServerByIP(p->systemAddress.ToString(false));

	return ;

}

//----------------------------------------------------------------
bool  ServerListener::hasContectServer(const RakNet::SystemAddress& address)
{
	

	return true;
}


//----------------------------------------------------------------
void  ServerListener::updateServerList()
{


}