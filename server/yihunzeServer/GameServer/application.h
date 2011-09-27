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

	/**��ʼ��window*/
	bool    initWindow(int width, int height);

	/**ÿ֡����*/
	void    update(float time);

    void    go();

	/**������Ϣ������
	*@param outlog �Ƿ��������־�ļ���,false �����
	*/
	void    addPrintMessage(const std::string& message,bool outlog = false);



protected:


	/**����״̬������*/
//	bool    connectStateServer(/*const  Config& config*/);

     
	/**�Ͽ�״̬������*/
//	bool    disConnectStateServer();




	/**������Ļ���
	*/
	void    printMessage();


private:
	
private:
	//YihunzeServerMainFrame* mFrame;

    HINSTANCE               mInstance;///���̾�� 
	
	HWND                    mHwnd;///���ھ��

	NetWorkServer*                m_pNetWork;///����ʵ�� 
	

	HWND                    m_PrintWind;           ///��ӡ�Ķ����ļ��� 

	std::list<std::string>  m_LogMessage;

	DatabaseInstace*        m_pDatabaseInstance; ///����ʵ�� 

	netWorkListener*        m_pNetlistener;    ///�����¼�����

	AccountManager*         m_pAccountManager;

	Config                  m_Config;

	StateServer*            m_pStateServer;   ///״̬������

};


