// CGameDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "LLK.h"
#include "CGameDlg.h"
#include "afxdialogex.h"


// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAMW_DIALOG, pParent)
{

}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
END_MESSAGE_MAP()


// CGameDlg 消息处理程序
