#include"Graph.h"
struct Graph m_Graph;

void Init()
{//��ͼ���г�ʼ��
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
			m_Graph.m_aAdjMatrix[i][j] = 0;
	m_Graph.m_nVexNum = 0;
}

int InsertVex(Vex sVex)
{//��������ӵ�����������
	m_Graph.m_aVexs[m_Graph.m_nVexNum++] = sVex;
	return 0;
}

int InsertEdge(Edge sEdge)
{//���߱��浽������
	m_Graph.m_aAdjMatrix[sEdge.vex1][sEdge.vex2] = sEdge.weight;
	m_Graph.m_aAdjMatrix[sEdge.vex2][sEdge.vex1] = sEdge.weight;
	return 0;
}

Vex GetVex(int nVex)
{//��ѯ�������Ϣ
	return m_Graph.m_aVexs[nVex];
}

int FindEdge(int nVex, Edge aEdge[])
{//��ѯ��ָ�����������ı�
	
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
{//��ȡ��ǰ������
	return m_Graph.m_nVexNum;
}

void DFSTraverse(int nVex, PathList &pList)
{//��������ı�ŵõ����ʵĽ��
	int nIndex = 0;
	bool bVisited[20] = { false };//�����ʱ�־����Ϊδ����״̬
	DFS(nVex, bVisited, nIndex, pList);
}

void DFS(int nVex, bool bVisited[], int &nIndex, PathList &pList)
{//�Ľ���ͼ��������ȱ����㷨
	bVisited[nVex] = true;				//��Ϊ�ѷ���
	pList->vexs[nIndex] = nVex;		//���ʶ���nVex����ֵ������Ȼ������ֵ�Լ�
	nIndex++;

	//����״̬�жϵõ���·���Ƿ�����									
	int countVisit = 0;
	for (int i = 0; i < m_Graph.m_nVexNum; i++){
		if (bVisited[i]==true)
			countVisit++;
	}
	if (countVisit == m_Graph.m_nVexNum){
		//����һ��·��
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
			//�������е��ڽӵ�
			if (!bVisited[i] && m_Graph.m_aAdjMatrix[nVex][i] > 0){
				DFS(i, bVisited, nIndex, pList);	//�ݹ����DFS
				bVisited[i] = false;	//����
				nIndex--;	//��ȼ�һ
			}
		}
	}
}

int FindShortPath(int nVexStart, int nVexEnd, Edge aPath[])
{//ʹ�õϽ�˹���������·��
	int nShortPath[20][20];       //�������·��
	int nShortDistance[20];       //������̾���
	bool aVisited[20];            //�ж�ĳ�����Ƿ��Ѿ����뵽���·����
	int v;                        //��ʾÿһ���ҵ��Ŀ��Լ��뼯�ϵĶ��㣬���Ѿ��ҵ��˴���㵽�ö�������·��
	//��ʼ����̾���������ľ���
	for (int v = 0; v < m_Graph.m_nVexNum; v++) {
		//���øõ��״̬
		aVisited[v] = false;
		if (m_Graph.m_aAdjMatrix[nVexStart][v] != 0) {
			nShortDistance[v] = m_Graph.m_aAdjMatrix[nVexStart][v];	    //�бߵ�ʱ��ֱ������Ϊ�ߵĳ���
		}
		else {
			nShortDistance[v] = INT_MAX;	//�ޱߵ�ʱ������Ϊ�������
		}
		nShortPath[v][0] = nVexStart;   //��ʼ��ΪnVexStart
		//��ʼ�����·��
		for (int w = 1; w < m_Graph.m_nVexNum; w++) {
			nShortPath[v][w] = -1;
		}
	}
	//��ʼ������nVexStart������뵽������
	aVisited[nVexStart] = true;
	int min;					//�ݴ�·������Сֵ
	for (int i = 1; i < m_Graph.m_nVexNum; i++)
	{
		min = 0x7FFFFFFF;
		bool bAdd = false;		//�ж��Ƿ��ж�����Լ��뼯��
		for (int w = 0; w < m_Graph.m_nVexNum; w++)
		{
			if (!aVisited[w] && nShortDistance[w] < min)
			{
				v = w;						//w�������nVexStart�������
				min = nShortDistance[w];	//w��nVexStart����̾���Ϊmin
				bAdd = true;
			}
		}
		//����û�ж�����Լ��뵽���ϣ�������ѭ��
		if (!bAdd) break;
		aVisited[v] = true;			//��w������뵽����
		nShortPath[v][i] = v;		//ÿ���ҵ����·���󣬾��൱�ڴ�Դ����������յ㣬����nShortPath[v][i]=v
		for (int w = 0; w < m_Graph.m_nVexNum; w++)
		{
			//��w��Ϊ���ɶ������nVexStartͨ��w��ÿ������ľ���
			if (!aVisited[w] && (min + m_Graph.m_aAdjMatrix[v][w] < nShortDistance[w]) && (m_Graph.m_aAdjMatrix[v][w] > 0))
			{
				//���µ�ǰ���·��������
				nShortDistance[w] = min + m_Graph.m_aAdjMatrix[v][w];
				for (int i = 0; i < m_Graph.m_nVexNum; i++) {
					//���ͨ��w�ﵽ����i�ľ���Ƚ϶̣���w�����·�����Ƹ�i
					nShortPath[w][i] = nShortPath[v][i];
				}
			}
		}
	}

	int nIndex = 0;
	int nVex1 = nVexStart;
	//�����·������Ϊ�ߵĽṹ������
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
{//ʹ������ķ�㷨����С������
	bool aVisited[20] = { false };		//�ж��Ƿ�ĳ��������뵽����������
	aVisited[0] = true;					//����0��ʼ
	int length = 0;
	int min;
	int nVex1, nVex2;
	int minTreeNum = m_Graph.m_nVexNum - 1;	//����õ���С�������ı���
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
		length += min;	//���³���
		//����ߵ���������
		aPath[k].vex1 = nVex1;
		aPath[k].vex2 = nVex2;
		aPath[k].weight = m_Graph.m_aAdjMatrix[nVex1][nVex2];
		//������������뼯��
		aVisited[nVex1] = true;
		aVisited[nVex2] = true;
	}
	return length;
}