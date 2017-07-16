#include "Includes.h"
#include "InputWindow.h"
#include "Patient.h"

extern HWND hLstPatients;  // ������ ����� - ��������

extern Patient patient;	           // ��������� ��������
extern list<Patient>::iterator it; // ��������, ��������� �� ������� ������� ������
extern INT nResult;                // ����� ������� ������, �������������� ��������� 
extern InputMode bInputMode; // ����� ������ ���� - ����/��������������

static HDC hDC;            // ����� ��������� ����������
static HFONT hFont, hFontStatic, hFontEdit, hFontBtn, hOldFont;   // ����� ��� ������
static LOGFONT lf;         // ��������� ��� �������� ������

HWND hStFamIO;        // ������� � ���� ����� �������
HWND hStWeight;       // ������� � ���� ����� ����

HWND hEdFamIO;        // ���� ����� �������
HWND hEdWeight;       // ���� ����� ����

HWND hBtnInputWrite;  // ������ "��������"
HWND hBtnInputClose;  // ������ "�������"

extern fstream fs;    // ����� �����/������

// ��� ������� � ������ ���������
extern list<Patient> List;

LRESULT CALLBACK Input_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
		HANDLE_MSG(hWnd, WM_CREATE, Input_OnCreate);  // �������� ����
		HANDLE_MSG(hWnd, WM_SIZE, Input_OnSize);      // ��������� ������� ������
		HANDLE_MSG(hWnd, WM_GETMINMAXINFO, Input_OnGetMinMaxInfo);
		HANDLE_MSG(hWnd, WM_CLOSE, Input_OnClose);
		HANDLE_MSG(hWnd, WM_DESTROY, Input_OnDestroy);
		HANDLE_MSG(hWnd, WM_COMMAND, Input_OnCommand);
		HANDLE_MSG(hWnd, WM_CTLCOLORSTATIC, Input_OnCtlColorStatic);

		// ��������� ��������� ��� ������� �� ������������� ��������� � ����� ����
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	} // switch

	return 0;
} // Input_WndProc


