
/********************************************
������״̬������������
***********************************************/


#pragma  once
#include "RemoteServer.h"



class StateServer :public RemoteServer
{

public:

	/**
	*@param gameserverName ��Ϸ����������
	*@param stateserver ip ״̬������ip��ַ
	*@param portnumber ״̬�������˿ں�
	*@param password  ״̬����������
	*/
	StateServer(const std::string& gameserverName,const std::string& stateserverip,unsigned int portnumber,const std::string& password);



	/**���캯��*/
	StateServer(const Config& config);


	~StateServer();


	

	/**ÿ֡���£��������һЩ��Ϣ����״̬������*/
	virtual void  update(float time);



protected:

	/**���͵�ǰ��Ϣ״̬������*/
	void  setInformationToStateServer();


protected:

	std::string             m_GameServerName;///��ǰ��Ϸ������������


	float                   m_CurrentTime;     ///����һ�η���Ϣ��ʱ��



};