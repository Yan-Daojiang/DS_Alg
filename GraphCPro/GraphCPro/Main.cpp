#include<iostream>
#include"Tourism.h"
using namespace std;

void doChoose();
void output();

int main()
{
	
	cout << "================��ӭ������������ϵͳ=============" << endl;
	cout << "!!!!!!!!!!!!!��ȷ���������в����ڽ���ͼ�����!!!!!!!!!!!!!!!!" << endl;
	doChoose();
	system("pause");
	return 0;
}

void doChoose()
{
	int nSection = -1;
	do {
		output();//չʾ�˵�
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
	cout << "1.��������ͼ" << endl;
	cout << "2.��ѯ������Ϣ" << endl;
	cout << "3.���ξ��㵼��" << endl;
	cout << "4.���·������" << endl;
	cout << "5.�����·�滮" << endl;
	cout << "0.�˳�" << endl;
	cout << "����������ѡ��:";
}