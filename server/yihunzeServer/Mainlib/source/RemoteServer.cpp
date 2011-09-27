
#include "pch.h"
#include "RemoteServer.h"
#include "netWork.h"

//-----------------------------------------------------------------------------
RemoteServer::RemoteServer(const std::string& serverip,unsigned int portnumber,const std::string& password)
:m_RemoteIP(serverip),m_PortNumber(portnumber),m_PassWord(password)
{


}

//-----------------------------------------------------------------------------
RemoteServer::~RemoteServer()
{

}


//-----------------------------------------------------------------------------
bool RemoteServer::connect()
{
	if(hasConnnect()==true)
	{
		closeConnect();
	}

	return  NetWork::getSingleton().conect(m_RemoteIP,m_PortNumber,m_PassWord);

}


//-----------------------------------------------------------------------------
bool RemoteServer::hasConnnect() const 
{

	RakNet::SystemAddress address(m_RemoteIP.c_str(),m_PortNumber);
   return 	NetWork::getSingleton().getConnectState(address)==RakNet::IS_CONNECTED;

}


//-----------------------------------------------------------------------------
void RemoteServer::closeConnect()
{
		RakNet::SystemAddress address(m_RemoteIP.c_str(),m_PortNumber);
        NetWork::getSingleton().close(address);
}


//-----------------------------------------------------------------------------
void RemoteServer::setNetParament(const std::string& serverip,unsigned int portnumber,const std::string& password)
{
	m_RemoteIP=serverip;
	m_PortNumber=portnumber;
	m_PassWord=password;

	if(hasConnnect())
	{
		closeConnect();
	}

}


//-----------------------------------------------------------------------------
RakNet::SystemAddress RemoteServer::getRakNetAddress()const
{

	return RakNet::SystemAddress(m_RemoteIP.c_str(),m_PortNumber);

}