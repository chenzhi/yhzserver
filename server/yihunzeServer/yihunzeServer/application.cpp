#include "pch.h"
//#include "vld.h"
#include "application.h"
#include "netWork.h"
#include "LoginManager.h"
#include "NetWorkListener.h"
#include "xLogManager.h"
#include "databaseInstance.h"
#include "GameServerManager.h"


#define ServerName       "印魂者状态服务器"

#define PrintWindID   99999


INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
{


    Application* g_pApp=NULL;

	try
	{

		g_pApp= new  Application(hInst);
		g_pApp->go();
		

	}
	catch(std::exception &e)
	{
		//MessageBox(NULL, e.getFullDescription().c_str(), "Exception", MB_OK | MB_ICONERROR | MB_TASKMODAL);
		MessageBox(NULL, e.what(), "Exception", MB_OK | MB_ICONERROR | MB_TASKMODAL);

	}

	SafeDelete(g_pApp);
	return 0;
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:

		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 在此添加任意绘图代码...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}





template<> Application* Singleton<Application>::ms_Singleton=NULL;

//-----------------------------------------------------------------
Application::Application(HINSTANCE  Instance)
:mInstance(Instance),mHwnd(NULL),m_pNetWork(NULL),m_pLoginManager(NULL),m_PrintWind(NULL),
/*m_pDatabaseInstance(NULL),*/m_pNetlistener(NULL),m_GameSreverManager(NULL)
{


	Helper::setCurrentWorkPath();

	new xLogMessager("stateserver.log");
	xLogMessager::getSingleton().logMessage("印魂者状态服务器启动...");

}


//-----------------------------------------------------------------
Application:: ~Application()
{


	SafeDelete(m_GameSreverManager);
	SafeDelete(m_pLoginManager);
	SafeDelete(m_pNetWork);

	SafeDelete(m_pNetlistener);
    //SafeDelete(m_pDatabaseInstance);
	

	xLogMessager::getSingleton().logMessage("服务器退出...");
	delete xLogMessager::getSingletonPtr();


}

void    Application::update(float time)
{
	if(m_pNetWork!=NULL)
	{
		m_pNetWork->update();
	}

	return ;

}

