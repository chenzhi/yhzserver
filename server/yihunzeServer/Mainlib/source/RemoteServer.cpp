
#include "pch.h"
#include "RemoteServer.h"



//*
//-----------------------------------------------------------------------------
RemoteServer::RemoteServer(const std::string& serverip,unsigned int portnumber,const std::string& password)
:m_RemoteIP(serverip),m_PortNumber(portnumber),m_PassWord(password)
{

	m_Address=RakNet::SystemAddress(m_RemoteIP.c_str(),m_PortNumber);

}

//-----------------------------------------------------------------------------
RemoteServer::~RemoteServer()
{
   closeConnect();
}


//-----------------------------------------------------------------------------
bool RemoteServer::connect()
{
	if(hasConnnect()==true)
	{
		closeConnect();
	}


	NetWorkServer::getSingletonPtr()->connect(m_RemoteIP,m_PortNumber,m_PassWord);


	return true;


}


//-----------------------------------------------------------------------------
bool RemoteServer::hasConnnect() const 
{

	RakNet::SystemAddress address(m_RemoteIP.c_str(),m_PortNumber);
    return 	NetWorkServer::getSingleton().getConnectState(address)==RakNet::IS_CONNECTED;

}


//-----------------------------------------------------------------------------
void RemoteServer::closeConnect()
{
	
        NetWorkServer::getSingleton().close(m_Address);
}


//-----------------------------------------------------------------------------
void RemoteServer::setNetParament(const std::string& serverip,unsigned int portnumber,const std::string& password)
{
	m_RemoteIP=serverip;
	m_PortNumber=portnumber;
	m_PassWord=password;

	m_Address=RakNet::SystemAddress(m_RemoteIP.c_str(),m_PortNumber);

	if(hasConnnect())
	{
		closeConnect();
	}

}


//-----------------------------------------------------------------------------
const  RakNet::SystemAddress& RemoteServer::getRakNetAddress()const
{

	return m_Address;

}

//*/