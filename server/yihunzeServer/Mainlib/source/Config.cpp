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
		if(sscanf(tmpBuf,"%s = %s",key,val)>0)
		{
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
bool Config::hasKey(const std::string& key) const 
{

	ValueMap::const_iterator it=m_Value.find(key);
	if(it==m_Value.end())
		return false;

	return  true;
}




/**�ֲ������ļ������Զ�ȡ�����ŷֲ�*/
CategoryCofig::CategoryCofig()
{

}


CategoryCofig::~CategoryCofig()
{

}


bool CategoryCofig::loadfile(const std::string& configFile)
{

	m_CategoryMap.clear();

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


	std::string currentSection;///��ǰ����

	while (!file.eof())
	{
		file.getline(tmpBuf,256);
		if(tmpBuf[0]=='#'||tmpBuf[0]=='/')
		{
			continue;
		}

		///�����һ���ַ������һ���ַ��ֱ���[]��ʾ����һ������



		std::string line(tmpBuf);
		if(line[0]=='['&&line.length()>3&&line[line.length()-1]==']')
		{
			currentSection= line.substr(1, line.length() - 2);

			std::map<std::string ,std::string > values;
			m_CategoryMap[currentSection]=values;



		}else if(currentSection.empty()==false)//���������
		{
			//char key[256];
			//char val[256];

			std::string::size_type pos=line.find_first_of('=');
			if(pos!=std::string::npos)///�����=�ŷֽ��ַ�
			{
				std::string key=line.substr(0,pos);
				std::string value=line.substr(pos+1);
				m_CategoryMap[currentSection][key]=value;
			}

		}

	

	}

	file.close();


	return true;
}