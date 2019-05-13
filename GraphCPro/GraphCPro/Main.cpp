#include<iostream>
#include"Tourism.h"
using namespace std;

void doChoose();
void output();

int main()
{
	
	cout << "================欢迎来到景区管理系统=============" << endl;
	cout << "!!!!!!!!!!!!!请确保您的所有操作在建立图后进行!!!!!!!!!!!!!!!!" << endl;
	doChoose();
	system("pause");
	return 0;
}

void doChoose()
{
	int nSection = -1;
	do {
		output();//展示菜单
		nSection = -1;
		cin >> nSection;
		switch (nSection){
		case 1:{
			CreateGraph();
			break;
		}
		case 2:{
			GetSpotInfo();
			break;
		}
		case 3:{
			TravelPath();
			break;
		}
		case 5: {
			DesignPath();
			break;
		}
		default:
			break;
		}
	} while (nSection != 0);
}

void output()
{
	cout << "****************************************" << endl;
	cout << "1.创建景点图" << endl;
	cout << "2.查询景点信息" << endl;
	cout << "3.旅游景点导航" << endl;
	cout << "4.最短路径搜索" << endl;
	cout << "5.铺设电路规划" << endl;
	cout << "0.退出" << endl;
	cout << "请输入您的选择:";
}