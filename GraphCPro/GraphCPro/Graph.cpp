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
	bVisited[nVex] = true;				
	pList->vexs[nIndex] = nVex;		
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

int FindMinTree(Edge aPath[])
{//使用普林姆算法求最小生成树
	bool aVisited[20] = { false };		//判断是否将某个顶点加入到了生成树中
	aVisited[0] = true;					//顶点0开始
	int length = 0;
	int min;
	int nVex1, nVex2;
	int minTreeNum = m_Graph.m_nVexNum - 1;	//计算得到最小生成树的变数
	for (int k = 0; k < minTreeNum; k++) {
		min = INT16_MAX;
		for (int i = 0; i < m_Graph.m_nVexNum; i++) {
			if (aVisited[i]) {
				for (int j = 0; j < m_Graph.m_nVexNum; j++) {
					//点没有访问,有边同时这两点的距离要比之前循环得到的小就更新
					if (!aVisited[j] && m_Graph.m_aAdjMatrix[i][j] != 0 && m_Graph.m_aAdjMatrix[i][j] < min) {
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