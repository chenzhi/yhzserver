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

	return ;
}

//----------------------------------------------------------------
void ServerListener::onDisconnect(RakNet::Packet* p)
{

	std::string tem=p->systemAddress.ToString(false);;
	tem+=": �˳�";
	Application::getSingleton().addPrintMessage(tem);


	///֪ͨ����Ϸ����������Ա
	GameServerManager::getSingleton().removeGameServerByIP(p->systemAddress.ToString(false));
	
	return ;
}

//----------------------------------------------------------------
void  ServerListener::onConnectlost(RakNet::Packet* p)
{
	std::string tem=p->systemAddress.ToString(false);
	tem+=": ����";
	Application::getSingleton().addPrintMessage(tem);


	///֪ͨ����Ϸ����������Ա
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