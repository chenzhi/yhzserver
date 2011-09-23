
/***********************************
帐号服务器，负责帐号的验证
*****************************************/


#pragma once	



class AccountManager
{
public:

	AccountManager();


	~AccountManager();

protected:


	/**处理帐号验证消息*/
	void processAccountTest(NetPack* pdata);


	/**初始化*/
	void init();


	/**消毁*/
	void destroy();



protected:



};