#include "pch.h"
#include "NetWorkClient.h"



template<> NetWorkClient* Singleton<NetWorkClient>::ms_Singleton=NULL;

//----------------------------------------------------------------
NetWorkClient::NetWorkClient()
{


	m_isServer=false;

	m_pNetInterface->SetTimeoutTime(NetWorkTimeOut,RakNet::UNASSIGNED_SYSTEM_ADDRESS);

	m_pNetInterface->Startup(8, &RakNet::SocketDescriptor(), 1);

	m_pNetInterface->SetMaximumIncomingConnections(8);

	m_pNetInterface->SetOccasionalPing(true);

}


//----------------------------------------------------------------
NetWorkClient::~NetWorkClient()
{

}


//----------------------------------------------------------------
bool NetWorkClient::connect(const std::string& ip,unsigned int serverPort,const std::string& password)
{
	if(NetWork::connect(ip,serverPort,password))
	{

		m_ServerIP=ip;
		m_PortNumber=serverPort;
		m_PassWord=password;
		m_ServerAddress=RakNet::SystemAddress(m_ServerIP.c_str(),m_PortNumber);
		return true;
	}

	return false;
}



//----------------------------------------------------------------
bool  NetWorkClient::hasConnect() const 
{

	return 	NetWork::getConnectState(m_ServerAddress)==RakNet::IS_CONNECTED;

}


//----------------------------------------------------------------
void  NetWorkClient::update( )
{
	NetWork::update();

	return ;
}


//-------------------------------------------------------------------------
void  NetWorkClient::closeConnect()
{
	NetWork::close(m_ServerAddress);
	return ;
}


//--------------------------------------------------------------------------------------
void NetWorkClient::send(unsigned int message,const  char* pData,unsigned int length)
{

	unsigned int bitdatalenght=length<<3;
	unsigned int mesagelenght=sizeof(byte)+sizeof(unsigned int)+length;

	RakNet::BitStream stream;
	stream.Write((byte)GM_User);
	stream.Write((unsigned int)message);
	stream.WriteBits((const unsigned char*)pData,bitdatalenght);
	m_pNetInterface->Send(&stream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, m_ServerAddress, false,1);
}