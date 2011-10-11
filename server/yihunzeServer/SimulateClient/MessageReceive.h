
#pragma  once



class MessageReceive : public Singleton<MessageReceive>
{

public:


	MessageReceive();


	~MessageReceive();

	///���º���
	void update();


	bool connectGameServer();


protected:

	///���������Ϣʧ��
	void processAccountFaild(NetPack* pPack);

	///�������ɹ���Ϣ
	void processAccountSucceed(NetPack* pPack);


	///�ɹ�����Զ�̼����
	void processConnectRemoteServer(NetPack* pPack);


	///������Ϸ�߼�������������Ϣ
	void processChatMessage(NetPack* pPack);




protected:

	//RakNet::SystemAddress m_GameServerAdderss;
	std::string           m_GameServerIp;
	unsigned int          m_GameServerPortNumber;
	std::string           m_GameServerPassWord;


	bool                  m_NeedConectGameServer;///�Ƿ���Ҫ���ӵ�gameserver



};