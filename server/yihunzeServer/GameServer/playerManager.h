

/****************************************************
玩家管理类
******************************************************/

#pragma once

#include "Singleton.h"
#include "player.h"





//




class PlayerManager :public Singleton<PlayerManager>
{

public:


	PlayerManager();


	~PlayerManager();


	/**每帧更新函数*/
	void update(float time);


	/**注册网络消息
	*/
	bool registerNetWorkMessage();


	/**注销网络消息
	*/
	bool unregisterNetWorkMessage();



protected:


	/**更新登入用户时间*/
	void updateLoginUser(float time);

	/**判断一个ip地址是否允许登入*/
	bool AllowLogin(std::string& ip);


	/**从数据中读取指定帐号的的所有玩家*/
	bool loadPlayerFromDB(unsigned int account,PlayerVector& playerCollect);




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

	///处理聊天包
	void processChatMessage(NetPack* pPack);


	///处理将会有客户端联接通知
	void processWillClientConnect(NetPack* pPack);


	///处理客户端联接请求
	void processClientConnect(NetPack* pPack);


	///转发数据库服务器发过来的用户玩家数据
	void processDatabasePlayer(NetPack* pPack);




	/**@}*/


protected:


	struct LoginPlayer
	{
		std::string   m_UserIP;
		float         m_time;

		inline bool operator ==(const LoginPlayer& p1)
		{
			return p1.m_UserIP==m_UserIP;
		}
	};
	typedef std::vector<LoginPlayer> LoginPlayerVector;///状态服务器发过来的需要登入的玩家



protected:


	PlayerIDMap     m_PlayerIDCollect;     ///玩家id为key的map

	PlayerNameMap   m_PlayerNameCollect;      ///玩家名字


	LoginPlayerVector  m_LoginUser;           ///将会登入的玩家


};