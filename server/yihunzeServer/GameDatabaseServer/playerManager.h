

/****************************************************
��ҹ�����
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



	/**ע��������Ϣ
	*/
	bool registerNetWorkMessage();


	/**ע��������Ϣ
	*/
	bool unregisterNetWorkMessage();



protected:


	/**�������ж�ȡָ���ʺŵĵ��������*/
	bool loadPlayerFromDB(unsigned int account,TagPlayerVector& playerCollect);




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

	/**�����ʺ��ж��ٸ����*/
	void processRequestPlayer(NetPack* pPack);



	/**@}*/



protected:





protected:


	PlayerIDMap     m_PlayerIDCollect;     ///���idΪkey��map

	PlayerNameMap   m_PlayerNameCollect;      ///�������


};