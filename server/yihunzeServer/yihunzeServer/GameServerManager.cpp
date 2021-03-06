
#include "pch.h"
#include "GameServerManager.h"
#include "usermessage.h"
#include "application.h"


template<> GameServerManager* Singleton<GameServerManager>::ms_Singleton=NULL;

//------------------------------------------------------------------------
GameServerManager::GameServerManager(const std::string& configFile)
{


	///注册网络销息
	registerMessage();


    CategoryCofig categoryConfig;
	categoryConfig.loadfile(configFile);

	CategoryCofig::SectionIterator it=categoryConfig.getSectionIterator();


	while(it.hasMoreElements())
	{
		std::string serverName=it.peekNextKey();

		std::string ip;
		std::string servername;
		std::string password;
		unsigned int portnumber;
		const std::map<std::string,std::string>& sect= it.getNext();


		std::map<std::string,std::string>::const_iterator it=sect.find("ip");
		if(it!=sect.end())
		{
			ip=it->second;
		}else
		{
			xLogMessager::getSingleton().logMessage("读取配置文件错误，没有找到服务器的ip设置");
			assert(false);
			continue;
		}

		it=sect.find("servername");
		if(it!=sect.end())
		{
			servername=it->second;
		}else
		{
			servername=ip;
		}

		it=sect.find("password");
		if(it!=sect.end())
		{
			password=it->second;
		}

		it=sect.find("portnumber");
		if(it!=sect.end())
		{
			portnumber=Helper::StringToInt(it->second);
		}
	




		GameServer* pserver=new GameServer(servername,ip,portnumber,password);
		m_GameServerCollect.push_back(pserver);

		


	}


}

//------------------------------------------------------------------------
GameServerManager::~GameServerManager()
{
	GameServerCollect::iterator it=m_GameServerCollect.begin();
	GameServerCollect::iterator itend=m_GameServerCollect.end();

	for(;it!=itend;++it)
	{
		SafeDelete(*it);
	}

	m_GameServerCollect.clear();


	unregisterMessage();

}
				   

//------------------------------------------------------------------------
const GameServer* GameServerManager::getGameServerByIndex(unsigned int index)
{
	if(index>=m_GameServerCollect.size())
		return NULL;
	return m_GameServerCollect[index];

}

//------------------------------------------------------------------------
unsigned int GameServerManager::getGameServerCount()
{
	return m_GameServerCollect.size();

}

//------------------------------------------------------------------------
bool GameServerManager::removeGameServerByIP(const std::string& ip)
{

	GameServerCollect::iterator it=m_GameServerCollect.begin();
	GameServerCollect::iterator itend=m_GameServerCollect.end();

	for(;it!=itend;++it)
	{
		if((*it)->getIP()==ip)
		{
           SafeDelete(*it);
		   m_GameServerCollect.erase(it);
		   return true;
		}

		
	}


	return false;
}


//------------------------------------------------------------------------
//bool  GameServerManager::addGameServer(const std::string& ip,const std::string& name)
//{
//
//	if(hasGameServer(ip))
//		return false;
//
//	GameServer* pserver=new GameServer(name,ip);
//	m_GameServerCollect.push_back(pserver);
//	return true;
//}


//------------------------------------------------------------------------
bool      GameServerManager::hasGameServer(const std::string& ip)
{

	GameServerCollect::iterator it=m_GameServerCollect.begin();
	GameServerCollect::iterator itend=m_GameServerCollect.end();

	for(;it!=itend;++it)
	{
		if((*it)->getIP()==ip)
		{
		return true;
		}


	}

	return false;

}


//------------------------------------------------------------
const GameServer*  GameServerManager::getBestGameServer()const
{
	if(m_GameServerCollect.empty())
		return NULL;
	return m_GameServerCollect[0];

}


///注册网络消息
void   GameServerManager::registerMessage()
{

	NetWorkServer::getSingleton().registerMessageHandle(GM_GAMESERVER_CONNECT,&GameServerManager::onGameServerConnect,this);
	NetWorkServer::getSingleton().registerMessageHandle(GM_GAMESERVER_DISCONNECT,&GameServerManager::onGameServerDisConnect,this);

}

///注销网络消息
void  GameServerManager::unregisterMessage()
{
	NetWorkServer::getSingleton().unregisterMessageHandle(GM_GAMESERVER_CONNECT,this);
	NetWorkServer::getSingleton().unregisterMessageHandle(GM_GAMESERVER_DISCONNECT,this);

}


/**有游戏服务器进入*/
void GameServerManager::onGameServerConnect(RakNet::Packet* p)
{
	
		GameServerCollect::iterator it=m_GameServerCollect.begin();
		GameServerCollect::iterator itend=m_GameServerCollect.end();
       
		const char* ip=p->systemAddress.ToString(false);
		for(;it!=itend;++it)
		{
			if((*it)->getIP()==ip)
			{
 
				(*it)->setConnect();
				char message[512];
				::ZeroMemory(message,512);
				_snprintf(message,512,"游戏服务器登入，server name: %s, ip: %s",(*it)->getName().c_str(),p->systemAddress.ToString(false));
				Application::getSingleton().addPrintMessage(message);
				xLogMessager::getSingleton().logMessage(message);

				return ;
			}


		}

return ;

}


/**游戏服务器离开*/
void GameServerManager::onGameServerDisConnect(RakNet::Packet* p)
{


	GameServerCollect::iterator it=m_GameServerCollect.begin();
	GameServerCollect::iterator itend=m_GameServerCollect.end();

	const char* ip=p->systemAddress.ToString(false);
	for(;it!=itend;++it)
	{
		if((*it)->getIP()==ip&&(*it)->hasConnect())
		{

			(*it)->disConnect();
			char message[512];
			::ZeroMemory(message,512);
			_snprintf(message,512,"游戏服务器退出 ，server ip: %s",p->systemAddress.ToString(false));
			Application::getSingleton().addPrintMessage(message);
			xLogMessager::getSingleton().logMessage(message);

			return ;
		}


	}

	
	//if(removeGameServerByIP(pPack->getAddress().ToString(false)))
	//{

	//	char message[512];
	//	::ZeroMemory(message,512);
	//	_snprintf(message,512,"游戏服务器退出 ，server ip: %s",pPack->getAddress().ToString(false));
	//	Application::getSingleton().addPrintMessage(message);
	//	xLogMessager::getSingleton().logMessage(message);
	////}

	return ;
}