// ���������� ��������� WM_CREATE - ���������� ������� "��� ��������" 
// ������ ����
BOOL Input_OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
	ZeroMemory(&lf, sizeof(LOGFONT));
	_tcscpy(lf.lfFaceName, _T("Verdana"));
	lf.lfHeight = 19;
	hFontStatic = CreateFontIndirect(&lf);
	ZeroMemory(&lf, sizeof(LOGFONT));
	_tcscpy(lf.lfFaceName, _T("Georgia"));
	lf.lfHeight = 21;
	hFontEdit   = CreateFontIndirect(&lf);
	ZeroMemory(&lf, sizeof(LOGFONT));
	_tcscpy(lf.lfFaceName, _T("Consolas"));
	lf.lfHeight = 22;
	hFontBtn    = CreateFontIndirect(&lf);
	
	// ���� ����� - ��������� ����� "�������" - "��������" / "static" - "edit"
	INT xPos = 10;
	INT yPos = 10;
	hStFamIO = CreateWindow(_T("static"), _T("������� �.�.:"), WS_CHILD | WS_VISIBLE,
		xPos, yPos, 150, 25, hWnd, NULL, lpCreateStruct->hInstance, NULL);
	yPos += 20;
	hEdFamIO = CreateWindow(_T("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
		xPos, yPos, 340, 25, hWnd, (HMENU)IDC_INPUT_EDFAMIO, lpCreateStruct->hInstance, NULL);
	SendMessage(hEdFamIO, WM_SETFONT, WPARAM(hFontEdit), NULL);


	yPos += 45;
	hStFamIO = CreateWindow(_T("static"), _T("��� (��):"), WS_CHILD | WS_VISIBLE,
		xPos, yPos, 150, 25, hWnd, NULL, lpCreateStruct->hInstance, NULL);
	yPos += 20;
	hEdWeight = CreateWindow(_T("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
		xPos, yPos, 340, 25, hWnd, (HMENU)IDC_INPUT_EDWEIGHT, lpCreateStruct->hInstance, NULL);
	SendMessage(hEdWeight, WM_SETFONT, WPARAM(hFontEdit), NULL);

	// ����������� ������
	yPos += 60;
	hBtnInputWrite = CreateWindow(_T("button"), _T("��������"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 160, 25, hWnd, (HMENU)IDC_INPUT_WRITE, lpCreateStruct->hInstance, NULL);
	SendMessage(hBtnInputWrite, WM_SETFONT, WPARAM(hFontBtn), NULL);
	hBtnInputClose = CreateWindow(_T("button"), _T("�������"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos + 180, yPos, 160, 25, hWnd, (HMENU)IDC_INPUT_CLOSE, lpCreateStruct->hInstance, NULL);
	SendMessage(hBtnInputClose, WM_SETFONT, WPARAM(hFontBtn), NULL);

	// ����� ����� ������ � ���� ����� ������� � ���������
	SetFocus(hEdFamIO);

	return TRUE;
} // Input_OnCreate


// ��������� ��������� WM_COMMAND - ��� ���������� �� ��������� ����������
// � ��������� - �� ������
void Input_OnCommand(HWND hWnd, INT id, HWND hWndCtl, UINT codeNotify)
{
	TCHAR szBuf1[100];
	TCHAR szBuf2[100];
	UINT  weight;	    // ��������������� ���������� ��� ������ � �����

	switch (id) {

		// �������
	case IDC_INPUT_CLOSE:
		// ���� ����� ����������� ����, ��������� ����
		// �������� �� ������� ����� ((
		// ������� �������� - ��. ����
		// CloseWindow(hWnd);

		// ��� ������� ���� - ������ �������� ���� � ������
		// ������� ))) ������ �� MS
		ShowWindow(hWnd, HIDE_WINDOW);
		break;

		// ��������
	case IDC_INPUT_WRITE:
		SendMessage(hEdFamIO, WM_GETTEXT, (WPARAM)100, (LPARAM)szBuf1);		
		if (_tcslen(szBuf1) == 0) return;									
		patient.setFamIO(szBuf1);											

		SendMessage(hEdWeight, WM_GETTEXT, (WPARAM)100, (LPARAM)szBuf2);
		if (_tcslen(szBuf2) == 0) return;
		_stscanf(szBuf2, _T("%u"), &weight);	// ������������� ������ � ����������� �����
		patient.setWeight(weight);

		_tcscat(szBuf1, _T(" "));
		_tcscat(szBuf1, szBuf2);

		if (bInputMode == MODE_APPEND) {
			SendMessage(hLstPatients, LB_ADDSTRING, NULL, (LPARAM)szBuf1);

			// ������� ����� �����, ���������� ��� ����� ������ 
			// ���������� ��������
			SendMessage(hEdFamIO, WM_SETTEXT, NULL, NULL);
			SendMessage(hEdWeight, WM_SETTEXT, NULL, NULL);
			// SendMessage(hEdFamIO, WM_SETFOCUS, NULL, NULL);

			// �������� ���������� �������� � ��������� - ������
			List.push_back(patient);
			patient.Save(fs, true);   // true - �.�. �������� � ����� �����
		} else {
			// �������� ��������� ������� � ������-����������, � � ������ �� ������
			*it = patient;
			SendMessage(hLstPatients, LB_DELETESTRING, nResult, NULL);
			SendMessage(hLstPatients, LB_INSERTSTRING, nResult, (LPARAM)szBuf1);

			// �������� ������ � �����
			fs.seekp(nResult*Patient::LEN_RECORD, ios::beg);
			fs.seekg(nResult*Patient::LEN_RECORD, ios::beg);
			patient.Save(fs);

			// ��������� - � ������ ������ �������� ������� �� �� ������
			SendMessage(hLstPatients, LB_SETCURSEL, nResult, NULL);
		} // if

		break;
	} // switch
} // Input_OnCommand


// ���������� ��������� WM_SIZE - ���������� ������� "��� ��������� �������" 
// ������ ����
void Input_OnSize(HWND hWnd, UINT state, INT cx, INT cy)
{
	RECT rect;       // ������������� - ��� �������� ��������� ������� ������� ���� 

	GetClientRect(hWnd, &rect);         // ������ ������� ���� ��� �����������
	InvalidateRect(hWnd, &rect, TRUE);  // �������� ������� ���������������� => ����������� WM_PAINT
} // Input_OnSize


// ����������� ������������ ������� �������� ���� ����������
// !! �������� ������ � OnSize !!
void Input_OnGetMinMaxInfo(HWND hWnd, LPMINMAXINFO lpMinMaxInfo)
{
	lpMinMaxInfo->ptMinTrackSize = { INPUT_WIDTH, INPUT_HEIGHT };
	lpMinMaxInfo->ptMaxTrackSize = { INPUT_WIDTH, INPUT_HEIGHT };
} // Input_OnGetMinMaxInfo


// ���������� ��������� WM_CLOSE - ���������� ������� "��� �������� ����" 
void Input_OnClose(HWND hWnd)
{
	SelectFont(hDC, hOldFont);
	DeleteFont(hFont);
	DeleteFont(hFontStatic);
	DeleteFont(hFontEdit);
	DeleteFont(hFontBtn);
	
	// CloseWindow(hWnd);
} // Input_OnClose


// ���������� ��������� WM_DESTROY - ���������� ������� "��� ����������� ����" 
void Input_OnDestroy(HWND hWnd)
{
	PostQuitMessage(0);
} // OnDestroy


// ��������� ���� ������������ ������������ ��������
// ��� - ��������� � ����� ������� ������� ����
HBRUSH Input_OnCtlColorStatic(HWND, HDC hDC, HWND, INT)
{
	SetBkMode(hDC, TRANSPARENT);
	hOldFont = SelectFont(hDC, hFontStatic);

	SetTextColor(hDC, RGB(0x41, 0x69, 0xE1));
	return CreateSolidBrush(INPUT_BACKGROUND);
} // Input_OnCtlColorStatic


// ������������� ���� ����� �� ��������� ����� ������� patient 
void SetInput()
{
	// ������� ��� � ����� ������
	TCHAR szBuf[20];
	_stprintf(szBuf, _T("%d"), patient.getWeight());

	// ���������� �������� ��������� ����� �����
	SendMessage(hEdFamIO, WM_SETTEXT, NULL, (LPARAM)patient.getFamIO().c_str());
	SendMessage(hEdWeight, WM_SETTEXT, NULL, (LPARAM)szBuf);
} // SetInput