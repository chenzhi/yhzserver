
/**********************************
连接游戏数据库服务器。游戏需要正关的数据库查询都
需要在这里发送消息组数据库服务器，并处理数据库服务器
回应的消息
*************************************/

#include "Singleton.h"
#include "RemoteServer.h"


class DatabaserServer :public Singleton<DatabaseInstace> ,public RemoteServer
{

public:

	/**构造函数*/
	DatabaserServer(const Config& config);


	virtual ~DatabaserServer();



	/**注册需要响应的数据库网络消息*/
	void registerMessage();

    /**注销网络消息*/
	void unregisterMessage();


	virtual void update(float time);


protected:



	/**@{消息响应函数
	*/

	/**数据库数据发过来的连接成功消息*/
	void processConnectSucceed(NetPack* pPacek);


	/**@}
	*/


protected:



};