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

};








///消息包的结构体定义

///玩家请求登入
#pragma pack(push, 1)
struct UserLogin
{
	char  m_account[20];
	char  m_password[20];

};


#pragma pack(pop)


///游戏服务器转发用户请求登入包
#pragma pack(push, 1)
struct UserAccount
{
	char  m_account[20];  //用户名
	char  m_password[20]; //密码
	char  m_ip      [10];  //ip地址
};
#pragma pack(pop)


///返回用户请求登入是否成功
#pragma pack(push, 1)
struct RespondAccount
{
	char   m_userip[20];  //用户ip
	char   m_login;       //是否登入,0表示帐号用户名不对，1表示同意登入
};
#pragma pack(pop)