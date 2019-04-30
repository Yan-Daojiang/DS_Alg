#pragma once
#ifndef COMMPRESS_H
#define COMMPRESS_H
#include"Huffman.h"
//�ļ�ͷ
struct HEAD
{
	char type[4];//�ļ�����
	int length;//ԭ�ļ�����
	int weight[256];//Ȩֵ��ֵ
};
typedef char *BUFFER;

void Compress(const char *PFilename,int weight[], int n);
int Encode(const char *PFilename, const int nSize, HuffmanCode HC);
int InitHead(const char *PFilename);
char Str2byte(const char *PBinStr);
int WriteFile(const char *PFilename, const BUFFER pBuffer, const int nSize);

#endif // COMMPRESS_H

