#include "pch.h"
#include "netWork.h"
#include <fstream>
#include "xLogManager.h"
#include "usermessage.h"



//-----------------------------------------------
//NetWork::NetWork(bool isClient,unsigned int ClientPort)
//:m_pNetInterface(NULL),m_isServer(false),m_pLinstener(NULL)
//{
//
//	m_pNetInterface=RakNet::RakPeerInterface::GetInstance();
//	assert(m_pNetInterface);
//	if(isClient)
//	{
//		RakNet::SocketDescriptor socketDescriptor(ClientPort,0);
//		m_pNetInterface->Startup(8,&socketDescriptor, 1);
//		m_pNetInterface->SetOccasionalPing(true);
//	}
//
//}

//--------------------------------------------------------------------------------------------
NetWork::NetWork()
:m_pNetInterface(NULL),m_isServer(false),m_pLinstener(NULL),m_pNetPack(NULL)
{

	m_pNetInterface=RakNet::RakPeerInterface::GetInstance();
	assert(m_pNetInterface);

}

/*
//--------------------------------------------------------------------------------------------
bool NetWork::initFromFile(const std::string& configFile)
{
	std::ifstream file;
	file.open(configFile.c_str());
	if (file.fail())
	{
		std::string err="netWork can't find configFile filename is:"+configFile;
	   // throw (std::exception(err.c_str()))
		xLogMessager::getSingleton().logMessage(err);
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
		///没有找到server定义
		//wxMessageBox("网络配置文件未定义server字段");
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
			if(ParamList.end()==ParamIterator)///客户端没有找到服务器ip
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

  ///查找端口号
    ParamIterator=ParamList.find("portnumber");
	if(ParamIterator==ParamList.end())
	{
		///未找到端口号定义
		std::string err="netWork can't find partnumber field  in  configFile";
		throw (std::exception(err.c_str()));
		return false;

	}else
	{
		m_portNumber=atoi(ParamIterator->second.c_str());
	}
	

	///查找密码
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
	

	}else///如果是客户端
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
//*/


/*
//--------------------------------------------------------------------------------------------
bool NetWork::startServer(unsigned int portNumber,const std::string& password)
{

	m_portNumber=portNumber;
	m_isServer=true;

	if(password.empty()==false)
	{
		m_pNetInterface->SetIncomingPassword(password.c_str(),password.length());
	}

	m_pNetInterface->SetTimeoutTime(NetWorkTimeOut,RakNet::UNASSIGNED_SYSTEM_ADDRESS);
	m_pNetInterface->Startup(NetWorkMaxClientNumber ,&RakNet::SocketDescriptor(portNumber,0), 1);
	m_pNetInterface->SetMaximumIncomingConnections(NetWorkMaxClientNumber);

	m_pNetInterface->SetOccasionalPing(true);
	m_pNetInterface->SetUnreliableTimeout(1000);

	return true;

}
//*/

//--------------------------------------------------------------------------------------------
NetWork::~NetWork()
{


	SafeDelete(m_pNetPack);
	if(m_pNetInterface!=NULL)
	{
		m_pNetInterface->Shutdown(300);
		RakNet::RakPeerInterface::DestroyInstance(m_pNetInterface);
		m_pNetInterface=NULL;
	}

}




//--------------------------------------------------------------------------------------------
void NetWork::receive()
{

	if(m_pNetInterface==NULL)
		return ;
	
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

		case GM_User:///游戏消息
			/**获取包中的游戏消息定义*/
			processGameMessage(p);
			break;

		case ID_DISCONNECTION_NOTIFICATION:///玩家主动退出
			// Connection lost normally
			printf("ID_DISCONNECTION_NOTIFICATION from %s\n", p->systemAddress.ToString(true));

			if(m_pLinstener!=NULL)
			{
              m_pLinstener->onDisconnect(p);
			}
			break;
             
		case ID_NEW_INCOMING_CONNECTION:  ///新玩家进入
			// Somebody connected.  We have their IP now
			printf("ID_NEW_INCOMING_CONNECTION from %s with GUID %s\n", p->systemAddress.ToString(true), p->guid.ToString());
			//clientID=p->systemAddress; // Record the player ID of the client
			if(m_pLinstener!=NULL)
			{
				m_pLinstener->onConnect(p);
			}

			if(m_isServer)
			{
				///如果是服务器就回一消息组客户端
				RakNet::BitStream stream;
				stream.Write((byte)GM_User);
				stream.Write((unsigned int)GM_ACCEPTCOME);
				m_pNetInterface->Send(&stream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, p->guid, false);
				//this->send(GM_ACCEPTCOME,0,p->guid);
			}
			//玩家进入后发一条确认信息

			break;

	/*	
	    case   GM_ACCEPTCOME :
			if(m_pLinstener!=NULL)
			{
				m_pLinstener->onConnect(p);
			}
			break;
			//*/

		case ID_INCOMPATIBLE_PROTOCOL_VERSION:
			printf("ID_INCOMPATIBLE_PROTOCOL_VERSION\n");
			break;

			//case ID_MODIFIED_PACKET:
			// Cheater!
			//	printf("ID_MODIFIED_PACKET\n");
			//	break;

		case ID_CONNECTION_LOST://玩家异常掉线等异常退出情况
			// Couldn't deliver a reliable packet - i.e. the other system was abnormally
			// terminated
			if(m_pLinstener!=NULL)
			{
				m_pLinstener->onConnectlost(p);
			}

			printf("ID_CONNECTION_LOST from %s\n", p->systemAddress.ToString(true));;
			break;
		case ID_CONNECTION_ATTEMPT_FAILED:
			if(m_pLinstener!=NULL)
			{
				m_pLinstener->onConnectFailed(p);
			}

			break;;

	

		default:
		
			break;
		}


	}

  return ;
}

