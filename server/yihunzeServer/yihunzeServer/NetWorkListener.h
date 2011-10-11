
#pragma  once

#include "netWork.h"



typedef std::vector<RakNet::SystemAddress> AddressVector;

class  ServerListener :public netWorkListener
{

public:
	
	ServerListener(){};


	/**��һ����ҽ���*/
	virtual void  onConnect(RakNet::Packet* p);

	/**����뿪*/
	virtual void  onDisconnect(RakNet::Packet* p);

	/**��ҵ���*/
	virtual void  onConnectlost(RakNet::Packet* p);

	
    /**��ȡ���ӻ���������*/
	size_t        getServerCount()const {return m_AddressVector.size();}


	/**�Ƿ�������ָ���Ļ���*/
	bool          hasContectServer(const RakNet::SystemAddress& address);


	/**���·������б�*/
	void           updateServerList();


protected:

	AddressVector m_AddressVector;

};
