#pragma  once

#include "Singleton.h"

class NetWorkServer;
class DatabaseInstace;
class AccountManager;


class Application  :public Singleton<Application>
{
public:
	Application();


	virtual ~Application();

	bool	init();

	/**初始化window*/
	bool    initWindow(int width, int height);

	/**每帧更新*/
	void    update(float time);

    void    go();

	/**输入信息到窗口*/
	void    addPrintMessage(const std::string& message);



protected:



	/**更新屏幕输出*/
	void    printMessage();


private:
	
private:
	//YihunzeServerMainFrame* mFrame;

    HINSTANCE               mInstance;///进程句柄 
	
	HWND                    mHwnd;///窗口句柄

	NetWorkServer*                m_pNetWork;///网络实例 
	

	HWND                    m_PrintWind;           ///打印的多行文件框 

	std::list<std::string>  m_LogMessage;

	DatabaseInstace*        m_pDatabaseInstance; ///数据实例 

	netWorkListener*        m_pNetlistener;    ///网络事件监听

	AccountManager*         m_pAccountManager;

};


