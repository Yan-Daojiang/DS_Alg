#define _CRT_SECURE_NO_WARNINGS
#include"Compress.h"
#include"Huffman.h"
#include<iostream>
#include<iomanip>
using namespace std;

char *pBuffer = NULL;
HEAD sHead;

void Compress(const char *PFilename,int weight[],int n)
{
	//文件压缩
	HuffmanTree HT;
	HuffmanCode HC;
	HuffmanCoding(HT, HC, weight, n);
	int nSize = 0;
	for (int i = 0; i < 256; i++)
	{
		nSize += weight[i] * strlen(HC[i + 1]);
	}
	nSize = (nSize % 8) ? nSize / 8 + 1 : nSize / 8;

	Encode(PFilename,nSize ,HC);

	InitHead(PFilename);
	int len = WriteFile(PFilename, pBuffer, nSize);
	
	cout << "原文件的大小:" << sHead.length <<"字节"<< endl;
	cout <<"压缩后的文件大小:" <<len << "字节" << endl;
	cout << "压缩率:" << setprecision(4) << double(len) * 100 / sHead.length  << "%" << endl;
	cout << "=========================================" << endl;
}
int Encode(const char *PFilename, const int nSize, HuffmanCode HC)
{
	//根据得到的哈夫曼编码对图片进行压缩
	FILE *in = fopen(PFilename, "rb");
	pBuffer = (char*)malloc(nSize * sizeof(char));

	char cd[256] = { 0 };
	int pos = 0;
	int ch;

	if (!pBuffer)
	{
		cout << "开辟缓冲区失败！" << endl;
		return 0;
	}

	while ((ch = getc(in)) != EOF)
	{
		strcat(cd, HC[ch+1 ]);//从HC复制串到cd中，即对当前的字节重新编码

		while (strlen(cd) >= 8)
		{
			pBuffer[pos++] = Str2byte(cd);

			for (int i = 0; i < 256 - 8; i++)
			{
				cd[i] = cd[i + 8];
			}
		}

	}

	if (strlen(cd) > 0)
	{
		pBuffer[pos++] = Str2byte(cd);
	}
	
	return 0;
}

int InitHead(const char *PFilename)
{
	//初始化文件头
	int ch;
	strcpy(sHead.type, "HUF");
	sHead.length = 0;//原文件长度

	for (int i = 0; i < 256; i++)
	{
		sHead.weight[i] = 0;
	}
	//以二进制流形式打开文件
	FILE *in = fopen(PFilename, "rb");

	while ((ch = getc(in)) != EOF)
	{
		sHead.weight[ch]++;
		sHead.length++;
	}

	fclose(in);
	in = NULL;
	return 0;

}



char Str2byte(const char *PBinStr)
{	//将二进制转化为字节
	char b = 0x00;

	for (int i = 0; i < 8; i++)
	{
		b = b << 1;

		if (PBinStr[i] == '1')
		{
			b = b | 0x01;
		}

	}
	return b;
}

int WriteFile(const char *PFilename, const BUFFER pBuffer, const int nSize)
{
	//生成文件名
	char filename[256] = { 0 };
	strcpy(filename, PFilename);

	strcat(filename, ".huf");

	//以二进制流形式打开文件
	FILE *out = fopen(filename, "wb");

	//写文件头
	fwrite(&sHead, sizeof(HEAD), 1, out);

	//写压缩后的编码
	fwrite(pBuffer, sizeof(char), nSize, out);

	
	fclose(out);
	out = NULL;

	cout << "=================压缩完成================" << endl;
	cout << "生成压缩文件： " << filename << endl;

	int len = sizeof(HEAD) + strlen(PFilename) + 1 + nSize;

	return len;
}