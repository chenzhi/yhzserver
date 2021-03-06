#pragma  once

#include "Singleton.h"

class NetWorkServer;
class LoginManager;
class DatabaseInstace;
class GameServerManager;


class Application  :public Singleton<Application>
{
public:
	Application( HINSTANCE  Instance);


	virtual ~Application();

	bool	init();

	/**初始化window*/
	bool    initWindow(int width, int height);

	/**每帧更新*/
	void    update(float time);

    void    go();

	/**输入信息到窗口*/
	void    addPrintMessage(const std::string& message);



	/**获取到帐号服务器地址*/
	const std::string&  getAccountServer()const{return m_accountServer;}

	/**获取帐号服务器端口号*/
	unsigned int   getAccountServerPort()const {return m_accountServerPortnumber;}


	/**获取游戏服务器端口号*/
	unsigned int   getGameserverPort()const {return m_gameServerPortnumber;}





protected:

	/**更新屏幕输出*/
	void    printMessage();

	/**连接到帐号服务器*/
	bool connectAccountServer(const Config& config);



private:
	
private:
	//YihunzeServerMainFrame* mFrame;

    HINSTANCE               mInstance;///进程句柄 
	
	HWND                    mHwnd;///窗口句柄

	NetWorkServer*                m_pNetWork;///网络实例 
	
	LoginManager*          m_pLoginManager; ////登入管理器

	HWND                    m_PrintWind;           ///打印的多行文件框 

	std::list<std::string>  m_LogMessage;


	netWorkListener*        m_pNetlistener;    ///网络事件监听

	std::string             m_accountServer;    ///帐号服务器ip

	unsigned int            m_accountServerPortnumber;//帐号服务器端口号

	unsigned int            m_gameServerPortnumber;  //游戏服务器端口号


	GameServerManager*      m_GameSreverManager;      //游戏服务器管理器

};


