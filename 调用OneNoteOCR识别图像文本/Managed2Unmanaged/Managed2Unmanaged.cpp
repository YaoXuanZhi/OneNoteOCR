//�˴�����Դ�ڣ�C++����C#�����й�C++�ַ������й��ַ�����ת�����������޸ĺ�õ�
//http://wenku.baidu.com/link?url=Xm5du2oRvHcB0M1NW4NUYrSrZukdKIDnxdY1MlbLTDrD9hcnV9trb_1t2TCJ_LT9f_pb6n8LTbT5hHfQ5JwfpFsuMKx1iag7UpBri2oVas_

//#pragma warning (disable: 4996)
#include "Managed2Unmanaged.h"
/**
*@brief	���й��ַ���ת���ɷ��йܵ�ANSI�ַ���
*@param ManagedStr��String^��˵��������Ҫת��Ϊ���й��ַ������й��ַ�����������ӦC/C++�е�char*
*@return ���ط��й��ַ���������Ϊchar*
*/
char *ManagedStr2UnmanagedStr(String^ ManagedStr)
{
	IntPtr ip = Marshal::StringToHGlobalAnsi(ManagedStr);
	const char*pTemp = static_cast<const char*>(ip.ToPointer());
	char* UnmanagedStr = new char[strlen(pTemp) + 1];
#if _MSC_VER<1400 
	strcpy(UnmanagedStr, pTemp);
#else
	//strcpy_s()�ڶ���������ָ���������ַ����Ĵ�С����Ҫ����'\0'Ŷ�����+1
	strcpy_s(UnmanagedStr, strlen(pTemp)+1, pTemp);
#endif
	Marshal::FreeHGlobal(ip);
	return UnmanagedStr;
}


/**
*@brief	�����йܵ�ANSI�ַ���ת�����й��ַ��� 
*@param UnmanagedStr��char *��˵��������Ҫת��Ϊ�й��ַ����ķ��й��ַ�����������ӦC#�е�String^
*@return �����й��ַ���������ΪString^
*/
String^ UnmanagedStr2ManagedStr(char *UnmanagedStr)
{
	String^ ManagedStr = Marshal::PtrToStringAnsi(static_cast<IntPtr>(UnmanagedStr));
	return ManagedStr;
}