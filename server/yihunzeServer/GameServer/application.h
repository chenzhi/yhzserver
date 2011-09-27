#pragma  once

#include "Singleton.h"

class NetWorkServer;
class DatabaseInstace;
class AccountManager;
class StateServer;


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

	/**输入信息到窗口
	*@param outlog 是否输出到日志文件中,false 不输出
	*/
	void    addPrintMessage(const std::string& message,bool outlog = false);



protected:


	/**连接状态服务器*/
//	bool    connectStateServer(/*const  Config& config*/);

     
	/**断开状态服务器*/
//	bool    disConnectStateServer();




	/**更新屏幕输出
	*/
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

	Config                  m_Config;

	StateServer*            m_pStateServer;   ///状态服务器

};


