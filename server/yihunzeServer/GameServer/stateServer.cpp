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
		Application::getSingleton().addPrintMessage("未找到状态服务器ip设置",true);
	}

	std::string temValue;
	if(config.getValue("stattserverportnumber",temValue)==false)
	{
		Application::getSingleton().addPrintMessage("未找到状态服务器端口号设置",true);
	}
	m_StateServerPort=Helper::StringToInt(temValue);

	if(config.getValue("gameservername",m_GameServerName)==false)
	{
		Application::getSingleton().addPrintMessage("未找到状态服务器 游戏服务器线路名设置",true);
	
	}

	if(config.getValue("statserverpassword",m_StatePassWord)==false)
	{
		Application::getSingleton().addPrintMessage("未找到状态服务器 游戏服务器线路名设置",true);

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

	///如果连接成功，发送注册游戏服务器
	if(m_IsConnect==true)
	{
		RakNet::SystemAddress address(m_StateServerIP.c_str(),m_StateServerPort);
		NetWork::getSingleton().send(GM_GAMESERVER_CONNECT,m_GameServerName.c_str(),m_GameServerName.length(),address);
	}

	return m_IsConnect;

}


/**断开状态服务器连接*/
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
		///在这发送信息组状态服务器
		setInformationToStateServer();
	}



}


/**是否连接到了状态服务器*/
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