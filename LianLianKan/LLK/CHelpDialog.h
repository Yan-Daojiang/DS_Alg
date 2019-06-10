#pragma once


// CHelpDialog 对话框

class CHelpDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CHelpDialog)

public:
	CHelpDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CHelpDialog();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_HELP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:

	virtual BOOL OnInitDialog();

	afx_msg void OnPaint();

protected:
	HICON m_hIcon;    //系统图片
	CDC m_dcMem;      //内存DC
	CDC m_dcHelp;     //帮助图片DC
	CRect m_rtHelp;   //帮助图片显示区域

public:
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	void UpdateHelp(int nPos);    //根据滚动条的位置，设置帮助图片的位置显示的内容


};
