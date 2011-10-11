#include "pch.h"
#include "NetWorkListener.h"
#include "application.h"
#include "GameServerManager.h"



//----------------------------------------------------------------
void ServerListener::onConnect(RakNet::Packet* p)
{
	std::string tem=p->systemAddress.ToString(false);
	tem+=": ����";
	Application::getSingleton().addPrintMessage(tem);

	GameServerManager::getSingleton().onGameServerConnect(p);

	return ;
}

//----------------------------------------------------------------
void ServerListener::onDisconnect(RakNet::Packet* p)
{

	std::string tem=p->systemAddress.ToString(false);;
	tem+=": �˳�";
	Application::getSingleton().addPrintMessage(tem);


	///֪ͨ����Ϸ����������Ա
	//GameServerManager::getSingleton().removeGameServerByIP(p->systemAddress.ToString(false));
	GameServerManager::getSingleton().onGameServerDisConnect(p);
	
	return ;
}

//----------------------------------------------------------------
void  ServerListener::onConnectlost(RakNet::Packet* p)
{
	std::string tem=p->systemAddress.ToString(false);
	tem+=": ����";
	Application::getSingleton().addPrintMessage(tem);


	///֪ͨ����Ϸ����������Ա
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
	tem+=": ����ʧ��,Զ������Ӧ";
	Application::getSingleton().addPrintMessage(tem);
}