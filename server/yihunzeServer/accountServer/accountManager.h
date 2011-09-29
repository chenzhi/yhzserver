
/***********************************
帐号服务器，负责帐号的验证
*****************************************/


#pragma once	



class AccountManager
{
public:

	AccountManager();


	~AccountManager();


	/**创建一个用户
	*@param 帐户名
	*@param password 密码
	*@return 创建成功返回真，失败返回假，如果已有了帐号不能再创建
	*/
	bool createAccount(const std::string& accountName,const std::string& password);



	/**判断帐号密码是否正确
	*@param accountid 如果验证通过，返回帐号id,
	*@return 如果有些帐号密码返回真，无返回false
	*/
	bool checkAccount(const std::string& accountName,const std::string& password, int&accountid);




protected:


	/**处理帐号验证消息*/
	void processAccountTest(NetPack* pdata);


	/**初始化*/
	void init();


	/**消毁*/
	void destroy();






protected:



};