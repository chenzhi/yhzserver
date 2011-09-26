
#include "pch.h"
#include "GameServerManager.h"
#include "usermessage.h"
#include "application.h"


template<> GameServerManager* Singleton<GameServerManager>::ms_Singleton=NULL;

//------------------------------------------------------------------------
GameServerManager::GameServerManager(const std::string& configFile)
{


	///ע��������Ϣ
	registerMessage();


    CategoryCofig categoryConfig;
	categoryConfig.loadfile("gameserver.cfg");

	CategoryCofig::SectionIterator it=categoryConfig.getSectionIterator();


	while(it.hasMoreElements())
	{
		std::string serverName=it.peekNextKey();

		std::string ip;
		std::string servername;
		const std::map<std::string,std::string>& sect= it.getNext();


		std::map<std::string,std::string>::const_iterator it=sect.find("ip");
		if(it!=sect.end())
		{
			ip=it->second;
		}else
		{
			xLogMessager::getSingleton().logMessage("��ȡ�����ļ�����û���ҵ���������ip����");
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
	



		GameServer* pserver=new GameServer(servername,ip);
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
bool  GameServerManager::addGameServer(const std::string& ip,const std::string& name)
{

	if(hasGameServer(ip))
		return false;

	GameServer* pserver=new GameServer(name,ip);
	m_GameServerCollect.push_back(pserver);
	return true;
}


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


///ע��������Ϣ
void   GameServerManager::registerMessage()
{

}

///ע��������Ϣ
void  GameServerManager::unregisterMessage()
{

}


/**����Ϸ����������*/
void GameServerManager::onGameServerConnect(NetPack* pPack)
{
	NetString* pServerName=(NetString*)pPack->getData();
	if(addGameServer(pServerName->m_char,pPack->getAddress().ToString(false)))
	{
		char message[512];
		::ZeroMemory(message,512);
		_snprintf(message,512,"��Ϸ���������룬server name: %s, ip: %s",pServerName->m_char,pPack->getAddress().ToString(false));
		Application::getSingleton().addPrintMessage(message);
		xLogMessager::getSingleton().logMessage(message);
	}

}


/**��Ϸ�������뿪*/
void GameServerManager::onGameServerDisConnect(NetPack* pPack)
{
	if(removeGameServerByIP(pPack->getAddress().ToString(false)))
	{

		char message[512];
		::ZeroMemory(message,512);
		_snprintf(message,512,"��Ϸ�������˳� ��server ip: %s",pPack->getAddress().ToString(false));
		Application::getSingleton().addPrintMessage(message);
		xLogMessager::getSingleton().logMessage(message);
	}

	return ;
}