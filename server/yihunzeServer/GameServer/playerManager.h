

/****************************************************
��ҹ�����
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


	/**ÿ֡���º���*/
	void update(float time);


	/**ע��������Ϣ
	*/
	bool registerNetWorkMessage();


	/**ע��������Ϣ
	*/
	bool unregisterNetWorkMessage();



protected:


	/**���µ����û�ʱ��*/
	void updateLoginUser(float time);

	/**�ж�һ��ip��ַ�Ƿ��������*/
	bool AllowLogin(std::string& ip);


	/**�������ж�ȡָ���ʺŵĵ��������*/
	bool loadPlayerFromDB(unsigned int account,PlayerVector& playerCollect);




	/**�����ݿ��д���һ�����
	*@param name �������
	*/
	bool loadPlayerFromDB(const std::string& name);


	/**
	*@param id ͨ��id��ȡ��ҡ�
	*@return ���û���ҵ����ؿ�
	*/
	Player* getPlayerByID(unsigned int id)const;


	/**����������ҵ���ң����û�з��ؿ�*/
	Player* getPlayerByName(const std::string& name) const ;




	/**����һ�������
	*@param name ����ҵ�����
	*@return  �����������Ѿ����˾Ͳ����ٴ����᷵�ؿ�
	*/
	Player*  createPlayer(const std::string& name);




protected:
	/**@{��Ϣ������
	*/

	///���������
	void processChatMessage(NetPack* pPack);


	///�������пͻ�������֪ͨ
	void processWillClientConnect(NetPack* pPack);


	///����ͻ�����������
	void processClientConnect(NetPack* pPack);


	///ת�����ݿ���������������û��������
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
	typedef std::vector<LoginPlayer> LoginPlayerVector;///״̬����������������Ҫ��������



protected:


	PlayerIDMap     m_PlayerIDCollect;     ///���idΪkey��map

	PlayerNameMap   m_PlayerNameCollect;      ///�������


	LoginPlayerVector  m_LoginUser;           ///�����������


};