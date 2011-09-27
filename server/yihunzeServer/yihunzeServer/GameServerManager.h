
#pragma  once

#include "GameServer.h"



class GameServerManager :public Singleton<GameServerManager>
{

public:

	GameServerManager(const std::string& configFile);



	~GameServerManager();



	/**获取共有几个游戏服务器*/
	unsigned int getGameServerCount();


	/**通过索引获取游戏服务器
	*@return 如果没有返回空
	*/
	const GameServer* getGameServerByIndex(unsigned int index);


	/**移除指定ip的游戏务器*/
	bool     removeGameServerByIP(const std::string& ip);


	/**加入一新的游戏服务器*/
//	bool     addGameServer(const std::string& ip,const std::string& name);


	/**判断是否有指定ip的游戏服务器*/
	bool      hasGameServer(const std::string& ip);



	/**获取现在最空的游戏服务器,
	*@return 如果没找到，返回空
	*/
    const GameServer*  getBestGameServer()const;
	

	/**有游戏服务器进入*/
	void onGameServerConnect(RakNet::Packet* p);


	/**游戏服务器离开*/
	void onGameServerDisConnect(RakNet::Packet* p);




protected:


	///注册网络消息
	void  registerMessage();

   ///注销网络消息
	void unregisterMessage();








protected:



	GameServerCollect m_GameServerCollect;




};