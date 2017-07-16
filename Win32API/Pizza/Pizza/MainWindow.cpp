#include "Includes.h"
#include "MainWindow.h"
#include "Pizza.h"

// ��������� ������� ��� �������� ������
static Pizza *pizza;

// ���������� � ������� ��� �������� ���� ����������
static HDC hDC;                 // ����� ��������� ����������
static HFONT hFont, hOldFont;   // ����� ��� ������
static LOGFONT lf;              // ��������� ��� �������� ������

static TCHAR szBufFio[256];	    // ������ ����� ���
static TCHAR szBufPhone[15];	// ������ ����� ������ ��������

HWND hBtnQuit;					// �����
HWND hBtnOrder;					// ��������

// ����������� �������� ����������
//    ��������      �����
HWND hStInitials, hStPhone;

// ������ �������������� ��� ��������� � ������ ��������
HWND hEditInitial, hEditPhone;

/*   ���        ����� �.     ������      �����   */
HWND hStFamIO, hStPNumber, hStDiscount, hStOptions;

// ����������� ��� ������
HWND hRdBut0, hRdBut5, hRdBut15;

// ������ ��� ����������� �����
/*       ���     ,   ������   ,    �����   ,    �������  */
HWND hChBoxCheese, hChBoxOlive, hChBoxFungi, hChBoxSausage;

