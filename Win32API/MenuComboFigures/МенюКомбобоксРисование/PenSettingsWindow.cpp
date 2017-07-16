#include "Includes.h"
#include "PenSettingsWindow.h"

static HWND hMain;  // Хэндл главного окна (окна - родителя)

static HDC hDC;
static HFONT hFont, hFontStatic, hFontEdit, hFontBtn, hOldFont;
static LOGFONT lf;

// Строки комбобокса и соответствующие им цвета
TCHAR *szStrColors[N_COLORS] = {
	_T("Красный"),  _T("Зелёный"), _T("Синий"), _T("Жёлтый"),
	_T("Розовый"), _T("Фиолетовый"), _T("Шоколадный")
};
DWORD rgbPenColors[N_COLORS] = {
	RGB(0xEE, 0x00, 0x00), RGB(0x00, 0xEE, 0x00), RGB(0x00, 0x00, 0xEE), RGB(0xFF, 0xFF, 0x00),
	RGB(0xFF, 0x00, 0xFF), RGB(0xA0, 0x20, 0xF0), RGB(0xFF, 0x7F, 0x24)
};

HWND hStColor;   // Пара элементов для выбора цвета
HWND hCombo;

HWND hStPenWidth; // Пара элементов для задания толщины пера
HWND hEdPenWidth;

// По любой из кнопок окно закрывается
HWND hBtnPenOK;        // Кнопка "OK" - запомнить новые значения
HWND hBtnPenCancel;    // Кнопка "Cancel" - не запоминать новые значения

extern UINT  uPenWidth;		  // переменная для работы с шириной пера
extern DWORD rgbPenColor;     // Цвет пера

LRESULT CALLBACK PenSettings_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
		HANDLE_MSG(hWnd, WM_CREATE, PenSettings_OnCreate);
		HANDLE_MSG(hWnd, WM_SIZE, PenSettings_OnSize);
		HANDLE_MSG(hWnd, WM_GETMINMAXINFO, PenSettings_OnGetMinMaxInfo);
		HANDLE_MSG(hWnd, WM_CLOSE, PenSettings_OnClose);
		HANDLE_MSG(hWnd, WM_DESTROY, PenSettings_OnDestroy);
		HANDLE_MSG(hWnd, WM_COMMAND, PenSettings_OnCommand);
		HANDLE_MSG(hWnd, WM_CTLCOLORSTATIC, PenSettings_OnCtlColorStatic);

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	} // switch

	return 0;
} // PenSettings_WndProc


