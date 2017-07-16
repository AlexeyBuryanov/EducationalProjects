#include "Includes.h"
#include "MainWindow.h"
#include "Employee.h"

// ��������� ������� ��� �������� ����������
Employee person;

// ���������� � ������� ��� �������� ���� ����������
static HDC hDC;             // ����� ��������� ����������
static TCHAR szBuf[100];
static TCHAR szBuf1[256];	// ������ ����� ���

static HFONT hFont, hOldFont;       // ����� ��� ������
static LOGFONT lf;                  // ��������� ��� �������� ������

HWND hBtnQuit;	  // �����
HWND hBtnReport;  // �����

// ����������� �������� ���������� - �������
HWND hStInitials;    // ��������
HWND hStFamIO, hStRank, hStSkills;

HWND hEditInitial;   // ������ �������������� ��� ���������

// �����������
HWND hRdButEngineer;
HWND hRdButDevelop;
HWND hRdButLeadDevelop;

HWND hChBoxC, hChBoxWinApi, hChBoxHard, hChBoxAndroid;

// ���������� ��� ���������� ������� (���-������)
BOOL Mode = true; 

// ���������� ��� ���������� ���������� ��������������(�����������)
// 0 - IDC_RDBTNENG, 1 - IDC_RDBTNDEV, 2 - IDC_RDBTNLEAD
UINT uNumber = 1;

// ������� ������� - ��������� ���������, ���������� �����
// hWnd	  - ���������� ����
// msg	  - �������� ��� ���������
// wParam - ������ ����� ���������� ���������
// lParam - ������ ����� ���������� ���������
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);  // �������� ����
		HANDLE_MSG(hWnd, WM_SIZE, OnSize);      // ��������� ������� ������
		HANDLE_MSG(hWnd, WM_LBUTTONDOWN, OnLButtonDown);
		HANDLE_MSG(hWnd, WM_RBUTTONDOWN, OnRButtonDown);
		HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hWnd, WM_CLOSE, OnClose);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_CTLCOLORSTATIC, OnCtlColorStatic);
	
		// ��������� ��������� ��� ������� �� ������������� ��������� � ����� ����
		default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	} // switch

	return 0;
} // WndProc


