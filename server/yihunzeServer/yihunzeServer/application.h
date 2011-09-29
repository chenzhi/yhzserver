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

	/**��ʼ��window*/
	bool    initWindow(int width, int height);

	/**ÿ֡����*/
	void    update(float time);

    void    go();

	/**������Ϣ������*/
	void    addPrintMessage(const std::string& message);



	/**��ȡ���ʺŷ�������ַ*/
	const std::string&  getAccountServer()const{return m_accountServer;}

	/**��ȡ�ʺŷ������˿ں�*/
	unsigned int   getAccountServerPort()const {return m_accountServerPortnumber;}


	/**��ȡ��Ϸ�������˿ں�*/
	unsigned int   getGameserverPort()const {return m_gameServerPortnumber;}





protected:

	/**������Ļ���*/
	void    printMessage();

	/**���ӵ��ʺŷ�����*/
	bool connectAccountServer(const Config& config);



private:
	
private:
	//YihunzeServerMainFrame* mFrame;

    HINSTANCE               mInstance;///���̾�� 
	
	HWND                    mHwnd;///���ھ��

	NetWorkServer*                m_pNetWork;///����ʵ�� 
	
	LoginManager*          m_pLoginManager; ////���������

	HWND                    m_PrintWind;           ///��ӡ�Ķ����ļ��� 

	std::list<std::string>  m_LogMessage;


	netWorkListener*        m_pNetlistener;    ///�����¼�����

	std::string             m_accountServer;    ///�ʺŷ�����ip

	unsigned int            m_accountServerPortnumber;//�ʺŷ������˿ں�

	unsigned int            m_gameServerPortnumber;  //��Ϸ�������˿ں�


	GameServerManager*      m_GameSreverManager;      //��Ϸ������������

};


