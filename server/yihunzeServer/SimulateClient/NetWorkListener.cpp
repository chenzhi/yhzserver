#include "pch.h"
#include "NetWorkListener.h"
#include "SimulateClientMainFrame.h"
#include "App.h"
#include "MessageReceive.h"

template<> ServerListener* Singleton<ServerListener>::ms_Singleton=NULL;

//----------------------------------------------------------------
void ServerListener::onConnect(RakNet::Packet* p)
{

	if(hasContectServer(p->systemAddress))
	{
		return ;
	}

	m_AddressVector.push_back(p->systemAddress);


	updateServerList();
	return ;
}

//----------------------------------------------------------------
void ServerListener::onDisconnect(RakNet::Packet* p)
{

	AddressVector::const_iterator it=std::find(m_AddressVector.begin(),m_AddressVector.end(),p->systemAddress);
	if(it!=m_AddressVector.end())
	{
		m_AddressVector.erase(it);
	}
	
//	MessageReceive::getSingletonPtr()->connectGameServer();

	updateServerList();
	return ;
}

//----------------------------------------------------------------
void  ServerListener::onConnectlost(RakNet::Packet* p)
{
	AddressVector::const_iterator it=std::find(m_AddressVector.begin(),m_AddressVector.end(),p->systemAddress);
	if(it!=m_AddressVector.end())
	{
		m_AddressVector.erase(it);
	}

	updateServerList();
	return ;

}

//----------------------------------------------------------------
bool  ServerListener::hasContectServer(const RakNet::SystemAddress& address)
{
	
	AddressVector::const_iterator  it=std::find(m_AddressVector.begin(),m_AddressVector.end(),address);
	if(it==m_AddressVector.end())
		return false;

	return true;
}


//----------------------------------------------------------------
void  ServerListener::updateServerList()
{

	MyApp* pApp=static_cast<MyApp*>(&wxGetApp());
	pApp->m_pframe->updateServerList(m_AddressVector);


}


void  ServerListener::onConnectFailed(RakNet::Packet* p)
{
	MyApp* pApp=static_cast<MyApp*>(&wxGetApp());
	pApp->m_pframe->updateServerList(m_AddressVector);
	pApp->m_pframe->addReceiveMessage( "���ӷ�����ʧ�ܣ�",p->systemAddress);

}