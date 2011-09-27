#include "pch.h"
#include "vld.h"
#include "application.h"
#include "netWork.h"
#include "NetWorkListener.h"
#include "xLogManager.h"
#include "databaseInstance.h"
#include  "helper.h"
#include "accountManager.h"

#define PrintWindID   99999


INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
{



    Application* g_pApp=NULL;

	try
	{

		g_pApp= new  Application();
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
		// TODO: �ڴ���������ͼ����...
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
Application::Application()
:mInstance(NULL),mHwnd(NULL),m_pNetWork(NULL),m_PrintWind(NULL),
m_pDatabaseInstance(NULL),m_pNetlistener(NULL),m_pAccountManager(NULL)
{

  Helper::setCurrentWorkPath();

}


//-----------------------------------------------------------------
Application:: ~Application()
{
	if(mHwnd!=NULL)
	{
		DestroyWindow(mHwnd);
		mHwnd=NULL;
	}
	
    SafeDelete(m_pAccountManager);
	SafeDelete(m_pNetWork);
	SafeDelete(m_pNetlistener);
    SafeDelete(m_pDatabaseInstance);


	xLogMessager::getSingleton().logMessage("�ʺŷ������˳�...");
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
			// ������˳���Ϣ,�˳�
			if(msg.message == WM_QUIT) 
				return;

			// ����������Ϣ
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




	new xLogMessager("accountserver.log");

	xLogMessager::getSingleton().logMessage("�ʺŷ���������...");
	addPrintMessage("�ʺŷ���������...");




	Config config;
	if(config.loadfile("accountserver.cfg")==false)
	{
		::MessageBox(NULL,"��ȡ accountserver.cfg �����ļ�����δ�ҵ��ļ�","���� ",MB_OK);
		xLogMessager::getSingleton().logMessage("��ȡ accountserver.cfg �����ļ�����δ�ҵ��ļ�");
		return false;
	}



	std::string portNumber;
	std::string networkpassword;
	unsigned    iport=0;
	if(config.getValue("networkportnumber",portNumber))
	{
		iport=Helper::StringToInt(portNumber);

	}else
	{
		::MessageBox(NULL,"��ȡ accountserver.cfg �ļ�����,δ�ҵ��˿ں�����","���� ",MB_OK);
		xLogMessager::getSingleton().logMessage("��ȡ accountserver.cfg �ļ�����,δ�ҵ��˿ں�����");
		return false;
	}

	config.getValue("networkpassword",networkpassword);

	
	m_pNetWork=new NetWork();
	if(m_pNetWork->startServer(iport,networkpassword)==false)
	{
		::MessageBox(NULL,"��ʼ������������������ļ��Ƿ���ȷ","����",MB_OK);
		SafeDelete(m_pNetWork);
		return false;
	}
	m_pNetlistener=new ServerListener();
	m_pNetWork->setListener(m_pNetlistener);



	


	///���ݿ�����
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

		std::string error="��ȡ accountserver.cfg �ļ��������ݿ����ô��� ";
		::MessageBox(NULL,error.c_str(),"���� ",MB_OK);
		xLogMessager::getSingleton().logMessage(error);
		return false;

	}

	iport=Helper::StringToInt(DataPortNumber);
	m_pDatabaseInstance=new DatabaseInstace();
	if(	m_pDatabaseInstance->open(DataServer.c_str(),DataUser.c_str(),DataPassWord.c_str(),DataName.c_str(),iport)==false)
	{
		Application::getSingleton().addPrintMessage("�����ݿ�ɹ�");
		xLogMessager::getSingleton().logMessage("�����ݿ�ɹ�...");
        return false;
	}else
	{
		Application::getSingleton().addPrintMessage("�����ݿ�ɹ�");
		xLogMessager::getSingleton().logMessage("�����ݿ�ɹ�...");
	}



	//CppMySQLQuery* pQuery=NULL;
	//if(m_pDatabaseInstance->querySQL("select * from account",&pQuery))
	//{
	//	while(pQuery->eof()==false)
	//	{
	//		std::string username=pQuery->getStringField("name","");
 //           username=username;
	//		pQuery->nextRow();

	//	}
	//}





	m_pAccountManager=new AccountManager();


	return true;
}

//-----------------------------------------------------------------
bool Application::initWindow(int width, int height)
{

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= mInstance;
	wcex.hIcon			= 0;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= 0;
	wcex.lpszClassName	= "mainwindow";
	wcex.hIconSm		= 0;

	RegisterClassEx(&wcex);

	mHwnd = CreateWindow("mainwindow", "�ʺŷ�����", WS_OVERLAPPEDWINDOW,
		100, 100, 1024, 768, NULL, NULL, mInstance, NULL);

	if (!mHwnd)
	{
		return FALSE;
	}


	///����һ��������Ϣ��
	m_PrintWind=CreateWindow( "edit", "",
		WS_VISIBLE|WS_CHILD|WS_BORDER|WS_VSCROLL|WS_HSCROLL|
		ES_MULTILINE|ES_WANTRETURN|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_READONLY,
		0, 0, 1000, 700, mHwnd, (HMENU)PrintWindID, mInstance, NULL);





	 ShowWindow(m_PrintWind,1);



	ShowWindow(mHwnd, 1);
	UpdateWindow(mHwnd);
	return true;
}


/**������Ϣ������*/
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

