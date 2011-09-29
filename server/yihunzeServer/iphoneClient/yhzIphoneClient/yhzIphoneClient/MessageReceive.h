
#pragma  once

#include  "Singleton.h"
#include  "NetWork.h"

#import <UIKit/UIKit.h>
#import "yhzIphoneClientViewController.h"

@class yhzIphoneClientViewController;

class MessageReceive : public Singleton<MessageReceive> ,public netWorkListener
{

public:


	MessageReceive( yhzIphoneClientViewController* pController);


	~MessageReceive();

    
    
    
    
protected:
    ///**����뿪*/
	void onDisconnect(RakNet::Packet* p);
    
	///**��ҵ���*/
	void  onConnectlost(RakNet::Packet* p);

    void onConnect(RakNet::Packet* p){}
    

protected:

	///���������Ϣʧ��
	void processAccountFaild(NetPack* pPack);

	///�������ɹ���Ϣ
	void processAccountSucceed(NetPack* pPack);


	///�ɹ�����Զ�̼����
	void processConnectRemoteServer(NetPack* pPack);




protected:

	RakNet::SystemAddress m_GameServerAdderss;
	std::string           m_GameServerPassWord;
    
    yhzIphoneClientViewController*          m_pController;


};