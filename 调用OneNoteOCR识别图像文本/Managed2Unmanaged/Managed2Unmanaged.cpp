//此代码来源于：C++调用C#类库非托管C++字符串和托管字符串的转换，经部分修改后得到
//http://wenku.baidu.com/link?url=Xm5du2oRvHcB0M1NW4NUYrSrZukdKIDnxdY1MlbLTDrD9hcnV9trb_1t2TCJ_LT9f_pb6n8LTbT5hHfQ5JwfpFsuMKx1iag7UpBri2oVas_

//#pragma warning (disable: 4996)
#include "Managed2Unmanaged.h"
/**
*@brief	将托管字符串转换成非托管的ANSI字符串
*@param ManagedStr：String^，说明：将将要转换为非托管字符串的托管字符串变量，对应C/C++中的char*
*@return 返回非托管字符串，类型为char*
*/
char *ManagedStr2UnmanagedStr(String^ ManagedStr)
{
	IntPtr ip = Marshal::StringToHGlobalAnsi(ManagedStr);
	const char*pTemp = static_cast<const char*>(ip.ToPointer());
	char* UnmanagedStr = new char[strlen(pTemp) + 1];
#if _MSC_VER<1400 
	strcpy(UnmanagedStr, pTemp);
#else
	//strcpy_s()第二个参数是指被拷贝的字符串的大小，需要考虑'\0'哦，因此+1
	strcpy_s(UnmanagedStr, strlen(pTemp)+1, pTemp);
#endif
	Marshal::FreeHGlobal(ip);
	return UnmanagedStr;
}


/**
*@brief	将非托管的ANSI字符串转换成托管字符串 
*@param UnmanagedStr：char *，说明：将将要转换为托管字符串的非托管字符串变量，对应C#中的String^
*@return 返回托管字符串，类型为String^
*/
String^ UnmanagedStr2ManagedStr(char *UnmanagedStr)
{
	String^ ManagedStr = Marshal::PtrToStringAnsi(static_cast<IntPtr>(UnmanagedStr));
	return ManagedStr;
}