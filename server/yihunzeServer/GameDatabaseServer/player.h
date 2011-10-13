
/*********************************************************
�����
********************************************************/


#pragma once



class Player
{


		friend class PlayerManager;


public:



	Player(unsigned int id,const std::string& name,unsigned int accountID);


	virtual ~Player();



protected:


	unsigned int           m_ID;   ///���id.Ψһֵ;

	std::string            m_Name	;///�����Ψһֵ

	unsigned               m_AccountID;   ///�ʺ�id;



};


typedef stdext::hash_map<unsigned int,Player*> PlayerIDMap;

typedef stdext::hash_map<std::string,Player*> PlayerNameMap;


typedef std::vector<Player*> PlayerVector;