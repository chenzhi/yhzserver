#include "pch.h"
#include "netWork.h"
#include <fstream>




template<> NetWork*  Singleton<NetWork>::ms_Singleton=NULL;

//-----------------------------------------------
NetWork::NetWork(bool isClient,unsigned int ClientPort)
:m_pNetInterface(NULL),m_isServer(false),m_pLinstener(NULL)
{

	m_pNetInterface=RakNet::RakPeerInterface::GetInstance();
	assert(m_pNetInterface);
	if(isClient)
	{
		RakNet::SocketDescriptor socketDescriptor(ClientPort,0);
		m_pNetInterface->Startup(8,&socketDescriptor, 1);
		m_pNetInterface->SetOccasionalPing(true);
	}

}

//--------------------------------------------------------------------------------------------
NetWork::NetWork()
:m_pNetInterface(NULL),m_isServer(false),m_pLinstener(NULL)
{

}


//--------------------------------------------------------------------------------------------
bool NetWork::initFromFile(const std::string& configFile)
{
	std::ifstream file;
	file.open(configFile.c_str());
	if (file.fail())
	{
		std::string err="netWork can't find configFile filename is:"+configFile;
	    throw (std::exception(err.c_str()));
		return false ;
	}

	char tmpBuf [256];
	memset(tmpBuf,0,256);
	std::string retString;
	size_t readCount=0;


	std::map<std::string,std::string>ParamList;


	while (!file.eof())
	{
		file.getline(tmpBuf,256);
		if(tmpBuf[0]=='#')
		{
			continue;
		}

		char key[256];
		char val[256];
		sscanf(tmpBuf,"%s = %s",key,val);
		ParamList.insert(std::make_pair(key,val));

	}

	std::string serverip;
	std::string password;
	std::map<std::string,std::string>::iterator ParamIterator=ParamList.find("server");
	if(ParamIterator==ParamList.end())
	{
		///û���ҵ�server����
		//wxMessageBox("���������ļ�δ����server�ֶ�");
		std::string err="netWork can't find server field  in  configFile";
		throw (std::exception(err.c_str()));
		return false;
	}else
	{
		if(ParamIterator->second=="true"||ParamIterator->second=="True"||ParamIterator->second=="TRUE")
		{
         m_isServer=true;

		}else
		{
			m_isServer=false;
			ParamIterator=ParamList.find("serverip");
			if(ParamList.end()==ParamIterator)///�ͻ���û���ҵ�������ip
			{
				std::string err="netWork can't find serverip field  in  configFile";
				throw (std::exception(err.c_str()));
				return false;
			}else
			{
				serverip=ParamIterator->second;
			}
		}
	}

  ///���Ҷ˿ں�
    ParamIterator=ParamList.find("portnumber");
	if(ParamIterator==ParamList.end())
	{
		///δ�ҵ��˿ںŶ���
		std::string err="netWork can't find partnumber field  in  configFile";
		throw (std::exception(err.c_str()));
		return false;

	}else
	{
		m_portNumber=atoi(ParamIterator->second.c_str());
	}



	m_pNetInterface=RakNet::RakPeerInterface::GetInstance();
	assert(m_pNetInterface);

	///��������
	ParamIterator=ParamList.find("password");
	if(ParamIterator!=ParamList.end())
	{
		password=ParamIterator->second;
		
	}

	

	if(m_isServer)
	{

		if(password.empty()==false)
		{
			m_pNetInterface->SetIncomingPassword(ParamIterator->second.c_str(),ParamIterator->second.length());
		}

        m_pNetInterface->SetTimeoutTime(NetWorkTimeOut,RakNet::UNASSIGNED_SYSTEM_ADDRESS);
		m_pNetInterface->Startup(NetWorkMaxClientNumber ,&RakNet::SocketDescriptor(m_portNumber,0), 1);
		m_pNetInterface->SetMaximumIncomingConnections(NetWorkMaxClientNumber);
	

	}else///����ǿͻ���
	{

		 m_pNetInterface->SetTimeoutTime(NetWorkTimeOut,RakNet::UNASSIGNED_SYSTEM_ADDRESS);
		m_pNetInterface->Startup(8, &RakNet::SocketDescriptor(), 1);
		m_pNetInterface->SetMaximumIncomingConnections(8);
		m_pNetInterface->SetOccasionalPing(true);

		RakNet::ConnectionAttemptResult res =m_pNetInterface ->Connect(serverip.c_str(), m_portNumber, password.c_str(), password.length());
		if(res>0)
			return false;
	}




	





	return true;
}

