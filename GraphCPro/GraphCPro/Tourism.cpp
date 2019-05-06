#define _CRT_SECURE_NO_WARNINGS
#include"Tourism.h"
using namespace std;
extern Graph m_Graph;
void CreateGraph(void)
{
	//初始化图
	Init();
	//设置图的顶点
	//读取VEX.txt;
	FILE *pVex = fopen("Vex.txt", "r");
	if (!pVex){
		cout << "打开文件失败";
		return;
	}
	//读取景点数目数目
	int nSpotCout = 0;
	fscanf(pVex, "%d\n", &nSpotCout);
	cout << "顶点数目：" << nSpotCout << endl;
	//读取顶点信息
	cout << "-----顶点------" << endl;
	Vex sVex;
	while (fscanf(pVex, "%d\n%s\n%s\n", &sVex.num, sVex.name, sVex.desc) != -1){
		cout << sVex.num << "--" << sVex.name << endl;
		InsertVex(sVex);
	}
	fclose(pVex);
	pVex = NULL;

	//读取边
	FILE *pEdge = fopen("Edge.txt", "r");
	if (!pEdge){
		cerr << "打开文件失败";
		return;
	}
	Edge sEdge;

	while (fscanf(pEdge, "%d\t%d\t%d\n", &sEdge.vex1, &sEdge.vex2, &sEdge.weight) != -1){
		cout << "(" << sEdge.vex1 << "," << sEdge.vex2 << ")	" << sEdge.weight << endl;	
		InsertEdge(sEdge);
		if (InsertEdge(sEdge) == -1)cout << "插入失败" << endl;
	}	
}

void GetSpotInfo(void)
{
	cout << "--------查询景点信息--------" << endl;
	//显示景点列表
	int vexNum = GetVexnum();
	for (int i = 0; i < vexNum; i++){
		Vex sVex = GetVex(i);
		cout << sVex.num << "--" << sVex.name << endl;
	}
	//查询景点
	cout << "请输入您要查询的景点编号：";
	int nVex = 0;
	cin >> nVex;
	if (nVex < 0 || nVex >= vexNum){
		cout << "输入错误" << endl;
		return;
	}

	Vex sVex = GetVex(nVex);
	cout << "**简介**" << endl;
	cout << sVex.name << endl;
	cout << sVex.desc << endl;
	Edge sEdge[20];

	//查询附近景点
	cout << endl << "**周围景点**" << endl;
	int nEdgNum = FindEdge(nVex, sEdge);
	for (int i = 0; i < nEdgNum; i++)
	{
		Vex v1 = GetVex(sEdge[i].vex1);
		Vex v2 = GetVex(sEdge[i].vex2);
		cout << v1.name << "->" << v2.name << " " << sEdge[i].weight << endl << endl;
	}	
}

void TravelPath()
{//通过调用DFSTraverse()函数,将查询到的景点导航路线显示在界面上
	cout << "--------查询景点信息--------" << endl;

	//显示景点列表
	int vexNum = GetVexnum();
	for (int i = 0; i < vexNum; i++){
		Vex sVex = GetVex(i);
		cout << sVex.num << "--" << sVex.name << endl;
	}
	cout << "请输入开始编号:" << endl;
	int startNum;
	cin >> startNum;

	//从指定点开始的路径信息
	PathList pList = new Path;
	PathList pHead = pList;
	DFSTraverse(startNum, pList);
	pList = pHead;
	
	cout << "导游路线为:" << endl;
	int count = 1;    //记录路线的总数
	while (pList->next != NULL) {
		Vex curVex = GetVex(pList->vexs[0]);
		cout << "路线" << count << ":" << curVex.name;
		count++;
		for (int j = 1; j < m_Graph.m_nVexNum; j++) {
			curVex = GetVex(pList->vexs[j]);
			cout << "-->" << curVex.name;
		}
		cout << endl;
		pList = pList->next;
	}
}