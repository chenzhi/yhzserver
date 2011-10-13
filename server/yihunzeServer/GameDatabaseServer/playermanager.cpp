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


	//TagPlayerVector	playerCollect;
	//loadPlayerFromDB(0,playerCollect);

	//processRequestPlayer(NULL);

}



//--------------------------------------------------------
PlayerManager::~PlayerManager()
{

	unregisterNetWorkMessage();
}


//--------------------------------------------------------
bool PlayerManager::loadPlayerFromDB(unsigned int account,TagPlayerVector& playerCollect)
{

	char sql[256];
	memset(sql,0,256);
	sprintf(sql,"select * from player where account=%d",account);

	CppMySQLQuery* pQuery=NULL;
	if(DatabaseInstace::getSingletonPtr()->querySQL(sql,&pQuery)==false)
		return false;

	playerCollect.clear();
	while (!pQuery->eof())
	{
		Tag_Player tagplayer;
		tagplayer.m_ID=pQuery->getIntField("id");
		strcpy(tagplayer.m_Name,pQuery->getStringField("name"));
		tagplayer.m_AccountID=pQuery->getIntField("account");
		tagplayer.m_profession=pQuery->getIntField("profession");
		tagplayer.m_hp=pQuery->getIntField("hp");
		tagplayer.m_mp=pQuery->getIntField("mp");
		tagplayer.m_atk=pQuery->getIntField("atk");
		tagplayer.m_dam=pQuery->getIntField("dam");
		tagplayer.m_def=pQuery->getIntField("def");
		tagplayer.m_endurance=pQuery->getIntField("endurance");
		tagplayer.m_intelligence=pQuery->getIntField("intelligence");
		tagplayer.m_maxdam=pQuery->getIntField("maxdam");
		tagplayer.m_mindam=pQuery->getIntField("mindam");
		tagplayer.m_power=pQuery->getIntField("power");

		playerCollect.push_back(tagplayer);
		pQuery->nextRow();
	}



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

	pNetWork->registerMessageHandle(GM_REQUEST_PLAYERS,&PlayerManager::processRequestPlayer,this);



	return true;

}


//--------------------------------------------------------
bool PlayerManager::unregisterNetWorkMessage()
{
	NetWorkServer* pNetWork=NetWorkServer::getSingletonPtr();

 
	return true;
}


void  PlayerManager::processRequestPlayer(NetPack* pPack)
{

	ClientAccount* accountid=NULL;
	if(pPack==NULL)
	{
		accountid= new ClientAccount;
		ZeroMemory(accountid,sizeof(ClientAccount));
		accountid->m_accountID = 0;
	}else
	{
       accountid=static_cast<ClientAccount*>(pPack->getData());
	}
	

	TagPlayerVector playerCollect;

	char*  pTemData=NULL;
	Tag_PlayerCollect* senddata=NULL;
	UINT size=0;
	//memset(&senddata,0,sizeof(Tag_PlayerCollect));

	bool b=loadPlayerFromDB(accountid->m_accountID,playerCollect);


	size=sizeof(Tag_PlayerCollect)-sizeof(Tag_Player)+sizeof(Tag_Player)*playerCollect.size();
	char* pbuffer =new char[size];
	ZeroMemory(pbuffer,size);
	senddata=(Tag_PlayerCollect*)pbuffer;
	senddata->m_Count=playerCollect.size();
	senddata->m_Account=accountid->m_accountID;
	strcpy(senddata->m_ip,accountid->m_userip);
	if(b)
	{
		memcpy(&(senddata->m_pPlayer),&(playerCollect[0]),sizeof(Tag_Player)*senddata->m_Count);
	}
	
	NetWorkServer::getSingletonPtr()->send(GM_REQUEST_PLAYERS,pbuffer,size,pPack->getAddress());

	Application::getSingleton().addPrintMessage("发送玩家帐号消息");


	delete [] pbuffer;
 	

	return ;
}
