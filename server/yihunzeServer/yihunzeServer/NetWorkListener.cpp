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

	GameServerManager::getSingleton().onGameServerConnect(p);

	return ;
}

//----------------------------------------------------------------
void ServerListener::onDisconnect(RakNet::Packet* p)
{

	std::string tem=p->systemAddress.ToString(false);;
	tem+=": 退出";
	Application::getSingleton().addPrintMessage(tem);


	///通知有游戏服务器管理员
	//GameServerManager::getSingleton().removeGameServerByIP(p->systemAddress.ToString(false));
	GameServerManager::getSingleton().onGameServerDisConnect(p);
	
	return ;
}

//----------------------------------------------------------------
void  ServerListener::onConnectlost(RakNet::Packet* p)
{
	std::string tem=p->systemAddress.ToString(false);
	tem+=": 掉线";
	Application::getSingleton().addPrintMessage(tem);


	///通知有游戏服务器管理员
	//GameServerManager::getSingleton().removeGameServerByIP(p->systemAddress.ToString(false));
	GameServerManager::getSingleton().onGameServerDisConnect(p);

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

void  ServerListener::onConnectFailed(RakNet::Packet* p)
{
	std::string tem=p->systemAddress.ToString(false);
	tem+=": 连接失败,远程无响应";
	Application::getSingleton().addPrintMessage(tem);
}