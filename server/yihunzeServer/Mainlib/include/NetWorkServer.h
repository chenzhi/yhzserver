
/***************************************
�����������
****************************************/


class NetWorkServer
{

public:

	/**����*/
	NetWorkServer();


    virtual ~NetWorkServer();


	/**����������*/
	bool startServer();



	/**�رշ�����*/
	bool stopServer();



	/**���ӵ�ָ����Զ�̼ƻ�*/
	bool connect();


	/**�Ͽ�Զ��*/
	bool closeConnect();


	virtual void update();


protected:


};