#pragma once
#include "global.h"
#include "GameControl.h"
#include "GameLogic.h"

// CGameDlg �Ի���
class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = nullptr);   // ��׼���캯��
	virtual ~CGameDlg();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif

protected:
	CDC m_dcMem;			//�ڴ�DC
	CDC m_dcElm;			//Ԫ���ڴ�DC
	CDC m_dcMask;			//�����ڴ�DC
	CDC m_dcBG;				//����DC
	CDC m_dcCache;			//�ڸ���Ϸ��ͼ

	CPoint m_ptGameTop;		//��ʼ������
	CSize m_sizeElem;		//ͼƬԪ�ش�С
	CRect m_rtGameRect;     //��Ϸ����Ĵ�С

	bool m_bFirstPoint;		//ѡ�е�ͼƬ�ǲ��ǵ�һ��ѡ�еģ�TRUE   �ǣ�FALSE  ��
	Vertex m_ptSelFirst;	//��һ��ѡ�еĵ�(x��ʾ��)
	Vertex m_ptSelSec;		//�ڶ���ѡ�еĵ�

	CGameControl m_gameControl; //��Ϸ������

	bool m_bPlaying; //�Ƿ�������Ϸ
	

protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	void InitBackground();	//��ʼ������
	void InitElement();		//��ʼ��Ԫ��
	void UpdateWindow();		
	void UpdateMap();
	void DrawTipFrame(int nRow, int nCol);		//������Ϸ��ʾ��
	void DrawTipLine(Vertex avPath[MAX_VERTEX_NUM], int nVexnum);    //������ʾ��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnClickedButtonStart();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);		//������¼�
	CProgressCtrl m_GameProgress;
};
