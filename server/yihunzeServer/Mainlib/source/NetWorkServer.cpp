
#include "pch.h"
#include "NetWorkServer.h"



template<> NetWorkServer* Singleton<NetWorkServer>::ms_Singleton=NULL;
//---------------------------------------------------------------------------
NetWorkServer::NetWorkServer()
{
	m_isServer=true;


}

//---------------------------------------------------------------------------
NetWorkServer::~NetWorkServer()
{

}


//---------------------------------------------------------------------------
bool NetWorkServer::startServer(unsigned int portNumber,const std::string& password)
{


	if(password.empty()==false)
	{
		m_pNetInterface->SetIncomingPassword(password.c_str(),password.length());
	}

	m_pNetInterface->SetTimeoutTime(NetWorkTimeOut,RakNet::UNASSIGNED_SYSTEM_ADDRESS);
    RakNet::SocketDescriptor  sopcket(portNumber,0);
	m_pNetInterface->Startup(NetWorkMaxClientNumber ,&sopcket, 1);
	m_pNetInterface->SetMaximumIncomingConnections(NetWorkMaxClientNumber);
	m_pNetInterface->SetOccasionalPing(true);
	m_pNetInterface->SetUnreliableTimeout(1000);


	return true;

}


//---------------------------------------------------------------------------
bool NetWorkServer::stopServer()
{

	if(m_pNetInterface!=NULL)
	{
		m_pNetInterface->Shutdown(300);
		return true;
	}

	return false;
}


//---------------------------------------------------------------------------
//bool NetWorkServer::connect()
//{
//
//
//
//	return true;
//}


//---------------------------------------------------------------------------
bool NetWorkServer::closeConnect(const RakNet::SystemAddress& address)
{
	if(m_pNetInterface!=NULL)
	{
		m_pNetInterface->CloseConnection(address,true);
		return  true;
	}
	return false;
}


//---------------------------------------------------------------------------
void NetWorkServer::update()
{
	NetWork::update();

	return ;
}



//--------------------------------------------------------------------------------------------
void NetWorkServer::send(unsigned int message,const  char* pData,unsigned int length,const RakNet::RakNetGUID receiver)
{

	unsigned int bitdatalenght=length<<3;
	unsigned int mesagelenght=sizeof(byte)+sizeof(unsigned int)+length;

	RakNet::BitStream stream;
	stream.Write((byte)GM_User);
	stream.Write((unsigned int)message);
	stream.WriteBits((const unsigned char*)pData,bitdatalenght);

	m_pNetInterface->Send(&stream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, receiver, false);
}


//--------------------------------------------------------------------------------------------
void NetWorkServer::send(unsigned int message,const  char* pData,unsigned int length,const RakNet::SystemAddress& receiver)
{
	if(m_pNetInterface==NULL)
		return ;

	RakNet::RakNetGUID id=m_pNetInterface->GetGuidFromSystemAddress(receiver);
	send(message,pData,length,id);
	return ;

}


//--------------------------------------------------------------------------------------------
void  NetWorkServer::broadcastMessage(unsigned int message,const unsigned  char* pdata,unsigned length)
{
	unsigned int bitdatalenght=length*8;
	unsigned int mesagelenght=sizeof(byte)+sizeof(unsigned int)+length;

	RakNet::BitStream stream;
	stream.Write((unsigned char)GM_User);
	stream.Write((unsigned int)message);
	stream.WriteBits(pdata,bitdatalenght);

	bitdatalenght=stream.GetNumberOfBitsUsed();
	m_pNetInterface->Send(&stream, HIGH_PRIORITY, RELIABLE_ORDERED, 0,RakNet::UNASSIGNED_SYSTEM_ADDRESS , true);

}