//--------------------------------------------------------------------------------------------
NetWork::~NetWork()
{

	if(m_pNetInterface!=NULL)
	{
		m_pNetInterface->Shutdown(300);
		RakNet::RakPeerInterface::DestroyInstance(m_pNetInterface);
	}

	if(m_pLinstener!=NULL)
	{
		SafeDelete(m_pLinstener);
	}


}




//--------------------------------------------------------------------------------------------
void NetWork::receive()
{

	
	RakNet::Packet* p=NULL;
	// GetPacketIdentifier returns this
	unsigned char packetIdentifier;
	unsigned char* pdata=NULL;
	unsigned int usermessageid=0;

	for (p=m_pNetInterface->Receive(); p; m_pNetInterface->DeallocatePacket(p), p=m_pNetInterface->Receive())
	{
		// We got a packet, get the identifier with our handy function
		packetIdentifier = GetPacketIdentifier(p);

		// Check if this is a network message packet
		switch (packetIdentifier)
		{

		case GM_User:///��Ϸ��Ϣ
			/**��ȡ���е���Ϸ��Ϣ����*/
			processGameMessage(p);
			break;

		case ID_DISCONNECTION_NOTIFICATION:///��������˳�
			// Connection lost normally
			printf("ID_DISCONNECTION_NOTIFICATION from %s\n", p->systemAddress.ToString(true));

			if(m_pLinstener!=NULL)
			{
              m_pLinstener->onDisconnect(p);
			}

		
			

			break;


		case ID_NEW_INCOMING_CONNECTION:  ///����ҽ���
			// Somebody connected.  We have their IP now
			printf("ID_NEW_INCOMING_CONNECTION from %s with GUID %s\n", p->systemAddress.ToString(true), p->guid.ToString());
			//clientID=p->systemAddress; // Record the player ID of the client
			if(m_pLinstener!=NULL)
			{
				m_pLinstener->onConnect(p);
			}

			if(m_isServer)
			{
				char tem[2];
				tem[0]=GM_ACCEPTCOME;
				m_pNetInterface->Send(tem,2,HIGH_PRIORITY, RELIABLE,0,p->guid,false);
			}
			//��ҽ����һ��ȷ����Ϣ

			break;

		case   GM_ACCEPTCOME :
			if(m_pLinstener!=NULL)
			{
				m_pLinstener->onConnect(p);
			}
			break;

		case ID_INCOMPATIBLE_PROTOCOL_VERSION:
			printf("ID_INCOMPATIBLE_PROTOCOL_VERSION\n");
			break;

			//case ID_MODIFIED_PACKET:
			// Cheater!
			//	printf("ID_MODIFIED_PACKET\n");
			//	break;

		case ID_CONNECTION_LOST://����쳣���ߵ��쳣�˳����
			// Couldn't deliver a reliable packet - i.e. the other system was abnormally
			// terminated
			if(m_pLinstener!=NULL)
			{
				m_pLinstener->onConnectlost(p);
			}

			printf("ID_CONNECTION_LOST from %s\n", p->systemAddress.ToString(true));;
			break;

	

		default:
		
			break;
		}


	}

  return ;
}

//--------------------------------------------------------------------------------------------
bool NetWork::conect(const std::string& ip,unsigned int serverPort,const std::string& password)
{

	RakNet::ConnectionAttemptResult res=m_pNetInterface->Connect(ip.c_str(), serverPort, password.c_str(), password.length()==RakNet::CONNECTION_ATTEMPT_STARTED);
	
	return res==RakNet::CONNECTION_ATTEMPT_STARTED;



}

//--------------------------------------------------------------------------------------------
//void NetWork::close(const RakNet::SystemAddress& paddress)
//{
//	if(m_pNetInterface!=NULL)
//	{
//      m_pNetInterface->CloseConnection(paddress,true);
//	}
//
//}


/**�ر�����*/
void NetWork::close(const char* pAddress,short unsigned int portnumber)
{

	if(m_pNetInterface!=NULL)
	{
		m_pNetInterface->CloseConnection(RakNet::SystemAddress(pAddress,portnumber),true);
	}

}

//--------------------------------------------------------------------------------------------
void NetWork::update()
{

	receive();

}

