#include "Includes.h"
#include "InputWindow.h"
#include "Price.h"

extern Price price;	               // ��������� ������
extern HWND hLstGoods;             // ������ ����� - ������
extern HWND hStBar;                // ������ ���������
extern fstream fs;                 // ����� �����/������
extern list<Price>::iterator it;   // ��������, ��������� �� ������� ������� ������
extern list<Price> List;           // ��� ������� � ������ ������

extern INT nResult;                // ����� ������� ������, �������������� ��������� 
extern InputMode bInputMode;       // ����� ������ ���� - ����/��������������
			  
static HDC hDC;					   // ����� ��������� ����������
static HFONT hFont, hFontStatic, hFontEdit, hFontBtn, hOldFont;
static LOGFONT lf;				   // ��������� ��� �������� ������

HWND hStShop;
HWND hStGoods;
HWND hStCost;

HWND hComboShop;
HWND hEdGoods; 
HWND hEdCost;

HWND hBtnInputSave;
HWND hBtnInputClose;

TCHAR szShops[] = _T("��������.txt");

LRESULT CALLBACK Input_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
		HANDLE_MSG(hWnd, WM_CREATE,			Input_OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND,		Input_OnCommand);
		HANDLE_MSG(hWnd, WM_SIZE,			Input_OnSize);      
		HANDLE_MSG(hWnd, WM_GETMINMAXINFO,  Input_OnGetMinMaxInfo);
		HANDLE_MSG(hWnd, WM_CLOSE,          Input_OnClose);
		HANDLE_MSG(hWnd, WM_DESTROY,        Input_OnDestroy);
		HANDLE_MSG(hWnd, WM_CTLCOLORSTATIC, Input_OnCtlColorStatic);

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	} // switch

	return 0;
} // Input_WndProc


