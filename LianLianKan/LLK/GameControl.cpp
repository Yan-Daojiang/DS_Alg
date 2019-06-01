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
