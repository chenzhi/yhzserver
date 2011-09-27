
/*******************************************************
��Ϸ�������࣬��¼ÿһ����Ϸ������״̬��

**********************************************************/



#pragma  once


class GameServer
{
public:

	GameServer(const std::string& name,const std::string& ip,unsigned int portNumber,const std::string& password);

	~GameServer(){}


	/**��ȡ����*/
	const std::string& getName()const {return m_Name;}



	/**��ȡip*/
	const std::string& getIP()const {return m_IP;}


	unsigned int getPortNumber()const {return m_PortNumber;}

	const std::string& getPassWord()const {return m_PassWord;}


	/**��¼Ϊ����״̬*/
	void setConnect(){m_IsConnect=true;}

	/**��¼Ϊ�Ͽ�״̬*/
	void disConnect(){m_IsConnect=false;}

	bool hasConnect()const {return m_IsConnect;}

protected:

	std::string                m_Name;//����
	std::string                m_IP;

	unsigned int               m_PortNumber; ///�˿ں�
	std::string                m_PassWord;   ///����
	bool                       m_IsConnect;///�Ƿ�����



};


typedef std::vector<GameServer*> GameServerCollect;