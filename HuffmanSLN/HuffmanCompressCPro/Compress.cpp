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
	//�ļ�ѹ��
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
	
	cout << "ԭ�ļ��Ĵ�С:" << sHead.length <<"�ֽ�"<< endl;
	cout <<"ѹ������ļ���С:" <<len << "�ֽ�" << endl;
	cout << "ѹ����:" << setprecision(4) << double(len) * 100 / sHead.length  << "%" << endl;
	cout << "=========================================" << endl;
}
int Encode(const char *PFilename, const int nSize, HuffmanCode HC)
{
	//���ݵõ��Ĺ����������ͼƬ����ѹ��
	FILE *in = fopen(PFilename, "rb");
	pBuffer = (char*)malloc(nSize * sizeof(char));

	char cd[256] = { 0 };
	int pos = 0;
	int ch;

	if (!pBuffer)
	{
		cout << "���ٻ�����ʧ�ܣ�" << endl;
		return 0;
	}

	while ((ch = getc(in)) != EOF)
	{
		strcat(cd, HC[ch+1 ]);//��HC���ƴ���cd�У����Ե�ǰ���ֽ����±���

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
	//��ʼ���ļ�ͷ
	int ch;
	strcpy(sHead.type, "HUF");
	sHead.length = 0;//ԭ�ļ�����

	for (int i = 0; i < 256; i++)
	{
		sHead.weight[i] = 0;
	}
	//�Զ���������ʽ���ļ�
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
{	//��������ת��Ϊ�ֽ�
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
	//�����ļ���
	char filename[256] = { 0 };
	strcpy(filename, PFilename);

	strcat(filename, ".huf");

	//�Զ���������ʽ���ļ�
	FILE *out = fopen(filename, "wb");

	//д�ļ�ͷ
	fwrite(&sHead, sizeof(HEAD), 1, out);

	//дѹ����ı���
	fwrite(pBuffer, sizeof(char), nSize, out);

	
	fclose(out);
	out = NULL;

	cout << "=================ѹ�����================" << endl;
	cout << "����ѹ���ļ��� " << filename << endl;

	int len = sizeof(HEAD) + strlen(PFilename) + 1 + nSize;

	return len;
}