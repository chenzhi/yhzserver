

/***
Զ�̼����������ָ��Զ�̼����������
�����NetWork�����������ȴ���network
*/

//
//class XClass RemoteServer
//{
//public:
//
//	/**����Զ�̼������ip.�˿ںź�����*/
//	RemoteServer(const std::string& serverip,unsigned int portnumber,const std::string& password);
//
//
//	virtual  ~RemoteServer();
//
//
//	/**����Զ�̼ƻ�
//	*�����沢����ʾ������ɡ�ֻ�Ǳ�ʾ���ӳɹ�
//	*/
//	bool connect();
//
//
//	/**�Ƿ��������*/
//	bool hasConnnect() const ;
//
//
//	/**�Ͽ�����*/
//	void closeConnect();
//
//
//	/**�����������
//	*�����²������Զ��ϵ��������ӵ�Զ�̼����
//	*/
//	void setNetParament(const std::string& serverip,unsigned int portnumber,const std::string& password);
//
//
//	/**����Զ��raknet�����ӵ�ַ*/
//	RakNet::SystemAddress getRakNetAddress()const;
//
//
//
//	/**���º���,
//	*@param time ��һ֡���ʱ��
//	*/
//	virtual void update(float time){};
//
//
//
//protected:
//
//	std::string             m_RemoteIP;  ///Զ�̵�ַ
//	std::string             m_PassWord;  ///����
//	unsigned int            m_PortNumber; ///�˿ں�
//
//
//
//
//};