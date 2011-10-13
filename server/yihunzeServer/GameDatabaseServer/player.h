
/*********************************************************
玩家类
********************************************************/


#pragma once



class Player
{


		friend class PlayerManager;


public:



	Player(unsigned int id,const std::string& name,unsigned int accountID);


	virtual ~Player();



protected:


	unsigned int           m_ID;   ///玩家id.唯一值;

	std::string            m_Name	;///玩家名唯一值

	unsigned               m_AccountID;   ///帐号id;



};


typedef stdext::hash_map<unsigned int,Player*> PlayerIDMap;

typedef stdext::hash_map<std::string,Player*> PlayerNameMap;


typedef std::vector<Player*> PlayerVector;