#include "pch.h"
#include "NetWorkListener.h"
#include "application.h"



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
	
	return ;
}

//----------------------------------------------------------------
void  ServerListener::onConnectlost(RakNet::Packet* p)
{
	std::string tem=p->systemAddress.ToString(false);
	tem+=": 掉线";
	Application::getSingleton().addPrintMessage(tem);

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