//--------------------------------------------------------------------------------------------
bool NetWork:: connect(const std::string& ip,unsigned int serverPort,const std::string& password)
{

	RakNet::ConnectionAttemptResult res=m_pNetInterface->Connect(ip.c_str(), serverPort, password.c_str(), password.length());
	
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


/**关闭连接*/
void NetWork::close(const char* pAddress,short unsigned int portnumber)
{

	if(m_pNetInterface!=NULL)
	{
		m_pNetInterface->CloseConnection(RakNet::SystemAddress(pAddress,portnumber),true,0,IMMEDIATE_PRIORITY);
	}

}

//--------------------------------------------------------------------------------------------
void NetWork::close(const  RakNet::SystemAddress& address)
{
	
	if(m_pNetInterface!=NULL)
	{
		m_pNetInterface->CloseConnection(address,true);
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
void NetWork::setListener(netWorkListener* pListener)
{
	SafeDelete(m_pLinstener);
	m_pLinstener=pListener;

}

//--------------------------------------------------------------------------------------------
void NetWork::processGameMessage(RakNet::Packet* p)
{

	
	if(m_pNetPack==NULL)
	{
		m_pNetPack=new NetPack(p);
	}

	unsigned int messageid=m_pNetPack->getGameMessageID();
	if(messageid==GM_ACCEPTCOME&&m_pLinstener!=NULL)
	{
		m_pLinstener->onConnect(p);
	}


	m_pNetPack->setRaknetPack(p);
	fireMessage( m_pNetPack->getGameMessageID() ,m_pNetPack );

	return ;






	unsigned long t = 0;
	int msgInfoLenth = 0;

	unsigned char * pdata = NULL;

	//构造数据流，并读取类型数据
	RakNet::BitStream bitStream( p->data , p->length ,false );
	bitStream.IgnoreBytes(sizeof(unsigned char));
	bitStream.Read( t );

	int size = bitStream.GetNumberOfBytesUsed()-( sizeof(DWORD) + sizeof(byte) );

	assert(size>0);
	pdata = new unsigned char[size];

	//读取包数据
	bitStream.ReadBits( pdata, size*8 );

	//发送消息
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


//--------------------------------------------------------------------------------------------
 void*  NetWork::getPackDataptr(RakNet::Packet* p)
{
	if(p==NULL)
		return NULL;


	//unsigned long t = 0;
	//int msgInfoLenth = 0;

	//unsigned char * pdata = NULL;

	//构造数据流，并读取类型数据
	//RakNet::BitStream bitStream( p->data , p->length ,false );
	//bitStream.IgnoreBytes(sizeof(unsigned char));
	//bitStream.Read( t );

	//int size = bitStream.GetNumberOfBytesUsed()-( sizeof(DWORD) + sizeof(byte) );

	return p->data+sizeof(DWORD) + sizeof(byte);
}


//--------------------------------------------------------------------------------------------
 RakNet::ConnectionState   NetWork::getConnectState(const RakNet::SystemAddress& address) const 
 {
	 if(m_pNetInterface==NULL)
		 return RakNet::IS_NOT_CONNECTED;

	 RakNet::AddressOrGUID temadd(address);
	 return  m_pNetInterface->GetConnectionState(RakNet::AddressOrGUID(temadd));


 }