BOOL Input_OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
	#pragma region �������� �������
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
	lf.lfHeight = 18;
	hFontBtn    = CreateFontIndirect(&lf);
	#pragma endregion
	
	#pragma region �������� ��������� �����
	INT xPos = 50;
	INT yPos = 20;
	hStShop = CreateWindow(_T("static"), _T("�������� ��������:"), WS_CHILD | WS_VISIBLE,
		xPos, yPos, 200, 25, hWnd, NULL, lpCreateStruct->hInstance, NULL);
	yPos += 20;
	hComboShop = CreateWindow(_T("combobox"), NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_AUTOHSCROLL | CBS_DROPDOWN,
		xPos, yPos, 260, 230, hWnd, (HMENU)IDC_INPUT_COMBO_SHOP, lpCreateStruct->hInstance, NULL);
	SendMessage(hComboShop, WM_SETFONT, WPARAM(hFontEdit), NULL);

	yPos += 45;
	hStGoods = CreateWindow(_T("static"), _T("�������� ������:"), WS_CHILD | WS_VISIBLE,
		xPos, yPos, 200, 25, hWnd, NULL, lpCreateStruct->hInstance, NULL);
	yPos += 20;
	hEdGoods = CreateWindow(_T("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
		xPos, yPos, 260, 25, hWnd, (HMENU)IDC_INPUT_EDGOODS, lpCreateStruct->hInstance, NULL);
	SendMessage(hEdGoods, WM_SETFONT, WPARAM(hFontEdit), NULL);

	yPos += 45;
	hStCost = CreateWindow(_T("static"), _T("���� ������:"), WS_CHILD | WS_VISIBLE,
		xPos, yPos, 200, 25, hWnd, NULL, lpCreateStruct->hInstance, NULL);
	yPos += 20;
	hEdCost = CreateWindow(_T("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
		xPos, yPos, 260, 25, hWnd, (HMENU)IDC_INPUT_EDCOST, lpCreateStruct->hInstance, NULL);
	SendMessage(hEdCost, WM_SETFONT, WPARAM(hFontEdit), NULL);
	#pragma endregion

	#pragma region �������� ������
	yPos += 93;
	hBtnInputSave = CreateWindow(_T("button"), _T("���������"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 120, 25, hWnd, (HMENU)IDC_INPUT_SAVE, lpCreateStruct->hInstance, NULL);
	SendMessage(hBtnInputSave, WM_SETFONT, WPARAM(hFontBtn), NULL);
	hBtnInputClose = CreateWindow(_T("button"), _T("�������"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos + 140, yPos, 120, 25, hWnd, (HMENU)IDC_INPUT_CLOSE, lpCreateStruct->hInstance, NULL);
	SendMessage(hBtnInputClose, WM_SETFONT, WPARAM(hFontBtn), NULL);

	yPos = 1;
	xPos = 30;
	CreateWindow(_T("button"), NULL, BS_GROUPBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 300, 220, hWnd, NULL, lpCreateStruct->hInstance, NULL);

	yPos = 230;
	xPos = 30;
	CreateWindow(_T("button"), NULL, BS_GROUPBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 300, 80, hWnd, NULL, lpCreateStruct->hInstance, NULL);
	#pragma endregion

	// ��������� �����-���� ������� �� ����� � ���������� ���������
	LoadShopNames();

	// ����� �����
	SetFocus(hComboShop);

	return TRUE;
} // Input_OnCreate


void Input_OnCommand(HWND hWnd, INT id, HWND hWndCtl, UINT codeNotify)
{
	TCHAR szBuf[150];
	TCHAR szBuf1[100];
	TCHAR szBuf2[100];
	TCHAR szBuf3[100];
	UINT  cost;

	switch (id) {

		// �������
	case IDC_INPUT_CLOSE:
		ShowWindow(hWnd, HIDE_WINDOW);
		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("������. ������ �����"));
		break;

		// ���������
	case IDC_INPUT_SAVE:
		SendMessage(hComboShop, WM_GETTEXT, (WPARAM)100, (LPARAM)szBuf1);
		if (_tcslen(szBuf1) == 0) break;
		price.setShop(szBuf1);

		SendMessage(hEdGoods, WM_GETTEXT, (WPARAM)100, (LPARAM)szBuf2);		
		if (_tcslen(szBuf2) == 0) break;									
		price.setGoods(szBuf2);											

		SendMessage(hEdCost, WM_GETTEXT, (WPARAM)100, (LPARAM)szBuf3);
		if (_tcslen(szBuf3) == 0) break;
		_stscanf(szBuf3, _T("%u"), &cost);
		price.setCost(cost);

		_stprintf(szBuf, _T("%-25s | %-32s | %10u"), szBuf1, szBuf2, cost);

		if (bInputMode == MODE_APPEND) {
			SendMessage(hLstGoods, LB_ADDSTRING, NULL, (LPARAM)szBuf);

			// ������� ����� �����
			SendMessage(hComboShop, WM_SETTEXT, NULL, NULL);
			SendMessage(hEdGoods, WM_SETTEXT, NULL, NULL);
			SendMessage(hEdCost, WM_SETTEXT, NULL, NULL);

			// �������� ����� � ��������� - ������
			List.push_back(price);
			price.Save(fs, true);   // true - �.�. �������� � ����� �����
		} else {
			// �������� ��������� ������� � ������-����������, � � ������ �� ������
			*it = price;
			SendMessage(hLstGoods, LB_DELETESTRING, nResult, NULL);
			SendMessage(hLstGoods, LB_INSERTSTRING, nResult, (LPARAM)szBuf);

			// �������� ������ � �����
			fs.seekp(nResult*Price::LEN_RECORD, ios::beg);
			price.Save(fs);

			// � ������ ������ �������� ������� �� �� ������
			SendMessage(hLstGoods, LB_SETCURSEL, nResult, NULL);
		} // if
		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("������. ������ ���������"));
		ShowWindow(hWnd, HIDE_WINDOW);
		break;
	} // switch
} // Input_OnCommand


void Input_OnSize(HWND hWnd, UINT state, INT cx, INT cy)
{
	RECT rect;

	GetClientRect(hWnd, &rect);
	InvalidateRect(hWnd, &rect, TRUE);
} // Input_OnSize


void Input_OnGetMinMaxInfo(HWND hWnd, LPMINMAXINFO lpMinMaxInfo)
{
	lpMinMaxInfo->ptMinTrackSize = { INPUT_WIDTH, INPUT_HEIGHT };
	lpMinMaxInfo->ptMaxTrackSize = { INPUT_WIDTH, INPUT_HEIGHT };
} // Input_OnGetMinMaxInfo


void Input_OnClose(HWND hWnd)
{
	SelectFont(hDC, hOldFont);
	DeleteFont(hFont);
	DeleteFont(hFontStatic);
	DeleteFont(hFontEdit);
	DeleteFont(hFontBtn);
	
	ShowWindow(hWnd, HIDE_WINDOW);
} // Input_OnClose


void Input_OnDestroy(HWND hWnd)
{
	PostQuitMessage(0);
} // OnDestroy


HBRUSH Input_OnCtlColorStatic(HWND, HDC hDC, HWND, INT)
{
	SetBkMode(hDC, TRANSPARENT);
	SelectFont(hDC, hFontStatic);
	SetTextColor(hDC, RGB(0x41, 0x69, 0xE1));
	return CreateSolidBrush(INPUT_BACKGROUND);
} // Input_OnCtlColorStatic


// ������������� ���� ����� �� ��������� ����� ������� price 
void SetInput()
{
	// �������� ��������� � ����� ������
	TCHAR szBuf[20];
	_stprintf(szBuf, _T("%u"), price.getCost());

	// ���������� �������� ��������� ����� �����
	SendMessage(hComboShop, WM_SETTEXT, NULL, (LPARAM)price.getShop().c_str());
	SendMessage(hEdGoods, WM_SETTEXT, NULL, (LPARAM)price.getGoods().c_str());
	SendMessage(hEdCost, WM_SETTEXT, NULL, (LPARAM)szBuf);
} // SetInput

// ��������� �������� ��������� � �����-���� �� �����
// � ��������� UTF-8
void LoadShopNames()
{
	TCHAR szMessage[256];

	// ����� ����� - ������� ���������
	FILE *fin = _tfopen(szShops, _T("r, ccs=UTF-8"));
	if (!fin) {
		_stprintf(szMessage, _T("���� %s �� ������ ��� �� ��������"), szShops);
		MessageBox(HWND_DESKTOP, szMessage, _T("������"), MB_OK | MB_ICONERROR);
		PostQuitMessage(1);
	} // if

	// ������ �� ����� ��������, ���������� �������� �������� � �����-����
	while (!feof(fin)) {
		// ������ ��� ������ ������ TCHAR[] - ��� ��� TCHAR[] ���������� UTF-8  
		// ������ �������� ������ � �������� �������� ������
		_fgetts(szMessage, 255, fin);
		// ������� ������ �������� ������. 
		szMessage[_tcslen(szMessage) - 1] = 0;
		SendMessage(hComboShop, CB_ADDSTRING, 0, (LPARAM)szMessage);
	} // while

	fclose(fin);
} // LoadShopNames