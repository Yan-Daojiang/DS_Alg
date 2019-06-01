#pragma once
#include "global.h";
#include "Graph.h";
class CGameLogic
{
public:
	CGameLogic();
	~CGameLogic();

protected:
	Vertex m_avPath[MAX_VERTEX_NUM];    //��������·������ʼ�㡢�յ㡢�յ�
	int m_anPath[MAX_VERTEX_NUM];		//�����ڽ��������ж�ʱ�������Ķ���
	int m_nCorner;						//����·���еĹյ���
	int m_nVexNum;						//��ʾ������

public:

	//��ʼ����Ϸ��ͼ
	void InitMap(CGraph &graph);

	//����ͼ�ıߵ����飬���±�
	void UpdateArc(CGraph &graph, int nRow, int nCol);

	//�����жϺ���
	bool IsLink(CGraph &graph, Vertex v1, Vertex v2);

	//���Ӻ���
	void Clear(CGraph &graph, Vertex v1, Vertex v2);


	//�ж�ѡ������������Ƿ���ͨ
	bool SearchPath(CGraph &graph, int nV0, int nV1);

	//�ж϶����Ƿ�����·���д���
	bool IsExsit(int nVi);

	//�жϹյ����Ч��
	bool IsCornor(void);

	//���һ��·������
	void PushVertex(int v);

	//ȡ��һ��·������
	void PopVertex();

	//�õ�·�������ص��Ƕ�����
	int GetVexPath(Vertex avPath[MAX_VERTEX_NUM]);

	////�ж�ͼ�ж����ǲ���ȫ�ǿ�
	bool IsBlank(CGraph &graph);

	//��ʾ�㷨��
	bool SearchValidPath(CGraph &graph);

	//ʵ��ͼ�ṹ������
	void ResetGraph(CGraph& graph);


};

