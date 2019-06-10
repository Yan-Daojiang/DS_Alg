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

	//��ʼ��ͼ��ѡ��״̬
	m_bFirstPoint = true;
	m_bPlaying = false;

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
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_TIPS, &CGameDlg::OnClickedButtonTips)
	ON_BN_CLICKED(IDC_BUTTON_RESTART, &CGameDlg::OnClickedButtonRestart)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CGameDlg::OnClickedButtonStop)
	ON_EN_CHANGE(IDC_EDIT_TIME, &CGameDlg::OnChangeEditTime)
	ON_BN_CLICKED(IDC_BUTTON_HELP, &CGameDlg::OnBnClickedButtonHelp)
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

	//��ͣʱ����Ӧ
	if (m_bPause == true) return;

	m_gameControl.StartGame();

	//��ʼʱ����300
	timeCount = 300;




	//�ж��Ƿ���������Ϸ
	m_bPlaying = true;
	//��ֹ����ʼ��Ϸ����ť���
	this->GetDlgItem(IDC_BUTTON_START)->EnableWindow(false);

	//��ʼ��������
	m_GameProgress.SetRange(0, 60 * 5);    //��ʼ��Χ
	m_GameProgress.SetStep(-1);            //��ʼ����ֵ
	m_GameProgress.SetPos(60 * 5);         //���ó�ʼֵ
	//������ʱ��
	this->SetTimer(PLAY_TIMER_ID, 1000, NULL);

	//���µ�ͼ
	UpdateMap();

	//���´���
	Invalidate(FALSE);

	//���ý��������غ�ʣ��ʱ��ؼ�
	this->GetDlgItem(IDC_GAME_TIME)->ShowWindow(TRUE);
	this->GetDlgItem(IDC_EDIT_TIME)->ShowWindow(TRUE);
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


void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	// TODO: �ڴ˴����ʵ�ִ���.

	//ȥ��С��0״̬
	if (point.x < m_ptGameTop.x || point.y < m_ptGameTop.y) {
		return CDialogEx::OnLButtonUp(nFlags, point);
	}

	//������������
	int nRow = (point.y - m_ptGameTop.y) / m_sizeElem.cy;//�к�
	int nCol = (point.x - m_ptGameTop.x) / m_sizeElem.cx;

	//�ж��������Ч��
	if (nRow > MAX_ROW - 1 || nCol > MAX_COL - 1) {
		return CDialogEx::OnLButtonUp(nFlags, point);
	}

	//��һ����
	if (m_bFirstPoint) {
		//������ʾ��
		DrawTipFrame(nRow, nCol);
		m_gameControl.SetFirstPoint(nRow, nCol);

	}
	//�ڶ�����
	else {
		//������ʾ��
		DrawTipFrame(nRow, nCol);
		m_gameControl.SetSecPoint(nRow, nCol);

		Vertex avPath[MAX_VERTEX_NUM];     //���·��   16Ϊ·��������ᵽ16��·���ģ�
		int nVexnum = 0;      //�������

		//�ж��Ƿ�����ͬͼƬ	
		if (m_gameControl.Link(avPath, nVexnum)) {

			//����ʾ��
			DrawTipLine(avPath, nVexnum);

			//���µ�ͼ
			UpdateMap();
		}
		Sleep(200);    //�ӳ�
		InvalidateRect(m_rtGameRect, FALSE); //�ֲ����θ���

		//�ж�ʤ��
		JudgeWin();

		/*
		if (m_gameControl.IsWin()) {
			MessageBox(_T("\t��ʤ��"),_T("����������������ģʽ"));
			m_bPlaying = false;
			this->GetDlgItem(IDC_BUTTON_START)->EnableWindow(true); //��Ϸ������������ʼ��Ϸ����ť����Ϊ�ɵ��״̬

			return;
		}*/

	}
	m_bFirstPoint = !m_bFirstPoint; //����ֵ

	CDialogEx::OnLButtonUp(nFlags, point);
}


//���ƾ�����ʾ��
void CGameDlg::DrawTipFrame(int nRow, int nCol) {
	CClientDC dc(this);
	CBrush brush(RGB(233, 43, 43));
	CRect rtTipFrame;
	rtTipFrame.left = m_ptGameTop.x + nCol * m_sizeElem.cx;
	rtTipFrame.top = m_ptGameTop.y + nRow * m_sizeElem.cy;
	rtTipFrame.right = rtTipFrame.left + m_sizeElem.cx;
	rtTipFrame.bottom = rtTipFrame.top + m_sizeElem.cy;
	dc.FrameRect(rtTipFrame, &brush);
}

