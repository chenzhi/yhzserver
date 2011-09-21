/************************************************************
用户消息定义
**************************************************************/
#pragma  once


#include "MessageIdentifiers.h"


enum GameMessage
{
	GM_User=ID_USER_PACKET_ENUM,

	GM_ACCEPTCOME,   ///有新用户进入后发送的确认信息

	GM_TEXT_MESSAGE,   ///文字消息
	

};