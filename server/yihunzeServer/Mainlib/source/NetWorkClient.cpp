#include "pch.h"
#include "NetWorkClient.h"




//----------------------------------------------------------------
NetWorkClientInstance::NetWorkClientInstance(const std::string& name)
:m_Name(name),m_needShoudown(false)
{


	m_isServer=false;



}


//----------------------------------------------------------------
NetWorkClientInstance::~NetWorkClientInstance()
{

	if(hasConnect())
	{
		closeConnect();
	}

}


//----------------------------------------------------------------
bool NetWorkClientInstance::connect(const std::string& ip,unsigned int serverPort,const std::string& password)
{

	if(m_pNetInterface==NULL)
	{
		m_pNetInterface=RakNet::RakPeerInterface::GetInstance();
	}

//	m_pNetInterface->SetTimeoutTime(NetWorkTimeOut,RakNet::UNASSIGNED_SYSTEM_ADDRESS);
	//m_pNetInterface->AllowConnectionResponseIPMigration(false);
	RakNet::SocketDescriptor socketDescriptor(0,0);


	m_pNetInterface->Startup(1, &socketDescriptor,1);
	//m_pNetInterface->SetMaximumIncomingConnections(1);
	//m_pNetInterface->SetOccasionalPing(true);
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
bool  NetWorkClientInstance::hasConnect() const 
{

	return 	NetWork::getConnectState(m_ServerAddress)==RakNet::IS_CONNECTED;

}


//----------------------------------------------------------------
void  NetWorkClientInstance::update( )
{

	NetWork::update();
	return ;
}


//-------------------------------------------------------------------------
void  NetWorkClientInstance::closeConnect()
{
	NetWork::close(m_ServerAddress);
	return ;
}


//--------------------------------------------------------------------------------------
void NetWorkClientInstance::send(unsigned int message,const  char* pData,unsigned int length)
{

	unsigned int bitdatalenght=length<<3;
	unsigned int mesagelenght=sizeof(byte)+sizeof(unsigned int)+length;

	RakNet::BitStream stream;
	stream.Write((byte)GM_User);
	stream.Write((unsigned int)message);
	stream.WriteBits((const unsigned char*)pData,bitdatalenght);
	m_pNetInterface->Send(&stream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, m_ServerAddress, false,1);
}




//-------------------------------------------------------------------

template<> NetWorkClient* Singleton<NetWorkClient>::ms_Singleton=NULL;



void NetWorkClient::update()
{

	size_t size=m_InstanceCollect.size();
	for(size_t i=0;i<size;++i)
	{
		m_InstanceCollect[i]->update();
	}


	///如果有需要销毁的
	size=DestroyInstanceCollect.size();
	for(size_t i=0;i<size;++i)
	{
		this->_destroyAllInstance(DestroyInstanceCollect[i]);	
	}
	DestroyInstanceCollect.clear();
	
	return ;

}


//-------------------------------------------------------------------
void NetWorkClient::setNetworkListener(netWorkListener* pListener)
{

	m_pListener=pListener;
}


//-------------------------------------------------------------------
bool NetWorkClient::createConnect(const std::string& name,const std::string& serverip,unsigned int portnumber,const std::string& passWord)
{

	NetWorkClientInstance* pInstance=new NetWorkClientInstance(name);
	if(pInstance->connect(serverip,portnumber,passWord)==false)
	{

		delete pInstance;
		return false;
	}
	m_InstanceCollect.push_back(pInstance);
	if(m_pListener!=NULL)
	{
		pInstance->setListener(m_pListener);
	}

	return true;


}

//-------------------------------------------------------------------
NetWorkClientInstance* NetWorkClient::getConnectInstance(const std::string& name) const 
{

	ClientInstanceCollect::const_iterator it=m_InstanceCollect.begin();
	ClientInstanceCollect::const_iterator endit=m_InstanceCollect.end();
	for(;it!=endit;++it)
	{
		if((*it)->getName()==name)
			return *it;
	}

	return NULL;
}

//-------------------------------------------------------------------
void NetWorkClient::destroyInstance(const std::string& name)
{

	DestroyInstanceCollect.push_back(name);
	
	return ;
}


//-------------------------------------------------------------------
void NetWorkClient::destroyAllInstance()
{

	ClientInstanceCollect::iterator it=m_InstanceCollect.begin();
	ClientInstanceCollect::iterator endit=m_InstanceCollect.end();
	for(;it!=endit;++it)
	{
		SafeDelete(*it);
    }

	m_InstanceCollect.clear();
	return ;


}


///真实的销毁动作
void NetWorkClient::_destroyAllInstance(const std::string& name)
{

	ClientInstanceCollect::iterator it=m_InstanceCollect.begin();
	ClientInstanceCollect::iterator endit=m_InstanceCollect.end();
	for(;it!=endit;++it)
	{
		if((*it)->getName()==name)
		{
			SafeDelete(*it);
			m_InstanceCollect.erase(it);
			return ;
		 }
	}
   return ;
}