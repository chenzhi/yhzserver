#include "pch.h"
#include "SimulateClientMainFrame.h"
#include "usermessage.h"

SimulateClientMainFrame::SimulateClientMainFrame( wxWindow* parent )
:
MainFrame( parent )
{

	initMessageID();


}

void SimulateClientMainFrame::onMainFrameKeyDown( wxKeyEvent& event )
{
// TODO: Implement onMainFrameKeyDown
}

void SimulateClientMainFrame::onSelectServer( wxCommandEvent& event )
{
// TODO: Implement onSelectServer
}

void SimulateClientMainFrame::onSelectMessage( wxCommandEvent& event )
{
// TODO: Implement onSelectMessage
}

void SimulateClientMainFrame::OnSend( wxCommandEvent& event )
{

	wxString serverName=m_serverList->GetStringSelection();
	wxString messageID=m_messagelist->GetStringSelection();
	wxString message= m_MessageText->GetValue();

	if(serverName.empty()||messageID.empty()||messageID.empty())
	{
		wxMessageBox("请选择服务器，消息id，和消息内容");
		return ;
	}

	unsigned int  id=stringToMessageID(messageID.c_str());
	RakNet::SystemAddress address;
	address.SetBinaryAddress(serverName.c_str());

	if(id==GM_TEXT_MESSAGE)
	{
		NetWork::getSingletonPtr()->send(id,message.c_str(),message.Length(),address);
		m_MessageText->Clear();
		addSendMessage(message);
	}else if(GM_ACCOUNT_REQUEST==id)
	{
         UserLogin userlogin;
		 ::ZeroMemory(&userlogin,sizeof(userlogin));
		 memcpy(userlogin.m_account,"palyer1",strlen("player1"));
		 memcpy(userlogin.m_password,"palyer1",strlen("player1"));
		 NetWork::getSingleton().send(id,userlogin,address);
	}





	return ;



	

}


void  SimulateClientMainFrame::OnMessageTextKeyup( wxKeyEvent& event )
{

	if(event.GetKeyCode()==WXK_RETURN)
	{
	   wxCommandEvent e;
      OnSend(e);
	}

}

//---------------------------------------------------------------------
void SimulateClientMainFrame::updateServerList(const AddressVector& serverLister)
{
	m_serverList->Clear();
	AddressVector::const_iterator it=serverLister.begin();
	AddressVector::const_iterator endit=serverLister.end();
	for(;it!=endit;++it)
	{
		m_serverList->Insert(wxString(it->ToString()),0);
	}

}


//---------------------------------------------------------------------
void SimulateClientMainFrame::initMessageID()
{

	m_MessageMap["GM_TEXT_MESSAGE"]=GM_TEXT_MESSAGE;
	m_MessageMap["GM_ACCOUNT_REQUEST"]=GM_ACCOUNT_REQUEST;






	m_messagelist->Clear();
	MessageIDMap::const_iterator it=m_MessageMap.begin();
	MessageIDMap::const_iterator endit=m_MessageMap.end();
	for(;it!=endit;++it)
	{
		m_messagelist->Insert(wxString(it->first),0);
	}

}

//---------------------------------------------------------------------
unsigned int SimulateClientMainFrame::stringToMessageID(const std::string& message)
{
	MessageIDMap::const_iterator it=m_MessageMap.find(message);
	if(it!=m_MessageMap.end())
	{
		return it->second;
	}

	return 0;
}


///加条发送的消息
void  SimulateClientMainFrame::addReceiveMessage(const std::string& message,RakNet::SystemAddress& Address)
{
	wxString tem;
	tem+=Address.ToString();
	tem+=": ";
	tem+=message;
	tem+="\n";

	m_receiveText->AppendText(message);

}


///加入一条接收的消息
void  SimulateClientMainFrame::addSendMessage(const wxString& message)
{
	
	wxString tem;
	tem+=message;
	tem+="\n";
	m_receiveText->AppendText(tem);

}