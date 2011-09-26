
#pragma  once



class MessageReceive : public Singleton<MessageReceive>
{

public:


	MessageReceive();


	~MessageReceive();


protected:

	///处理登入消息
	void processAccount(NetPack* pPack);


};