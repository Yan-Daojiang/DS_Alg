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

	void SetFirstPoint(int nRow, int nCol);             //���õ�һ���㺯��
	void SetSecPoint(int nRow, int nCol);               //���õڶ����㺯��

	//�����жϺ���
	bool Link(Vertex avPath[MAX_VERTEX_NUM], int &nVexnum);

	//��ʤ   //�����ʱ���ܺ��������޸�
	//bool IsWin();
	bool IsWin(int nTime);

	//��������ʾ����
	bool Help(Vertex avPath[MAX_VERTEX_NUM], int &nVexnum);

	//ʵ�����Ź���
	void Reset(void);



};

