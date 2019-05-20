#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"Huffman.h"
#include"Compress.h"
using namespace std;

#define N 256

//程序入口
int main()
{
	int weight[N] = { 0 };//权值统计，初始化为0
	char  filename[256];
	cout << "请输入您的文件名:";
	cin >> filename;

	//读取文件进行统计
	int ch;
	FILE *in = fopen(filename, "rb");

	while ((ch = getc(in)) != EOF)
	{
		weight[ch]++;	//频度统计
	}
	
	/*
	cout << "============原文件每个字符的权值=========" << endl;
	
	for (int i = 0; i < 256; i++)
	{
		printf("\t0x%02x\t\t%d\n", i, weight[i]);
	}
	cout << "========================================="<<endl;
	*/
	
	fclose(in);

	/*
	//检查构造的哈弗曼树和哈夫曼编码是否正确
	HuffmanTree HT;
	HuffmanCode HC;
	HuffmanCoding(HT, HC, weight, N);
	*/
	
	/*
	cout << "===========进行哈夫曼编码的结果==========" << endl;
	for (int i = 1; i <= N; i++)
	{
		cout << i<<"\t";
		puts(HC[i]);
	}
	cout << "=========================================" << endl;
	*/
	
	Compress(filename, weight, N);//压缩

	system("pause");
	return 0;
}