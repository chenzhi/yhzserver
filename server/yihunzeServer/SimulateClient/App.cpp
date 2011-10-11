#include "pch.h"
#include "vld.h"
#include "App.h"
#include "SimulateClientMainFrame.h"
#include "netWork.h"
#include "netWorkListener.h"
#include "MessageReceive.h"












IMPLEMENT_APP(MyApp)



bool:: MyApp::OnInit()
{

	Helper::setCurrentWorkPath();

	new xLogMessager("SimulateClient.log");


	Config config;
	assert(config.loadfile("networker.cfg"));

	std::string serverip;
	std::string password;
	unsigned int portnubmer;

	assert(config.getValue("serverip",serverip));
	assert(config.getValue("portnumber",password));
	portnubmer=Helper::StringToInt(password);
	assert(config.getValue("password",password));




	m_pNetWorker=new NetWorkClient();

	if(m_pNetWorker->createConnect("statserver",serverip,portnubmer,password)==false)
		return false;

  // if(m_pNetWorker-> connect(serverip,portnubmer,password)==false)
	 //  return false;

	m_pNetWorkListener=new ServerListener();
	m_pNetWorker->setNetworkListener(m_pNetWorkListener);

	m_pframe = new SimulateClientMainFrame(NULL);
	m_pframe->Show(true);


	new MessageReceive();

	return true;
}


bool   MyApp::ProcessIdle()
{


	MessageReceive::getSingletonPtr()->update();

	if(m_pNetWorker!=NULL)
	{
		m_pNetWorker->update();
	}


	wxApp::ProcessIdle();
	return 	true;
	
}



 int MyApp::OnExit()
 {

	 delete MessageReceive::getSingletonPtr();


	 SafeDelete(m_pNetWorker);
	 SafeDelete(m_pNetWorkListener);
	 delete xLogMessager::getSingletonPtr();

	
	 return 0;
 }


 void  MyApp::OnKeyUp(wxKeyEvent& event)
 {
	 if(event.m_keyCode==WXK_ESCAPE)
	 {
	 ::PostQuitMessage(0);
	 }

	event.Skip();

	return ;

 }