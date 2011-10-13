/************************************************************
�û���Ϣ����
**************************************************************/
#pragma  once


#include "MessageIdentifiers.h"


enum GameMessage
{
	///
	GM_ACCEPTCOME=100,      ///���ӵ�Զ�̼������������ɹ���Զ�̷��ص���Ϣ,Զ��ֻ�з������Ż᷵�ش���Ϣ

	GM_TEXT_MESSAGE,   ///������Ϣ

   ///�ʺŷ�������Ϣ����
	GM_ACCOUNT_REQUEST,   ///��֤�Ƿ�������ʺ�
	GM_ACCOUNT_RESPOND,   ///�ʺŷ��񷢸�ȫ�ַ��������ʺ���֤��Ϣ
	GM_ACCOUNT_RESPOND_FAILED,   //��Ӧ��֤��Ϣ,δ����֤���û���������
	GM_ACCOUNT_RESPOND_SUCCEED,    //��Ӧ��֤��Ϣ,��ȷ���û���������,������Ϸ������





	///״̬��������Ϣ����
	GM_GAMESERVER_CONNECT,   ///��Ϸ����������
	GM_GAMESERVER_DISCONNECT, ///��Ϸ�������Ͽ�
    GM_STATESERVER_CLIENT_CONNECT,///״̬������֪ͨ��Ϸ�������пͻ�����Ҫ����,������һ����������



	///��Ϸ�߼���������Ϣ����
	GM_CHATMESSAGE,                ///�߼������������Դ���
	GM_CONNECT_GAMESERVER,         ///�ͻ������������߼�������
	



	///��Ϸ���ݿ��������Ϣ����
	GM_REQUEST_PLAYERS,              ///����Ϸ���ݿ����������Ϣ




	///�ͻ�����Ϣ
	//GM_CLIENT_CONNECT_GAMESERVER,///�ͻ�������������Ϸ������


};





#define IPaddressLength  50///����ip��ַ��Ҫ�ٿռ�
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
	char  m_account [UserNameLength];  //�û���
	char  m_password[UserNameLength]; //����
	char  m_ip      [IPaddressLength];  //ip��ַ
	//short unsigned int  m_portnumber;
};
#pragma pack(pop)


///�����û���������Ƿ�ɹ�
#pragma pack(push, 1)
struct RespondAccount
{
	
	char   m_login;       //�Ƿ����,0��ʾ�ʺ��û������ԣ�1��ʾͬ�����
	int    m_accountID;///�ʺ�id
	char   m_userip[IPaddressLength];  //�û�ip

};
#pragma pack(pop)



///�ͻ����ʺ���Ϣ
#pragma pack(push, 1)
struct ClientAccount
{

	int    m_accountID;///�ʺ�id
	char   m_userip[IPaddressLength];  //�û�ip

};
#pragma pack(pop)




///����һ���ֽ�һ���������Ƿ�ɹ�
#pragma pack(push, 1)
struct NetByte
{
	char  m_byte;
};
#pragma pack(pop)



///����һ������
#pragma pack(push, 1)
struct NetInt
{
	int   m_int;
};
#pragma pack(pop)



///һ���ַ����ṹ
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




///����ͻ���������Ϸ����
#pragma pack(push, 1)
struct GameServerInfor
{
	char  m_GameServerIP[IPaddressLength];          ///��Ϸ��������ַ�Ͷ˿ں�
	char  m_GameServerPassWord[UserNameLength];     ///��Ϸ����������
	unsigned int m_PortNumber;                      ///��Ʒ��
	int m_accountid;                        ///����ʺ�id
};
#pragma pack(pop)


///�����Ϣ
#pragma pack(push, 1)
struct Tag_Player
{
	unsigned int        m_ID;
	char                m_Name[UserNameLength];
	unsigned int        m_AccountID;
	short unsigned int  m_profession;//ְҵ0Ϊսʿ1Ϊ��ʦ
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
	UINT          m_Count;  ///���ٸ����
	char          m_ip[IPaddressLength];
	Tag_Player   m_pPlayer;///�������

};
#pragma pack(pop)