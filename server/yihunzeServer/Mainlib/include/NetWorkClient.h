

/**********************************
����ͻ��ˣ���һ��ʱ�����ֻ������һ��������
***********************************/
#include "network.h"


class XClass NetWorkClient : public Singleton<NetWorkClient>, public NetWork
{

public:


	/**����*/
	NetWorkClient();


    /**����*/
	~NetWorkClient();


	/**���ӵ�ָ���ķ������������Ƿ�������ͻ��˶����Ե��ýӿ�����Զ�̼����
	*@param  ip ���ӶԷ���ip��ַ
	*@param  serverPort �˿ں�
	*@param  password   ��������
	*@return ���ӳɹ������档ʧ�ܷ��ؼ�
	*/
	virtual bool connect(const std::string& ip,unsigned int serverPort,const std::string& password);



	/**�Ƿ����ӳɹ�*/
	bool  hasConnect() const ;


	/**ÿ֡����*/
	virtual  void update();


	/**�Ͽ�����*/
	void  closeConnect();



	/**
	*������Ϣ��������������
	*@param address ���͵ĵ�ַ
	*@param msgType ��Ϣid
	*@param ��������
	*/
	template<typename T>
	bool send( unsigned long msgType , const T & pdata )
	{ 
		if(m_pNetInterface==NULL)
			return false;

		static RakNet::BitStream streem;
		streem.Reset();
		streem.Write( (unsigned char)GM_User);
		streem.Write( msgType );
		streem.WriteBits( (unsigned char *)&pdata , sizeof( T ) * 8 );
		m_pNetInterface->Send( &streem , HIGH_PRIORITY, RELIABLE_ORDERED, 0, m_ServerAddress, false );
		return true;
	}


	/**
	*@see send;
	*/
	void send(unsigned int message,const  char* pData,unsigned int length);




protected:

	std::string         m_ServerIP ;         //Զ�̷�����ip

	unsigned int        m_PortNumber;        ///Զ�̶˿ں�

	std::string         m_PassWord;          //����

	RakNet::SystemAddress m_ServerAddress;   ///Զ�̵�ַ





};