#pragma once
#include <stdio.h>
#include <windows.h>
//����.net�������ռ�
using namespace std;
using namespace System;
using namespace System::Runtime::InteropServices;



//���й��ַ���ת���ɷ��йܵ�ANSI�ַ���
char *ManagedStr2UnmanagedStr(String^ UnmanagedStr);

//�����йܵ�ANSI�ַ���ת�����й��ַ��� 
String^ UnmanagedStr2ManagedStr(char *UnmanagedStr);

