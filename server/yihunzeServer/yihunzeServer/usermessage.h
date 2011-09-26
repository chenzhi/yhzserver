/************************************************************
�û���Ϣ����
**************************************************************/
#pragma  once


#include "MessageIdentifiers.h"


enum GameMessage
{
	GM_TEXT_MESSAGE=100,   ///������Ϣ

	GM_ACCOUNT_REQUEST,   ///��֤�Ƿ�������ʺ�
	GM_ACCOUNT_RESPOND,   //��Ӧ��֤��Ϣ





	///״̬��������Ϣ����
	GM_GAMESERVER_CONNECT,   ///��Ϸ����������
	GM_GAMESERVER_DISCONNECT, ///��Ϸ�������Ͽ�

};





#define IPaddressLength  30///����ip��ַ��Ҫ�ٿռ�
#define UserNameLength   20//�û�������



///��Ϣ���Ľṹ�嶨��

///����������
#pragma pack(push, 1)
struct UserLogin
{
	char  m_account[UserNameLength];
	char  m_password[UserNameLength];

};


#pragma pack(pop)


///��Ϸ������ת���û���������
#pragma pack(push, 1)
struct UserAccount
{
	char  m_account[UserNameLength];  //�û���
	char  m_password[UserNameLength]; //����
	char  m_ip      [IPaddressLength];  //ip��ַ
};
#pragma pack(pop)


///�����û���������Ƿ�ɹ�
#pragma pack(push, 1)
struct RespondAccount
{
	char   m_userip[IPaddressLength];  //�û�ip
	char   m_login;       //�Ƿ����,0��ʾ�ʺ��û������ԣ�1��ʾͬ�����
};
#pragma pack(pop)


///����һ���ֽ�һ���������Ƿ�ɹ�
#pragma pack(push, 1)
struct NetByte
{
	char  m_byte;
};
#pragma pack(pop)



///һ���ַ����ṹ
#pragma pack(push, 1)
struct NetString
{
	char  m_char[UserNameLength];
};
#pragma pack(pop)