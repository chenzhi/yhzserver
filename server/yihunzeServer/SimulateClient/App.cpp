#include "pch.h"
#include "App.h"
#include "SimulateClientMainFrame.h"
#include "../yihunzeServer/netWork.h"
#include "netWorkListener.h"













IMPLEMENT_APP(MyApp)



bool:: MyApp::OnInit()
{

	char pBuffer[1024];
	ZeroMemory(pBuffer, 1024);
	GetModuleFileName(NULL, pBuffer, 1024);

	//设置当前目录为进程目录，防止通过文件关联打开程序的当前目录不正确
	std::string	 dirname;
	std::string cc=pBuffer;
	std::string::size_type pos =cc.find_last_of("\\");
	dirname = cc.substr(0,pos);
	SetCurrentDirectory(dirname.c_str());


	m_pNetWorker=new NetWork();
	m_pNetWorker->initFromFile("networker.cfg");

	m_pNetWorkListener=new ServerListener();
	m_pNetWorker->setListener(m_pNetWorkListener);

	m_pframe = new SimulateClientMainFrame(NULL);
	m_pframe->Show(true);

	return true;
}


bool   MyApp::ProcessIdle()
{

	if(m_pNetWorker!=NULL)
	{
		m_pNetWorker->update();
	}

	wxApp::ProcessIdle();
	return 	true;
	
}



 int MyApp::OnExit()
 {


	 SafeDelete(m_pNetWorker);

	
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