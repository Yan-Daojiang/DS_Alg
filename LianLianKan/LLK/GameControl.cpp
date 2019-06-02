#include "stdafx.h"
#include "GameControl.h"
#include "GameLogic.h"


CGameControl::CGameControl()
{
}


CGameControl::~CGameControl()
{
}

//��ʼ��Ϸ����
void CGameControl::StartGame(void)
{
	CGameLogic gameLogic;
	gameLogic.InitMap(m_graph);

}

//���ĳ��ĳ�е�ͼƬ��ź���
int CGameControl::GetElement(int nRow, int nCol)
{
	return m_graph.GetVertex(nRow * MAX_COL + nCol);
}

//���õ�һ���㺯��
void CGameControl::SetFirstPoint(int nRow, int nCol)
{
	m_ptSelFirst.row = nRow;
	m_ptSelFirst.col = nCol;
}

//���õڶ����㺯��
void CGameControl::SetSecPoint(int nRow, int nCol)
{
	m_ptSelSec.row = nRow;
	m_ptSelSec.col = nCol;
}

//�����ж�   �����жϺ���
bool CGameControl::Link(Vertex avPath[MAX_VERTEX_NUM], int & nVexnum)
{

	//�ж�ѡ�еĵ��Ƿ�Ϊͬһ��ͼƬ����Ϊͬһ��ͼƬ��������ͨ
	if (m_ptSelFirst.row == m_ptSelSec.row && m_ptSelFirst.col == m_ptSelSec.col)
	{
		return false;
	}

	//�ж�ͼƬ�Ƿ���ͬ�������ͬ������ͨ
	int	nInfo1 = m_graph.GetVertex(m_ptSelFirst.row * MAX_COL + m_ptSelFirst.col);
	int	nInfo2 = m_graph.GetVertex(m_ptSelSec.row * MAX_COL + m_ptSelSec.col);

	if (nInfo1 != nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK)
	{
		return false;
	}

	//�ж��Ƿ������ͨ
	CGameLogic gameLogic;
	if (gameLogic.IsLink(m_graph, m_ptSelFirst, m_ptSelSec) == true)
	{
		//����
		gameLogic.Clear(m_graph, m_ptSelFirst, m_ptSelSec);


		//����·������
		nVexnum = gameLogic.GetVexPath(avPath);
		return true;
	}

	return false;
}

