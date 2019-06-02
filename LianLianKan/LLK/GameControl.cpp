#include "stdafx.h"
#include "GameControl.h"
#include "GameLogic.h"


CGameControl::CGameControl()
{
}


CGameControl::~CGameControl()
{
}

//开始游戏函数
void CGameControl::StartGame(void)
{
	CGameLogic gameLogic;
	gameLogic.InitMap(m_graph);

}

//获得某行某列的图片编号函数
int CGameControl::GetElement(int nRow, int nCol)
{
	return m_graph.GetVertex(nRow * MAX_COL + nCol);
}

//设置第一个点函数
void CGameControl::SetFirstPoint(int nRow, int nCol)
{
	m_ptSelFirst.row = nRow;
	m_ptSelFirst.col = nCol;
}

//设置第二个点函数
void CGameControl::SetSecPoint(int nRow, int nCol)
{
	m_ptSelSec.row = nRow;
	m_ptSelSec.col = nCol;
}

//消子判断   连接判断函数
bool CGameControl::Link(Vertex avPath[MAX_VERTEX_NUM], int & nVexnum)
{

	//判断选中的点是否为同一个图片，若为同一个图片，则不能连通
	if (m_ptSelFirst.row == m_ptSelSec.row && m_ptSelFirst.col == m_ptSelSec.col)
	{
		return false;
	}

	//判断图片是否相同，如果不同则不能连通
	int	nInfo1 = m_graph.GetVertex(m_ptSelFirst.row * MAX_COL + m_ptSelFirst.col);
	int	nInfo2 = m_graph.GetVertex(m_ptSelSec.row * MAX_COL + m_ptSelSec.col);

	if (nInfo1 != nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK)
	{
		return false;
	}

	//判断是否可以连通
	CGameLogic gameLogic;
	if (gameLogic.IsLink(m_graph, m_ptSelFirst, m_ptSelSec) == true)
	{
		//消子
		gameLogic.Clear(m_graph, m_ptSelFirst, m_ptSelSec);


		//返回路径顶点
		nVexnum = gameLogic.GetVexPath(avPath);
		return true;
	}

	return false;
}

