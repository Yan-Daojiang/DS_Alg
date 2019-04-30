#define _CRT_SECURE_NO_WARNINGS
#include"Huffman.h"
#include<iostream>
using namespace std;

void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n) 
{ //根据得到的权值构造哈夫曼树并进行哈夫曼编码
	int m, i, s1, s2; 
	HuffmanTree p;

	if (n <= 1)    return;
	m = 2 * n - 1;//m计算得到的为树中的结点的总数

	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode)); // 结点分配存储空间,0号单元未用
	//初始化数的树的所有结点
	for (p = HT + 1, i = 1; i <= n; ++i, ++p, ++w)
	{//初始化叶子结点
		(*p).weight = *w;
		(*p).parent = 0;
		(*p).lchild = 0;
		(*p).rchild = 0;
	}
	for (; i <= m; ++i, ++p)
	{//初始化剩余结点
		(*p).parent = 0;
		(*p).parent = 0;
		(*p).lchild = 0;
		(*p).rchild = 0;
	}

	for (i = n + 1; i <= m; ++i) // 建赫夫曼树
	{ // 在HT[1~i-1]中选择parent为0且weight最小的两个结点,其序号分别为s1和s2
		select(HT, i - 1, s1, s2);
		HT[s1].parent = HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	/*
	cout << "==========哈夫曼树每个结点的信息=========" << endl;
	cout << "HT\tweight\tparent\tlchild\trchild" << endl;
	for (int i = 1; i < 512; i++)
	{
		cout << "HT[" << i << "]" << "\t" << HT[i].weight << "\t" << HT[i].parent << "\t" << HT[i].lchild << "\t" << HT[i].rchild << endl;
	}
	cout << "=========================================" << endl;
	*/
	

	/*===============求哈夫曼编码========================*/
	unsigned c, cdlen;
	HC = (HuffmanCode)malloc((n + 1) * sizeof(char*));
	// 分配n个字符编码的头指针向量
	char *cd;
	cd = (char*)malloc(n * sizeof(char)); 
	c = m;
	cdlen = 0;

	for (i = 1; i <= m; ++i)
		HT[i].weight = 0; // 遍历赫夫曼树时用作结点状态标志
	while (c)
	{
		if (HT[c].weight == 0)
		{ // 向左
			HT[c].weight = 1;
			if (HT[c].lchild != 0)
			{
				c = HT[c].lchild;
				cd[cdlen++] = '0';
			}
			else if (HT[c].rchild == 0)
			{ // 登记叶子结点的字符的编码
				HC[c] = (char *)malloc((cdlen + 1) * sizeof(char));
				cd[cdlen] = '\0';
				strcpy(HC[c], cd); // 复制编码(串)
			}
		}
		else if (HT[c].weight == 1)
		{ // 向右
			HT[c].weight = 2;
			if (HT[c].rchild != 0)
			{
				c = HT[c].rchild;
				cd[cdlen++] = '1';
			}
		}
		else
		{ // HT[c].weight==2,退回
			HT[c].weight = 0;
			c = HT[c].parent;
			--cdlen; // 退到父结点,编码长度减1
		}
	}
	free(cd);
}

void select(HuffmanTree t, int i, int &s1, int &s2)
{ // s1为最小，s2为次小
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
{ // select()调用
	int j, s;
	int k = INT_MAX; // 取k为不小于可能的值
	for (j = 1; j <= i; j++)
		if (t[j].weight < k&&t[j].parent == 0)
		{
			k = t[j].weight; 
			s = j;
		}
	t[s].parent = 1;	//weight的值暂时修改，方便下次调用时选择次小的

	return s;
}
