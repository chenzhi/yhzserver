
/************************************************\
��ȡ�����ļ���
*****************************************************/

#include "iteratorWapper.h"


class XClass Config
{

public:

	Config();


	~Config();

	
	bool loadfile(const std::string& file);


	/**��ȡ�ᶨֵ\
	*@param key 
	*@param value ����key��ֵ
	*@return �ҵ������棬ʧ�ܷ��ؼ�
	*/
	bool getValue(const std::string& key,std::string& value) const ;



	/**�ж�����ָ����ֵ*/
	bool hasKey(const std::string& key) const ;


protected:

	typedef std::map<std::string,std::string> ValueMap;

	ValueMap m_Value;///�����ļ����key��ֵ�б�

};




/**�ֲ������ļ������Զ�ȡ�����ŷֲ�*/
class XClass CategoryCofig
{

	
public:

	

	typedef  std::map<std::string,std::map<std::string,std::string> > CategoryMap;

	typedef  MapIterator< CategoryMap> SectionIterator; 



public:

	CategoryCofig();


	~CategoryCofig();


	bool loadfile(const std::string& file);



	SectionIterator getSectionIterator(){ return  SectionIterator(m_CategoryMap.begin(),m_CategoryMap.end());}



protected:


    CategoryMap                   m_CategoryMap;


};