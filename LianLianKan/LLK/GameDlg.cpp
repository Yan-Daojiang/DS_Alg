// CGameDlg.cpp: ʵ���ļ�
//

#include "stdafx.h"
#include "LLK.h"
#include "GameDlg.h"
#include "afxdialogex.h"


// CGameDlg �Ի���

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	//��ʼ����ʼ������
	m_ptGameTop.x = 50;
	m_ptGameTop.y = 50;

	//��ʼ��ͼƬԪ�ش�С
	m_sizeElem.cx = 40;
	m_sizeElem.cy = 40;

	//��ʼ����Ϸ��������
	m_rtGameRect.top = m_ptGameTop.y;
	m_rtGameRect.left = m_ptGameTop.x;
	m_rtGameRect.right = m_rtGameRect.left + m_sizeElem.cx * MAX_COL;
	m_rtGameRect.bottom = m_rtGameRect.top + m_sizeElem.cy * MAX_ROW;

	

}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GAME_TIME, m_GameProgress);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_START, &CGameDlg::OnClickedButtonStart)
END_MESSAGE_MAP()


//��ʼ�����ڱ����ʹ�С
void CGameDlg::InitBackground()
{	// TODO: �ڴ˴����ʵ�ִ���.

	//����BMPͼƬ��Դ
	HANDLE Backbmp = ::LoadImage(NULL, _T("theme\\picture\\fruit_bg.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//��õ�ǰ�Ի������Ƶ����
	CClientDC dc(this);

	//��������Ƶ���ݼ��ݵ��ڴ�DC
	m_dcBG.CreateCompatibleDC(&dc);

	//��λͼ��Դѡ��DC
	m_dcBG.SelectObject(Backbmp);

	//��ʼ���ڴ�DC
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 800, 600);
	m_dcMem.SelectObject(&bmpMem);

	//hu���Ʊ������ڴ�DC��
	m_dcMem.BitBlt(0, 0, 800, 600, &m_dcBG, 0, 0, SRCCOPY);

	//���ô��ڴ�С
	UpdateWindow();
}


BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//���ڱ���
	this->SetWindowTextW(_T("����������������ģʽ"));

	//��ʼ������
	InitBackground();

	//��ʼ��Ԫ��
	InitElement();

	//���ý��������غ�ʣ��ʱ��ؼ�
	this->GetDlgItem(IDC_GAME_TIME)->ShowWindow(FALSE);
	this->GetDlgItem(IDC_EDIT_TIME)->ShowWindow(FALSE);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	dc.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);
}

//��ʼ��Ԫ��
void CGameDlg::InitElement() {
	CClientDC dc(this);

	//����BMPͼƬ��Դ
	HANDLE Elmbmp = ::LoadImage(NULL, _T("theme\\picture\\fruit_element.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	m_dcElm.CreateCompatibleDC(&dc);

	m_dcElm.SelectObject(Elmbmp);

	//����ͼ����
	HANDLE Maskbmp = ::LoadImage(NULL, _T("theme\\picture\\fruit_mask.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	m_dcMask.CreateCompatibleDC(&dc);

	m_dcMask.SelectObject(Maskbmp);

	//�����ڸ�ͼƬ
	//����BMPͼƬ��Դ
	HANDLE hCache = ::LoadImage(NULL, _T("theme\\picture\\fruit_pause.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//��������Ƶ�ڴ���ݵ��ڴ�DC
	m_dcCache.CreateCompatibleDC(&dc);
	//��λͼ��Դѡ��DC
	m_dcCache.SelectObject(hCache);

}

//��ʼ��Ϸ
void CGameDlg::OnClickedButtonStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_gameControl.StartGame();

	//���µ�ͼ
	UpdateMap();

	//���´���
	Invalidate(FALSE);	
}

//�������ڴ�С
void CGameDlg::UpdateWindow()
{

	// TODO: �ڴ˴����ʵ�ִ���.

	//�������ڴ�С
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);		//��ô��ڴ�С
	this->GetWindowRect(rtClient);	//��ÿͻ�����С

									//����������߿�Ĵ�С
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Width() - rtClient.Width();

	//���ô��ڴ�С
	MoveWindow(0, 0, 800 + nSpanWidth, 600 + nSpanHeight);

	CenterWindow();
}

//���µ�ͼ
void CGameDlg::UpdateMap()
{
	// TODO: �ڴ˴����ʵ�ִ���.

	//����ͼƬ�Ķ���������ͼƬ��С
	int nTop = m_ptGameTop.y;
	int nLeft = m_ptGameTop.x;
	int nElemW = m_sizeElem.cx;
	int nElemH = m_sizeElem.cy;

	m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top,
		m_rtGameRect.Width(), m_rtGameRect.Height(), &m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);

	for (int i = 0; i < MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {

			int nInfo = m_gameControl.GetElement(i, j);       //��ǰԪ��ͼƬ����ֵ
			if (nInfo == BLANK)  continue;


			//��������������򣬱߱�����ͼ������Ϊ1
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcMask, 0, nInfo * nElemH, SRCPAINT);

			//��Ԫ��ͼƬ���룬�߱�����ͼ������ΪԪ��ͼƬ
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElm, 0, nInfo * nElemH, SRCAND);

		}
	}

}