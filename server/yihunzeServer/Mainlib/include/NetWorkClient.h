

/**********************************
����ͻ��ˣ���һ��ʱ�����ֻ������һ��������
***********************************/
#pragma once 
#include "network.h"













class XClass NetWorkClientInstance :public NetWork
{

public:


	/**����*/
	NetWorkClientInstance(const std::string& name);


    /**����*/
	~NetWorkClientInstance();


	const std::string& getName()const{return m_Name;}

	/**���ӵ�ָ���ķ������������Ƿ�������ͻ��˶����Ե��ýӿ�����Զ�̼����
	*@param  ip ���ӶԷ���ip��ַ
	*@param  serverPort �˿ں�
	*@param  password   ��������
	*@return ���ӳɹ������档ʧ�ܷ��ؼ�
	*/
	virtual bool connect(const std::string& ip,unsigned int serverPort,const std::string& password);



	/**�Ƿ����ӳɹ�*/
	bool  hasConnect() const ;


	/**ÿ֡����*/
	virtual  void update();


	/**�Ͽ�����*/
	void  closeConnect();



	/**
	*������Ϣ��������������
	*@param address ���͵ĵ�ַ
	*@param msgType ��Ϣid
	*@param ��������
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

	std::string         m_ServerIP ;         //Զ�̷�����ip

	unsigned int        m_PortNumber;        ///Զ�̶˿ں�

	std::string         m_PassWord;          //����

	RakNet::SystemAddress m_ServerAddress;   ///Զ�̵�ַ

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


	/**���º���*/
    void update();

	void setNetworkListener(netWorkListener* pListener);


	/**����һ���µ�����ʵ��
	*���������ͬ����ʵ�����׳��쳣
	*/
	bool createConnect(const std::string& name,const std::string& serverip,unsigned int portnumber,const std::string& passWord);


	/**��ȡָ�����ֵ�����ʵ�������û���ҵ����ؿ�*/
	NetWorkClientInstance* getConnectInstance(const std::string& name) const ;


	/**����һ������ʵ�� */
	void destroyInstance(const std::string& name);



protected:

	/**������������ʵ��*/
	void destroyAllInstance();

	///��ʵ�����ٶ���
	void _destroyAllInstance(const std::string& name);



protected:

	netWorkListener*      m_pListener;

	ClientInstanceCollect m_InstanceCollect;

	std::vector<std::string> DestroyInstanceCollect;



};