
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


///���������Ϣ
void MessageReceive::processAccount(NetPack* pPack)
{
	NetByte* puser=reinterpret_cast<NetByte*>(pPack->getData());
	if(puser->m_byte==0)
	{
		MessageBox(NULL,"�û����������!","����",MB_OK);
	}else
	{
         MessageBox(NULL,"�û�����ȷ","��ȷ",MB_OK);
	}

	return ;
}
