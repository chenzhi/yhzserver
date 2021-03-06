

/***
远程计算机，管理指定远程计算机的连接
本类对NetWorkServer有依赖必须先创建NetWorkServer,必须用在服务器上，

*/

#pragma  once

#include "networkServer.h"


class XClass RemoteServer
{
public:


	/**构造函数*/
	RemoteServer(){}

	/**定义远程计算机的ip.端口号和密码*/
	RemoteServer(const std::string& serverip,unsigned int portnumber,const std::string& password);


	virtual  ~RemoteServer();


	/**连接远程计机
	*返回真并不表示连接完成。只是表示连接成功
	*/
	virtual bool connect();


	/**是否完成连接*/
	bool hasConnnect() const ;


	/**断开连接*/
	virtual void closeConnect();


	/**设置网络参数
	*设置新参数会自动断掉现在连接的远程计算机
	*/
	void setNetParament(const std::string& serverip,unsigned int portnumber,const std::string& password);


	/**返回远程raknet的连接地址*/
	const RakNet::SystemAddress&  getRakNetAddress()const;


	/**更新函数,
	*@param time 上一帧间隔时间
	*/
	virtual void update(float time){};



	
	/**
	*发送信息给服务器的例程
	*@param address 发送的地址
	*@param msgType 消息id
	*@param 发送数据
	*/
	template<typename T>
	bool send( unsigned long msgType , const T & pdata )
	{ 
		if(NetWorkServer::getSingletonPtr()==NULL)
			return false;
		NetWorkServer::getSingletonPtr()->send( msgType ,pdata,m_Address );
		return true;
	}


	/**
	*@see send;
	*/
	bool  send(unsigned int message,const  char* pData,unsigned int length)
	{

		if(NetWorkServer::getSingletonPtr()==NULL)
			return false;
		NetWorkServer::getSingletonPtr()->send( message ,pData,length,m_Address );
		return  true;

	}



protected:

	std::string             m_RemoteIP;  ///远程地址
	std::string             m_PassWord;  ///密码
	unsigned int            m_PortNumber; ///端口号
	RakNet::SystemAddress   m_Address;      //远程地址



};