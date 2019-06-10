#pragma once


// CHelpDialog �Ի���

class CHelpDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CHelpDialog)

public:
	CHelpDialog(CWnd* pParent = nullptr);   // ��׼���캯��
	virtual ~CHelpDialog();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_HELP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:

	virtual BOOL OnInitDialog();

	afx_msg void OnPaint();

protected:
	HICON m_hIcon;    //ϵͳͼƬ
	CDC m_dcMem;      //�ڴ�DC
	CDC m_dcHelp;     //����ͼƬDC
	CRect m_rtHelp;   //����ͼƬ��ʾ����

public:
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	void UpdateHelp(int nPos);    //���ݹ�������λ�ã����ð���ͼƬ��λ����ʾ������


};
