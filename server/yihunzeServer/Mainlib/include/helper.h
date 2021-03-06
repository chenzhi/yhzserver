
/**********************************************
工具类，一般常用的函数放这个类里
************************************************/

#pragma  once


class XClass Helper
{

public:
	Helper(){}

	~Helper(){}


	/**设置当前运行目录为工作目录*/
	static void  setCurrentWorkPath();


	/**@{字符串相关功能函数
	*/
	static int StringToInt(const std::string& str);

	static  std::string IntToString(int i);

	static float StringTofloat(const  std::string& str);

	static  std::string floatToString(float f);

	/**@}
	*/



};


