
/**********************************************
�����࣬һ�㳣�õĺ������������
************************************************/

#pragma  once


class XClass Helper
{

public:
	Helper(){}

	~Helper(){}


	/**���õ�ǰ����Ŀ¼Ϊ����Ŀ¼*/
	static void  setCurrentWorkPath();


	/**@{�ַ�����ع��ܺ���
	*/
	static int StringToInt(const std::string& str);

	static  std::string IntToString(int i);

	static float StringTofloat(const  std::string& str);

	static  std::string floatToString(float f);

	/**@}
	*/



};


