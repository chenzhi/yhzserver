#pragma  once

#include "Singleton.h"

class NetWork;
class PlayerManager;

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

	NetWork*                m_pNetWork;///����ʵ�� 
	
	PlayerManager*          m_pPlayerManager; ////�û�������

	HWND                    m_PrintWind;           ///��ӡ�Ķ����ļ��� 

	std::list<std::string>  m_LogMessage;

};


