

/****************************************************
玩家管理类
******************************************************/

#pragma once

#include "Singleton.h"
#include "player.h"


class PlayerManager :public Singleton<PlayerManager>
{

public:


	PlayerManager();


	~PlayerManager();



	/**注册网络消息
	*/
	bool registerNetWorkMessage();


	/**注销网络消息
	*/
	bool unregisterNetWorkMessage();



	/**从数据库中创建一个玩家
	*@param name 玩家名字
	*/
	bool loadPlayerFromDB(const std::string& name);


	/**
	*@param id 通过id获取玩家。
	*@return 如果没有找到近回空
	*/
	Player* getPlayerByID(unsigned int id)const;




	/**创建一个新玩家
	*@param name 新玩家的名字
	*@return  如果这个名字已经有了就不能再创建会返回空
	*/
	Player*  createPlayer(const std::string& name);




protected:
	/**@{消息处理函数
	*/


	/**@}*/




protected:


	PlayerIDMap     m_PlayerIDCollect;     ///玩家id为key的map


};