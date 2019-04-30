#include"Graph.h"
struct Graph m_Graph;
void Init()
{//��ͼ���г�ʼ��
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
			m_Graph.m_aAdjMatrix[i][j] = 0;
	m_Graph.m_nVexNum = 0;
}

int InsertVex(Vex sVex)
{//��������ӵ�����������
	m_Graph.m_aVexs[m_Graph.m_nVexNum++] = sVex;
	return 0;
}

int InsertEdge(Edge sEdge)
{//���߱��浽������
	
	m_Graph.m_aAdjMatrix[sEdge.vex1][sEdge.vex2] = sEdge.weight;
	m_Graph.m_aAdjMatrix[sEdge.vex2][sEdge.vex1] = sEdge.weight;
	return 0;
}

Vex GetVex(int nVex)
{//��ѯ�������Ϣ
	return m_Graph.m_aVexs[nVex];
}

int FindEdge(int nVex, Edge aEdge[])
{//��ѯ��ָ�����������ı�
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
{//��ȡ��ǰ������
	return m_Graph.m_nVexNum;
}