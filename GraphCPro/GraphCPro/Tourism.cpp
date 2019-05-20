#define _CRT_SECURE_NO_WARNINGS
#include"Tourism.h"
using namespace std;
extern Graph m_Graph;
void CreateGraph(void)
{
	//��ʼ��ͼ
	Init();
	//����ͼ�Ķ���
	//��ȡVEX.txt;
	FILE *pVex = fopen("Vex.txt", "r");
	if (!pVex){
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
	while (fscanf(pVex, "%d\n%s\n%s\n", &sVex.num, sVex.name, sVex.desc) != -1){
		cout << sVex.num << "--" << sVex.name << endl;
		InsertVex(sVex);
	}
	fclose(pVex);
	pVex = NULL;

	//��ȡ��
	FILE *pEdge = fopen("Edge.txt", "r");
	if (!pEdge){
		cerr << "���ļ�ʧ��";
		return;
	}
	Edge sEdge;

	while (fscanf(pEdge, "%d\t%d\t%d\n", &sEdge.vex1, &sEdge.vex2, &sEdge.weight) != -1){
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
	for (int i = 0; i < vexNum; i++){
		Vex sVex = GetVex(i);
		cout << sVex.num << "--" << sVex.name << endl;
	}
	//��ѯ����
	cout << "��������Ҫ��ѯ�ľ����ţ�";
	int nVex = 0;
	cin >> nVex;
	if (nVex < 0 || nVex >= vexNum){
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

void TravelPath()
{//ͨ������DFSTraverse()����,����ѯ���ľ��㵼��·����ʾ�ڽ�����
	cout << "--------��ѯ������Ϣ--------" << endl;

	//��ʾ�����б�
	int vexNum = GetVexnum();
	for (int i = 0; i < vexNum; i++){
		Vex sVex = GetVex(i);
		cout << sVex.num << "--" << sVex.name << endl;
	}
	cout << "�����뿪ʼ���:" << endl;
	int startNum;
	cin >> startNum;

	//��ָ���㿪ʼ��·����Ϣ
	PathList pList = new Path;
	PathList pHead = pList;
	DFSTraverse(startNum, pList);
	pList = pHead;
	
	cout << "����·��Ϊ:" << endl;
	int count = 1;    //��¼·�ߵ�����
	while (pList->next != NULL) {
		Vex curVex = GetVex(pList->vexs[0]);
		cout << "·��" << count << ":" << curVex.name;
		count++;
		for (int j = 1; j < m_Graph.m_nVexNum; j++) {
			curVex = GetVex(pList->vexs[j]);
			cout << "-->" << curVex.name;
		}
		cout << endl;
		pList = pList->next;
	}
}

void FindShortPath(void)
{
	cout << "==========�������·��==========" << endl;
	int nVexNum = m_Graph.m_nVexNum;
	//��Ӧ��ϵ��ʾ	
	for (int i = 0; i < m_Graph.m_nVexNum; i++)
	{
		Vex sVex = GetVex(i);
		cout << i << "-" << sVex.name << endl;
	}

	int start_place, end_place;
	cout << "���������ı�ţ�";
	cin >> start_place;
	cout << "�������յ�ı�ţ�";
	cin >> end_place;

	Edge aPath[20];						//����Ϣ���飬���α�����̵�·��
	
	//�������·�����������·��������index��ֵ
	int index = FindShortPath(start_place, end_place, aPath);
	int length = 0;						//���·���ܳ���
	Vex sVex = GetVex(aPath[0].vex1);	//������Ϣ��������Ϣ��

	//�����·���������ʾ
	cout << "���·��Ϊ��" << sVex.name;
	for (int i = 0; i < index; i++) {
		sVex = GetVex(aPath[i].vex2);
		cout << "->" << sVex.name;
		length += aPath[i].weight;
	}
	cout << endl;
	cout << "��̾���Ϊ��" << length << endl << endl;;

}

void DesignPath(void)
{
	cout << "==========�����·�滮==========" << endl;
	Edge aPath[20];
	int length=FindMinTree(aPath);
	int nVexNum = m_Graph.m_nVexNum;
	cout << "��������������֮�������·��" << endl;
	for (int i = 0; i < m_Graph.m_nVexNum - 1; i++)
	{
		Vex nVex1 = GetVex(aPath[i].vex1);
		Vex nVex2 = GetVex(aPath[i].vex2);
		cout << nVex1.name << "-" << nVex2.name << "    " << aPath[i].weight << "m" << endl;
	}
	cout << "�����·���ܳ����ǣ�" <<length << "m" << endl;
}
