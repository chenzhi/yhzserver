
#pragma  once

#include "netWork.h"



typedef std::vector<RakNet::SystemAddress> AddressVector;

class  ServerListener :public netWorkListener
{

public:
	
	ServerListener(){};


	/**当一个玩家进入*/
	virtual void  onConnect(RakNet::Packet* p);

	/**玩家离开*/
	virtual void  onDisconnect(RakNet::Packet* p);

	/**玩家掉线*/
	virtual void  onConnectlost(RakNet::Packet* p);

	
    /**获取连接机器的数量*/
	size_t        getServerCount()const {return m_AddressVector.size();}


	/**是否连接了指定的机器*/
	bool          hasContectServer(const RakNet::SystemAddress& address);


	/**更新服务器列表*/
	void           updateServerList();


protected:

	AddressVector m_AddressVector;

};
