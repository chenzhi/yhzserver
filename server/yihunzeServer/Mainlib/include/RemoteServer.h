

/***
Զ�̼����������ָ��Զ�̼����������
�����NetWorkServer�����������ȴ���NetWorkServer,�������ڷ������ϣ�

*/

#pragma  once

#include "networkServer.h"


class XClass RemoteServer
{
public:


	/**���캯��*/
	RemoteServer(){}

	/**����Զ�̼������ip.�˿ںź�����*/
	RemoteServer(const std::string& serverip,unsigned int portnumber,const std::string& password);


	virtual  ~RemoteServer();


	/**����Զ�̼ƻ�
	*�����沢����ʾ������ɡ�ֻ�Ǳ�ʾ���ӳɹ�
	*/
	virtual bool connect();


	/**�Ƿ��������*/
	bool hasConnnect() const ;


	/**�Ͽ�����*/
	virtual void closeConnect();


	/**�����������
	*�����²������Զ��ϵ��������ӵ�Զ�̼����
	*/
	void setNetParament(const std::string& serverip,unsigned int portnumber,const std::string& password);


	/**����Զ��raknet�����ӵ�ַ*/
	const RakNet::SystemAddress&  getRakNetAddress()const;


	/**���º���,
	*@param time ��һ֡���ʱ��
	*/
	virtual void update(float time){};



	
	/**
	*������Ϣ��������������
	*@param address ���͵ĵ�ַ
	*@param msgType ��Ϣid
	*@param ��������
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

	std::string             m_RemoteIP;  ///Զ�̵�ַ
	std::string             m_PassWord;  ///����
	unsigned int            m_PortNumber; ///�˿ں�
	RakNet::SystemAddress   m_Address;      //Զ�̵�ַ



};