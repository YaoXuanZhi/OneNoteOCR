#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include "Base64\Base64.h"
#include "Managed2Unmanaged\Managed2Unmanaged.h"

//����C#���
#using "..\Bin\OneNoteOCRRecognize.dll"
using namespace OneNoteOCRRecognize;

/**
*@brief	�˺��������Զ����Ʒ�ʽ��ȡ�ļ�����(C++��)
*@param FilePath��const char*��˵������Ҫ����ȡ���ļ�·��
*@param offsetcharc��size_t��˵����������ļ�ͷƫ�����ɸ��ֽ�
*@param OffsetToENd��long��˵�������Ϊ0����ô���ļ�ͷ��ȡ��ƫ�ƴ����������0�����ƫ�ƴ���ȡ���ļ�ĩβ
*@return ���ض�ȡ�����ļ����ݣ�����ͨ���˺�����ȡ���ļ���BOM�������ļ�����
*/
std::string ReadFileByBinaryInCPlusPlus(const char* FilePath, long offsetcharc, long OffsetToENd)
{
	std::ifstream infile(FilePath, std::ios::in | std::ios::binary);
	if (!infile) {
		std::cout << "File " << FilePath << " not found!\n";
		system("pause");
		exit(1);
	}
	//����һ������������ļ�����
	std::string FileData;
	if (OffsetToENd == 0)//���ļ�ͷ��ȡ��ƫ�ƴ�
	{
		//ΪFileData�����ڴ�ռ�
		FileData.resize(offsetcharc);//new char[FileSize];
		infile.read(&FileData[0], offsetcharc);
	}
	else//��ƫ�ƴ���ȡ���ļ�ĩβ
	{
		//�ƶ��ļ�ָ�뵽�ļ�ĩβ��Ŀ���ǽ���ftell()����ļ���С
		infile.seekg(0, std::ios::end);
		//����ļ���С
		long FileSize = (long)infile.tellg();
		//ΪFileData�����ڴ�ռ�
		FileData.resize(FileSize);//new char[FileSize];
		//�ƶ��ļ�ָ�뵽����ļ�ͷ��ƫ�ƴ�
		infile.seekg(offsetcharc, std::ios::beg);
		//������ļ�ͷָ��ƫ��offsetcharc����λ��ʼ��ȡ�ļ�
		infile.read(&FileData[0], FileSize - offsetcharc);
	}
	infile.close();
	return FileData;
}

/**
*@brief	ʶ������ϵ�ͼ��
*@param FilePath��char*��˵������Ҫ����OCRʶ���ͼƬ·��
*@return ����OCRʶ�����ı������ʶ���쳣����ô����ERROR
*/
char* OneNoteOCRInDisk(char* FilePath)
{
	OcrCommonAPI OCREngine;
	String^ TempResultStr = OCREngine.OCRPictrueInDisk(UnmanagedStr2ManagedStr(FilePath));
	return ManagedStr2UnmanagedStr(TempResultStr);
}


/**
*@brief	ʶ���ڴ��е�ͼ��
*
*�˺����Ƚ��ڴ��е�ͼƬ���ݽ���Base64���룬�ٽ�Base64���ݴ���C# DLL�ṩ��OCR�ӿڣ�
*Ŀ���Ǳ���char*��������Ϊʵ��ʱ��һ�������������������'\0'�����Զ�ֹͣ
*@param PictrueData��string��˵������Ҫ����OCRʶ���ͼƬ����
*@return ����OCRʶ�����ı������ʶ���쳣����ô����ERROR
*/
char* OneNoteOCRInMemory(string PictrueData)
{
	OcrCommonAPI OCREngine;
	string Base64Data = Base64::encode(PictrueData);
	String^ TempResultStr = OCREngine.OCRPictrueInMemory(UnmanagedStr2ManagedStr((char*)Base64Data.c_str()));
	return ManagedStr2UnmanagedStr(TempResultStr);
}

void main(int argc,char* argv[])
{
	if (argc < 2)
	{
		printf("��������ҪOCRʶ���ͼƬ·��\n");
		system("pause");
		exit(1);
	}
	cout << OneNoteOCRInMemory(ReadFileByBinaryInCPlusPlus(argv[1], 0, 1)) << endl;
	//cout << OneNoteOCRInDisk(argv[1]) << endl;
	system("pause");
}
