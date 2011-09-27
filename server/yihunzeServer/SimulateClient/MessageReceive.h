
#pragma  once



class MessageReceive : public Singleton<MessageReceive>
{

public:


	MessageReceive();


	~MessageReceive();


protected:

	///���������Ϣʧ��
	void processAccountFaild(NetPack* pPack);

	///�������ɹ���Ϣ
	void processAccountSucceed(NetPack* pPack);


	///�ɹ�����Զ�̼����
	void processConnectRemoteServer(NetPack* pPack);




protected:

	RakNet::SystemAddress m_GameServerAdderss;
	std::string           m_GameServerPassWord;


};