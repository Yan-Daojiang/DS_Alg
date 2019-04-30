#include"Graph.h"
struct Graph m_Graph;
void Init()
{//对图进行初始化
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
			m_Graph.m_aAdjMatrix[i][j] = 0;
	m_Graph.m_nVexNum = 0;
}

int InsertVex(Vex sVex)
{//将顶点添加到顶点数组中
	m_Graph.m_aVexs[m_Graph.m_nVexNum++] = sVex;
	return 0;
}

int InsertEdge(Edge sEdge)
{//将边保存到矩阵中
	
	m_Graph.m_aAdjMatrix[sEdge.vex1][sEdge.vex2] = sEdge.weight;
	m_Graph.m_aAdjMatrix[sEdge.vex2][sEdge.vex1] = sEdge.weight;
	return 0;
}

Vex GetVex(int nVex)
{//查询顶点的信息
	return m_Graph.m_aVexs[nVex];
}

int FindEdge(int nVex, Edge aEdge[])
{//查询与指定顶点相连的边
	{
		int k = 0;
		for (int i = 0; i < m_Graph.m_nVexNum; i++)
		{
			if (m_Graph.m_aAdjMatrix[nVex][i] != 0)
			{
				aEdge[k].vex1 = nVex;
				aEdge[k].vex2 = i;
				aEdge[k].weight = m_Graph.m_aAdjMatrix[nVex][i];
				k++;
			}

		}

		return k;
	}
}
int GetVexnum(void)
{//获取当前顶点数
	return m_Graph.m_nVexNum;
}