

/***
远程计算机，管理指定远程计算机的连接
本类对NetWork有依赖必须先创建network
*/

//
//class XClass RemoteServer
//{
//public:
//
//	/**定义远程计算机的ip.端口号和密码*/
//	RemoteServer(const std::string& serverip,unsigned int portnumber,const std::string& password);
//
//
//	virtual  ~RemoteServer();
//
//
//	/**连接远程计机
//	*返回真并不表示连接完成。只是表示连接成功
//	*/
//	bool connect();
//
//
//	/**是否完成连接*/
//	bool hasConnnect() const ;
//
//
//	/**断开连接*/
//	void closeConnect();
//
//
//	/**设置网络参数
//	*设置新参数会自动断掉现在连接的远程计算机
//	*/
//	void setNetParament(const std::string& serverip,unsigned int portnumber,const std::string& password);
//
//
//	/**返回远程raknet的连接地址*/
//	RakNet::SystemAddress getRakNetAddress()const;
//
//
//
//	/**更新函数,
//	*@param time 上一帧间隔时间
//	*/
//	virtual void update(float time){};
//
//
//
//protected:
//
//	std::string             m_RemoteIP;  ///远程地址
//	std::string             m_PassWord;  ///密码
//	unsigned int            m_PortNumber; ///端口号
//
//
//
//
//};