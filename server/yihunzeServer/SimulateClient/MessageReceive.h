
#pragma  once



class MessageReceive : public Singleton<MessageReceive>
{

public:


	MessageReceive();


	~MessageReceive();


protected:

	///���������Ϣ
	void processAccount(NetPack* pPack);


};