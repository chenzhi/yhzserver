#include "pch.h"
#include "LoginManager.h"
#include "usermessage.h"
#include "application.h"
#include "GameServerManager.h"


template<> LoginManager* Singleton<LoginManager>::ms_Singleton=NULL;

//------------------------------------------------------------
LoginManager::LoginManager()
{
	///ע��������Ϣ
	registerMessage();

}


//------------------------------------------------------------
LoginManager::~LoginManager()
{

	
	unregisterMessage();

}


//------------------------------------------------------------
void LoginManager::registerMessage()
{

	NetWorkServer* pNetWork=NetWorkServer::getSingletonPtr();

	pNetWork->registerMessageHandle(GM_ACCOUNT_REQUEST,&LoginManager::processAccountRequest,this);
	pNetWork->registerMessageHandle(GM_ACCOUNT_RESPOND,&LoginManager::processAccountRespond,this);

}


//------------------------------------------------------------
void LoginManager::unregisterMessage()
{

	NetWorkServer* pNetWork=NetWorkServer::getSingletonPtr();

	pNetWork->unregisterMessageHandle(GM_ACCOUNT_REQUEST,this);
	pNetWork->unregisterMessageHandle(GM_ACCOUNT_RESPOND,this);

}


//------------------------------------------------------------
void LoginManager::processAccountRequest(NetPack* pPack)
{

	UserLogin* pmessage=(UserLogin*)pPack->getData();

	//Application::getSingletonPtr()->addPrintMessage(pmessage);

	const std::string& serverip=Application::getSingleton().getAccountServer();
	unsigned int port=Application::getSingleton().getAccountServerPort();
	RakNet::SystemAddress address(serverip.c_str(),port);

	const char* sendip=pPack->getAddress().ToString(true);

	unsigned len=strlen(sendip);
	UserAccount account;
	unsigned size=sizeof(UserAccount);
	::ZeroMemory(&account,sizeof(UserAccount));

	strcpy(account.m_account,pmessage->m_account);
	strcpy(account.m_password,pmessage->m_password);
	strcpy(account.m_ip,sendip);


	NetWorkServer::getSingleton().send(GM_ACCOUNT_REQUEST,account,address);

	return ;

}



//------------------------------------------------------------
void LoginManager::processAccountRespond(NetPack* pPack)
{
	RespondAccount* prespond=reinterpret_cast<RespondAccount*>(pPack->getData());

	RakNet::SystemAddress  address;
	address.SetBinaryAddress(prespond->m_userip);

	if(prespond->m_login==0)
	{
		NetByte netbyte;
		netbyte.m_byte=prespond->m_login;
		NetWorkServer::getSingleton().send(GM_ACCOUNT_RESPOND_FAILED,netbyte,address);


	}else
	{
		///������Ϣ����Ϸ�߼���������֪ͨ�пͻ�����Ҫ����
		const GameServer* pGameserver=GameServerManager::getSingleton().getBestGameServer();
		if(pGameserver!=NULL)
		{
			///����Ϸ�������ĵ�ַ�����ͻ��ˣ��ÿͻ���������Ϸ������

			GameServerInfor gameserver;
			ZeroMemory(&gameserver,sizeof(GameServerInfor));
			strcpy(gameserver.m_GameServerIP,pGameserver->getIP().c_str());
			strcpy(gameserver.m_GameServerPassWord,pGameserver->getPassWord().c_str());
			gameserver.m_PortNumber=pGameserver->getPortNumber();
			gameserver.m_accountid=prespond->m_accountID;

			NetWorkServer::getSingleton().send(GM_ACCOUNT_RESPOND_SUCCEED,gameserver,address);


			///�ѿͻ�����Ϣ������Ϸ�߼�������
			NetIPAddress clientaddress;
			memset(&clientaddress,0,sizeof(NetIPAddress));
			strcpy(clientaddress.m_char,prespond->m_userip);
			address=RakNet::SystemAddress(gameserver.m_GameServerIP,gameserver.m_PortNumber);
			NetWorkServer::getSingleton().send(GM_STATESERVER_CLIENT_CONNECT,clientaddress,address);






		}






	}


	return ;

}