BOOL PenSettings_OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
	// Запомнить хэндл окна-родителя
	hMain = lpCreateStruct->hwndParent;

	ZeroMemory(&lf, sizeof(LOGFONT));
	_tcscpy(lf.lfFaceName, _T("Verdana"));
	lf.lfHeight = 19;
	hFontStatic = CreateFontIndirect(&lf);
	ZeroMemory(&lf, sizeof(LOGFONT));
	_tcscpy(lf.lfFaceName, _T("Georgia"));
	lf.lfHeight = 18;
	hFontEdit   = CreateFontIndirect(&lf);
	ZeroMemory(&lf, sizeof(LOGFONT));
	_tcscpy(lf.lfFaceName, _T("Consolas"));
	lf.lfHeight = 22;
	hFontBtn    = CreateFontIndirect(&lf);

	INT xPos = 10;
	INT yPos = 10;
	hStPenWidth = CreateWindow(_T("static"), _T("Толщина пера:"), WS_CHILD | WS_VISIBLE,
		xPos, yPos, 150, 25, hWnd, NULL, lpCreateStruct->hInstance, NULL);
	yPos += 20;
	hEdPenWidth = CreateWindow(_T("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
		xPos, yPos, 150, 25, hWnd, (HMENU)IDC_PENWIDTH, lpCreateStruct->hInstance, NULL);
	SendMessage(hEdPenWidth, WM_SETFONT, WPARAM(hFontEdit), NULL);
	
	yPos = 10;
	xPos += 190;
	hStColor = CreateWindow(_T("static"), _T("Цвет:"), WS_CHILD | WS_VISIBLE,
		xPos, yPos, 150, 25, hWnd, NULL, lpCreateStruct->hInstance, NULL);
	yPos += 20;
	hCombo = CreateWindow(_T("combobox"), NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_AUTOHSCROLL | CBS_DROPDOWNLIST,
		xPos, yPos, 150, 230, hWnd, (HMENU)IDC_COMBO, lpCreateStruct->hInstance, NULL);
	SendMessage(hCombo, WM_SETFONT, WPARAM(hFontEdit), NULL);
	for (UINT i = 0; i < N_COLORS; i++)	{
		SendMessage(hCombo, CB_ADDSTRING, NULL, (LPARAM)szStrColors[i]);
	} // for i
	SendMessage(hCombo, CB_SETCURSEL, 0, 0);
	
	xPos = 10;
	yPos += 85;
	hBtnPenOK = CreateWindow(_T("button"), _T("OK"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 150, 25, hWnd, (HMENU)IDC_OK, lpCreateStruct->hInstance, NULL);
	SendMessage(hBtnPenOK, WM_SETFONT, WPARAM(hFontBtn), NULL);
	hBtnPenCancel = CreateWindow(_T("button"), _T("Отмена"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos + 190, yPos, 150, 25, hWnd, (HMENU)IDC_CANCEL, lpCreateStruct->hInstance, NULL);
	SendMessage(hBtnPenCancel, WM_SETFONT, WPARAM(hFontBtn), NULL);

	yPos = 80;
	xPos = 0;
	CreateWindow(_T("button"), NULL, BS_GROUPBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 370, 86, hWnd, NULL, NULL, NULL);

	// Фокус ввода
	SetFocus(hEdPenWidth);

	return TRUE;
} // PenSettings_OnCreate


void PenSettings_OnCommand(HWND hWnd, INT id, HWND hWndCtl, UINT codeNotify)
{
	TCHAR szBuf[20];
	INT nColor;

	switch (id) {
	case IDC_OK:
		// Получить цвет из комбобокса
		nColor = SendMessage(hCombo, CB_GETCURSEL, NULL, NULL);
		if (nColor != CB_ERR) rgbPenColor = rgbPenColors[nColor];

		// Получить ширину пера
		SendMessage(hEdPenWidth, WM_GETTEXT, 20, (LPARAM)szBuf);
		if (_tcslen(szBuf) != 0) _stscanf(szBuf, _T("%u"), &uPenWidth);
		ShowWindow(hWnd, HIDE_WINDOW);
		InvalidateRect(hMain, NULL, TRUE);
		break;

	case IDC_CANCEL:
		ShowWindow(hWnd, HIDE_WINDOW);
		break;
		
	} // switch
} // PenSettings_OnCommand


void PenSettings_OnSize(HWND hWnd, UINT state, INT cx, INT cy)
{
	RECT rect;

	GetClientRect(hWnd, &rect);
	InvalidateRect(hWnd, &rect, TRUE);
} // PenSettings_OnSize


void PenSettings_OnGetMinMaxInfo(HWND hWnd, LPMINMAXINFO lpMinMaxInfo)
{
	lpMinMaxInfo->ptMinTrackSize = { PENSETTINGS_WIDTH, PENSETTINGS_HEIGHT };
	lpMinMaxInfo->ptMaxTrackSize = { PENSETTINGS_WIDTH, PENSETTINGS_HEIGHT };
} // PenSettings_OnGetMinMaxInfo

 
void PenSettings_OnClose(HWND hWnd)
{
	SelectFont(hDC, hOldFont);
	DeleteFont(hFont);
	DeleteFont(hFontStatic);
	DeleteFont(hFontEdit);
	DeleteFont(hFontBtn);
} // PenSettings_OnClose


void PenSettings_OnDestroy(HWND hWnd)
{
	PostQuitMessage(0);
} // PenSettings_OnDestroy


HBRUSH PenSettings_OnCtlColorStatic(HWND, HDC hDC, HWND, INT)
{
	SetBkMode(hDC, TRANSPARENT);
	hOldFont = SelectFont(hDC, hFontStatic);

	SetTextColor(hDC, RGB(0x41, 0x69, 0xE1));
	return CreateSolidBrush(PENSETTINGS_BACKGROUND);
} // PenSettings_OnCtlColorStatic