#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include "Base64\Base64.h"
#include "Managed2Unmanaged\Managed2Unmanaged.h"

//引入C#类库
#using "..\Bin\OneNoteOCRRecognize.dll"
using namespace OneNoteOCRRecognize;

/**
*@brief	此函数将会以二进制方式读取文件数据(C++版)
*@param FilePath：const char*，说明：将要被读取的文件路径
*@param offsetcharc：size_t，说明：相对于文件头偏移若干个字节
*@param OffsetToENd：long，说明：如果为0，那么从文件头读取到偏移处，如果大于0，则从偏移处读取到文件末尾
*@return 返回读取到的文件数据，可以通过此函数读取到文件的BOM或者是文件内容
*/
std::string ReadFileByBinaryInCPlusPlus(const char* FilePath, long offsetcharc, long OffsetToENd)
{
	std::ifstream infile(FilePath, std::ios::in | std::ios::binary);
	if (!infile) {
		std::cout << "File " << FilePath << " not found!\n";
		system("pause");
		exit(1);
	}
	//定义一个变量来存放文件数据
	std::string FileData;
	if (OffsetToENd == 0)//从文件头读取到偏移处
	{
		//为FileData分配内存空间
		FileData.resize(offsetcharc);//new char[FileSize];
		infile.read(&FileData[0], offsetcharc);
	}
	else//从偏移处读取到文件末尾
	{
		//移动文件指针到文件末尾，目的是借助ftell()求得文件大小
		infile.seekg(0, std::ios::end);
		//获得文件大小
		long FileSize = (long)infile.tellg();
		//为FileData分配内存空间
		FileData.resize(FileSize);//new char[FileSize];
		//移动文件指针到相对文件头的偏移处
		infile.seekg(offsetcharc, std::ios::beg);
		//从相对文件头指针偏移offsetcharc个单位开始读取文件
		infile.read(&FileData[0], FileSize - offsetcharc);
	}
	infile.close();
	return FileData;
}

/**
*@brief	识别磁盘上的图像
*@param FilePath：char*，说明：将要进行OCR识别的图片路径
*@return 返回OCR识别后的文本，如果识别异常，那么返回ERROR
*/
char* OneNoteOCRInDisk(char* FilePath)
{
	OcrCommonAPI OCREngine;
	String^ TempResultStr = OCREngine.OCRPictrueInDisk(UnmanagedStr2ManagedStr(FilePath));
	return ManagedStr2UnmanagedStr(TempResultStr);
}


/**
*@brief	识别内存中的图像
*
*此函数先将内存中的图片数据进行Base64编码，再将Base64数据传入C# DLL提供的OCR接口，
*目的是避免char*变量在作为实参时，一旦遇到二进制数据里的'\0'将会自动停止
*@param PictrueData：string，说明：将要进行OCR识别的图片数据
*@return 返回OCR识别后的文本，如果识别异常，那么返回ERROR
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
		printf("请输入需要OCR识别的图片路径\n");
		system("pause");
		exit(1);
	}
	cout << OneNoteOCRInMemory(ReadFileByBinaryInCPlusPlus(argv[1], 0, 1)) << endl;
	//cout << OneNoteOCRInDisk(argv[1]) << endl;
	system("pause");
}