// ���������� ��������� WM_CREATE - ���������� ������� "��� ��������" 
// ������ ����
BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
	TEXTMETRIC tm;
	INT yPos, xPos;
	hDC = GetDC(hWnd);
	GetTextMetrics(hDC, &tm);

	hFont = CreateFontIndirect(&lf);

	/*********************************�.�.�.*************************************/
	yPos = 30;
	xPos = 30;
	hStInitials = CreateWindow(_T("static"), _T("������� � ��������:"), WS_CHILD | WS_VISIBLE,
		xPos, yPos, 255, 25, hWnd, NULL, NULL, NULL);

	yPos += (tm.tmHeight + 2);
	hEditInitial = CreateWindow(_T("edit"), _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
		xPos, yPos, 430, tm.tmHeight + 8, hWnd, (HMENU)IDC_EDTINIT, NULL, NULL);
	SetFocus(hEditInitial);

	/*******************************�����������**********************************/
	yPos = 100;
	xPos = 30;
	// ����� ������ �����������
	CreateWindow(_T("button"), _T(" ��������� "), BS_GROUPBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 200, 110, hWnd, NULL, NULL, NULL);

	xPos = 45;
	// ������ ����������� (��������������)
	hRdButEngineer = CreateWindow(_T("button"), _T("�������"), BS_AUTORADIOBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, 125, 120, 25, hWnd, (HMENU)IDC_RDBTNENG, NULL, NULL);
	hRdButDevelop = CreateWindow(_T("button"), _T("�����������"), BS_AUTORADIOBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, 150, 120, 25, hWnd, (HMENU)IDC_RDBTNDEV, NULL, NULL);
	hRdButLeadDevelop = CreateWindow(_T("button"), _T("������� �����������"), BS_AUTORADIOBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, 175, 170, 25, hWnd, (HMENU)IDC_RDBTNLEAD, NULL, NULL);


	/********************************���-�����***********************************/
	// ����� ������ �������
	yPos = 100;
	xPos = 260;
	CreateWindow(_T("button"), _T(" ������ "), BS_GROUPBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 200, 110, hWnd, NULL, NULL, NULL);

	// ������
	yPos = 120;
	xPos = 280;
	hChBoxC = CreateWindow(_T("button"), _T("����� C++"), BS_AUTOCHECKBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 150, 25, hWnd, (HMENU)IDC_CHBOXC, NULL, NULL);
	yPos = 140;
	xPos = 280;
	hChBoxWinApi = CreateWindow(_T("button"), _T("����� WinAPI"), BS_AUTOCHECKBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 150, 25, hWnd, (HMENU)IDC_CHBOXWINAPI, NULL, NULL);
	yPos = 160;
	xPos = 280;
	hChBoxHard = CreateWindow(_T("button"), _T("����� Hardware"), BS_AUTOCHECKBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 150, 25, hWnd, (HMENU)IDC_CHBOXHARD, NULL, NULL);
	yPos = 180;
	xPos = 280;
	hChBoxAndroid = CreateWindow(_T("button"), _T("����� Android"), BS_AUTOCHECKBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 150, 25, hWnd, (HMENU)IDC_CHBOXANDROID, NULL, NULL);


	/********************************���������***********************************/
	yPos = 40;
	xPos = 490;
	// ����� ������ ��������
	CreateWindow(_T("button"), _T(" ������ "), BS_GROUPBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 330, 265, hWnd, NULL, NULL, NULL);

	// ������� �.�.
	yPos = 70;
	xPos = 510;
	hStFamIO = CreateWindow(_T("static"), szBuf1, WS_CHILD | WS_VISIBLE,
		xPos, yPos, 255, 25, hWnd, NULL, NULL, NULL);

	// ���������
	yPos = 90;
	xPos = 510;
	hStRank = CreateWindow(_T("static"), _T(" "), WS_CHILD | WS_VISIBLE,
		xPos, yPos, 255, 25, hWnd, NULL, NULL, NULL);

	// ������
	yPos = 110;
	xPos = 510;
	hStSkills = CreateWindow(_T("static"), _T(" "), WS_CHILD | WS_VISIBLE,
		xPos, yPos, 255, 25, hWnd, NULL, NULL, NULL);

	/**********************************�����*************************************/
	yPos = 265;
	xPos = 50;
	hBtnReport = CreateWindow(_T("button"), _T("�����"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 180, 25, hWnd, (HMENU)IDC_REPORT, NULL, NULL);

	/**********************************�����*************************************/
	yPos = 265;
	xPos = 260;
	hBtnQuit = CreateWindow(_T("button"), _T("�����"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 180, 25, hWnd, (HMENU)IDC_QUIT, NULL, NULL);

	// ����� ������ ������ ����� � �����
	yPos = 240;
	xPos = 30;
	CreateWindow(_T("button"), NULL, BS_GROUPBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 430, 65, hWnd, NULL, NULL, NULL);

	// ���������� ����������� �������� � ������������ � ������ �������
	person.Setup();
	return TRUE;
} // OnCreate


// ��������� ��������� WM_COMMAND - ��� ���������� �� ��������� ����������
// � ��������� - �� ������
void OnCommand(HWND hWnd, INT id, HWND hWndCtl, UINT codeNotify)
{
	LRESULT cbState;
	TCHAR szBuf[100];

	switch (id) {

	case IDC_CHBOXC:
		cbState = Button_GetCheck(hWndCtl);
		person.SetSkill(0, (cbState == BST_CHECKED) ? TRUE : FALSE);
		break;

	case IDC_CHBOXWINAPI:
		cbState = Button_GetCheck(hWndCtl);
		person.SetSkill(1, (cbState == BST_CHECKED) ? TRUE : FALSE);
		break;

	case IDC_CHBOXHARD:
		cbState = Button_GetCheck(hWndCtl);
		person.SetSkill(2, (cbState == BST_CHECKED) ? TRUE : FALSE);
		break;

	case IDC_CHBOXANDROID:
		cbState = Button_GetCheck(hWndCtl);
		person.SetSkill(3, (cbState == BST_CHECKED) ? TRUE : FALSE);
		break;

		// �������� ����� ������������� ����������� - ��� ���������
	case IDC_RDBTNENG:
		person.SetRank(0);
		break;
	case IDC_RDBTNDEV:
		person.SetRank(1);
		break;
	case IDC_RDBTNLEAD:
		person.SetRank(2);
		break;

		// ��������� ������� ������ "�����"
	case IDC_REPORT:
		SendMessage(hEditInitial, WM_GETTEXT, (WPARAM)100, (LPARAM)szBuf);
		person.SetFamIO(szBuf);

		person.Show();
		break;

	case IDC_QUIT:
		int nReply = MessageBox(hWnd, _T("�� ������������� ������ �����?"), _T("�����"), MB_YESNO | MB_ICONQUESTION);
		if (nReply == IDYES)
		PostQuitMessage(0);
		break;
	} // switch
} // OnCommand


// ���������� ��������� WM_SIZE - ���������� ������� "��� ��������� �������" 
// ������ ����
void OnSize(HWND hWnd, UINT state, INT cx, INT cy)
{
	RECT rect;       // ������������� - ��� �������� ��������� ������� ������� ���� 

	GetClientRect(hWnd, &rect);         // ������ ������� ���� ��� �����������
	InvalidateRect(hWnd, &rect, TRUE);  // �������� ������� ���������������� => ����������� WM_PAINT
} // OnSize


// ���������� ��������� WM_LBUTTONDOWN - ���������� ������� "������ ���" 
void OnLButtonDown(HWND hWnd, BOOL fDoubleClick, INT x, INT y, UINT keyFlags)
{
	RECT rect;       // ������������� - ��� �������� ��������� ������� ������� ���� 

	GetClientRect(hWnd, &rect);
	InvalidateRect(hWnd, &rect, TRUE);  // !!!!! �������������� �� ����� ������ !!!!!
} // OnLButtonDown


// ���������� ��������� WM_RBUTTONDOWN - ���������� ������� "������ ���" 
void OnRButtonDown(HWND hWnd, BOOL fDoubleClick, INT x, INT y, UINT keyFlags)
{
	RECT rect;       // ������������� - ��� �������� ��������� ������� ������� ���� 

	GetClientRect(hWnd, &rect);
	InvalidateRect(hWnd, &rect, TRUE);  // !!!!! �������������� �� ����� ������ !!!!!
} // OnRButtonDown


// ���������� ��������� WM_PAINT - ���������� ������� "��� ���������" 
void OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;  // ��������� ��������� ����������
	RECT rect;       // ������������� - ��� �������� ��������� ������� ������� ���� 

	hDC = BeginPaint(hWnd, &ps);    // �������� ����� ��������� ����������
	GetClientRect(hWnd, &rect);     // �������� ���������� ������� ��� ���������

	ZeroMemory(&lf, sizeof(LOGFONT));
	_tcscpy(lf.lfFaceName, _T("Consolas"));

	EndPaint(hWnd, &ps);            // ���������� �������� ��� ���������� ������ �������
} // OnPaint


// ���������� ��������� WM_CLOSE - ���������� ������� "��� �������� ����" 
void OnClose(HWND hWnd)
{
	SelectFont(hDC, hOldFont);
	DeleteFont(hFont);

	DestroyWindow(hWnd);
} // OnClose


// ���������� ��������� WM_DESTROY - ���������� ������� "��� ����������� ����" 
void OnDestroy(HWND hWnd)
{
	PostQuitMessage(0);
} // OnDestroy


// ��������� ���� ������������ ������������ ��������
// ��� - ��������� � ����� ������� ������� ����
HBRUSH OnCtlColorStatic(HWND, HDC hDC, HWND, INT)
{
	SetBkMode(hDC, TRANSPARENT);
	hOldFont = SelectFont(hDC, hFont);

	SetTextColor(hDC, RGB(0x00, 0x00, 0x80));
	return CreateSolidBrush(BACKGROUND);
} // OnCtlColorStatic