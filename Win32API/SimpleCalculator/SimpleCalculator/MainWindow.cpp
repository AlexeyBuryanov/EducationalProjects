#include "Includes.h"
#include "MainWindow.h"

// ���������� � ������� ��� �������� ���� ����������
static HDC hDC;     // ����� ��������� ����������

HWND hBtnPlus;      // ������ ��� ������� "+"
HWND hBtnMinus;     // ������ ��� ������� "-"
HWND hBtnMultiply;  // ������ ��� ������� "*"
HWND hBtnDivide;    // ������ ��� ������� "/"
HWND hBtnReset;		// ������ ��� ������� "�����"
HWND hBtnQuit;		// ������ ��� ������� "�����"

HWND hStat1;        // �������
HWND hStat2;        // �������
HWND hStat3;        // �������

HWND hEdit1;        // ������ �������������� ������� �����
HWND hEdit2;        // ������ �������������� ������� �����
HWND hEditResult;	// ������ �������������� ����������

// ������ ��� ���������
INT nNumber1 = 0;
INT nNumber2 = 0;
INT nResult  = 0;

static TCHAR szBuf1[256];
static TCHAR szBuf2[256];
static TCHAR szBufRes[256];

// ������� ������� - ��������� ���������, ���������� �����
// hwnd	  - ���������� ����
// msg	  - �������� ��� ���������
// wParam - ������ ����� ���������� ���������
// lParam - ������ ����� ���������� ���������
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);  // �������� ����
		HANDLE_MSG(hWnd, WM_SIZE, OnSize);      // ��������� ������� ������
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
	TCHAR szBuf[50];

	hDC = GetDC(hWnd);
	GetTextMetrics(hDC, &tm);

	yPos = 20;
	xPos = 10;
	hStat1 = CreateWindow(_T("static"), _T("����� �1:"), WS_CHILD | WS_VISIBLE,
		xPos, yPos, 110, tm.tmHeight, hWnd, NULL, NULL, NULL);

	_stprintf(szBuf, _T("%d"), nNumber1);  // ����������� ��������� ������ ��� ����������� � ��������� 
	yPos += (tm.tmHeight + 2);
	hEdit1 = CreateWindow(_T("edit"), szBuf, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
		xPos, yPos, 110, tm.tmHeight + 8, hWnd, (HMENU)IDC_EDIT1, NULL, NULL);

	xPos += 150;
	yPos = 20;
	hStat2 = CreateWindow(_T("static"), _T("����� �2:"), WS_CHILD | WS_VISIBLE,
		xPos, yPos, 110, tm.tmHeight, hWnd, NULL, NULL, NULL);

	yPos += (tm.tmHeight + 2);
	_stprintf(szBuf, _T("%d"), nNumber2); 
	hEdit2 = CreateWindow(_T("edit"), szBuf, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
		xPos, yPos, 110, tm.tmHeight + 8, hWnd, (HMENU)IDC_EDIT2, NULL, NULL);
	
	xPos = 10;
	yPos = 80;
	hStat3 = CreateWindow(_T("static"), _T("���������:"), WS_CHILD | WS_VISIBLE,
		xPos, yPos, 260, tm.tmHeight, hWnd, NULL, NULL, NULL);

	yPos += (tm.tmHeight + 2);
	_stprintf(szBuf, _T("%d"), nResult); 
	hEditResult = CreateWindow(_T("edit"), szBuf, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
		xPos, yPos, 260, tm.tmHeight + 8, hWnd, (HMENU)IDC_EDIT2, NULL, NULL);

	yPos += (tm.tmHeight + 30);
	hBtnPlus = CreateWindow(_T("button"), _T("+"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 50, 25, hWnd, (HMENU)IDC_PLUS, NULL, NULL);

	xPos += 70;
	hBtnMinus = CreateWindow(_T("button"), _T("-"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 50, 25, hWnd, (HMENU)IDC_MINUS, NULL, NULL);

	xPos += 70;
	hBtnMinus = CreateWindow(_T("button"), _T("*"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 50, 25, hWnd, (HMENU)IDC_MULTIPLY, NULL, NULL);

	xPos += 70;
	hBtnMinus = CreateWindow(_T("button"), _T("/"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 50, 25, hWnd, (HMENU)IDC_DIVIDE, NULL, NULL);

	xPos = 10;
	yPos += 50;
	hBtnReset = CreateWindow(_T("button"), _T("�����"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 120, 25, hWnd, (HMENU)IDC_RESET, NULL, NULL);

	xPos += 140;
	hBtnQuit = CreateWindow(_T("button"), _T("�����"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 120, 25, hWnd, (HMENU)IDC_QUIT, NULL, NULL);

	return TRUE;
} // OnCreate


// ���������� ��������� WM_SIZE - ���������� ������� "��� ��������� �������" 
// ������ ����
void OnSize(HWND hwnd, UINT state, int cx, int cy)
{
	RECT rect;       // ������������� - ��� �������� ��������� ������� ������� ���� 

	GetClientRect(hwnd, &rect);         // ������ ������� ���� ��� �����������
	InvalidateRect(hwnd, &rect, TRUE);  // �������� ������� ���������������� => ����������� WM_PAINT
} // OnSize


// ���������� ��������� WM_CLOSE - ���������� ������� "��� �������� ����" 
void OnClose(HWND hwnd)
{
	DestroyWindow(hwnd);
} // OnClose


// ���������� ��������� WM_DESTROY - ���������� ������� "��� ����������� ����" 
void OnDestroy(HWND hwnd)
{
	PostQuitMessage(0);
} // OnDestroy


// ��������� ��������� WM_COMMAND - ��� ���������� �� ��������� ����������
// � ��������� - �� ������
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	INT nReply; // ����� ������������

 	switch (id) {
	
	// ����
	case IDC_PLUS:
		Plus();
		break;

	// �����
	case IDC_MINUS:
		Minus();
		break;

	// ��������
	case IDC_MULTIPLY:
		Multiply();
		break;

	// ���������
	case IDC_DIVIDE:
		Divide();
		break;

	// �����
	case IDC_RESET:
		Reset();
		break;

	// �����
	case IDC_QUIT:
		//SendMessage(hwndCtl, WM_SETTEXT, 0, (LPARAM)_T("� �� ���"));
		nReply = MessageBox(hwnd, _T("�� ������������� ������ �����?"), _T("�����"), MB_YESNO | MB_ICONQUESTION);
		if (nReply == IDYES) {
			PostQuitMessage(0);
		} else {
			Reset();
		} // if
		break;
	} // switch
} // OnCommand


// ��������� ���� ������������ ������������ ��������
// ��� - ��������� � ����� ������� ������� ����
HBRUSH OnCtlColorStatic(HWND, HDC hDC, HWND, INT)
{
	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(0x7F, 0xFF, 0x00));
	return CreateSolidBrush(BACKGROUND);
} // OnCtlColorStatic


void Plus()
{
	// ������ ��������� ������ �� ��������� hEdit1 � hEdit2
	SendMessage(hEdit1, WM_GETTEXT, (WPARAM)256, (LPARAM)szBuf1);
	SendMessage(hEdit2, WM_GETTEXT, (WPARAM)256, (LPARAM)szBuf2);

	// ������������� ��������� ������ � �������� ���������� ���� int
	_stscanf(szBuf1, _T("%d"), &nNumber1);
	_stscanf(szBuf2, _T("%d"), &nNumber2);
	nResult = nNumber1 + nNumber2;

	// ��������� ����� ������ � ���������� ��������� ����������
	_stprintf(szBufRes, _T("%d"), nResult);

	// ���������� ��� ������ � �������� ������ ����������
	SendMessage(hEditResult, WM_SETTEXT, 0, (LPARAM)szBufRes);
} // Plus


void Minus()
{
	// ������ ��������� ������ �� ��������� hEdit1 � hEdit2
	SendMessage(hEdit1, WM_GETTEXT, (WPARAM)256, (LPARAM)szBuf1);
	SendMessage(hEdit2, WM_GETTEXT, (WPARAM)256, (LPARAM)szBuf2);

	// ������������� ��������� ������ � �������� ���������� ���� int
	_stscanf(szBuf1, _T("%d"), &nNumber1);
	_stscanf(szBuf2, _T("%d"), &nNumber2);
	nResult = nNumber1 - nNumber2;

	// ��������� ����� ������ � ���������� ��������� ����������
	_stprintf(szBufRes, _T("%d"), nResult);

	// ���������� ��� ������ � �������� ������ ����������
	SendMessage(hEditResult, WM_SETTEXT, 0, (LPARAM)szBufRes);
} // Minus


void Multiply()
{
	// ������ ��������� ������ �� ��������� hEdit1 � hEdit2
	SendMessage(hEdit1, WM_GETTEXT, (WPARAM)256, (LPARAM)szBuf1);
	SendMessage(hEdit2, WM_GETTEXT, (WPARAM)256, (LPARAM)szBuf2);

	// ������������� ��������� ������ � �������� ���������� ���� int
	_stscanf(szBuf1, _T("%d"), &nNumber1);
	_stscanf(szBuf2, _T("%d"), &nNumber2);
	nResult = nNumber1 * nNumber2;

	// ��������� ����� ������ � ���������� ��������� ����������
	_stprintf(szBufRes, _T("%d"), nResult);

	// ���������� ��� ������ � �������� ������ ����������
	SendMessage(hEditResult, WM_SETTEXT, 0, (LPARAM)szBufRes);
} // Multiply


void Divide()
{
	// ������ ��������� ������ �� ��������� hEdit1 � hEdit2
	SendMessage(hEdit1, WM_GETTEXT, (WPARAM)256, (LPARAM)szBuf1);
	SendMessage(hEdit2, WM_GETTEXT, (WPARAM)256, (LPARAM)szBuf2);

	// ������������� ��������� ������ � �������� ���������� ���� int
	_stscanf(szBuf1, _T("%d"), &nNumber1);
	_stscanf(szBuf2, _T("%d"), &nNumber2);

	if (nNumber2 != 0) {
		nResult = nNumber1 / nNumber2;

		// ��������� ����� ������ � ���������� ��������� ����������
		_stprintf(szBufRes, _T("%d"), nResult);
	}
	else {
		_stprintf(szBufRes, _T("������� �� ����"));
	} // if

	// ���������� ��� ������ � �������� ������ ����������
	SendMessage(hEditResult, WM_SETTEXT, 0, (LPARAM)szBufRes);
} // Divide


void Reset()
{
	nNumber1 = nNumber2 = nResult = 0;
	SendMessage(hEdit1, WM_SETTEXT, 0, NULL);
	SendMessage(hEdit2, WM_SETTEXT, 0, NULL);
	SendMessage(hEditResult, WM_SETTEXT, 0, NULL);
} // Reset