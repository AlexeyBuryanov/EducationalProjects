#include "Includes.h"
#include "MainWindow.h"

// ���������� � ������� ��� �������� ���� ����������
static HDC hDC;                 // ����� ��������� ����������
static HFONT hFont, hOldFont;   // ����� ��� ������
static LOGFONT lf;              // ��������� ��� �������� ������

HWND hBtnQuit;
// ������ �����
HWND hListBox1, hListBox2;
/*         �������� ������         |            �������            |   ��������   |              ������� ������               */
HWND hBtnAddString1, hBtnAddString2, hBtnDelStringL, hBtnDelStringR, hBtnGetString, hBtnClearAll, hBtnClearLeft, hBtnClearRight;
HWND hBtnPushLeft, hBtnPushRight;  // ����������� ��������� ������ �� ������ ������ � ������
/*�������� ����� | ������1 | ������2 - ����������� �������*/
HWND hStText, hStList1, hStList2;
// ������ ����� - �������� ������
HWND hEdText;       
/*�������� � ����� ������  | ������ ������*/
HWND hBtnInputLeft, hBtnInputRight;

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
	INT yPos, xPos;
	
	ZeroMemory(&lf, sizeof(LOGFONT));
	_tcscpy(lf.lfFaceName, _T("Verdana"));
	lf.lfHeight = 19;
	hFont    = CreateFontIndirect(&lf);
	hOldFont = SelectFont(hDC, hFont);

	
	xPos = 40;
	yPos = 20;
	hStList1 = CreateWindow(_T("static"), _T("������ ����� �1:"), WS_CHILD | WS_VISIBLE,
		xPos, yPos, 260, 25, hWnd, NULL, NULL, NULL);

	yPos += 20;
	hListBox1 = CreateWindow(_T("listbox"), NULL, LBS_NOTIFY | WS_VSCROLL | WS_BORDER | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 210, 410, hWnd, (HMENU)IDC_LISTBOX1, lpCreateStruct->hInstance, NULL);

	
	xPos = 300;
	yPos = 50;
	hStText = CreateWindow(_T("static"), _T("������ ������:"), WS_CHILD | WS_VISIBLE,
		xPos, yPos, 260, 25, hWnd, NULL, NULL, NULL);
	yPos += 20;
	hEdText = CreateWindow(_T("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
		xPos, yPos, 260, 25, hWnd, (HMENU)IDC_EDTTEXT, NULL, NULL);
	yPos += 40;
	hBtnInputLeft = CreateWindow(_T("button"), _T("<<"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 100, 25, hWnd, (HMENU)IDC_BTNINPLEFT, lpCreateStruct->hInstance, NULL);
	xPos += 160;
	hBtnInputRight = CreateWindow(_T("button"), _T(">>"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 100, 25, hWnd, (HMENU)IDC_BTNINPRIGHT, lpCreateStruct->hInstance, NULL);

	
	xPos = 610;
	yPos = 20;
	hStList2 = CreateWindow(_T("static"), _T("������ ����� �2:"), WS_CHILD | WS_VISIBLE,
		xPos, yPos, 260, 25, hWnd, NULL, NULL, NULL);

	yPos += 20;
	hListBox2 = CreateWindow(_T("listbox"), NULL, LBS_NOTIFY | WS_VSCROLL | WS_BORDER | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 210, 410, hWnd, (HMENU)IDC_LISTBOX2, lpCreateStruct->hInstance, NULL);

	
	xPos = 300;
	yPos = 150;
	hBtnDelStringL = CreateWindow(_T("button"), _T("������� ������ �� ������ �1"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 260, 25, hWnd, (HMENU)IDC_BTNDELLEFT, lpCreateStruct->hInstance, NULL);
	yPos += 40;
	hBtnDelStringR = CreateWindow(_T("button"), _T("������� ������ �� ������ �2"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 260, 25, hWnd, (HMENU)IDC_BTNDELRIGHT, lpCreateStruct->hInstance, NULL);

	
	xPos = 300;
	yPos = 230;
	hBtnPushRight = CreateWindow(_T("button"), _T(">>>"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 120, 25, hWnd, (HMENU)IDC_BTNPUSHRIGHT, lpCreateStruct->hInstance, NULL);
	xPos += 140;
	hBtnPushLeft = CreateWindow(_T("button"), _T("<<<"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 120, 25, hWnd, (HMENU)IDC_BTNPUSHLEFT, lpCreateStruct->hInstance, NULL);
	
	xPos = 300;
	yPos = 270;
	hBtnClearLeft = CreateWindow(_T("button"), _T("������� ������� ������"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 260, 25, hWnd, (HMENU)IDC_BTNCLRLEFT, lpCreateStruct->hInstance, NULL);
	yPos += 40;
	hBtnClearRight = CreateWindow(_T("button"), _T("������� ������� ������"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 260, 25, hWnd, (HMENU)IDC_BTNCLRRIGHT, lpCreateStruct->hInstance, NULL);
	yPos += 40;
	hBtnClearAll = CreateWindow(_T("button"), _T("������� ���� ������� �����"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 260, 25, hWnd, (HMENU)IDC_BTNCLR, lpCreateStruct->hInstance, NULL);
	
	yPos += 40;
	hBtnQuit = CreateWindow(_T("button"), _T("���������� ������"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 260, 35, hWnd, (HMENU)IDC_QUIT, NULL, NULL);

	// ������� �� ������ ����� �������
	yPos = 32;
	xPos = 280;
	CreateWindow(_T("button"), NULL, BS_GROUPBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 300, 411, hWnd, NULL, NULL, NULL);

	return TRUE;
} // OnCreate


// ��������� ��������� WM_COMMAND - ��� ���������� �� ��������� ����������
// � ��������� - �� ������
void OnCommand(HWND hWnd, INT id, HWND hWndCtl, UINT codeNotify)
{
	INT nReply;
	TCHAR szStr[100];   // ������ ��� ������ �� �������

	INT nCurString;

	switch (id) {

	case IDC_BTNINPLEFT:
		SendMessage(hEdText, WM_GETTEXT, (WPARAM)100, (LPARAM)szStr);    
		if (_tcslen(szStr) == 0) break;
		SendMessage(hListBox1, LB_ADDSTRING, NULL, (LPARAM)szStr);     
		SendMessage(hEdText, WM_SETTEXT, NULL, NULL);                  
		break;

	case IDC_BTNINPRIGHT:
		SendMessage(hEdText, WM_GETTEXT, (WPARAM)100, (LPARAM)szStr);    
		if (_tcslen(szStr) == 0) break;
		SendMessage(hListBox2, LB_ADDSTRING, NULL, (LPARAM)szStr);     
		SendMessage(hEdText, WM_SETTEXT, NULL, NULL);                  
		break;

	case IDC_BTNDELLEFT:
		nCurString = SendMessage(hListBox1, LB_GETCURSEL, NULL, NULL);
		if (nCurString != LB_ERR) {
			SendMessage(hListBox1, LB_DELETESTRING, (WPARAM)nCurString, 0);
		} // if
		break;

	case IDC_BTNDELRIGHT:
		nCurString = SendMessage(hListBox2, LB_GETCURSEL, NULL, NULL);
		if (nCurString != LB_ERR) {
			SendMessage(hListBox2, LB_DELETESTRING, (WPARAM)nCurString, 0);
		} // if
		break;

	case IDC_BTNPUSHRIGHT:
		nCurString = SendMessage(hListBox1, LB_GETCURSEL, NULL, NULL);			  
		if (nCurString != LB_ERR) {												  
			SendMessage(hListBox1, LB_GETTEXT, (WPARAM)nCurString, (LPARAM)szStr);
			SendMessage(hListBox2, LB_ADDSTRING, NULL, (LPARAM)szStr);			  
			SendMessage(hListBox1, LB_DELETESTRING, (WPARAM)nCurString, 0);		  
		} // if
		break;

	case IDC_BTNPUSHLEFT:
		nCurString = SendMessage(hListBox2, LB_GETCURSEL, NULL, NULL);			  
		if (nCurString != LB_ERR) {												  
			SendMessage(hListBox2, LB_GETTEXT, (WPARAM)nCurString, (LPARAM)szStr);
			SendMessage(hListBox1, LB_ADDSTRING, NULL, (LPARAM)szStr);			  
			SendMessage(hListBox2, LB_DELETESTRING, (WPARAM)nCurString, 0);		  
		} // if
		break;

	case IDC_BTNCLRLEFT:
		SendMessage(hListBox1, LB_RESETCONTENT, NULL, NULL);
		break;

	case IDC_BTNCLRRIGHT:
		SendMessage(hListBox2, LB_RESETCONTENT, NULL, NULL);
		break;

	case IDC_BTNCLR:
		SendMessage(hListBox1, LB_RESETCONTENT, NULL, NULL);
		SendMessage(hListBox2, LB_RESETCONTENT, NULL, NULL);
		break;

	case IDC_QUIT:
		nReply = MessageBox(hWnd, _T("����� �� ���� ����������?.."), _T("�� �������!"), MB_YESNO | MB_ICONINFORMATION);
		if (nReply == IDNO) PostQuitMessage(0);
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

	SetTextColor(hDC, RGB(0xFF, 0x45, 0x00));
	return CreateSolidBrush(BACKGROUND);
} // OnCtlColorStatic