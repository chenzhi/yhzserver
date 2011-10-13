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


/**每帧更新函数*/
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



/**根据玩家名找到玩家，如果没有返回空*/
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

///处理聊天包
void  PlayerManager::processChatMessage(NetPack* pPack)
{
	const char* pMessage= static_cast<const char*>(pPack->getData());


	std::string reMessage="recive__";
	reMessage+=pMessage;

	NetWorkServer::getSingletonPtr()->send(GM_CHATMESSAGE,reMessage.c_str(),reMessage.length(),pPack->getSendGUID());
	return ;

}


//-------------------------------------------------------------------------------
///处理将会有客户端联接通知
void  PlayerManager::processWillClientConnect(NetPack* pPack)
{
	NetIPAddress* paddress=static_cast<NetIPAddress*>( pPack->getData());

	LoginPlayer loginplayer;
	loginplayer.m_UserIP=paddress->m_char;
	loginplayer.m_time=0.0f;
	m_LoginUser.push_back(loginplayer);
	return ;
	//MessageBox(NULL,"客户端将要联接通知",NULL,MB_OK);

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

	////如果允许登入就把帐号发到数据库数据器，不允许登入断开客户端连接
	std::string clientip=pPack->getAddress().ToString(true);

	if(this->AllowLogin(clientip))
	{
		///发包给数据库。请求玩家信息
		const RakNet::SystemAddress& address = Application::getSingleton().getDatabaseServerAddress();

        ClientAccount clientAccount;
		ZeroMemory(&clientAccount,sizeof(ClientAccount));
		clientAccount.m_accountID=accountid->m_int;
		strcpy(clientAccount.m_userip,pPack->getAddress().ToString());
		NetWorkServer::getSingleton().send(GM_REQUEST_PLAYERS,clientAccount,address);

		Application::getSingleton().addPrintMessage("发送玩家帐号消息给数据库服务器:");


	}else
	{
		NetWorkServer::getSingletonPtr()->closeConnect(pPack->getAddress());

		///可能需要在这里写入记录。记录恶意攻击者

	}


	return ;

}


//------------------------------------------------------------------------------------
void PlayerManager::processDatabasePlayer(NetPack* pPack)
{
	///把数据转发给客户端

	Tag_PlayerCollect* players=static_cast<Tag_PlayerCollect*>(pPack->getData());

	
	if(players->m_Count==0)///表示这个帐号还没有新建角色
	{


	}else                      ///把所有角色发给客户端
	{

	}

	RakNet::SystemAddress address;
	address.SetBinaryAddress(players->m_ip);
	NetWorkServer::getSingleton().send(GM_REQUEST_PLAYERS,(const char*)pPack->getData(),pPack->getDataLength(),address);


	Application::getSingleton().addPrintMessage(std::string("发送玩家帐号消息给客户端")+players->m_ip);

	return ;
}