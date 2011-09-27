
/*******************************************************
游戏服务器类，记录每一个游戏服务器状态。

**********************************************************/



#pragma  once


class GameServer
{
public:

	GameServer(const std::string& name,const std::string& ip,unsigned int portNumber,const std::string& password);

	~GameServer(){}


	/**获取名字*/
	const std::string& getName()const {return m_Name;}



	/**获取ip*/
	const std::string& getIP()const {return m_IP;}


	unsigned int getPortNumber()const {return m_PortNumber;}

	const std::string& getPassWord()const {return m_PassWord;}


	/**记录为联接状态*/
	void setConnect(){m_IsConnect=true;}

	/**记录为断开状态*/
	void disConnect(){m_IsConnect=false;}

	bool hasConnect()const {return m_IsConnect;}

protected:

	std::string                m_Name;//名字
	std::string                m_IP;

	unsigned int               m_PortNumber; ///端口号
	std::string                m_PassWord;   ///密码
	bool                       m_IsConnect;///是否连接



};


typedef std::vector<GameServer*> GameServerCollect;