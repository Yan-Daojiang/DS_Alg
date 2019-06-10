#include "StdAfx.h"
#include "GameLogic.h"
#include "global.h"

CGameLogic::CGameLogic(void)
{
	m_nVexNum = 0;     //������ʵ��Ԫ�صĸ���
	m_nCorner = 0;     //·���еĹյ���
}


CGameLogic::~CGameLogic(void)
{
}

//��ʼ����Ϸ��ͼ
void CGameLogic::InitMap(CGraph &graph)
{
	//��Ϸ��ͼ��ʼ�����̶���ֵ
	//int anTemp[4][4] = { 2, 0, 1, 3, 2, 2, 1, 3, 2, 1, 0, 0, 1, 3, 0, 3 };
	//������ɵ�ͼ
	int anTemp[MAX_VERTEX_NUM];
	//���ٻ�ɫ
	for (int i = 0; i < MAX_PIC_NUM; i++)
	{
		//�ظ���
		for (int j = 0; j < REPEAT_NUM; j++)
		{
			anTemp[i * REPEAT_NUM + j] = i;
		}
	}
	//��������
	srand((int)time(NULL));

	//������⽻����������
	for (int i = 0; i < 300; i++)
	{
		//����õ���������
		int nIndex1 = rand() % MAX_VERTEX_NUM;
		int nIndex2 = rand() % MAX_VERTEX_NUM;

		//����������ֵ
		int nTemp = anTemp[nIndex1];
		anTemp[nIndex1] = anTemp[nIndex2];
		anTemp[nIndex2] = nTemp;
	}

	//��ʼ������
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		graph.AddVertex(anTemp[i]);
	}

	//���»���Ϣ
	for (int i = 0; i < MAX_ROW; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			UpdateArc(graph, i, j);
		}
	}
}

//�����жϺ���
bool CGameLogic::IsLink(CGraph &graph, Vertex v1, Vertex v2)
{
	//��ö���������
	int nV1Index = v1.row * MAX_COL + v1.col;
	int nV2Index = v2.row * MAX_COL + v2.col;

	PushVertex(nV1Index);  //ѹ���һ����

	//��Ѱ����֮�����ͨ·��
	if (SearchPath(graph, nV1Index, nV2Index) == true)
	{
		return true;
	}

	PopVertex();

	/*�޸��ж���Ȧ������*/

	if (v1.row == v2.row) {
		if (v1.row == 0 || v1.row == MAX_ROW - 1) {
			return true;
		}
	}

	if (v1.col == v2.col) {
		if (v1.col == 0 || v1.col == MAX_COL - 1) {
			return true;
		}
	}
	return false;
}


//���һ��·������
void CGameLogic::PushVertex(int nV)
{
	//������ѹջ
	m_anPath[m_nVexNum] = nV;
	m_nVexNum++;

	//�ж��Ƿ��γ��µĹյ�
	if (IsCornor())
	{
		m_nCorner++;
	}
}

//ȡ��һ��·������
void CGameLogic::PopVertex()
{
	//�ж��Ƿ��γɹյ㣬������ڹյ㣬��ȡ��֮ǰ���ٹյ���
	if (IsCornor())
	{
		m_nCorner--;
	}
	m_nVexNum--;
}

//�õ�·�������ص��Ƕ�����
int CGameLogic::GetVexPath(Vertex avPath[MAX_VERTEX_NUM])
{
	Vertex point;
	for (int i = 0; i < m_nVexNum; i++)
		for (point.col = 0; point.col < MAX_COL; point.col++)
		{
			for (point.row = 0; point.row < MAX_ROW; point.row++)
			{
				if (point.row * MAX_COL + point.col == m_anPath[i])
				{
					avPath[i] = point;
				}
			}
		}
	return m_nVexNum;
}

//���Ӻ���
void CGameLogic::Clear(CGraph &graph, Vertex v1, Vertex v2)
{
	//��ö���������
	int nV1Index = v1.row * MAX_COL + v1.col;
	int nV2Index = v2.row * MAX_COL + v2.col;

	//���¶���
	graph.UpdateVertex(nV1Index, BLANK);
	graph.UpdateVertex(nV2Index, BLANK);

	//���±���Ϣ
	UpdateArc(graph, v1.row, v1.col);
	UpdateArc(graph, v2.row, v2.col);
}

