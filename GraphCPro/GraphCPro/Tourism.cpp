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

void FindShortPath(void)
{
	cout << "==========搜索最短路径==========" << endl;
	int nVexNum = m_Graph.m_nVexNum;
	//对应关系显示	
	for (int i = 0; i < m_Graph.m_nVexNum; i++)
	{
		Vex sVex = GetVex(i);
		cout << i << "-" << sVex.name << endl;
	}

	int start_place, end_place;
	cout << "请输入起点的编号：";
	cin >> start_place;
	cout << "请输入终点的编号：";
	cin >> end_place;

	Edge aPath[20];						//边信息数组，依次保存最短的路径
	
	//查找最短路径，并给最短路径的条数index赋值
	int index = FindShortPath(start_place, end_place, aPath);
	int length = 0;						//最短路径总长度
	Vex sVex = GetVex(aPath[0].vex1);	//顶点信息（景点信息）

	//将最短路径输出，显示
	cout << "最短路径为：" << sVex.name;
	for (int i = 0; i < index; i++) {
		sVex = GetVex(aPath[i].vex2);
		cout << "->" << sVex.name;
		length += aPath[i].weight;
	}
	cout << endl;
	cout << "最短距离为：" << length << endl << endl;;

}

void DesignPath(void)
{
	cout << "==========铺设电路规划==========" << endl;
	Edge aPath[20];
	int length=FindMinTree(aPath);
	int nVexNum = m_Graph.m_nVexNum;
	cout << "在以下两个景点之间铺设电路：" << endl;
	for (int i = 0; i < m_Graph.m_nVexNum - 1; i++)
	{
		Vex nVex1 = GetVex(aPath[i].vex1);
		Vex nVex2 = GetVex(aPath[i].vex2);
		cout << nVex1.name << "-" << nVex2.name << "    " << aPath[i].weight << "m" << endl;
	}
	cout << "铺设电路的总长度是：" <<length << "m" << endl;
}
