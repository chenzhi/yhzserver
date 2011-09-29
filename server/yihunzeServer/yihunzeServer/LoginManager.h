

/***************************************
管理用户的登入，
******************************************/


#pragma  once



class LoginManager :public Singleton<LoginManager>
{

public:

	LoginManager();


	~LoginManager();


	/**注测网络消息*/
	void registerMessage();


	/**注销网络消息*/
	void unregisterMessage();


protected:

	/**@{网络消息响应函数
	*/



	/**处理客户帐号服务器消息验证*/
	void processAccountRequest(NetPack* pdata);


	/**处理帐号服务器发过来的验证结果消息*/
	void processAccountRespond(NetPack* pdata);
	






	/**@}
	*/




protected:

};