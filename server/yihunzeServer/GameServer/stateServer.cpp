#include "pch.h"
#include "Stateserver.h"
#include "netWork.h"
#include "application.h"
#include "usermessage.h"



//----------------------------------------------------------------------------------------------
StateServer::StateServer(const std::string& gameserverName,const std::string& stateserverip,unsigned int portnumber,const std::string& password)
:m_GameServerName(gameserverName),m_StateServerIP(stateserverip),m_StatePassWord(password),m_StateServerPort(portnumber),m_IsConnect(false),
m_CurrentTime(0.0f)
{


}

//----------------------------------------------------------------------------------------------
StateServer::StateServer(const Config& config)
:m_StateServerPort(0),m_CurrentTime(0.0f),m_IsConnect(false)
{
	std::string Value;
	if(config.getValue("stateserverip",m_StateServerIP)==false)
	{
		Application::getSingleton().addPrintMessage("δ�ҵ�״̬������ip����",true);
	}

	std::string temValue;
	if(config.getValue("stattserverportnumber",temValue)==false)
	{
		Application::getSingleton().addPrintMessage("δ�ҵ�״̬�������˿ں�����",true);
	}
	m_StateServerPort=Helper::StringToInt(temValue);

	if(config.getValue("gameservername",m_GameServerName)==false)
	{
		Application::getSingleton().addPrintMessage("δ�ҵ�״̬������ ��Ϸ��������·������",true);
	
	}

	if(config.getValue("statserverpassword",m_StatePassWord)==false)
	{
		Application::getSingleton().addPrintMessage("δ�ҵ�״̬������ ��Ϸ��������·������",true);

	}



}


//----------------------------------------------------------------------------------------------
StateServer::~StateServer()
{
	disConnect();

}

//----------------------------------------------------------------------------------------------
bool  StateServer::connect()
{

	m_IsConnect=NetWork::getSingleton().conect(m_StateServerIP,m_StateServerPort,m_StatePassWord);

	///������ӳɹ�������ע����Ϸ������
	if(m_IsConnect==true)
	{
		RakNet::SystemAddress address(m_StateServerIP.c_str(),m_StateServerPort);
		NetWork::getSingleton().send(GM_GAMESERVER_CONNECT,m_GameServerName.c_str(),m_GameServerName.length(),address);
	}

	return m_IsConnect;

}


/**�Ͽ�״̬����������*/
void  StateServer::disConnect()
{

	///
	if(m_IsConnect)
	{

		RakNet::SystemAddress address(m_StateServerIP.c_str(),m_StateServerPort);
		NetWork::getSingleton().send(GM_GAMESERVER_DISCONNECT,m_GameServerName.c_str(),m_GameServerName.length(),address);

		NetWork::getSingleton().close(m_StateServerIP.c_str(),m_StateServerPort);   
	}

	m_IsConnect=false;
}

//----------------------------------------------------------------------------------------------
void StateServer::update(float time)
{

	if(isConnect()==false)
	{
		connect();
		return ;
	}

	m_CurrentTime+=time;

	static unsigned int minute=1;

	if(m_CurrentTime>=60*minute)
	{
		m_CurrentTime-=60*minute;
		///���ⷢ����Ϣ��״̬������
		setInformationToStateServer();
	}



}


/**�Ƿ����ӵ���״̬������*/
bool  StateServer::isConnect()
{

	RakNet::ConnectionState stat=NetWork::getSingleton().getConnectState(RakNet::SystemAddress(m_StateServerIP.c_str(),m_StateServerPort));

	return stat==RakNet::IS_CONNECTED;

}


//----------------------------------------------------------------------------------------------
void StateServer::setInformationToStateServer()
{

	return ;
}