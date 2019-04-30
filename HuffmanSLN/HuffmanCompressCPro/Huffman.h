#pragma once
#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_
#include<cstring>
#include<cstdlib>

struct HTNode {

	int weight;
	int parent;
	int lchild;
	int rchild;
};

typedef HTNode *HuffmanTree;
typedef char **HuffmanCode;

void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n);
void select(HuffmanTree t, int i, int &s1, int &s2);
int min(HuffmanTree t, int i);

#endif