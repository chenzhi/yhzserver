

/***************************************
�����û��ĵ��룬
******************************************/


#pragma  once



class LoginManager :public Singleton<LoginManager>
{

public:

	LoginManager();


	~LoginManager();


	/**ע��������Ϣ*/
	void registerMessage();


	/**ע��������Ϣ*/
	void unregisterMessage();


protected:

	/**@{������Ϣ��Ӧ����
	*/



	/**����ͻ��ʺŷ�������Ϣ��֤*/
	void processAccountRequest(NetPack* pdata);


	/**�����ʺŷ���������������֤�����Ϣ*/
	void processAccountRespond(NetPack* pdata);
	






	/**@}
	*/




protected:

};