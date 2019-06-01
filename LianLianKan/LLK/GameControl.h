#pragma once
#include "global.h";
#include "Graph.h"

class CGameControl
{
public:
	CGameControl();
	~CGameControl();

protected:
	CGraph m_graph;			//初始游戏地图
	Vertex m_ptSelFirst;	//第一次选中的点(x表示列)
	Vertex m_ptSelSec;		//第二次选中的点

public:
	//开始游戏函数
	void StartGame(void);

	//获得某行某列的图片编号函数
	int GetElement(int nRow, int nCol);

};

#pragma once
