

/****************************************************
玩家管理类
******************************************************/

#pragma once

#include "Singleton.h"
#include "player.h"



typedef std::vector<Tag_Player>TagPlayerVector;

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



protected:


	/**从数据中读取指定帐号的的所有玩家*/
	bool loadPlayerFromDB(unsigned int account,TagPlayerVector& playerCollect);




	/**从数据库中创建一个玩家
	*@param name 玩家名字
	*/
	bool loadPlayerFromDB(const std::string& name);


	/**
	*@param id 通过id获取玩家。
	*@return 如果没有找到近回空
	*/
	Player* getPlayerByID(unsigned int id)const;


	/**根据玩家名找到玩家，如果没有返回空*/
	Player* getPlayerByName(const std::string& name) const ;




	/**创建一个新玩家
	*@param name 新玩家的名字
	*@return  如果这个名字已经有了就不能再创建会返回空
	*/
	Player*  createPlayer(const std::string& name);




protected:
	/**@{消息处理函数
	*/

	/**请求帐号有多少个玩家*/
	void processRequestPlayer(NetPack* pPack);



	/**@}*/



protected:





protected:


	PlayerIDMap     m_PlayerIDCollect;     ///玩家id为key的map

	PlayerNameMap   m_PlayerNameCollect;      ///玩家名字


};