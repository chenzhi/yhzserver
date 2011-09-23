#include "pch.h"
#include "config.h"
#include "xLogManager.h"


//------------------------------------------------------------------------
Config::Config()
{
	

}

//------------------------------------------------------------------------
Config::~Config()
{

}

//------------------------------------------------------------------------
bool Config::loadfile(const std::string& configFile)
{
	m_Value.clear();

	std::ifstream file;

	file.open(configFile.c_str());
	if (file.fail())
	{
		std::string err="netWork can't find configFile filename is:"+configFile;
		xLogMessager::getSingleton().logMessage(err);

		return false ;
	}

	char tmpBuf [256];
	memset(tmpBuf,0,256);
	std::string retString;
	size_t readCount=0;

	while (!file.eof())
	{
		file.getline(tmpBuf,256);
		if(tmpBuf[0]=='#'||tmpBuf[0]=='/')
		{
			continue;
		}
		char key[256];
		char val[256];
		sscanf(tmpBuf,"%s = %s",key,val);
		if(hasKey(key))
		{
			std::string waring="Config::loadfile has same key: ";
			waring+=+key;
			waring+=" will user the first value";
			xLogMessager::getSingleton().logMessage(waring);
			continue;
		}
		m_Value.insert(std::make_pair(key,val));
	}

	file.close();

	return true;

}

//------------------------------------------------------------------------
bool Config::getValue(const std::string& key,std::string& value)const 
{

	ValueMap::const_iterator it=m_Value.find(key);
	if(it==m_Value.end())
		return false;

	value= it->second;
	return  true;

}

//------------------------------------------------------------------------
bool Config::hasKey(const std::string& key)
{

	ValueMap::const_iterator it=m_Value.find(key);
	if(it==m_Value.end())
		return false;

	return  true;
}