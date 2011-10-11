
#pragma  once



class MessageReceive : public Singleton<MessageReceive>
{

public:


	MessageReceive();


	~MessageReceive();

	///更新函数
	void update();


	bool connectGameServer();


protected:

	///处理登入消息失败
	void processAccountFaild(NetPack* pPack);

	///处理登入成功消息
	void processAccountSucceed(NetPack* pPack);


	///成功连接远程计算机
	void processConnectRemoteServer(NetPack* pPack);


	///处理游戏逻辑服务器聊天消息
	void processChatMessage(NetPack* pPack);




protected:

	//RakNet::SystemAddress m_GameServerAdderss;
	std::string           m_GameServerIp;
	unsigned int          m_GameServerPortNumber;
	std::string           m_GameServerPassWord;


	bool                  m_NeedConectGameServer;///是否需要连接到gameserver



};