

/**********************************
网络客户端，在一个时间段内只能连接一个服务器
***********************************/
#pragma once 
#include "network.h"













class XClass NetWorkClientInstance :public NetWork
{

public:


	/**构造*/
	NetWorkClientInstance(const std::string& name);


    /**析构*/
	~NetWorkClientInstance();


	const std::string& getName()const{return m_Name;}

	/**连接到指定的服务器，无论是服务器或客户端都可以调用接口连接远程计算机
	*@param  ip 连接对方的ip地址
	*@param  serverPort 端口号
	*@param  password   连接密码
	*@return 连接成功返回真。失败返回假
	*/
	virtual bool connect(const std::string& ip,unsigned int serverPort,const std::string& password);



	/**是否连接成功*/
	bool  hasConnect() const ;


	/**每帧更新*/
	virtual  void update();


	/**断开连接*/
	void  closeConnect();



	/**
	*发送信息给服务器的例程
	*@param address 发送的地址
	*@param msgType 消息id
	*@param 发送数据
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

	std::string         m_Name;

	std::string         m_ServerIP ;         //远程服务器ip

	unsigned int        m_PortNumber;        ///远程端口号

	std::string         m_PassWord;          //密码

	RakNet::SystemAddress m_ServerAddress;   ///远程地址

	bool                m_needShoudown;//





};



typedef std::vector<NetWorkClientInstance*>ClientInstanceCollect;


class XClass  NetWorkClient :public Singleton<NetWorkClient>
{

public:

	NetWorkClient()
		:m_pListener(NULL)
	{}


	~NetWorkClient(){	destroyAllInstance();}


	/**更新函数*/
    void update();

	void setNetworkListener(netWorkListener* pListener);


	/**创建一个新的连接实例
	*如果创建相同名的实例，抛出异常
	*/
	bool createConnect(const std::string& name,const std::string& serverip,unsigned int portnumber,const std::string& passWord);


	/**获取指定名字的连接实例，如果没有找到返回空*/
	NetWorkClientInstance* getConnectInstance(const std::string& name) const ;


	/**销毁一个连接实例 */
	void destroyInstance(const std::string& name);



protected:

	/**销毁所有连接实例*/
	void destroyAllInstance();

	///真实的销毁动作
	void _destroyAllInstance(const std::string& name);



protected:

	netWorkListener*      m_pListener;

	ClientInstanceCollect m_InstanceCollect;

	std::vector<std::string> DestroyInstanceCollect;



};