//����ͼ������
void CGameLogic::UpdateArc(CGraph &graph, int nRow, int nCol)
{
	int nV1Index = nRow * MAX_COL + nCol;
	if (nCol > 0)   //�������
	{
		int nV2Index = nV1Index - 1;
		int nV1Info = graph.GetVertex(nV1Index);
		int nV2Info = graph.GetVertex(nV2Index);

		//�ж���������ڵ��Ƿ��й�ϵ
		if (nV1Info == nV2Info || nV1Info == BLANK || nV2Info == BLANK)
		{
			graph.AddArc(nV1Index, nV2Index);
		}
	}
	if (nCol < MAX_COL - 1)   //�ұ�����
	{
		int nV2Index = nV1Index + 1;
		int nV1Info = graph.GetVertex(nV1Index);
		int nV2Info = graph.GetVertex(nV2Index);

		//�ж����ұ����ڵ��Ƿ��й�ϵ
		if (nV1Info == nV2Info || nV1Info == BLANK || nV2Info == BLANK)
		{
			graph.AddArc(nV1Index, nV2Index);
		}
	}
	if (nRow > 0)   //���Ϸ�����
	{
		int nV2Index = nV1Index - MAX_COL;
		int nV1Info = graph.GetVertex(nV1Index);
		int nV2Info = graph.GetVertex(nV2Index);

		//�ж������Ϸ����Ƿ��й�ϵ
		if (nV1Info == nV2Info || nV1Info == BLANK || nV2Info == BLANK)
		{
			graph.AddArc(nV1Index, nV2Index);
		}
	}
	if (nRow < MAX_ROW - 1)   //���·�����
	{
		int nV2Index = nV1Index + MAX_COL;
		int nV1Info = graph.GetVertex(nV1Index);
		int nV2Info = graph.GetVertex(nV2Index);

		//�ж������·����Ƿ��й�ϵ
		if (nV1Info == nV2Info || nV1Info == BLANK || nV2Info == BLANK)
		{
			graph.AddArc(nV1Index, nV2Index);
		}
	}
}

//ʹ�����������������Ѱһ����Ч��ͨ·��
bool CGameLogic::SearchPath(CGraph &graph, int nV0, int nV1)
{
	//�õ�������
	int nVexnum = graph.GetVexnum();

	//����ͼ��nV0�У���0�е�nVexnum�У�ֵΪtrue�ĵ�
	for (int nVi = 0; nVi < nVexnum; nVi++)
	{
		if (graph.GetArc(nV0, nVi) && !IsExsit(nVi))
		{
			//ѹ�뵱ǰ���㣬����Ϊ·����һ����Ч����
			PushVertex(nVi);
			//���յ�������2 ʱ��ֱ�ӷ����ö���
			if (m_nCorner > 2)
			{
				PopVertex();          //ȡ��ѹ��Ķ��㣬��PushWertex(nVi)��Ӧ
				continue;
			}
			//��ǰ���㲻��nViʱ��������Ѱ��һ����������ͨ�Ķ���
			if (nVi != nV1)
			{
				//���м䶥�㲻Ϊ��ʱ����ʾ����·����ͨ
				if (graph.GetVertex(nVi) != BLANK)
				{
					PopVertex();      //ȡ��ѹ��Ķ��㣬��PushWertex(nVi)��Ӧ
					continue;
				}
				//���nVi��һ���������ĵ㣬���жϣ�nVi��nV1���Ƿ���ͨ
				if (SearchPath(graph, nVi, nV1))
				{
					//SearchPath(garph, nVi, nV1) == true,��ʾ�Ѿ��ҵ�һ����ͨ·�����򷵻�true
					return true;
				}
			}
			else
			{
				return true;
			}

			PopVertex();     //ȡ��ѹ��Ķ��㣬��PushWertex(nVi)��Ӧ
		}
	}
	return false;
}

//�ж϶����Ƿ�����·���д���
bool CGameLogic::IsExsit(int nVi)
{
	for (int i = 0; i < m_nVexNum; i++)
	{
		if (m_anPath[i] == nVi)
		{
			return true;
		}
	}
	return false;
}

//�жϹյ����Ч��
bool CGameLogic::IsCornor(void)
{
	if (m_nVexNum >= 3)
	{
		if ((m_anPath[m_nVexNum - 1] + m_anPath[m_nVexNum - 3]) / 2 != m_anPath[m_nVexNum - 2])
		{
			return true;
		}
	}
	return false;
}

//�ж�ͼ�ж����ǲ���Ϊ��
bool CGameLogic::IsBlank(CGraph &graph)
{
	int nVexnum = graph.GetVexnum();
	for (int i = 0; i < nVexnum; i++)
	{
		if (graph.GetVertex(i) != BLANK)
		{
			return false;
		}
	}
	return true;
}

bool CGameLogic::SearchValidPath(CGraph& graph)
{
	//�õ�������
	int nVexnum = graph.GetVexnum();
	for (int i = 0; i < nVexnum; i++)
	{
		//�õ���һ���ǿն���
		if (graph.GetVertex(i) == BLANK)
		{
			continue;
		}
		//�����õ��ڶ���ͬɫ����
		for (int j = 0; j < nVexnum; j++)
		{
			if (i != j)
			{
				//�����i����͵�j����ͬɫ
				if (graph.GetVertex(i) == graph.GetVertex(j))
				{
					//ѹ���һ����
					PushVertex(i);
					if (SearchPath(graph, i, j) == true)
					{
						return true;
					}
					//ȡ��ѹ��Ķ���ʱ����PushVertex(i);��Ӧ
					PopVertex();
				}

			}
		}
	}
	return false;
}

//ʵ��ͼ�ṹ������
void CGameLogic::ResetGraph(CGraph& graph)
{
	//��������������������������ֵ
	for (int i = 0; i < 200; i++)
	{
		//����õ���������
		int nIndex1 = rand() % MAX_VERTEX_NUM;
		int nIndex2 = rand() % MAX_VERTEX_NUM;

		//����������ֵ
		graph.ChangeVerex(nIndex1, nIndex2);
	}

	//���»���Ϣ
	for (int i = 0; i < MAX_ROW; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			UpdateArc(graph, i, j);
		}
	}

}
