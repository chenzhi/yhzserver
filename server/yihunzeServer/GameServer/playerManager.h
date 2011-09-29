

/****************************************************
��ҹ�����
******************************************************/

#pragma once

#include "Singleton.h"
#include "player.h"


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



	/**�����ݿ��д���һ�����
	*@param name �������
	*/
	bool loadPlayerFromDB(const std::string& name);


	/**
	*@param id ͨ��id��ȡ��ҡ�
	*@return ���û���ҵ����ؿ�
	*/
	Player* getPlayerByID(unsigned int id)const;




	/**����һ�������
	*@param name ����ҵ�����
	*@return  �����������Ѿ����˾Ͳ����ٴ����᷵�ؿ�
	*/
	Player*  createPlayer(const std::string& name);




protected:
	/**@{��Ϣ������
	*/


	/**@}*/




protected:


	PlayerIDMap     m_PlayerIDCollect;     ///���idΪkey��map


};