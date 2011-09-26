/************************************************************
用户消息定义
**************************************************************/
#pragma  once


#include "MessageIdentifiers.h"


enum GameMessage
{
	GM_TEXT_MESSAGE=100,   ///文字消息

	GM_ACCOUNT_REQUEST,   ///验证是否有这个帐号
	GM_ACCOUNT_RESPOND,   //回应验证消息





	///状态服务器消息定义
	GM_GAMESERVER_CONNECT,   ///游戏服务器连接
	GM_GAMESERVER_DISCONNECT, ///游戏服务器断开

};





#define IPaddressLength  30///定义ip地址需要少空间
#define UserNameLength   20//用户名长度



///消息包的结构体定义

///玩家请求登入
#pragma pack(push, 1)
struct UserLogin
{
	char  m_account[UserNameLength];
	char  m_password[UserNameLength];

};


#pragma pack(pop)


///游戏服务器转发用户请求登入包
#pragma pack(push, 1)
struct UserAccount
{
	char  m_account[UserNameLength];  //用户名
	char  m_password[UserNameLength]; //密码
	char  m_ip      [IPaddressLength];  //ip地址
};
#pragma pack(pop)


///返回用户请求登入是否成功
#pragma pack(push, 1)
struct RespondAccount
{
	char   m_userip[IPaddressLength];  //用户ip
	char   m_login;       //是否登入,0表示帐号用户名不对，1表示同意登入
};
#pragma pack(pop)


///返回一个字节一般用来表是否成功
#pragma pack(push, 1)
struct NetByte
{
	char  m_byte;
};
#pragma pack(pop)



///一个字符串结构
#pragma pack(push, 1)
struct NetString
{
	char  m_char[UserNameLength];
};
#pragma pack(pop)