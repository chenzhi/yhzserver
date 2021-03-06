#pragma  once

#include "Singleton.h"
#include "EventManager.h"
#include "usermessage.h"
//#include "userstruct.h"




#ifdef _DEBUG
#define  NetWorkTimeOut         9000
#define  NetWorkMaxClientNumber 32

#else

#define  NetWorkMaxClientNumber 5000
#define  NetWorkTimeOut         9000

#endif




#define  GM_User          ID_USER_PACKET_ENUM
//#define  GM_ACCEPTCOME    GM_User+1








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

	/**连接失败*/
	virtual void  onConnectFailed(RakNet::Packet* p){};



};



/**网络包数据，
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

	/**获取网络包数据,
	*@reutrn 如果没有数据返回空
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


	/**获取数据块的长茺*/
	UINT getDataLength()const
	{
		assert(m_pData);
		return m_pPack->length-(sizeof(DWORD) + sizeof(byte));
	}


	/**获取包的发送的的ip地址
	*@pram portnumber 是否包含端口号
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


	/**反回包中的游戏消息id*/
	unsigned int getGameMessageID()
	{
		if(m_pPack==NULL)
			return -1;///最大正整数

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
		m_pPack=p;
	}



	
protected:

	RakNet::Packet* m_pPack;

	char*           m_pData;
	unsigned int    m_length;


};




class  XClass NetWork : public CEventManager
{

public:

	/**构造函数
	*@param isClient 是客户端还是服务器端,true为客户端
	*/
//	NetWork(bool isClient,unsigned int ClientPort);


	NetWork();


	virtual ~NetWork();


	/**构造函数，从配置文件里读取内容
    *@param configFile 配置文件
    *@return 成功返回真失败返回假
	*/
	//bool initFromFile(const std::string& configFile);


	/**本机做为服务器开始启动网络
	*@param portNumber 端口号
	*@return 成功返回真，失败返回假
	*/
	//bool startServer(unsigned int portNumber,const std::string& password);





	/**开始一个客户端*/




	/**连接到指定的服务器，无论是服务器或客户端都可以调用接口连接远程计算机
	*@param  ip 连接对方的ip地址
	*@param  serverPort 端口号
	*@param  password   连接密码
	*@return 连接成功返回真。失败返回假
	*/
	virtual bool  connect(const std::string& ip,unsigned int serverPort,const std::string& password);

 
	/**关闭连接*/
	//void close(const RakNet::SystemAddress& paddress);

	/**关闭连接
	*@param portnumber 端口号
	*/
	void close(const char* pAddress,short unsigned int portnumber);


	void close(const  RakNet::SystemAddress& address);


	/**设置监听者*/
	void setListener(netWorkListener* pListener);


	/**每帧更新*/
     virtual  void update();


	/**在局域网内寻找其它机器
    *@param portnmuber 端口号
	*/
	void pingLan(short unsigned int portnumber);


	/**判断是否连接到了指定的机器*/
	RakNet::ConnectionState    getConnectState(const RakNet::SystemAddress& address) const ;




protected:

	
	/**获取消息包里的数据首地址
	*/
	static void* getPackDataptr(RakNet::Packet* pPacek);





protected:
	
	/**收包函数*/
	void receive();

	/**获取包的消息定义*/
	unsigned char GetPacketIdentifier(RakNet::Packet *p);

	/**获取包中的游戏消息定义*/
	unsigned int getUserMessage(RakNet::Packet * p,unsigned char**pdata);



	/**处理游戏消息*/
	void processGameMessage(RakNet::Packet* p);



protected:

	bool                     m_isServer; ///是否是服务器
	/*raknet 连接实例指针*/
	RakNet::RakPeerInterface *m_pNetInterface;

	netWorkListener*          m_pLinstener;   ///监听者


	NetPack*                  m_pNetPack;///消息包

};