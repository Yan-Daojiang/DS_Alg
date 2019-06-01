#pragma once
#include "global.h";
#include "Graph.h"

class CGameControl
{
public:
	CGameControl();
	~CGameControl();

protected:
	CGraph m_graph;			//��ʼ��Ϸ��ͼ
	Vertex m_ptSelFirst;	//��һ��ѡ�еĵ�(x��ʾ��)
	Vertex m_ptSelSec;		//�ڶ���ѡ�еĵ�

public:
	//��ʼ��Ϸ����
	void StartGame(void);

	//���ĳ��ĳ�е�ͼƬ��ź���
	int GetElement(int nRow, int nCol);

};

#pragma once
