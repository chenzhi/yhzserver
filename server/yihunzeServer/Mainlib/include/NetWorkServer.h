
/***************************************
网络服务器类
****************************************/


class NetWorkServer
{

public:

	/**构造*/
	NetWorkServer();


    virtual ~NetWorkServer();


	/**启动服务器*/
	bool startServer();



	/**关闭服务历*/
	bool stopServer();



	/**连接到指定的远程计机*/
	bool connect();


	/**断开远程*/
	bool closeConnect();


	virtual void update();


protected:


};