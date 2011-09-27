#pragma  once

#include "Singleton.h"
#include "EventManager.h"
//#include "usermessage.h"
//#include "userstruct.h"




#ifdef _DEBUG
#define  NetWorkTimeOut         30000
#define  NetWorkMaxClientNumber 1000

#else

#define  NetWorkMaxClientNumber 65535
#define  NetWorkTimeOut         3000

#endif




#define  GM_User          ID_USER_PACKET_ENUM
//#define  GM_ACCEPTCOME    GM_User+1








/**
�����¼������ߣ���ص������¼���
*/
class XClass netWorkListener
{
public:


	netWorkListener(){}

	virtual ~netWorkListener(){};

 //    /**��һ����ҽ���*/
	virtual void onConnect(RakNet::Packet* p)=0;

	///**����뿪*/
	virtual void onDisconnect(RakNet::Packet* p)=0;

	///**��ҵ���*/
	virtual void  onConnectlost(RakNet::Packet* p)=0;

	    /**��һ����ҽ���*/


};



/**��������ݣ�
*/
class XClass NetPack
{
	friend class NetWork;

protected:

	NetPack(RakNet::Packet* p)
		:m_pPack(p),m_pData(NULL),m_length(2048)
	{

		m_pData = (char*)malloc(m_length);
	}

	~NetPack()
	{
        free(m_pData);
		m_pData=NULL;

	}

public:

	/**��ȡ���������,
	*@reutrn ���û�����ݷ��ؿ�
	*/
	void * getData()  
	{
		if(m_pPack==NULL)
			return NULL;

		if(m_pPack->length>=m_length)
		{
			free(m_pData);

			m_length=m_pPack->length+1;

			m_pData=(char*)malloc(m_length);
		}

		memset(m_pData,0,m_length);
		memcpy(m_pData,m_pPack->data,m_pPack->length);

		return m_pData+sizeof(DWORD) + sizeof(byte);

	}


	/**��ȡ���ķ��͵ĵ�ip��ַ
	*@pram portnumber �Ƿ�����˿ں�
	*/
	/*const char* getSendIP(bool portnumber=false)
	{
		if(m_pPack==NULL)
			return NULL;
		return m_pPack->systemAddress.ToString(portnumber);
	}*/



	RakNet::RakNetGUID getSendGUID()const
	{
		assert(m_pPack);
		return m_pPack->guid;

	}


	/**���ذ��е���Ϸ��Ϣid*/
	unsigned int getGameMessageID()
	{
		if(m_pPack==NULL)
			return -1;///���������

		RakNet::BitStream bitStream( m_pPack->data , m_pPack->length ,false );
		bitStream.IgnoreBytes(sizeof(unsigned char));
		unsigned long t = 0;
		bitStream.Read( t );
		return t;
	}

	const RakNet::SystemAddress& getAddress()const
	{
		assert(m_pPack);
		return  m_pPack->systemAddress;
	}
	

	RakNet::Packet* getRakNetPack()const {return m_pPack; }



protected:
	void setRaknetPack(RakNet::Packet* p)
	{
		m_pPack;
	}



	
protected:

	RakNet::Packet* m_pPack;

	char*           m_pData;
	unsigned int    m_length;


};




class  XClass NetWork :public Singleton<NetWork>, public CEventManager
{

public:

	/**���캯��
	*@param isClient �ǿͻ��˻��Ƿ�������,trueΪ�ͻ���
	*/
	NetWork(bool isClient,unsigned int ClientPort);


	NetWork();


	~NetWork();


	/**���캯�����������ļ����ȡ����
    *@param configFile �����ļ�
    *@return �ɹ�������ʧ�ܷ��ؼ�
	*/
	bool initFromFile(const std::string& configFile);


	/**������Ϊ��������ʼ��������
	*@param portNumber �˿ں�
	*@return �ɹ������棬ʧ�ܷ��ؼ�
	*/
	bool startServer(unsigned int portNumber,const std::string& password);





	/**��ʼһ���ͻ���*/





	/**���ӵ�ָ���ķ������������Ƿ�������ͻ��˶����Ե��ýӿ�����Զ�̼����
	*@param  ip ���ӶԷ���ip��ַ
	*@param  serverPort �˿ں�
	*@param  password   ��������
	*@return ���ӳɹ������档ʧ�ܷ��ؼ�
	*/
	bool conect(const std::string& ip,unsigned int serverPort,const std::string& password);


