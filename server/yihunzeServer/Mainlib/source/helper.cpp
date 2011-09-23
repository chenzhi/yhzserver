#include "pch.h"
#include "helper.h"





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
	_snprintf(buff,sizeof(buff),"%d",i);
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
	_snprintf(buff,sizeof(buff),"%f",f);
	return std::string(buff);
}
