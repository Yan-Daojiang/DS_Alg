#ifndef GRAPH_H
#define GRAPH_H
#include<iostream>

struct Vex//����ṹ��
{
	int num;
	char name[20];
	char desc[1024];
};

struct Edge//�߽ṹ��
{
	int vex1;
	int vex2;
	int weight;
};

struct Graph {
	int m_aAdjMatrix[20][20];
	Vex m_aVexs[20];//��������
	int m_nVexNum;//�������
};//�洢�����ľ���ͼ

typedef struct Path {
	int vexs[20];//����һ��·��
	Path *next;//��һ��·��
}*PathList;

void Init();
int InsertVex(Vex sVex);
int InsertEdge(Edge sEdge);
Vex GetVex(int nVex);
int FindEdge(int nVex, Edge aEdge[]);
int GetVexnum(void);
void DFS(int nVex, bool bVisit[], int &nIndex, PathList &pList);
void DFSTraverse(int nVex, PathList &pList);
int FindShortPath(int nVexStart, int nVexEnd, Edge aPath[]);
int FindMinTree(Edge aPath[]);
#endif


