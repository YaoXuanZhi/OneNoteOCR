#pragma once
#include <stdio.h>
#include <windows.h>
//引入.net的命名空间
using namespace std;
using namespace System;
using namespace System::Runtime::InteropServices;



//将托管字符串转换成非托管的ANSI字符串
char *ManagedStr2UnmanagedStr(String^ UnmanagedStr);

//将非托管的ANSI字符串转换成托管字符串 
String^ UnmanagedStr2ManagedStr(char *UnmanagedStr);

