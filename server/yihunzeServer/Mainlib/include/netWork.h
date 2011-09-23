#pragma  once

#include "Singleton.h"
#include "EventManager.h"
//#include "usermessage.h"
//#include "userstruct.h"




#define  NetWorkMaxClientNumber 65535
#define  NetWorkTimeOut         100000

#define  GM_User          ID_USER_PACKET_ENUM
#define  GM_ACCEPTCOME    GM_User+1








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





	/**���ӵ�ָ���ķ�������
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


	/**�㲥��Ϣ������Ϣ�ᷢ�����е��û�*/
	void broadcastMessage(unsigned int mesage,const unsigned char* pdata,unsigned length);



	/**�ھ�������Ѱ����������
    *@param portnmuber �˿ں�
	*/
	void pingLan(short unsigned int portnumber);



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