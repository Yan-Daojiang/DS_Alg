#include"Graph.h"
struct Graph m_Graph;

void Init()
{//对图进行初始化
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
			m_Graph.m_aAdjMatrix[i][j] = 0;
	m_Graph.m_nVexNum = 0;
}

int InsertVex(Vex sVex)
{//将顶点添加到顶点数组中
	m_Graph.m_aVexs[m_Graph.m_nVexNum++] = sVex;
	return 0;
}

int InsertEdge(Edge sEdge)
{//将边保存到矩阵中
	m_Graph.m_aAdjMatrix[sEdge.vex1][sEdge.vex2] = sEdge.weight;
	m_Graph.m_aAdjMatrix[sEdge.vex2][sEdge.vex1] = sEdge.weight;
	return 0;
}

Vex GetVex(int nVex)
{//查询顶点的信息
	return m_Graph.m_aVexs[nVex];
}

int FindEdge(int nVex, Edge aEdge[])
{//查询与指定顶点相连的边
	
	int k = 0;
	for (int i = 0; i < m_Graph.m_nVexNum; i++){
		if (m_Graph.m_aAdjMatrix[nVex][i] != 0){
			aEdge[k].vex1 = nVex;
			aEdge[k].vex2 = i;
			aEdge[k].weight = m_Graph.m_aAdjMatrix[nVex][i];
			k++;
		}

	}
	return k;
}

int GetVexnum(void)
{//获取当前顶点数
	return m_Graph.m_nVexNum;
}

void DFSTraverse(int nVex, PathList &pList)
{//根据输入的编号得到访问的结果
	int nIndex = 0;
	bool bVisited[20] = { false };//将访问标志设置为未访问状态
	DFS(nVex, bVisited, nIndex, pList);
}

void DFS(int nVex, bool bVisited[], int &nIndex, PathList &pList)
{//改进的图的深度优先遍历算法
	bVisited[nVex] = true;				//改为已访问
	pList->vexs[nIndex] = nVex;		//访问顶点nVex并赋值给链表，然后索引值自加
	nIndex++;

	//根据状态判断得到的路径是否完整									
	int countVisit = 0;
	for (int i = 0; i < m_Graph.m_nVexNum; i++){
		if (bVisited[i]==true)
			countVisit++;
	}
	if (countVisit == m_Graph.m_nVexNum){
		//保存一条路径
		pList->next = new Path;
		for (int i = 0; i < m_Graph.m_nVexNum; i++)
		{
			pList->next->vexs[i] = pList->vexs[i];
		}
		pList = pList->next;		
		pList->next = NULL;			
	}
	else{
		for (int i = 0; i < m_Graph.m_nVexNum; i++){
			//搜索所有的邻接点
			if (!bVisited[i] && m_Graph.m_aAdjMatrix[nVex][i] > 0){
				DFS(i, bVisited, nIndex, pList);	//递归调用DFS
				bVisited[i] = false;	//回退
				nIndex--;	//深度减一
			}
		}
	}
}

