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

	/**��ʼ��window*/
	bool    initWindow(int width, int height);

	/**ÿ֡����*/
	void    update(float time);

    void    go();

	/**������Ϣ������*/
	void    addPrintMessage(const std::string& message);



protected:



	/**������Ļ���*/
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

};


