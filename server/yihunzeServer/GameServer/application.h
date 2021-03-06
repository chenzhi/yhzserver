#pragma  once

#include "Singleton.h"

class NetWorkServer;
class DatabaseInstace;
class AccountManager;
class StateServer;
class DatabaserServer;
class PlayerManager;


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


	///
	void    initStatServer(const Config& config);

  
	void    initGameDataServer(const Config& config);


	/**获取状态服务器地址*/
	const RakNet::SystemAddress& getStatServerAddress()const {return m_StatServerAddress;}

	/**获取数据库服务器地址*/
	const RakNet::SystemAddress& getDatabaseServerAddress()const {return m_DatabaserAdderss;}


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

	//DatabaseInstace*        m_pDatabaseInstance; ///数据实例 

	netWorkListener*        m_pNetlistener;    ///网络事件监听

	//AccountManager*         m_pAccountManager;

	Config                  m_Config;

	RakNet::SystemAddress   m_StatServerAddress;   //状态服务器ip

	RakNet::SystemAddress   m_DatabaserAdderss;  ///数据库服务器

	PlayerManager*          m_pPlayerManger;

};