//--------------------------------------------------------------------------------------------
unsigned char  NetWork::GetPacketIdentifier(RakNet::Packet *p)
{
	if (p==0)
		return 255;

	if ((unsigned char)p->data[0] == ID_TIMESTAMP)
	{
		RakAssert(p->length > sizeof(unsigned char) + sizeof(unsigned long));
		return (unsigned char) p->data[sizeof(unsigned char) + sizeof(unsigned long)];
	}
	else
		return (unsigned char) p->data[0];
}



//--------------------------------------------------------------------------------------------
unsigned int NetWork::getUserMessage(RakNet::Packet * p,unsigned char**pdata)
{
	unsigned long usermessageid=0;
	if(p==NULL)
		return usermessageid;

	 

	if ((unsigned char)p->data[0] == ID_TIMESTAMP)
	{
		RakAssert(p->length > sizeof(unsigned char) + sizeof(unsigned long));

		assert(false);
		usermessageid= p->data[sizeof(unsigned char) + sizeof(unsigned long)+sizeof(BYTE)];
		*pdata=p->data+sizeof(unsigned char) + sizeof(unsigned long)+sizeof(BYTE)+sizeof(unsigned int);

	}
	else
	{
		

		RakNet::BitStream bs(p->data,p->length,false);
		bs.IgnoreBytes(sizeof(unsigned char));
		bs.Read(usermessageid);


		//unsigned int offset=sizeof(BYTE);
		//usermessageid= *((unsigned int*)(p->data+offset));
		*pdata=p->data+sizeof(BYTE)+sizeof(unsigned int);

	}

	return usermessageid;

}



//--------------------------------------------------------------------------------------------
void NetWork::send(unsigned int message,const  char* pData,unsigned int length,RakNet::RakNetGUID receiver)
{

	unsigned int bitdatalenght=length<<3;
	unsigned int mesagelenght=sizeof(byte)+sizeof(unsigned int)+length;

	RakNet::BitStream stream;
	stream.Write((byte)GM_User);
	stream.Write((unsigned int)message);
	stream.WriteBits((const unsigned char*)pData,bitdatalenght);

	m_pNetInterface->Send(&stream, HIGH_PRIORITY, RELIABLE, 0, receiver, false);
}


//--------------------------------------------------------------------------------------------
void NetWork::send(unsigned int message,const  char* pData,unsigned int length,RakNet::SystemAddress& receiver)
{
	if(m_pNetInterface==NULL)
		return ;

	RakNet::RakNetGUID id=m_pNetInterface->GetGuidFromSystemAddress(receiver);
	send(message,pData,length,id);
    return ;

}


//--------------------------------------------------------------------------------------------
void  NetWork::broadcastMessage(unsigned int message,const unsigned  char* pdata,unsigned length)
{
	unsigned int bitdatalenght=length*8;
	unsigned int mesagelenght=sizeof(byte)+sizeof(unsigned int)+length;

	RakNet::BitStream stream;
	stream.Write((unsigned char)GM_User);
	stream.Write((unsigned int)message);
	stream.WriteBits(pdata,bitdatalenght);

	bitdatalenght=stream.GetNumberOfBitsUsed();
	m_pNetInterface->Send(&stream, HIGH_PRIORITY, RELIABLE, 0,RakNet::UNASSIGNED_SYSTEM_ADDRESS , true);

}


//--------------------------------------------------------------------------------------------
void NetWork::setListener(netWorkListener* pListener)
{
	SafeDelete(m_pLinstener);
	m_pLinstener=pListener;

}

//--------------------------------------------------------------------------------------------
void NetWork::processGameMessage(RakNet::Packet* p)
{

	unsigned long t = 0;
	int msgInfoLenth = 0;

	unsigned char * pdata = NULL;

	//����������������ȡ��������
	RakNet::BitStream bitStream( p->data , p->length ,false );
	bitStream.IgnoreBytes(sizeof(unsigned char));
	bitStream.Read( t );

	int size = bitStream.GetNumberOfBytesUsed()-( sizeof(DWORD) + sizeof(byte) );

	assert(size>0);
	pdata = new unsigned char[size];

	//��ȡ������
	bitStream.ReadBits( pdata, size*8 );

	//������Ϣ
	fireMessage( t , pdata );

	if( !pdata )
	{
		delete []pdata;
	}

	return ;
}

//--------------------------------------------------------------------------------------------
void NetWork::pingLan(short unsigned int portnumber)
{
	if(m_pNetInterface!=NULL)
	{
		m_pNetInterface->Ping("255.255.255.255", portnumber, true);

	}

}