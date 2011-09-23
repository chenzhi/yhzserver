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
网络事件监听者，会回调网络事件。
*/
class XClass netWorkListener
{
public:


	netWorkListener(){}

	virtual ~netWorkListener(){};

 //    /**当一个玩家进入*/
	virtual void onConnect(RakNet::Packet* p)=0;

	///**玩家离开*/
	virtual void onDisconnect(RakNet::Packet* p)=0;

	///**玩家掉线*/
	virtual void  onConnectlost(RakNet::Packet* p)=0;

	    /**当一个玩家进入*/


};





class  XClass NetWork :public Singleton<NetWork>, public CEventManager
{

public:

	/**构造函数
	*@param isClient 是客户端还是服务器端,true为客户端
	*/
	NetWork(bool isClient,unsigned int ClientPort);



	NetWork();


	~NetWork();


	/**构造函数，从配置文件里读取内容
    *@param configFile 配置文件
    *@return 成功返回真失败返回假
	*/
	bool initFromFile(const std::string& configFile);





	/**连接到指定的服务器，
	*@param  ip 连接对方的ip地址
	*@param  serverPort 端口号
	*@param  password   连接密码
	*@return 连接成功返回真。失败返回假
	*/
	bool conect(const std::string& ip,unsigned int serverPort,const std::string& password);


	/**关闭连接*/
	//void close(const RakNet::SystemAddress& paddress);

	/**关闭连接
	*@param portnumber 端口号
	*/
	void close(const char* pAddress,short unsigned int portnumber);




	/**设置监听者*/
	void setListener(netWorkListener* pListener);


	/**每帧更新*/
    void update();



	/**发包函数,把消息发给指定的用户
	*@param message 消息id
	*@param pdata 消息内容
	*@param length 消息内容的长度
	*@param receiver接收者的id，
	*/
	void send(unsigned int message,const  char* pData,unsigned int length,RakNet::RakNetGUID receiver);


	/**
	*@see send;
	*/
	void send(unsigned int message,const  char* pData,unsigned int length,RakNet::SystemAddress& receiver);


	/**广播消息，此消息会发给所有的用户*/
	void broadcastMessage(unsigned int mesage,const unsigned char* pdata,unsigned length);



	/**在局域网内寻找其它机器
    *@param portnmuber 端口号
	*/
	void pingLan(short unsigned int portnumber);



protected:

	


protected:
	
	/**收包函数*/
	void receive();

	/**获取包的消息定义*/
	unsigned char GetPacketIdentifier(RakNet::Packet *p);

	/**获取包中的游戏消息定义*/
	unsigned int getUserMessage(RakNet::Packet * p,unsigned char**pdata);



	/**处理游戏消息*/
	void processGameMessage(RakNet::Packet* p);



private:

	bool                     m_isServer; ///是否是服务器
    short unsigned int       m_portNumber;///端口号

	/*raknet 连接实例指针*/
	RakNet::RakPeerInterface *m_pNetInterface;

	netWorkListener*          m_pLinstener;   ///监听者








};