	/**�ر�����*/
	//void close(const RakNet::SystemAddress& paddress);

	/**�ر�����
	*@param portnumber �˿ں�
	*/
	void close(const char* pAddress,short unsigned int portnumber);


	void close(const  RakNet::SystemAddress& address);




	/**���ü�����*/
	void setListener(netWorkListener* pListener);


	/**ÿ֡����*/
    void update();



	/**��������,����Ϣ����ָ�����û�
	*@param message ��Ϣid
	*@param pdata ��Ϣ����
	*@param length ��Ϣ���ݵĳ���
	*@param receiver�����ߵ�id��
	*/
	void send(unsigned int message,const  char* pData,unsigned int length,RakNet::RakNetGUID receiver);


	/**
	*@see send;
	*/
	void send(unsigned int message,const  char* pData,unsigned int length,RakNet::SystemAddress& receiver);


	/**
	*������Ϣ��������������
	*@param address ���͵ĵ�ַ
	*@param msgType ��Ϣid
	*@param ��������
	*/
	template<typename T>
	bool send( unsigned long msgType , const T & pdata,const  RakNet::SystemAddress& address )
	{ 
		if(m_pNetInterface==NULL)
			return false;

		static RakNet::BitStream streem;
		streem.Reset();
		streem.Write( (unsigned char)GM_User);
		streem.Write( msgType );
		streem.WriteBits( (unsigned char *)&pdata , sizeof( T ) * 8 );
		m_pNetInterface->Send( &streem , HIGH_PRIORITY, RELIABLE_ORDERED, 0, address, false );
		return true;
	}



	
	template<typename T>
	bool send( unsigned long msgType , const T & pdata,const  RakNet::RakNetGUID& guid )
	{ 
		if(m_pNetInterface==NULL)
			return false;

		static RakNet::BitStream streem;
		streem.Reset();
		streem.Write( (unsigned char)GM_User);
		streem.Write( msgType );
		streem.WriteBits( (unsigned char *)&pdata , sizeof( T ) * 8 );
		m_pNetInterface->Send( &streem , HIGH_PRIORITY, RELIABLE_ORDERED, 0, guid, false );
		return true;
	}







	/**�㲥��Ϣ������Ϣ�ᷢ�����е��û�*/
	void broadcastMessage(unsigned int mesage,const unsigned char* pdata,unsigned length);


	/**�㲥��Ϣ������Ϣ�ᷢ�����е��û�*/
	template<typename T>
	bool broadcastMessage( unsigned long msgType , const T & pdata )
	{ 
		if(m_pNetInterface==NULL)
			return false;
		static RakNet::BitStream streem;
		streem.Reset();
		streem.Write( (unsigned char)GM_User);
		streem.Write( msgType );
		streem.WriteBits( (unsigned char *)&pdata , sizeof( T ) * 8 );
		m_pNetInterface->Send( &streem , HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true );
		return true;
	}



	/**�ھ�������Ѱ����������
    *@param portnmuber �˿ں�
	*/
	void pingLan(short unsigned int portnumber);



	/**��ȡ��Ϣ����������׵�ַ
	*/
	static void* getPackDataptr(RakNet::Packet* pPacek);



	/**�ж��Ƿ����ӵ���ָ���Ļ���*/
	 RakNet::ConnectionState    getConnectState(const RakNet::SystemAddress& address);




protected:

	


protected:
	
	/**�հ�����*/
	void receive();

	/**��ȡ������Ϣ����*/
	unsigned char GetPacketIdentifier(RakNet::Packet *p);

	/**��ȡ���е���Ϸ��Ϣ����*/
	unsigned int getUserMessage(RakNet::Packet * p,unsigned char**pdata);



	/**������Ϸ��Ϣ*/
	void processGameMessage(RakNet::Packet* p);



private:

	bool                     m_isServer; ///�Ƿ��Ƿ�����
    short unsigned int       m_portNumber;///�˿ں�
	/*raknet ����ʵ��ָ��*/
	RakNet::RakPeerInterface *m_pNetInterface;

	netWorkListener*          m_pLinstener;   ///������

};