
#pragma  once



class MessageReceive : public Singleton<MessageReceive>
{

public:


	MessageReceive();


	~MessageReceive();


protected:

	///处理登入消息失败
	void processAccountFaild(NetPack* pPack);

	///处理登入成功消息
	void processAccountSucceed(NetPack* pPack);


	///成功连接远程计算机
	void processConnectRemoteServer(NetPack* pPack);




protected:

	RakNet::SystemAddress m_GameServerAdderss;
	std::string           m_GameServerPassWord;


};