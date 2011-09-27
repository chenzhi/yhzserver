#include "pch.h"
#include "GameServer.h"


GameServer::GameServer(const std::string& name,const std::string& ip,unsigned int portNumber,const std::string& password)
:m_Name(name),m_IP(ip),m_IsConnect(false),m_PortNumber(portNumber),m_PassWord(password)
{

}