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




class  XClass NetWork : public CEventManager
{

public:

	/**���캯��
	*@param isClient �ǿͻ��˻��Ƿ�������,trueΪ�ͻ���
	*/
//	NetWork(bool isClient,unsigned int ClientPort);


	NetWork();


	virtual ~NetWork();


	/**���캯�����������ļ����ȡ����
    *@param configFile �����ļ�
    *@return �ɹ�������ʧ�ܷ��ؼ�
	*/
	//bool initFromFile(const std::string& configFile);


	/**������Ϊ��������ʼ��������
	*@param portNumber �˿ں�
	*@return �ɹ������棬ʧ�ܷ��ؼ�
	*/
	//bool startServer(unsigned int portNumber,const std::string& password);





	/**��ʼһ���ͻ���*/





	/**���ӵ�ָ���ķ������������Ƿ�������ͻ��˶����Ե��ýӿ�����Զ�̼����
	*@param  ip ���ӶԷ���ip��ַ
	*@param  serverPort �˿ں�
	*@param  password   ��������
	*@return ���ӳɹ������档ʧ�ܷ��ؼ�
	*/
	virtual bool  connect(const std::string& ip,unsigned int serverPort,const std::string& password);

 
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
     virtual  void update();


	/**�ھ�������Ѱ����������
    *@param portnmuber �˿ں�
	*/
	void pingLan(short unsigned int portnumber);


	/**�ж��Ƿ����ӵ���ָ���Ļ���*/
	RakNet::ConnectionState    getConnectState(const RakNet::SystemAddress& address) const ;




protected:

	
	/**��ȡ��Ϣ����������׵�ַ
	*/
	static void* getPackDataptr(RakNet::Packet* pPacek);





protected:
	
	/**�հ�����*/
	void receive();

	/**��ȡ������Ϣ����*/
	unsigned char GetPacketIdentifier(RakNet::Packet *p);

	/**��ȡ���е���Ϸ��Ϣ����*/
	unsigned int getUserMessage(RakNet::Packet * p,unsigned char**pdata);



	/**������Ϸ��Ϣ*/
	void processGameMessage(RakNet::Packet* p);



protected:

	bool                     m_isServer; ///�Ƿ��Ƿ�����
	/*raknet ����ʵ��ָ��*/
	RakNet::RakPeerInterface *m_pNetInterface;

	netWorkListener*          m_pLinstener;   ///������


	NetPack*                  m_pNetPack;///��Ϣ��

};