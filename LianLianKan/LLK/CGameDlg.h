#pragma once
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
	HICON m_hIcon;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };    //通过ID进行对话框的关联
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

	bool m_bFirstPoint;		//选中的图片是不是第一次选中的，TRUE   是，FALSE  否
	Vertex m_ptSelFirst;	//第一次选中的点(x表示列)
	Vertex m_ptSelSec;		//第二次选中的点

	CGameControl m_gameControl; //游戏控制类

protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	
	
	virtual BOOL OnInitDialog();
	void InitBackground();
	void UpdateWindow();	//跟新界面
	void InitElement();		//初始化元素
	void UpdateMap();

	afx_msg void OnPaint();
	afx_msg void OnClickedButtonStart();	//开始按钮响应函数
};
