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

};








///��Ϣ���Ľṹ�嶨��

///����������
#pragma pack(push, 1)
struct UserLogin
{
	char  m_account[20];
	char  m_password[20];

};


#pragma pack(pop)


///��Ϸ������ת���û���������
#pragma pack(push, 1)
struct UserAccount
{
	char  m_account[20];  //�û���
	char  m_password[20]; //����
	char  m_ip      [10];  //ip��ַ
};
#pragma pack(pop)


///�����û���������Ƿ�ɹ�
#pragma pack(push, 1)
struct RespondAccount
{
	char   m_userip[20];  //�û�ip
	char   m_login;       //�Ƿ����,0��ʾ�ʺ��û������ԣ�1��ʾͬ�����
};
#pragma pack(pop)