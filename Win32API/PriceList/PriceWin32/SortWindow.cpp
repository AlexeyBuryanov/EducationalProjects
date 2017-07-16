#include "Includes.h"
#include "SortWindow.h"
#include "MainWindow.h"
#include "Price.h"
#include <algorithm>
#include <vector>

using std::vector;
using std::sort;

static HDC hDC;       // ����� ��������� ����������
static HFONT hFont, hFontStatic, hFontEdit, hFontBtn, hOldFont;
static LOGFONT lf;    // ��������� ��� �������� ������

// �����������
HWND hRdButNmShop, hRdButNmGoods, hRdButCost, hRdButNativ;
UINT uStatus = 3;	  // ��� ���������� ���������� �����������

HWND hBtnSortOK;      // ������ "OK"
HWND hBtnSortCancel;  // ������ "������"

// ����� �� ������� ������� � ��������� � ������
extern list<Price> List;
extern fstream fs;
extern TCHAR *szFileName;

// ������ ���������
extern HWND hStBar;

LRESULT CALLBACK Sort_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
		HANDLE_MSG(hWnd, WM_CREATE,			Sort_OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND,		Sort_OnCommand);
		HANDLE_MSG(hWnd, WM_SIZE,			Sort_OnSize);
		HANDLE_MSG(hWnd, WM_GETMINMAXINFO,  Sort_OnGetMinMaxInfo);
		HANDLE_MSG(hWnd, WM_CLOSE,			Sort_OnClose);
		HANDLE_MSG(hWnd, WM_DESTROY,		Sort_OnDestroy);
		HANDLE_MSG(hWnd, WM_CTLCOLORSTATIC, Sort_OnCtlColorStatic);

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	} // switch

	return 0;
} // Sort_WndProc