//������ʾ��
void CGameDlg::DrawTipLine(Vertex avPath[MAX_VERTEX_NUM], int nVexnum)
{
	//��ȡDC
	CClientDC dc(this);

	//���û���
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));

	//������ѡ��DC
	CPen* pOldPen = dc.SelectObject(&penLine);

	dc.MoveTo(m_ptGameTop.x + avPath[0].col * m_sizeElem.cx + m_sizeElem.cx / 2,
		m_ptGameTop.y + avPath[0].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	//����������
	for (int i = 0; i < nVexnum - 1; i++)
	{

		dc.LineTo(m_ptGameTop.x + avPath[i + 1].col * m_sizeElem.cx + m_sizeElem.cx / 2,
			m_ptGameTop.y + avPath[i + 1].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	}

	dc.SelectObject(pOldPen);
}

//����ʾ����ť  �������
void CGameDlg::OnClickedButtonTips()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//���û�н�����Ϸ���򷵻�
	if (m_bPlaying == false)
		return;

	//����ܹ���ͨ��������ʾ��������߲�������Ϸ��ͼ
	Vertex avPath[MAX_VERTEX_NUM];     //���·��
	int nVexnum = 0;      //�������
	if (m_gameControl.Help(avPath, nVexnum))
	{

		//����һ�������ʾ��
		DrawTipFrame(avPath[0].row, avPath[0].col);

		//����һ�������ʾ��
		DrawTipFrame(avPath[nVexnum - 1].row, avPath[nVexnum - 1].col);

		//����ʾ��
		DrawTipLine(avPath, nVexnum);

		Sleep(1000);    //�ӳ�

		UpdateMap();	//���µ�ͼ

		InvalidateRect(m_rtGameRect, FALSE);    //�ֲ����θ���
	}
	//Ϊ��ʹ�õڶ�����ʾ����Կ�������ͣ200ms����ˢ�½���
}

//�����š���ť  �������
void CGameDlg::OnClickedButtonRestart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//����CGameControl����ResetGraph();
	m_gameControl.Reset();

	//���µ�ͼ������UpdateMap(),���½�����ʾ
	UpdateMap();

	//֪ͨ�����ػ�
	InvalidateRect(m_rtGameRect, FALSE);    //�ֲ����θ���

}


void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	JudgeWin();

	/*if (nIDEvent == PLAY_TIMER_ID && m_bPlaying) {
		//��Ϸʱ�����һ��
		m_GameProgress.StepIt();
	}*/

	//���ý�������λ��֮ǰ����Ҫ�жϼ�ʱ���ı���Ƿ��ǵ�ǰ�ļ�ʱ��
	if (nIDEvent == PLAY_TIMER_ID && m_bPlaying && m_bPause == false)
	{
		//��Ϸʱ���һ��
		if (timeCount > -1)
		{
			CString str;
			str.Format(_T("%d"), timeCount);
			SetDlgItemText(IDC_EDIT_TIME, str);

			UpdateData(false);
			timeCount--;

			m_GameProgress.StepIt();
		}

	}


	CDialogEx::OnTimer(nIDEvent);
}

//�ж�ʤ��
void CGameDlg::JudgeWin(void)
{
	//��Ϸʤ���ж�
	BOOL bGameStatus = m_gameControl.IsWin(m_GameProgress.GetPos());
	//�ж��Ƿ������Ϸ
	if (bGameStatus == GAME_PLAY)
	{
		return;
	}
	else
	{
		//����Ϸ��ʶ��Ϊfalse
		m_bPlaying = false;

		//�رն�ʱ��
		KillTimer(PLAY_TIMER_ID);

		//��ʾ��ʤ
		CString strTitle;
		this->GetWindowTextW(strTitle);
		if (bGameStatus == GAME_SUCCESS)
		{
			MessageBox(_T("��ʤ��"), strTitle);
		}
		else if (bGameStatus == GAME_LOSE)
		{
			MessageBox(_T("���ź���ʱ�䵽�ˣ�"), strTitle);
		}
		//��ԭ��ʼ��Ϸ��ť��ʹ�ð�ť���Ե��
		this->GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
	}

}

//�������ͣ��Ϸ����ť
void CGameDlg::OnClickedButtonStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//��õ�ǰ�Ի������Ƶ����
	CClientDC dc(this);

	//��Ϸû�ڽ���ʱ��ֱ�ӷ���
	if (m_bPlaying == false)
		return;

	//�����Ϸû����ͣ
	if (m_bPause == false)
	{
		//hu���Ʊ������ڴ�DC��
		m_dcMem.BitBlt(MAP_LETF, MAP_TOP, 640, 400, &m_dcCache, 0, 0, SRCCOPY);

		GetDlgItem(IDC_BUTTON_TIPS)->EnableWindow(0);
		GetDlgItem(IDC_BUTTON_RESTART)->EnableWindow(0);
		InvalidateRect(m_rtGameRect, FALSE);    //�ֲ����θ���
		this->GetDlgItem(IDC_BUTTON_STOP)->SetWindowTextW(_T("������Ϸ"));
	}

	//�����Ϸ��ͣ
	if (m_bPause == true)
	{
		UpdateMap();
		GetDlgItem(IDC_BUTTON_TIPS)->EnableWindow(1);
		GetDlgItem(IDC_BUTTON_RESTART)->EnableWindow(1);
		InvalidateRect(m_rtGameRect, FALSE);    //�ֲ����θ���

		this->GetDlgItem(IDC_BUTTON_STOP)->SetWindowTextW(_T("��ͣ��Ϸ"));
	}

	m_bPause = !m_bPause;
}


void CGameDlg::OnChangeEditTime()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CGameDlg::OnBnClickedButtonHelp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CHelpDialog dlg;
	dlg.DoModal();
}
