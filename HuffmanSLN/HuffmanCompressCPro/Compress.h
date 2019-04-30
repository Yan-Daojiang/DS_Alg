#pragma once
#ifndef COMMPRESS_H
#define COMMPRESS_H
#include"Huffman.h"
//文件头
struct HEAD
{
	char type[4];//文件类型
	int length;//原文件长度
	int weight[256];//权值数值
};
typedef char *BUFFER;

void Compress(const char *PFilename,int weight[], int n);
int Encode(const char *PFilename, const int nSize, HuffmanCode HC);
int InitHead(const char *PFilename);
char Str2byte(const char *PBinStr);
int WriteFile(const char *PFilename, const BUFFER pBuffer, const int nSize);

#endif // COMMPRESS_H