BOOL Sort_OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
	ZeroMemory(&lf, sizeof(LOGFONT));
	_tcscpy(lf.lfFaceName, _T("Verdana"));
	lf.lfHeight = 20;
	hFontStatic = CreateFontIndirect(&lf);
	ZeroMemory(&lf, sizeof(LOGFONT));
	_tcscpy(lf.lfFaceName, _T("Georgia"));
	lf.lfHeight = 21;
	hFontEdit   = CreateFontIndirect(&lf);
	ZeroMemory(&lf, sizeof(LOGFONT));
	_tcscpy(lf.lfFaceName, _T("Consolas"));
	lf.lfHeight = 18;
	hFontBtn    = CreateFontIndirect(&lf);

	INT xPos = 30;
	INT yPos = 60;
	hRdButNmShop = CreateWindow(_T("button"), _T("�� �������� ��������"), BS_AUTORADIOBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 240, 25, hWnd, (HMENU)IDC_SORT_RDBTNNMSHOP, lpCreateStruct->hInstance, NULL);
	yPos += 30;
	hRdButNmGoods = CreateWindow(_T("button"), _T("�� �������� ������"), BS_AUTORADIOBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 240, 25, hWnd, (HMENU)IDC_SORT_RDBTNGOODS, lpCreateStruct->hInstance, NULL);
	yPos += 30;
	hRdButCost = CreateWindow(_T("button"), _T("�� ���� ������"), BS_AUTORADIOBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 200, 25, hWnd, (HMENU)IDC_SORT_RDBTNCOST, lpCreateStruct->hInstance, NULL);
	yPos += 30;
	hRdButNativ = CreateWindow(_T("button"), _T("��� ����������"), BS_AUTORADIOBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 200, 25, hWnd, (HMENU)IDC_SORT_RDBTNNATIV, lpCreateStruct->hInstance, NULL);

	yPos = 40;
	xPos = 20;
	CreateWindow(_T("button"), NULL, BS_GROUPBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 250, 150, hWnd, NULL, lpCreateStruct->hInstance, NULL);

	yPos += 200;
	hBtnSortOK = CreateWindow(_T("button"), _T("OK"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos + 17, yPos, 100, 25, hWnd, (HMENU)IDC_SORT_OK, lpCreateStruct->hInstance, NULL);
	SendMessage(hBtnSortOK, WM_SETFONT, WPARAM(hFontBtn), NULL);
	hBtnSortCancel = CreateWindow(_T("button"), _T("������"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos + 130, yPos, 100, 25, hWnd, (HMENU)IDC_SORT_CANCEL, lpCreateStruct->hInstance, NULL);
	SendMessage(hBtnSortCancel, WM_SETFONT, WPARAM(hFontBtn), NULL);

	yPos = 216;
	xPos = 20;
	CreateWindow(_T("button"), NULL, BS_GROUPBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 250, 60, hWnd, NULL, lpCreateStruct->hInstance, NULL);

	// ���������� �������� ����������� �� ���������
	CheckRadioButton(hWnd, IDC_SORT_RDBTNNMSHOP, IDC_SORT_RDBTNNATIV, IDC_SORT_RDBTNNMSHOP + uStatus);

	return TRUE;
} // Sort_OnCreate


void Sort_OnCommand(HWND hWnd, INT id, HWND hWndCtl, UINT codeNotify)
{
	CmpShop cmpShop;
	CmpGoods cmpGoods;
	CmpPrice cmpPrice;

	vector<Price> vec;
	wstring status;

	switch (id) {

		// ������
	case IDC_SORT_CANCEL:
		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("������. ����� ���������� �� ��������"));
		ShowWindow(hWnd, HIDE_WINDOW);
		break;

		// ����
	case IDC_SORT_OK:
		// ���������� � ���������� - �������� ������ � ������
		// �.�. ������ �� ����������� ���������� sort 
		if (uStatus >= 0 && uStatus < 3) {
			for (auto it = List.begin(); it != List.end(); ++it) {
				vec.push_back(*it);
			} // for it
		} // if

		// ���������� ���������� ������ List
		switch (uStatus) {
		case 0:
			sort(vec.begin(), vec.end(), cmpShop);
			status = _T("������. ���������� �� ��������� ���������");
			break;
		case 1:
			sort(vec.begin(), vec.end(), cmpGoods);
			status = _T("������. ���������� �� ��������� �������");
			break;
		case 2:
			sort(vec.begin(), vec.end(), cmpPrice);
			status = _T("������. ���������� �� ����� �������");
			break;
		} // switch

		// ������� ������ ����� ������������� ������ ������
		List.clear();

		// ���� ���� ����������, �� ��������� ������ List ����� �������������������
		// �� ���������������� �������
		if (uStatus >= 0 && uStatus < 3) {
			for (auto it = vec.begin(); it != vec.end(); ++it) {
				List.push_back(*it);
			} // for it
		} else {
			// ���������� �� ����� � ������ - ����������� ����!!!
			fs.close();
			fs.open(szFileName, ios::in | ios::out | ios::binary);
			LoadFile();
		} // if

		// ������� ����� ������ � ������� ����
		ListToListbox();
		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)status.c_str());
		ShowWindow(hWnd, HIDE_WINDOW);
		break;

		// �� ��������� ��������� (�� ��������)
	case IDC_SORT_RDBTNNMSHOP:
		uStatus = 0;
		break;

		// �� ������������� ������� (�� ��������)
	case IDC_SORT_RDBTNGOODS:
		uStatus = 1;
		break;

		// �� ���� ������ (�� ��������)
	case IDC_SORT_RDBTNCOST:
		uStatus = 2;
		break;

		// ��������� � ��������� ������� �������:
		// ���������� �� �����
	case IDC_SORT_RDBTNNATIV:
		uStatus = 3;
		break;

	} // switch
} // Sort_OnCommand


void Sort_OnSize(HWND hWnd, UINT state, INT cx, INT cy)
{
	RECT rect;

	GetClientRect(hWnd, &rect);
	InvalidateRect(hWnd, &rect, TRUE);
} // Sort_OnSize


void Sort_OnGetMinMaxInfo(HWND hWnd, LPMINMAXINFO lpMinMaxInfo)
{
	lpMinMaxInfo->ptMinTrackSize = { SORT_WIDTH, SORT_HEIGHT };
	lpMinMaxInfo->ptMaxTrackSize = { SORT_WIDTH, SORT_HEIGHT };
} // Sort_OnGetMinMaxInfo


void Sort_OnClose(HWND hWnd)
{
	SelectFont(hDC, hOldFont);
	DeleteFont(hFont);
	DeleteFont(hFontStatic);
	DeleteFont(hFontEdit);
	DeleteFont(hFontBtn);

	ShowWindow(hWnd, HIDE_WINDOW);
} // Sort_OnClose


void Sort_OnDestroy(HWND hWnd)
{
	PostQuitMessage(0);
} // Sort_OnDestroy


HBRUSH Sort_OnCtlColorStatic(HWND, HDC hDC, HWND, INT)
{
	SetBkMode(hDC, TRANSPARENT);
	SelectFont(hDC, hFontStatic);
	SetTextColor(hDC, RGB(0x41, 0x69, 0xE1));
	return CreateSolidBrush(SORT_BACKGROUND);
} // Sort_OnCtlColorStatic


