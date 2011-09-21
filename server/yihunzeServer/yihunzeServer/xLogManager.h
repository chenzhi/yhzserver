

//���̰߳�ȫ

#ifndef  __Log_H__
#define __Log_H__




#include <iostream>
#include <fstream>
#include "Singleton.h"

enum LogLevel 
{

	Log_LowLevle,
	Log_NormalLevel,
	Log_HeightLevel,
};



//!xLogMeessager ��־�࣬������һЩ�ض����¼������д����־�ļ�
/**
*����һ�������࣬����д��־��Ϣ
*
*/
class  xLogMessager :public Singleton<xLogMessager>
	//class _declspec(dllimport) Log
{
private:
	std::ofstream	mfpLog;


public:

	/**
	*���캯����
	*@param fileName �ļ���
	*/
	xLogMessager(const  std::string& fileName);

	~xLogMessager();

	/**
	*д����־
	*param message д����Ϣ
	*level ��Ϣ�ļ���
	*/
	void logMessage( const std::string& message,LogLevel level = Log_NormalLevel);



	/**����д�뼶�𣬵���������𲻻�д��*/
	void SetWriteLevel(LogLevel level){m_WriteLevel = level;}

	/**��ȡ��ǰ��д�뼶��*/
	LogLevel GetWriteLevel(){return m_WriteLevel;}



private:

	LogLevel m_WriteLevel;


};



#endif
