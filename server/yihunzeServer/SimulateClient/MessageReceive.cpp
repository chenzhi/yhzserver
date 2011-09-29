
#include "pch.h"
#include "MessageReceive.h"
#include "usermessage.h"
#include "NetWorkListener.h"
#include "App.h"
#include "SimulateClientMainFrame.h"

template<>
MessageReceive* Singleton<MessageReceive>::ms_Singleton=NULL;



MessageReceive::MessageReceive()
{
	NetWorkClient::getSingleton().registerMessageHandle(GM_ACCEPTCOME,&MessageReceive::processConnectRemoteServer,this);
	NetWorkClient::getSingleton().registerMessageHandle(GM_ACCOUNT_RESPOND_FAILED,&MessageReceive::processAccountFaild,this);
	NetWorkClient::getSingleton().registerMessageHandle(GM_ACCOUNT_RESPOND_SUCCEED,&MessageReceive::processAccountSucceed,this);

}


MessageReceive::~MessageReceive()
{

	NetWorkClient::getSingleton().unregisterMessageHandle(GM_ACCOUNT_RESPOND_FAILED,this);
	NetWorkClient::getSingleton().unregisterMessageHandle(GM_ACCOUNT_RESPOND_SUCCEED,this);

}


///���������Ϣ
void MessageReceive::processAccountFaild(NetPack* pPack)
{
	NetByte* puser=reinterpret_cast<NetByte*>(pPack->getData());
	if(puser->m_byte==0)
	{
		MessageBox(NULL,"�û����������!","����",MB_OK);
	}else
	{
         MessageBox(NULL,"�û�����ȷ","��ȷ",MB_OK);
	}

	return ;
}



///�������ɹ���Ϣ
void MessageReceive::processAccountSucceed(NetPack* pPack)
{

	GameServerInfor* pGameserver=(GameServerInfor*) pPack->getData();


	NetWorkClient::getSingleton().close(pPack->getAddress());
	NetWorkClient::getSingleton(). connect(pGameserver->m_GameServerIP,pGameserver->m_PortNumber,pGameserver->m_GameServerPassWord); 

	///��¼��Ϸ��������ַ
	RakNet::SystemAddress  tem(pGameserver->m_GameServerIP,pGameserver->m_PortNumber);
	m_GameServerAdderss=tem;
    m_GameServerPassWord=pGameserver->m_GameServerPassWord;


	MyApp* pApp=static_cast<MyApp*>(&wxGetApp());
	wxString receiveMessage;
	receiveMessage=receiveMessage.Format("�ʺŷ�������֤�ɹ��������ʺ�id: %d ", (pGameserver->m_accountid));
	pApp->m_pframe->addSendMessage(receiveMessage);




}

///�ɹ�����Զ�̼����
void MessageReceive::processConnectRemoteServer(NetPack* pPack)
{
	if(pPack->getAddress()==m_GameServerAdderss)
	{
		MyApp* pApp=static_cast<MyApp*>(&wxGetApp());
		wxString receiveMessage;
		receiveMessage=receiveMessage.Format("����Զ����Ϸ�������ɹ�:%s",pPack->getAddress().ToString());
		pApp->m_pframe->addSendMessage(receiveMessage);

	}

	ServerListener::getSingleton().onConnect(pPack->getRakNetPack());


}