// ���������� ��� ���������� �������
BOOL Mode = true;

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
		//HANDLE_MSG(hWnd, WM_GETMINMAXINFO, OnGetMinMaxInfo);
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
	pizza = new Pizza();

	TEXTMETRIC tm;
	INT yPos, xPos;
	hDC = GetDC(hWnd);
	GetTextMetrics(hDC, &tm);

	hFont = CreateFontIndirect(&lf);

	/*********************************�.�.�.*************************************/
	yPos = 30;
	xPos = 30;
	hStInitials = CreateWindow(_T("static"), _T("��� ��������� �����:"), WS_CHILD | WS_VISIBLE,
		xPos, yPos, 180, 25, hWnd, NULL, NULL, NULL);

	yPos += (tm.tmHeight + 2);
	hEditInitial = CreateWindow(_T("edit"), _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
		xPos, yPos, 200, tm.tmHeight + 8, hWnd, (HMENU)IDC_EDTINIT, NULL, NULL);
	SetFocus(hEditInitial);

	/******************************����� ��������********************************/
	yPos = 30;
	xPos = 300;
	hStPhone = CreateWindow(_T("static"), _T("����� ��������:"), WS_CHILD | WS_VISIBLE,
		xPos, yPos, 180, 25, hWnd, NULL, NULL, NULL);

	yPos += (tm.tmHeight + 2);
	hEditPhone = CreateWindow(_T("edit"), _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
		xPos, yPos, 200, tm.tmHeight + 8, hWnd, (HMENU)IDC_EDTINIT, NULL, NULL);

	/*******************************�����������**********************************/
	yPos = 100;
	xPos = 30;
	// ����� ������ �����������
	CreateWindow(_T("button"), _T(" ������ "), BS_GROUPBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 75, 110, hWnd, NULL, NULL, NULL);

	xPos = 45;
	// ������ ����������� (��������������)
	hRdBut0 = CreateWindow(_T("button"), _T("0%"), BS_AUTORADIOBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, 125, 50, 25, hWnd, (HMENU)IDC_RDBTN0, NULL, NULL);
	hRdBut5 = CreateWindow(_T("button"), _T("5%"), BS_AUTORADIOBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, 150, 50, 25, hWnd, (HMENU)IDC_RDBTN5, NULL, NULL);
	hRdBut15 = CreateWindow(_T("button"), _T("15%"), BS_AUTORADIOBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, 175, 50, 25, hWnd, (HMENU)IDC_RDBTN15, NULL, NULL);

	/********************************���-�����***********************************/
	// ����� ������ �������
	yPos = 100;
	xPos = 385;
	CreateWindow(_T("button"), _T(" ����������� "), BS_GROUPBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 115, 110, hWnd, NULL, NULL, NULL);

	// ������
	yPos = 120;
	xPos = 405;
	hChBoxCheese = CreateWindow(_T("button"), _T("���"), BS_AUTOCHECKBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 70, 25, hWnd, (HMENU)IDC_CHBOXCHEESE, NULL, NULL);
	yPos = 140;
	xPos = 405;
	hChBoxOlive = CreateWindow(_T("button"), _T("������"), BS_AUTOCHECKBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 70, 25, hWnd, (HMENU)IDC_CHBOXOLIVE, NULL, NULL);
	yPos = 160;
	xPos = 405;
	hChBoxFungi = CreateWindow(_T("button"), _T("�����"), BS_AUTOCHECKBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 70, 25, hWnd, (HMENU)IDC_CHBOXFUNGI, NULL, NULL);
	yPos = 180;
	xPos = 405;
	hChBoxSausage = CreateWindow(_T("button"), _T("�������"), BS_AUTOCHECKBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 80, 25, hWnd, (HMENU)IDC_CHBOXSAUSAGE, NULL, NULL);

	/********************************���������***********************************/
	yPos = 100;
	xPos = 110;
	// ����� ������ ��������
	CreateWindow(_T("button"), _T(" ����� "), BS_GROUPBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 270, 110, hWnd, NULL, NULL, NULL);

	// ������� �.�.
	yPos = 120;
	xPos = 125;
	hStFamIO = CreateWindow(_T("static"), szBufFio, WS_CHILD | WS_VISIBLE,
		xPos, yPos, 240, 25, hWnd, NULL, NULL, NULL);
	
	// ����� ��������
	yPos = 140;
	xPos = 125;
	hStPNumber = CreateWindow(_T("static"), szBufPhone, WS_CHILD | WS_VISIBLE,
		xPos, yPos, 240, 25, hWnd, NULL, NULL, NULL);

	// ������
	yPos = 160;
	xPos = 125;
	hStDiscount = CreateWindow(_T("static"), _T(" "), WS_CHILD | WS_VISIBLE,
		xPos, yPos, 240, 25, hWnd, NULL, NULL, NULL);

	// �����
	yPos = 180;
	xPos = 125;
	hStOptions = CreateWindow(_T("static"), _T(" "), WS_CHILD | WS_VISIBLE,
		xPos, yPos, 240, 25, hWnd, NULL, NULL, NULL);

	/**********************************�����*************************************/
	yPos = 265;
	xPos = 50;
	hBtnOrder = CreateWindow(_T("button"), _T("��������"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 180, 25, hWnd, (HMENU)IDC_ORDER, NULL, NULL);

	/**********************************�����*************************************/
	yPos = 265;
	xPos = 297;
	hBtnQuit = CreateWindow(_T("button"), _T("�����"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 180, 25, hWnd, (HMENU)IDC_QUIT, NULL, NULL);

	// ����� ������ ������ ����� � �����
	yPos = 240;
	xPos = 30;
	CreateWindow(_T("button"), NULL, BS_GROUPBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 470, 65, hWnd, NULL, NULL, NULL);

	// ���������� ����������� �������� � ������������ � ������ �������
	pizza->Setup();
	return TRUE;
} // OnCreate


// ��������� ��������� WM_COMMAND - ��� ���������� �� ��������� ����������
// � ��������� - �� ������
void OnCommand(HWND hWnd, INT id, HWND hWndCtl, UINT codeNotify)
{
	INT nReply;
	LRESULT cbState;
	TCHAR szBuf1[200];
	TCHAR szBuf2[20];

	switch (id) {

	case IDC_CHBOXCHEESE:
		cbState = Button_GetCheck(hWndCtl);
		pizza->SetOption(0, (cbState == BST_CHECKED) ? TRUE : FALSE);
		break;
	case IDC_CHBOXOLIVE:
		cbState = Button_GetCheck(hWndCtl);
		pizza->SetOption(1, (cbState == BST_CHECKED) ? TRUE : FALSE);
		break;
	case IDC_CHBOXFUNGI:
		cbState = Button_GetCheck(hWndCtl);
		pizza->SetOption(2, (cbState == BST_CHECKED) ? TRUE : FALSE);
		break;
	case IDC_CHBOXSAUSAGE:
		cbState = Button_GetCheck(hWndCtl);
		pizza->SetOption(3, (cbState == BST_CHECKED) ? TRUE : FALSE);
		break;

		// �������� ����� ������������� ����������� - ��� �����
	case IDC_RDBTN0:
		pizza->SetDiscount(0);
		break;
	case IDC_RDBTN5:
		pizza->SetDiscount(1);
		break;
	case IDC_RDBTN15:
		pizza->SetDiscount(2);
		break;

		// ��������� ������� ������ "��������"
	case IDC_ORDER:
		SendMessage(hEditInitial, WM_GETTEXT, (WPARAM)100, (LPARAM)szBuf1);
		pizza->SetFamIO(szBuf1);

		SendMessage(hEditPhone, WM_GETTEXT, (WPARAM)100, (LPARAM)szBuf2);
		pizza->SetPhone(szBuf2);

		pizza->Show();
		break;

	case IDC_QUIT:
		nReply = MessageBox(hWnd, _T("�� ������������� ������ �����?"), _T("�����"), MB_YESNO | MB_ICONEXCLAMATION);
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
	_tcscpy(lf.lfFaceName, _T("Cambria"));

	EndPaint(hWnd, &ps);            // ���������� �������� ��� ���������� ������ �������
} // OnPaint


// ���������� ��������� WM_CLOSE - ���������� ������� "��� �������� ����" 
void OnClose(HWND hWnd)
{
	SelectFont(hDC, hOldFont);
	DeleteFont(hFont);

	delete pizza;
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

	SetTextColor(hDC, RGB(0xB9, 0xD3, 0xEE));
	return CreateSolidBrush(BACKGROUND);
} // OnCtlColorStatic
  

// ����������� ������������ ������� �������� ���� ����������
// !! �������� ������ � OnSize !!
//void OnGetMinMaxInfo(hWnd hWnd, LPMINMAXINFO lpMinMaxInfo)
//{
//	lpMinMaxInfo->ptMintrackSize = { 480, 240 };
//} // OnGetMinMaxInfo