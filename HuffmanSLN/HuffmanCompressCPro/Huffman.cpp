#define _CRT_SECURE_NO_WARNINGS
#include"Huffman.h"
#include<iostream>
using namespace std;

void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n) 
{ //���ݵõ���Ȩֵ����������������й���������
	int m, i, s1, s2; 
	HuffmanTree p;

	if (n <= 1)    return;
	m = 2 * n - 1;//m����õ���Ϊ���еĽ�������

	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode)); // ������洢�ռ�,0�ŵ�Ԫδ��
	//��ʼ�������������н��
	for (p = HT + 1, i = 1; i <= n; ++i, ++p, ++w)
	{//��ʼ��Ҷ�ӽ��
		(*p).weight = *w;
		(*p).parent = 0;
		(*p).lchild = 0;
		(*p).rchild = 0;
	}
	for (; i <= m; ++i, ++p)
	{//��ʼ��ʣ����
		(*p).parent = 0;
		(*p).parent = 0;
		(*p).lchild = 0;
		(*p).rchild = 0;
	}

	for (i = n + 1; i <= m; ++i) // ���շ�����
	{ // ��HT[1~i-1]��ѡ��parentΪ0��weight��С���������,����ŷֱ�Ϊs1��s2
		select(HT, i - 1, s1, s2);
		HT[s1].parent = HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	/*
	cout << "==========��������ÿ��������Ϣ=========" << endl;
	cout << "HT\tweight\tparent\tlchild\trchild" << endl;
	for (int i = 1; i < 512; i++)
	{
		cout << "HT[" << i << "]" << "\t" << HT[i].weight << "\t" << HT[i].parent << "\t" << HT[i].lchild << "\t" << HT[i].rchild << endl;
	}
	cout << "=========================================" << endl;
	*/
	

	/*===============�����������========================*/
	unsigned c, cdlen;
	HC = (HuffmanCode)malloc((n + 1) * sizeof(char*));
	// ����n���ַ������ͷָ������
	char *cd;
	cd = (char*)malloc(n * sizeof(char)); 
	c = m;
	cdlen = 0;

	for (i = 1; i <= m; ++i)
		HT[i].weight = 0; // �����շ�����ʱ�������״̬��־
	while (c)
	{
		if (HT[c].weight == 0)
		{ // ����
			HT[c].weight = 1;
			if (HT[c].lchild != 0)
			{
				c = HT[c].lchild;
				cd[cdlen++] = '0';
			}
			else if (HT[c].rchild == 0)
			{ // �Ǽ�Ҷ�ӽ����ַ��ı���
				HC[c] = (char *)malloc((cdlen + 1) * sizeof(char));
				cd[cdlen] = '\0';
				strcpy(HC[c], cd); // ���Ʊ���(��)
			}
		}
		else if (HT[c].weight == 1)
		{ // ����
			HT[c].weight = 2;
			if (HT[c].rchild != 0)
			{
				c = HT[c].rchild;
				cd[cdlen++] = '1';
			}
		}
		else
		{ // HT[c].weight==2,�˻�
			HT[c].weight = 0;
			c = HT[c].parent;
			--cdlen; // �˵������,���볤�ȼ�1
		}
	}
	free(cd);
}

void select(HuffmanTree t, int i, int &s1, int &s2)
{ // s1Ϊ��С��s2Ϊ��С
	int j;
	s1 = min(t, i);
	s2 = min(t, i);
	if (s1 > s2)
	{
		j = s1;
		s1 = s2;
		s2 = j;
	}
}

int min(HuffmanTree t, int i)
{ // select()����
	int j, s;
	int k = INT_MAX; // ȡkΪ��С�ڿ��ܵ�ֵ
	for (j = 1; j <= i; j++)
		if (t[j].weight < k&&t[j].parent == 0)
		{
			k = t[j].weight; 
			s = j;
		}
	t[s].parent = 1;	//weight��ֵ��ʱ�޸ģ������´ε���ʱѡ���С��

	return s;
}
