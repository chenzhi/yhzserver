
/***************************************
网络服务器类
****************************************/

#pragma  once
#include "netWork.h"



class XClass  NetWorkServer :public Singleton<NetWorkServer>, public NetWork
{

public:

	/**构造*/
	NetWorkServer();


    virtual ~NetWorkServer();


	/**启动服务器*/
	bool startServer(unsigned int portNumber,const std::string& password);



	/**关闭服务历*/
	bool stopServer();



	/**连接到指定的远程计机*/
	//bool connect();


	/**断开远程*/
	bool closeConnect(const RakNet::SystemAddress& address );


	virtual void update();


	
	/**发包函数,把消息发给指定的用户
	*@param message 消息id
	*@param pdata 消息内容
	*@param length 消息内容的长度
	*@param receiver接收者的id，
	*/
	void send(unsigned int message,const  char* pData,unsigned int length, const  RakNet::RakNetGUID receiver);


	/**
	*@see send;
	*/
	void send(unsigned int message,const  char* pData,unsigned int length,const  RakNet::SystemAddress& receiver);


	/**
	*发送信息给服务器的例程
	*@param address 发送的地址
	*@param msgType 消息id
	*@param 发送数据
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







	/**广播消息，此消息会发给所有的用户*/
	void broadcastMessage(unsigned int mesage,const unsigned char* pdata,unsigned length);


	/**广播消息，此消息会发给所有的用户*/
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






protected:


};