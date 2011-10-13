#include "pch.h"
#include "playerManager.h"
#include "netWork.h"
#include "application.h"
#include "usermessage.h"
#include "GameServerManager.h"


template<> PlayerManager* Singleton<PlayerManager>::ms_Singleton=NULL;

//--------------------------------------------------------
PlayerManager::PlayerManager()
{

	registerNetWorkMessage();


}



//--------------------------------------------------------
PlayerManager::~PlayerManager()
{

	unregisterNetWorkMessage();
}


/**ÿ֡���º���*/
void PlayerManager::update(float time)
{
	updateLoginUser(time);

}

//--------------------------------------------------------
bool PlayerManager::loadPlayerFromDB(unsigned int account,PlayerVector& playerCollect)
{

	//DatabaserServer::getSingletonPtr()->querySQL()


	return true;

}



//--------------------------------------------------------
bool PlayerManager::loadPlayerFromDB(const std::string& name)
{

	return true;
}


//--------------------------------------------------------
Player* PlayerManager::getPlayerByID(unsigned int id)const
{
	return NULL;
}



/**����������ҵ���ң����û�з��ؿ�*/
Player* PlayerManager::getPlayerByName(const std::string& name) const 
{

	return NULL;
}


//--------------------------------------------------------
Player*  PlayerManager::createPlayer(const std::string& name)
{
	
	return NULL;
}



//--------------------------------------------------------
bool PlayerManager::registerNetWorkMessage()
{


	NetWorkServer* pNetWork=NetWorkServer::getSingletonPtr();
	pNetWork->registerMessageHandle(GM_CHATMESSAGE,&PlayerManager::processChatMessage,this);



	pNetWork->registerMessageHandle(GM_STATESERVER_CLIENT_CONNECT,&PlayerManager::processWillClientConnect,this);

	pNetWork->registerMessageHandle(GM_CONNECT_GAMESERVER,&PlayerManager::processClientConnect,this);

	pNetWork->registerMessageHandle(GM_REQUEST_PLAYERS,&PlayerManager::processDatabasePlayer,this);



	return true;

}


//--------------------------------------------------------
bool PlayerManager::unregisterNetWorkMessage()
{
	NetWorkServer* pNetWork=NetWorkServer::getSingletonPtr();
    pNetWork->unregisterMessageHandle(GM_CHATMESSAGE,this);

	return true;
}

///���������
void  PlayerManager::processChatMessage(NetPack* pPack)
{
	const char* pMessage= static_cast<const char*>(pPack->getData());


	std::string reMessage="recive__";
	reMessage+=pMessage;

	NetWorkServer::getSingletonPtr()->send(GM_CHATMESSAGE,reMessage.c_str(),reMessage.length(),pPack->getSendGUID());
	return ;

}


//-------------------------------------------------------------------------------
///�������пͻ�������֪ͨ
void  PlayerManager::processWillClientConnect(NetPack* pPack)
{
	NetIPAddress* paddress=static_cast<NetIPAddress*>( pPack->getData());

	LoginPlayer loginplayer;
	loginplayer.m_UserIP=paddress->m_char;
	loginplayer.m_time=0.0f;
	m_LoginUser.push_back(loginplayer);
	return ;
	//MessageBox(NULL,"�ͻ��˽�Ҫ����֪ͨ",NULL,MB_OK);

	return ;


}

//-------------------------------------------------------------------------------
void  PlayerManager::updateLoginUser(float time)
{

	LoginPlayerVector deleteuser;

	LoginPlayerVector::iterator it=m_LoginUser.begin();
	LoginPlayerVector::iterator endit=m_LoginUser.end();
	for(;it!=endit;++it)
	{
		it->m_time+=time;
		if(it->m_time>=10.0f)
		{
			deleteuser.push_back(*it);
		}
	}

	it=deleteuser.begin();
	endit=deleteuser.end();
	for(;it!=endit;++it)
	{
		LoginPlayerVector::iterator removeit=std::find(m_LoginUser.begin(),m_LoginUser.end(),*it);
		if(removeit!=m_LoginUser.end())
		{
              m_LoginUser.erase(removeit);
		}
	}

	return ;

}



//-------------------------------------------------------------------------------
bool  PlayerManager::AllowLogin(std::string& ip)
{
#ifdef _DEBUG

	return true;
#endif

	return true;


	LoginPlayerVector::iterator it=m_LoginUser.begin();
	LoginPlayerVector::iterator endit=m_LoginUser.end();
	for(;it!=endit;++it)
	{
	  if(it->m_UserIP==ip)
		  return true;
	}
	return false;
}


//-------------------------------------------------------------------------------
void  PlayerManager::processClientConnect(NetPack* pPack)
{
	NetInt* accountid=static_cast<NetInt*>(pPack->getData());

	////����������Ͱ��ʺŷ������ݿ������������������Ͽ��ͻ�������
	std::string clientip=pPack->getAddress().ToString(true);

	if(this->AllowLogin(clientip))
	{
		///���������ݿ⡣���������Ϣ
		const RakNet::SystemAddress& address = Application::getSingleton().getDatabaseServerAddress();

        ClientAccount clientAccount;
		ZeroMemory(&clientAccount,sizeof(ClientAccount));
		clientAccount.m_accountID=accountid->m_int;
		strcpy(clientAccount.m_userip,pPack->getAddress().ToString());
		NetWorkServer::getSingleton().send(GM_REQUEST_PLAYERS,clientAccount,address);

		Application::getSingleton().addPrintMessage("��������ʺ���Ϣ�����ݿ������:");


	}else
	{
		NetWorkServer::getSingletonPtr()->closeConnect(pPack->getAddress());

		///������Ҫ������д���¼����¼���⹥����

	}


	return ;

}


//------------------------------------------------------------------------------------
void PlayerManager::processDatabasePlayer(NetPack* pPack)
{
	///������ת�����ͻ���

	Tag_PlayerCollect* players=static_cast<Tag_PlayerCollect*>(pPack->getData());

	
	if(players->m_Count==0)///��ʾ����ʺŻ�û���½���ɫ
	{


	}else                      ///�����н�ɫ�����ͻ���
	{

	}

	RakNet::SystemAddress address;
	address.SetBinaryAddress(players->m_ip);
	NetWorkServer::getSingleton().send(GM_REQUEST_PLAYERS,(const char*)pPack->getData(),pPack->getDataLength(),address);


	Application::getSingleton().addPrintMessage(std::string("��������ʺ���Ϣ���ͻ���")+players->m_ip);

	return ;
}