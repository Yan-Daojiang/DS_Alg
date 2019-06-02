#pragma once
#include "global.h";
//ͼ  ���ݽṹ��

class CGraph
{
public:
	CGraph();
	~CGraph();

	typedef int Vertices[MAX_VERTEX_NUM];						//������������
	typedef bool AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];		//����������  ����


protected:

	Vertices m_Vertices;					//��������  һλ���飬������������Ϸ��ͼ�еĶ���
	AdjMatrix m_AdjMatrix;					//��ϵ����  ��λ���飬������������Ϸ�еĶ���ı�

	int m_nVexnum;		//������
	int m_nArcnum;		//����

public:

	//��ʼ��ͼ
	void InitGraph();

	//��Ӷ��㣬����ö������
	int AddVertex(int nInfo);

	//������ɱ�
	void AddArc(int nV1Index, int nV2Index);

	//��ȡ����������
	int GetVertex(int nIndex);

	//�����������ı���Ϣ
	bool GetArc(int nV1Index, int nV2Index);

	//���¶���,��ͼ����������������ΪNIndex�Ķ����ֵ����Ϊinfo
	void UpdateVertex(int nIndex, int info);

	//��ȡͼ�ж���ĸ���
	int GetVexnum();


};

