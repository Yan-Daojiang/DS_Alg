#define _CRT_SECURE_NO_WARNINGS
#include"Tourism.h"
using namespace std;

void CreateGraph(void)
{
	//��ʼ��ͼ
	Init();
	//����ͼ�Ķ���
	//��ȡVEX.txt;
	FILE *pVex = fopen("Vex.txt", "r");
	if (!pVex)
	{
		cout << "���ļ�ʧ��";
		return;
	}
	//��ȡ������Ŀ��Ŀ
	int nSpotCout = 0;
	fscanf(pVex, "%d\n", &nSpotCout);
	cout << "������Ŀ��" << nSpotCout << endl;
	//��ȡ������Ϣ
	cout << "-----����------" << endl;
	Vex sVex;
	while (fscanf(pVex, "%d\n%s\n%s\n", &sVex.num, sVex.name, sVex.desc) != -1)
	{
		cout << sVex.num << "--" << sVex.name << endl;
		InsertVex(sVex);
	}
	fclose(pVex);
	pVex = NULL;

	//��ȡ��
	FILE *pEdge = fopen("Edge.txt", "r");
	if (!pEdge)
	{
		cerr << "���ļ�ʧ��";
		return;
	}
	Edge sEdge;

	while (fscanf(pEdge, "%d\t%d\t%d\n", &sEdge.vex1, &sEdge.vex2, &sEdge.weight) != -1)
	{
		cout << "(" << sEdge.vex1 << "," << sEdge.vex2 << ")	" << sEdge.weight << endl;	
		InsertEdge(sEdge);
		if (InsertEdge(sEdge) == -1)cout << "����ʧ��" << endl;
	}	
}


void GetSpotInfo(void)
{
	cout << "--------��ѯ������Ϣ--------" << endl;

	//��ʾ�����б�
	int vexNum = GetVexnum();
	for (int i = 0; i < vexNum; i++)
	{
		Vex sVex = GetVex(i);
		cout << sVex.num << "--" << sVex.name << endl;
	}

	//��ѯ����
	cout << "��������Ҫ��ѯ�ľ����ţ�";
	int nVex = 0;
	cin >> nVex;
	if (nVex < 0 || nVex >= vexNum)
	{
		cout << "�������" << endl;
		return;
	}

	Vex sVex = GetVex(nVex);
	cout << "**���**" << endl;
	cout << sVex.name << endl;
	cout << sVex.desc << endl;

	Edge sEdge[20];

	//��ѯ��������
	cout << endl << "**��Χ����**" << endl;
	int nEdgNum = FindEdge(nVex, sEdge);
	for (int i = 0; i < nEdgNum; i++)
	{
		Vex v1 = GetVex(sEdge[i].vex1);
		Vex v2 = GetVex(sEdge[i].vex2);
		cout << v1.name << "->" << v2.name << " " << sEdge[i].weight << endl << endl;
	}	
}