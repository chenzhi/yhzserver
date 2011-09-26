
#include "pch.h"
#include "MessageReceive.h"
#include "usermessage.h"

template<>
MessageReceive* Singleton<MessageReceive>::ms_Singleton=NULL;



MessageReceive::MessageReceive()
{
	NetWork::getSingleton().registerMessageHandle(GM_ACCOUNT_RESPOND,&MessageReceive::processAccount,this);

}


MessageReceive::~MessageReceive()
{

	NetWork::getSingleton().unregisterMessageHandle(GM_ACCOUNT_RESPOND,this);

}


///处理登入消息
void MessageReceive::processAccount(NetPack* pPack)
{
	NetByte* puser=reinterpret_cast<NetByte*>(pPack->getData());
	if(puser->m_byte==0)
	{
		MessageBox(NULL,"用户名密码错误!","错误",MB_OK);
	}else
	{
         MessageBox(NULL,"用户名正确","正确",MB_OK);
	}

	return ;
}
