
/********************************************
管理与状态服务器的连接
***********************************************/


#pragma  once
#include "RemoteServer.h"



class StateServer :public RemoteServer
{

public:

	/**
	*@param gameserverName 游戏服务器名字
	*@param stateserver ip 状态服务器ip地址
	*@param portnumber 状态服务器端口号
	*@param password  状态服务器密码
	*/
	StateServer(const std::string& gameserverName,const std::string& stateserverip,unsigned int portnumber,const std::string& password);



	/**构造函数*/
	StateServer(const Config& config);


	~StateServer();


	

	/**每帧更新，发自身的一些信息发给状态服务器*/
	virtual void  update(float time);



protected:

	/**发送当前信息状态服务器*/
	void  setInformationToStateServer();


protected:

	std::string             m_GameServerName;///当前游戏服务器的名字


	float                   m_CurrentTime;     ///距上一次发消息的时间



};