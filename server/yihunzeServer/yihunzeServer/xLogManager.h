

//非线程安全

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



//!xLogMeessager 日志类，用来把一些特定的事件或错误写入日志文件
/**
*这是一个单件类，用来写日志消息
*
*/
class  xLogMessager :public Singleton<xLogMessager>
	//class _declspec(dllimport) Log
{
private:
	std::ofstream	mfpLog;


public:

	/**
	*构造函数，
	*@param fileName 文件名
	*/
	xLogMessager(const  std::string& fileName);

	~xLogMessager();

	/**
	*写入日志
	*param message 写入消息
	*level 消息的级别
	*/
	void logMessage( const std::string& message,LogLevel level = Log_NormalLevel);



	/**设置写入级别，低于这个级别不会写了*/
	void SetWriteLevel(LogLevel level){m_WriteLevel = level;}

	/**获取当前的写入级别*/
	LogLevel GetWriteLevel(){return m_WriteLevel;}



private:

	LogLevel m_WriteLevel;


};



#endif
