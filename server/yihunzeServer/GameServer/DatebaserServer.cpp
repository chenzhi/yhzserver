#include "pch.h"
#include "DatabaseServer.h"
#include "application.h"
#include "usermessage.h"





//-----------------------------------------------------------
DatabaserServer::DatabaserServer(const Config& config)
{
	registerMessage();

    std::string tem;
	bool b=config.getValue("gamedatabaseserver",m_RemoteIP);
	assert(b);
	b=config.getValue("gamedatabaseserverpassword",m_PassWord);
	assert(b);
	b=config.getValue("gamedatabaseserverportnumber",tem);
    assert(b);
	m_PortNumber=Helper::StringToInt(tem);
	m_Address=RakNet::SystemAddress(m_RemoteIP.c_str(),m_PortNumber);
	return ;
}

//-----------------------------------------------------------
DatabaserServer::~DatabaserServer()
{
	unregisterMessage();
}



//-----------------------------------------------------------
void DatabaserServer::registerMessage()
{

	NetWorkServer* pServer=NetWorkServer::getSingletonPtr();
	pServer->registerMessageHandle(GM_ACCEPTCOME,&DatabaserServer::processConnectSucceed,this);

}

//-----------------------------------------------------------
void DatabaserServer::unregisterMessage()
{
    NetWorkServer* pServer=NetWorkServer::getSingletonPtr();
	pServer->unregisterMessageHandle(GM_ACCEPTCOME,this);

}

//-----------------------------------------------------------
void DatabaserServer::update(float time)
{
	if(this->hasConnnect()==false)
	{
		connect();
	}

}


//---------------------------------------------------------------
void DatabaserServer::processConnectSucceed(NetPack* pPack)
{
	///�����ַ��ͬ����ʾ����Ϸ���ݿ���������͹�������Ϣ
	if(pPack->getAddress()==m_Address)
	{
		Application::getSingletonPtr()->addPrintMessage("������Ϸ���ݿ�������ɹ�");
	}

}