int FindShortPath(int nVexStart, int nVexEnd, Edge aPath[])
{//使用迪杰斯特拉求最短路径
	int nShortPath[20][20];       //保存最短路径
	int nShortDistance[20];       //保存最短距离
	bool aVisited[20];            //判断某顶点是否已经加入到最短路径中
	int v;                        //表示每一次找到的可以加入集合的顶点，即已经找到了从起点到该顶点的最短路径
	//初始化最短距离和两点间的距离
	for (int v = 0; v < m_Graph.m_nVexNum; v++) {
		//设置该点的状态
		aVisited[v] = false;
		if (m_Graph.m_aAdjMatrix[nVexStart][v] != 0) {
			nShortDistance[v] = m_Graph.m_aAdjMatrix[nVexStart][v];	    //有边的时候直接设置为边的长度
		}
		else {
			nShortDistance[v] = INT_MAX;	//无边的时候设置为最大整数
		}
		nShortPath[v][0] = nVexStart;   //起始点为nVexStart
		//初始化最短路径
		for (int w = 1; w < m_Graph.m_nVexNum; w++) {
			nShortPath[v][w] = -1;
		}
	}
	//初始化，将nVexStart顶点加入到集合中
	aVisited[nVexStart] = true;
	int min;					//暂存路径的最小值
	for (int i = 1; i < m_Graph.m_nVexNum; i++)
	{
		min = 0x7FFFFFFF;
		bool bAdd = false;		//判断是否还有顶点可以加入集合
		for (int w = 0; w < m_Graph.m_nVexNum; w++)
		{
			if (!aVisited[w] && nShortDistance[w] < min)
			{
				v = w;						//w顶点距离nVexStart顶点最近
				min = nShortDistance[w];	//w到nVexStart的最短距离为min
				bAdd = true;
			}
		}
		//若果没有顶点可以加入到集合，则跳出循环
		if (!bAdd) break;
		aVisited[v] = true;			//将w顶点加入到集合
		nShortPath[v][i] = v;		//每次找到最短路径后，就相当于从源点出发到了终点，所以nShortPath[v][i]=v
		for (int w = 0; w < m_Graph.m_nVexNum; w++)
		{
			//将w作为过渡顶点计算nVexStart通过w到每个顶点的距离
			if (!aVisited[w] && (min + m_Graph.m_aAdjMatrix[v][w] < nShortDistance[w]) && (m_Graph.m_aAdjMatrix[v][w] > 0))
			{
				//更新当前最短路径及距离
				nShortDistance[w] = min + m_Graph.m_aAdjMatrix[v][w];
				for (int i = 0; i < m_Graph.m_nVexNum; i++) {
					//如果通过w达到顶点i的距离比较短，则将w的最短路径复制给i
					nShortPath[w][i] = nShortPath[v][i];
				}
			}
		}
	}

	int nIndex = 0;
	int nVex1 = nVexStart;
	//将最短路径保存为边的结构体数组
	for (int i = 1; i < m_Graph.m_nVexNum; i++)
	{
		if (nShortPath[nVexEnd][i] != -1)
		{
			aPath[nIndex].vex1 = nVex1;
			aPath[nIndex].vex2 = nShortPath[nVexEnd][i];
			aPath[nIndex].weight = m_Graph.m_aAdjMatrix[nVex1][aPath[nIndex].vex2];
			nVex1 = nShortPath[nVexEnd][i];
			nIndex++;
		}
	}

	return nIndex;
}

int FindMinTree(Edge aPath[])
{//使用普林姆算法求最小生成树
	bool aVisited[20] = { false };		//判断是否将某个顶点加入到了生成树中
	aVisited[0] = true;					//顶点0开始
	int length = 0;
	int min;
	int nVex1, nVex2;
	int minTreeNum = m_Graph.m_nVexNum - 1;	//计算得到最小生成树的边数
	for (int k = 0; k < minTreeNum; k++) {
		min = INT16_MAX;	
		for (int i = 0; i < m_Graph.m_nVexNum; i++) {
			if (aVisited[i]) {
				for (int j = 0; j < m_Graph.m_nVexNum; j++) {
					if (!aVisited[j]&&m_Graph.m_aAdjMatrix[i][j]!=0&&m_Graph.m_aAdjMatrix[i][j]<min) {
						nVex1 = i;
						nVex2 = j;
						min = m_Graph.m_aAdjMatrix[nVex1][nVex2];
					}
				}
			}
		}
		length += min;	//更新长度
		//保存边的两个顶点
		aPath[k].vex1 = nVex1;
		aPath[k].vex2 = nVex2;
		aPath[k].weight = m_Graph.m_aAdjMatrix[nVex1][nVex2];
		//将两个顶点加入集合
		aVisited[nVex1] = true;
		aVisited[nVex2] = true;
	}
	return length;
}