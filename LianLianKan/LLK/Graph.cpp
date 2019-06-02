#include "stdafx.h"
#include "Graph.h"

CGraph::CGraph()
{
	InitGraph();   //��ʼ��ͼ
}


CGraph::~CGraph()
{
}

//��ʼ��ͼ
void CGraph::InitGraph()
{
	m_nArcnum = 0;
	m_nVexnum = 0;

	//��ʼ�����������Ϣ
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		//��ʼ������
		m_Vertices[i] = -1;
	}

	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		for (int j = 0; j < MAX_VERTEX_NUM; j++) {
			//��ʼ����
			m_AdjMatrix[i][j] = false;
		}
	}

}

//��Ӷ��㣬����ö������
int CGraph::AddVertex(int nInfo)
{
	// TODO: �ڴ˴����ʵ�ִ���.
	if (m_nVexnum >= MAX_VERTEX_NUM) {
		return 0;
	}
	m_Vertices[m_nVexnum] = nInfo;
	m_nVexnum++;
	return m_nVexnum;
}

//���ɱ�  ��ʼ����   �ڽӾ���
void CGraph::AddArc(int nV1Index, int nV2Index)
{
	m_AdjMatrix[nV1Index][nV2Index] = true;
	m_AdjMatrix[nV2Index][nV1Index] = true;
}

//�Ӷ���������ȡ����Ӧ�Ķ���
int CGraph::GetVertex(int nIndex)
{
	return m_Vertices[nIndex];
}

//�����������Ļ���Ϣ
bool CGraph::GetArc(int nV1Index, int nV2Index)
{
	return m_AdjMatrix[nV1Index][nV2Index];
}

//��Ҫ��ȥ�Ķ����ͼ����ΪBLANK��-1��
void CGraph::UpdateVertex(int nIndex, int info)
{
	m_Vertices[nIndex] = info;
}

//��ȡͼ�ж���ĸ���
int CGraph::GetVexnum()
{
	return m_nVexnum;
}


