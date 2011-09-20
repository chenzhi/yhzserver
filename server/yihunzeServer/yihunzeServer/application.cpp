#include "pch.h"
#include "application.h"
#include "netWork.h"
#include "playerManager.h"



#define PrintWindID   99999


INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
{


	char pBuffer[1024];
	ZeroMemory(pBuffer, 1024);
	GetModuleFileName(NULL, pBuffer, 1024);

	std::string	 dirname;
	std::string cc=pBuffer;
	std::string::size_type pos =cc.find_last_of("\\");
	dirname = cc.substr(0,pos);
	SetCurrentDirectory(dirname.c_str());
/////

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
Application::Application()
:mInstance(NULL),mHwnd(NULL),m_pNetWork(NULL),m_pPlayerManager(NULL),m_PrintWind(NULL)
{



}


//-----------------------------------------------------------------
Application:: ~Application()
{

	
	SafeDelete(m_pPlayerManager);
	SafeDelete(m_pNetWork);


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
				return;

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

	
	m_pNetWork=new NetWork();
	if(m_pNetWork->initFromFile("networker.cfg")==false)
	{
		::MessageBox(NULL,"初始化网络错误，请检查配置文件是否正确","错误",MB_OK);
		SafeDelete(m_pNetWork);
		return false;
	}


	m_pPlayerManager=new PlayerManager();



	return initWindow(800,600);
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

	mHwnd = CreateWindow("mainwindow", "印魂者服务器", WS_OVERLAPPEDWINDOW,
		100, 100, 1024, 768, NULL, NULL, mInstance, NULL);

	if (!mHwnd)
	{
		return FALSE;
	}


	///创建一个多行消息框
	m_PrintWind=CreateWindow( "edit", "",
		WS_VISIBLE|WS_CHILD|WS_BORDER|WS_VSCROLL|WS_HSCROLL|
		ES_MULTILINE|ES_WANTRETURN|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_READONLY,
		0, 0, 1000, 700, mHwnd, (HMENU)PrintWindID, mInstance, NULL);





	 ShowWindow(m_PrintWind,1);



	ShowWindow(mHwnd, 1);
	UpdateWindow(mHwnd);
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