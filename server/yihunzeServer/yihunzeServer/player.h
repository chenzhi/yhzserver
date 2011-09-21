
/***********************************************
玩家类 
***************************************************/


class Player
{


	friend class PlayerManager;

public:

	Player();

	~Player();


	///获取玩家名 
	const std::string& getName()const {return m_Name;}

    ///玩取玩家ID
	unsigned int getID()const {return m_ID;}




protected:





	unsigned int  m_ID;///玩家id

	std::string   m_Name;///玩家名字


};

typedef std::map<unsigned int,Player*> PlayerIDMap;



