
/********************************************
������״̬������������
***********************************************/


#pragma  once



class StateServer
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


	/**����״̬������
	*@return �ɹ�������
	*/
	bool  connect();


	/**�Ͽ�״̬����������*/
	void  disConnect();


	/**ÿ֡���£��������һЩ��Ϣ����״̬������*/
	void  update(float time);



protected:

	/**���͵�ǰ��Ϣ״̬������*/
	void  setInformationToStateServer();


protected:

	std::string             m_GameServerName;///��ǰ��Ϸ������������
	
	std::string             m_StateServerIP; ///״̬��������ip

	std::string             m_StatePassWord;///״̬��������

	unsigned int            m_StateServerPort;///״̬�������˿ں�


	bool                    m_IsConnect;       ///�Ƿ����ӵ���״̬������


	float                    m_CurrentTime;     ///����һ�η���Ϣ��ʱ��



};