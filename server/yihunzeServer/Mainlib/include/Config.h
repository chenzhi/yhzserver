
/************************************************\
读取配置文件类
*****************************************************/

class XClass Config
{

public:

	Config();


	~Config();

	
	bool loadfile(const std::string& file);


	/**获取提定值\
	*@param key 
	*@param value 返回key对值
	*@return 找到返回真，失败返回假
	*/
	bool getValue(const std::string& key,std::string& value) const ;



	/**判断是有指定的值*/
	bool hasKey(const std::string& key);


protected:

	typedef std::map<std::string,std::string> ValueMap;

	ValueMap m_Value;///配置文件里的key和值列表

};