//-----------------------------------------------------------------
void    Application::go()
{



	if(init()==false)
		return ;

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while(TRUE)
	{

		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
		{ 
			// 如果是退出消息,退出
			if(msg.message == WM_QUIT) 
				return ;

			// 处理其他消息
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		static DWORD lasttime=::GetTickCount();
		DWORD CurrentTime=::GetTickCount();
		float time=(CurrentTime-lasttime)*0.001f;
		update(time);
		lasttime=CurrentTime;

	}


}

//-----------------------------------------------------------------
bool	Application::init()
{


	
	if(initWindow(800,600)==false)
		return false;

	Config config;
	config.loadfile("stateserver.cfg");

	std::string portNumber;
	std::string networkpassword;
	unsigned   int  iport=0;
	if(config.getValue("networkportnumber",portNumber))
	{
		iport=Helper::StringToInt(portNumber);
		m_gameServerPortnumber=iport;

	}else
	{
		::MessageBox(NULL,"读取配置文件错误,未找到端口号设置","错误 ",MB_OK);
		xLogMessager::getSingleton().logMessage("读取配置文件错误,未找到端口号设置");
		return false;
	}

	config.getValue("networkpassword",networkpassword);



	
	m_pNetWork=new NetWorkServer();
	if(m_pNetWork->startServer(iport,networkpassword)==false)
	{
		::MessageBox(NULL,"初始化网络错误，请检查配置文件是否正确","错误",MB_OK);
		SafeDelete(m_pNetWork);
		return false;
	}


	

	/*
	///数据库连接
	std::string DataServer;
	std::string DataName;
	std::string DataUser;
	std::string DataPassWord;
	std::string DataPortNumber;
	config.getValue("databaseserver",DataServer);
	config.getValue("databasename",DataName);
	config.getValue("databaseuser",DataUser);
	config.getValue("databasepassword",DataPassWord);
	config.getValue("databaseportnumber",DataPortNumber);
	if(DataUser.empty()||DataServer.empty()||DataName.empty()||DataPassWord.empty()||DataPortNumber.empty())
	{

		std::string error="读取配置文件错误，数据库设置错误 ";
		::MessageBox(NULL,error.c_str(),"错误 ",MB_OK);
		xLogMessager::getSingleton().logMessage(error);
		return false;

	}
	iport=Helper::StringToInt(DataPortNumber);


	m_pDatabaseInstance=new DatabaseInstace();
	if(	m_pDatabaseInstance->open(DataServer.c_str(),DataUser.c_str(),DataPassWord.c_str(),DataName.c_str(),iport)==false)
	{
		Application::getSingleton().addPrintMessage("打开数据库成功");
		xLogMessager::getSingleton().logMessage("打开数据库成功...");
        return false;
	}else
	{
		Application::getSingleton().addPrintMessage("打开数据库成功");
		xLogMessager::getSingleton().logMessage("打开数据库成功...");
	}

	//*/



	///连接到帐号服务器
	if(connectAccountServer(config)==false)
	{
		return false;
	}





	//CppMySQLQuery *query=NULL;
	//m_pDatabaseInstance->querySQL("select * from player",&query);

	//unsigned int row=query->numRow();
	//
	//while(!query->eof())
	//{
	//	int playerid=query->getIntField("playerid",0);
	//	std::string name=query->getStringField("name","");
	//	query->nextRow();
	//}

	////CppMySQLQuery* pQuery=NULL;
	//m_pDatabaseInstance->execProcedurce("call query_student(17,@param2)" );

	//	if(m_pDatabaseInstance->querySQL("select @param2",&pQuery))
	//	{

	//		while(!pQuery->eof())
	//		{
	//			int playerid=pQuery->getIntField("@param2",0);
	//			pQuery->nextRow();
	//		}

	//	}



	m_pNetlistener=new ServerListener();
	m_pNetWork->setListener(m_pNetlistener);

	m_pLoginManager=new LoginManager();

	m_GameSreverManager=new GameServerManager("gameserver.cfg");

	return true;
}

//-----------------------------------------------------------------
bool Application::initWindow(int width, int height)
{

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	//::ZeroMemory(&wcex,wcex.cbSize);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= mInstance;
	wcex.hIcon			= 0;
	wcex.hCursor		= NULL;
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= 0;
	wcex.lpszClassName	= "yhzwindow";
	wcex.hIconSm		= 0;

	RegisterClassEx(&wcex);

	mHwnd = CreateWindow(wcex.lpszClassName, "印魂者全局服务器", WS_OVERLAPPEDWINDOW,
		100, 100, 1024, 768,/*100, 100, 1024, 768,*/ NULL, NULL, mInstance, NULL);

	if (!mHwnd)
	{
		return FALSE;
	}


	///创建一个多行消息框
	m_PrintWind=CreateWindow( "edit", "",
		WS_VISIBLE|WS_CHILD|WS_BORDER|WS_VSCROLL|WS_HSCROLL|
		ES_MULTILINE/*|ES_WANTRETURN*/|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_READONLY,
			0, 0, 1000, 700, mHwnd, (HMENU)PrintWindID, mInstance, NULL);



	ShowWindow(m_PrintWind,1);
	ShowWindow(mHwnd, 1);
	UpdateWindow(mHwnd);

	addPrintMessage("印魂者状态服务器启动...");
	return true;
}


/**输入信息到窗口*/
void    Application::printMessage()
{
	if(m_PrintWind==NULL)
		return ;

	std::list<std::string>::iterator it=m_LogMessage.begin();
	std::list<std::string>::iterator endit=m_LogMessage.end();

	std::string message;
	message.reserve(10000);

	for(;it!=endit;++it)
	{
		message+=(*it);
		message+="\r\n";

	}

	SetWindowText(m_PrintWind,message.c_str());

}


void    Application::addPrintMessage(const std::string& message)
{

	m_LogMessage.push_back(message);
	if(m_LogMessage.size()>200)
	{
		m_LogMessage.pop_front();
	}

	printMessage();


}


/**连接到帐号服务器*/
bool Application::connectAccountServer(const Config& config)
{

	std::string accountserver;
	std::string password;
	std::string portnumber;

	config.getValue("accountserver",accountserver);
	config.getValue("accountpassword",password);
	config.getValue("accountportnumber",portnumber);

	m_accountServer=accountserver;
	m_accountServerPortnumber=Helper::StringToInt(portnumber);

	if(accountserver.empty()||password.empty()||portnumber.empty())
	{
		MessageBox(NULL,"帐号服务器配置错误","错误",MB_OK);
		xLogMessager::getSingleton().logMessage("帐号服务器配置错误");
		return false;
	}

	bool  ret= m_pNetWork-> connect(accountserver,m_accountServerPortnumber,password);

	if(ret==false)
	{
		std::string error="连接帐号服务器错误"  ;
		xLogMessager::getSingleton().logMessage("连接帐号服务器错误");

	}

	return ret;
}