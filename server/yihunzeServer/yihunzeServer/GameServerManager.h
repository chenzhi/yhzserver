
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
	bool     addGameServer(const std::string& ip,const std::string& name);


	/**�ж��Ƿ���ָ��ip����Ϸ������*/
	bool      hasGameServer(const std::string& ip);



protected:


	///ע��������Ϣ
	void  registerMessage();

   ///ע��������Ϣ
	void unregisterMessage();



	/**����Ϸ����������*/
	void onGameServerConnect(NetPack* pPacek);


	/**��Ϸ�������뿪*/
	void onGameServerDisConnect(NetPack* pPack);






protected:



	GameServerCollect m_GameServerCollect;




};