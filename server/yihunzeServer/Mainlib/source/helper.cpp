#include "pch.h"
#include "helper.h"





//-----------------------------------------------------------
void Helper::setCurrentWorkPath()
{

#ifndef Platform
    
    char pBuffer[1024];
	ZeroMemory(pBuffer, 1024);
	GetModuleFileName(NULL, pBuffer, 1024);

	std::string	 dirname;
	std::string cc=pBuffer;
	std::string::size_type pos =cc.find_last_of("\\");
	dirname = cc.substr(0,pos);
	SetCurrentDirectory(dirname.c_str());
    
#endif
    

}


//-----------------------------------------------------------
int Helper::StringToInt(const std::string& str)
{
	int i=0;
	sscanf(str.c_str(),"%d",&i);
	return i;
}


//-----------------------------------------------------------
std::string Helper::IntToString(int i)
{
	char buff[64];
	sprintf(buff,"%d",i);
	return std::string(buff);

}


//-----------------------------------------------------------
float Helper::StringTofloat(const std::string& str)
{

	float f=0.0f;
	sscanf(str.c_str(),"%f",&f);
	return f;
}

//-----------------------------------------------------------
std::string Helper::floatToString(float f)
{
	char buff[128];
	sprintf(buff,"%f",f);
	return std::string(buff);
}
