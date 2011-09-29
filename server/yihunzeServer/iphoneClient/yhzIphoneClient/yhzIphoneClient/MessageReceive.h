
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
    ///**玩家离开*/
	void onDisconnect(RakNet::Packet* p);
    
	///**玩家掉线*/
	void  onConnectlost(RakNet::Packet* p);

    void onConnect(RakNet::Packet* p){}
    

protected:

	///处理登入消息失败
	void processAccountFaild(NetPack* pPack);

	///处理登入成功消息
	void processAccountSucceed(NetPack* pPack);


	///成功连接远程计算机
	void processConnectRemoteServer(NetPack* pPack);




protected:

	RakNet::SystemAddress m_GameServerAdderss;
	std::string           m_GameServerPassWord;
    
    yhzIphoneClientViewController*          m_pController;


};