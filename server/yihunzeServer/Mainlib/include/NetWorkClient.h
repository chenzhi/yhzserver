

/**********************************
����ͻ��ˣ�
***********************************/


class NetWorkClient
{

public:


	/**����*/
	NetWorkClient();


    /**����*/
	~NetWorkClient();


	/**���ӵ�ָ���ķ������������Ƿ�������ͻ��˶����Ե��ýӿ�����Զ�̼����
	*@param  ip ���ӶԷ���ip��ַ
	*@param  serverPort �˿ں�
	*@param  password   ��������
	*@return ���ӳɹ������档ʧ�ܷ��ؼ�
	*/
	bool connect(const std::string& ip,unsigned int serverPort,const std::string& password);



	/**�Ƿ����ӳɹ�*/
	bool  hasConnect() const ;


	/**ÿ֡����*/
	void  update(float time);


	/**�Ͽ�����*/
	void  closeConnect();



protected:



};