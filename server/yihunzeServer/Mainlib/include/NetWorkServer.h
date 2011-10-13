
/***************************************
�����������
****************************************/

#pragma  once
#include "netWork.h"



class XClass  NetWorkServer :public Singleton<NetWorkServer>, public NetWork
{

public:

	/**����*/
	NetWorkServer();


    virtual ~NetWorkServer();


	/**����������*/
	bool startServer(unsigned int portNumber,const std::string& password);



	/**�رշ�����*/
	bool stopServer();



	/**���ӵ�ָ����Զ�̼ƻ�*/
	//bool connect();


	/**�Ͽ�Զ��*/
	bool closeConnect(const RakNet::SystemAddress& address );


	virtual void update();


	
	/**��������,����Ϣ����ָ�����û�
	*@param message ��Ϣid
	*@param pdata ��Ϣ����
	*@param length ��Ϣ���ݵĳ���
	*@param receiver�����ߵ�id��
	*/
	void send(unsigned int message,const  char* pData,unsigned int length, const  RakNet::RakNetGUID receiver);


	/**
	*@see send;
	*/
	void send(unsigned int message,const  char* pData,unsigned int length,const  RakNet::SystemAddress& receiver);


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






protected:


};