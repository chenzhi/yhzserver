#include "pch.h"
#include "Stateserver.h"
#include "netWork.h"
#include "application.h"
#include "usermessage.h"



//----------------------------------------------------------------------------------------------
StateServer::StateServer(const std::string& gameserverName,const std::string& stateserverip,unsigned int portnumber,const std::string& password)
:RemoteServer(stateserverip,portnumber,password),m_GameServerName(gameserverName),m_CurrentTime(0.0f)
{


}

//----------------------------------------------------------------------------------------------
StateServer::StateServer(const Config& config)
{
	std::string Value;
	if(config.getValue("stateserverip",m_RemoteIP)==false)
	{
		Application::getSingleton().addPrintMessage("未找到状态服务器ip设置",true);
	}

	std::string temValue;
	if(config.getValue("stattserverportnumber",temValue)==false)
	{
		Application::getSingleton().addPrintMessage("未找到状态服务器端口号设置",true);
	}
	m_PortNumber=Helper::StringToInt(temValue);

	if(config.getValue("gameservername",m_GameServerName)==false)
	{
		Application::getSingleton().addPrintMessage("未找到状态服务器 游戏服务器线路名设置",true);
	
	}

	if(config.getValue("statserverpassword",m_PassWord)==false)
	{
		Application::getSingleton().addPrintMessage("未找到状态服务器 游戏服务器线路名设置",true);

	}

	m_Address=RakNet::SystemAddress(m_RemoteIP.c_str(),m_PortNumber);


}


//----------------------------------------------------------------------------------------------
StateServer::~StateServer()
{
	
	///向状态服务器发送注销游戏服务器
	send(GM_GAMESERVER_DISCONNECT,m_GameServerName.c_str(),m_GameServerName.length());

}




//----------------------------------------------------------------------------------------------
void StateServer::update(float time)
{

	if(hasConnnect()==false)
	{
		connect();
		return ;
	}

	static bool b=false;
	if(b==false)
	{
	    ///向状态服务器发送游戏服务器注册消息
		send(GM_GAMESERVER_CONNECT,m_GameServerName.c_str(),m_GameServerName.length());
		b=true;
	}


	m_CurrentTime+=time;

	static unsigned int minute=1;

	if(m_CurrentTime>=60*minute)
	{
		m_CurrentTime-=60*minute;
		///在这发送信息组状态服务器
		setInformationToStateServer();

		m_CurrentTime=0.0f;
	}



}


//----------------------------------------------------------------------------------------------
void StateServer::setInformationToStateServer()
{

	return ;
}