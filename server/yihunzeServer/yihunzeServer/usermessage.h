/************************************************************
用户消息定义
**************************************************************/
#pragma  once


#include "MessageIdentifiers.h"


enum GameMessage
{
	///
	GM_ACCEPTCOME=100,      ///连接到远程计算机服务器后成功后。远程返回的消息,远程只有服务器才会返回此消息

	GM_TEXT_MESSAGE,   ///文字消息

   ///帐号服务器消息定义
	GM_ACCOUNT_REQUEST,   ///验证是否有这个帐号
	GM_ACCOUNT_RESPOND,   ///帐号服务发给全局服务器的帐号验证消息
	GM_ACCOUNT_RESPOND_FAILED,   //回应验证消息,未能验证的用户名和密码
	GM_ACCOUNT_RESPOND_SUCCEED,    //回应验证消息,正确的用户名和密码,并把游戏服务器





	///状态服务器消息定义
	GM_GAMESERVER_CONNECT,   ///游戏服务器连接
	GM_GAMESERVER_DISCONNECT, ///游戏服务器断开
    GM_STATESERVER_CLIENT_CONNECT,///状态服务器通知游戏服务器有客户端需要连接,必须在一分钟内联接



	///游戏逻辑服务器消息定义
	GM_CHATMESSAGE,                ///逻辑服服报器测试代码
	GM_CONNECT_GAMESERVER,         ///客户端请求连接逻辑服务器
	



	///游戏数据库服务器消息定义
	GM_REQUEST_PLAYERS,              ///向游戏数据库请求玩家信息




	///客户端消息
	//GM_CLIENT_CONNECT_GAMESERVER,///客户端请求连接游戏服务器


};





#define IPaddressLength  50///定义ip地址需要少空间
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
	char  m_account [UserNameLength];  //用户名
	char  m_password[UserNameLength]; //密码
	char  m_ip      [IPaddressLength];  //ip地址
	//short unsigned int  m_portnumber;
};
#pragma pack(pop)


///返回用户请求登入是否成功
#pragma pack(push, 1)
struct RespondAccount
{
	
	char   m_login;       //是否登入,0表示帐号用户名不对，1表示同意登入
	int    m_accountID;///帐号id
	char   m_userip[IPaddressLength];  //用户ip

};
#pragma pack(pop)



///客户端帐号信息
#pragma pack(push, 1)
struct ClientAccount
{

	int    m_accountID;///帐号id
	char   m_userip[IPaddressLength];  //用户ip

};
#pragma pack(pop)




///返回一个字节一般用来表是否成功
#pragma pack(push, 1)
struct NetByte
{
	char  m_byte;
};
#pragma pack(pop)



///返回一个整型
#pragma pack(push, 1)
struct NetInt
{
	int   m_int;
};
#pragma pack(pop)



///一个字符串结构
#pragma pack(push, 1)
struct NetString
{
	char  m_char[UserNameLength];
};
#pragma pack(pop)



#pragma pack(push, 1)
struct NetIPAddress
{
	char  m_char[IPaddressLength];
};
#pragma pack(pop)




///允许客户端连接游戏服器
#pragma pack(push, 1)
struct GameServerInfor
{
	char  m_GameServerIP[IPaddressLength];          ///游戏服务器地址和端口号
	char  m_GameServerPassWord[UserNameLength];     ///游戏服务器密码
	unsigned int m_PortNumber;                      ///端品号
	int m_accountid;                        ///玩家帐号id
};
#pragma pack(pop)


///玩家信息
#pragma pack(push, 1)
struct Tag_Player
{
	unsigned int        m_ID;
	char                m_Name[UserNameLength];
	unsigned int        m_AccountID;
	short unsigned int  m_profession;//职业0为战士1为法师
	UINT                m_hp;
	UINT                m_mp;
	UINT                m_atk;
	UINT                m_def;
	UINT                m_power;
	UINT                m_endurance;
	UINT                m_intelligence;
	UINT                m_maxdam;
	UINT                m_dam;
	UINT                m_mindam;

};
#pragma pack(pop)


#pragma pack(push, 1)
struct Tag_PlayerCollect
{
	UINT          m_Account;
	UINT          m_Count;  ///多少个玩家
	char          m_ip[IPaddressLength];
	Tag_Player   m_pPlayer;///玩家数据

};
#pragma pack(pop)