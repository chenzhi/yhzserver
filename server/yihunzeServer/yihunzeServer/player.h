
/***********************************************
����� 
***************************************************/


class Player
{


	friend class PlayerManager;

public:

	Player();

	~Player();


	///��ȡ����� 
	const std::string& getName()const {return m_Name;}

    ///��ȡ���ID
	unsigned int getID()const {return m_ID;}




protected:





	unsigned int  m_ID;///���id

	std::string   m_Name;///�������


};

typedef std::map<unsigned int,Player*> PlayerIDMap;



