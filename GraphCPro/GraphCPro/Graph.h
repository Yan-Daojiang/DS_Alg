#ifndef GRAPH_H
#define GRAPH_H
struct Vex//顶点结构体
{
	int num;
	char name[20];
	char desc[1024];
};
struct Edge//边结构体
{
	int vex1;
	int vex2;
	int weight;
};

struct Graph {
	int m_aAdjMatrix[20][20];
	Vex m_aVexs[20];//定点数组
	int m_nVexNum;//定点个数
};//存储景区的景点图


void Init();
int InsertVex(Vex sVex);
int InsertEdge(Edge sEdge);
Vex GetVex(int nVex);
int FindEdge(int nVex, Edge aEdge[]);
int GetVexnum(void);
#endif


