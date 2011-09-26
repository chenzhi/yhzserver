
/***********************************
�ʺŷ������������ʺŵ���֤
*****************************************/


#pragma once	



class AccountManager
{
public:

	AccountManager();


	~AccountManager();


	/**����һ���û�
	*@param �ʻ���
	*@param password ����
	*@return �����ɹ������棬ʧ�ܷ��ؼ٣�����������ʺŲ����ٴ���
	*/
	bool createAccount(const std::string& accountName,const std::string& password);



	/**�ж��ʺ������Ƿ���ȷ
	*@return �����Щ�ʺ����뷵���棬�޷���false
	*/
	bool checkAccount(const std::string& accountName,const std::string& password);




protected:


	/**�����ʺ���֤��Ϣ*/
	void processAccountTest(NetPack* pdata);


	/**��ʼ��*/
	void init();


	/**����*/
	void destroy();






protected:



};