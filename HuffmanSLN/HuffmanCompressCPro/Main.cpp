#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"Huffman.h"
#include"Compress.h"
using namespace std;

#define N 256

//�������
int main()
{
	int weight[N] = { 0 };//Ȩֵͳ�ƣ���ʼ��Ϊ0
	char  filename[256];
	cout << "�����������ļ���:";
	cin >> filename;

	//��ȡ�ļ�����ͳ��
	int ch;
	FILE *in = fopen(filename, "rb");

	while ((ch = getc(in)) != EOF)
	{
		weight[ch]++;	//Ƶ��ͳ��
	}
	
	/*
	cout << "============ԭ�ļ�ÿ���ַ���Ȩֵ=========" << endl;
	
	for (int i = 0; i < 256; i++)
	{
		printf("\t0x%02x\t\t%d\n", i, weight[i]);
	}
	cout << "========================================="<<endl;
	*/
	
	fclose(in);

	/*
	//��鹹��Ĺ��������͹����������Ƿ���ȷ
	HuffmanTree HT;
	HuffmanCode HC;
	HuffmanCoding(HT, HC, weight, N);
	*/
	
	/*
	cout << "===========���й���������Ľ��==========" << endl;
	for (int i = 1; i <= N; i++)
	{
		cout << i<<"\t";
		puts(HC[i]);
	}
	cout << "=========================================" << endl;
	*/
	
	Compress(filename, weight, N);//ѹ��

	system("pause");
	return 0;
}