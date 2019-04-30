#ifndef GRAPH_H
#define GRAPH_H
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


void Init();
int InsertVex(Vex sVex);
int InsertEdge(Edge sEdge);
Vex GetVex(int nVex);
int FindEdge(int nVex, Edge aEdge[]);
int GetVexnum(void);
#endif


