

/**********************************
网络客户端，
***********************************/


class NetWorkClient
{

public:


	/**构造*/
	NetWorkClient();


    /**析构*/
	~NetWorkClient();


	/**连接到指定的服务器，无论是服务器或客户端都可以调用接口连接远程计算机
	*@param  ip 连接对方的ip地址
	*@param  serverPort 端口号
	*@param  password   连接密码
	*@return 连接成功返回真。失败返回假
	*/
	bool connect(const std::string& ip,unsigned int serverPort,const std::string& password);



	/**是否连接成功*/
	bool  hasConnect() const ;


	/**每帧更新*/
	void  update(float time);


	/**断开连接*/
	void  closeConnect();



protected:



};