
/*******************************************************
游戏服务器类，记录每一个游戏服务器状态。

**********************************************************/



#pragma  once


class GameServer
{
public:

	GameServer(const std::string& name,const std::string& ip);

	~GameServer(){}


	/**获取名字*/
	const std::string& getName()const {return m_Name;}



	/**获取ip*/
	const std::string& getIP()const {return m_IP;}



protected:

	std::string                m_Name;//名字
	std::string                m_IP;



};


typedef std::vector<GameServer*> GameServerCollect;