
/**********************************
������Ϸ���ݿ����������Ϸ��Ҫ���ص����ݿ��ѯ��
��Ҫ�����﷢����Ϣ�����ݿ�����������������ݿ������
��Ӧ����Ϣ
*************************************/

#include "Singleton.h"
#include "RemoteServer.h"


class DatabaserServer :public Singleton<DatabaseInstace> ,public RemoteServer
{

public:

	/**���캯��*/
	DatabaserServer(const Config& config);


	virtual ~DatabaserServer();



	/**ע����Ҫ��Ӧ�����ݿ�������Ϣ*/
	void registerMessage();

    /**ע��������Ϣ*/
	void unregisterMessage();


	virtual void update(float time);


protected:



	/**@{��Ϣ��Ӧ����
	*/

	/**���ݿ����ݷ����������ӳɹ���Ϣ*/
	void processConnectSucceed(NetPack* pPacek);


	/**@}
	*/


protected:



};