
/*******************************************************
��Ϸ�������࣬��¼ÿһ����Ϸ������״̬��

**********************************************************/



#pragma  once


class GameServer
{
public:

	GameServer(const std::string& name,const std::string& ip);

	~GameServer(){}


	/**��ȡ����*/
	const std::string& getName()const {return m_Name;}



	/**��ȡip*/
	const std::string& getIP()const {return m_IP;}



protected:

	std::string                m_Name;//����
	std::string                m_IP;



};


typedef std::vector<GameServer*> GameServerCollect;