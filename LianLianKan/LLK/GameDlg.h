#pragma once
#include "global.h"
#include "GameControl.h"
#include "GameLogic.h"

// CGameDlg 对话框

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGameDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif

protected:


	CDC m_dcMem;			//内存DC
	CDC m_dcElm;			//元素内存DC
	CDC m_dcMask;			//掩码内存DC
	CDC m_dcBG;				//背景DC
	CDC m_dcCache;			//掩盖游戏地图

	CPoint m_ptGameTop;		//起始点坐标
	CSize m_sizeElem;		//图片元素大小
	CRect m_rtGameRect;     //游戏区域的大小
	CGameControl m_gameControl; //游戏控制类


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void InitBackground();	//初始化背景
	void InitElement();		//初始化元素
	void UpdateWindow();		//
	void UpdateMap();

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();

	afx_msg void OnClickedButtonStart();
	
	CProgressCtrl m_GameProgress;
	
};
