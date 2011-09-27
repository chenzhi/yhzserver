
#pragma  once

#include "GameServer.h"



class GameServerManager :public Singleton<GameServerManager>
{

public:

	GameServerManager(const std::string& configFile);



	~GameServerManager();



	/**��ȡ���м�����Ϸ������*/
	unsigned int getGameServerCount();


	/**ͨ��������ȡ��Ϸ������
	*@return ���û�з��ؿ�
	*/
	const GameServer* getGameServerByIndex(unsigned int index);


	/**�Ƴ�ָ��ip����Ϸ����*/
	bool     removeGameServerByIP(const std::string& ip);


	/**����һ�µ���Ϸ������*/
//	bool     addGameServer(const std::string& ip,const std::string& name);


	/**�ж��Ƿ���ָ��ip����Ϸ������*/
	bool      hasGameServer(const std::string& ip);



	/**��ȡ������յ���Ϸ������,
	*@return ���û�ҵ������ؿ�
	*/
    const GameServer*  getBestGameServer()const;
	

	/**����Ϸ����������*/
	void onGameServerConnect(RakNet::Packet* p);


	/**��Ϸ�������뿪*/
	void onGameServerDisConnect(RakNet::Packet* p);




protected:


	///ע��������Ϣ
	void  registerMessage();

   ///ע��������Ϣ
	void unregisterMessage();








protected:



	GameServerCollect m_GameServerCollect;




};