#pragma  once

#include "Singleton.h"

class NetWork;
class PlayerManager;
class DatabaseInstace;


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



	/**��ȡ���ʺŷ�������ַ*/
	const std::string&  getAccountServer()const{return m_accountServer;}

	/**��ȡ�ʺŷ������˿ں�*/
	unsigned int   getAccountServerPort()const {return m_accountServerPortnumber;}



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

	NetWork*                m_pNetWork;///����ʵ�� 
	
	PlayerManager*          m_pPlayerManager; ////�û�������

	HWND                    m_PrintWind;           ///��ӡ�Ķ����ļ��� 

	std::list<std::string>  m_LogMessage;

	DatabaseInstace*        m_pDatabaseInstance; ///����ʵ�� 

	netWorkListener*        m_pNetlistener;    ///�����¼�����

	std::string             m_accountServer;    ///�ʺŷ�����ip

	unsigned int            m_accountServerPortnumber;//�ʺŷ������˿ں�

};


