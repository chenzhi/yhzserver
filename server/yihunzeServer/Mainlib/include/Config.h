
/************************************************\
��ȡ�����ļ���
*****************************************************/

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
	bool hasKey(const std::string& key);


protected:

	typedef std::map<std::string,std::string> ValueMap;

	ValueMap m_Value;///�����ļ����key��ֵ�б�

};