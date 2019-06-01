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
	CGameControl m_gameControl; //��Ϸ������


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	void InitBackground();	//��ʼ������
	void InitElement();		//��ʼ��Ԫ��
	void UpdateWindow();		//
	void UpdateMap();

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();

	afx_msg void OnClickedButtonStart();
	
	CProgressCtrl m_GameProgress;
	
};
