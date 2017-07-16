#include "Includes.h"
#include "FonBrushWindow.h"

static HDC hDC;
static HFONT hFont, hFontStatic, hFontEdit, hFontBtn, hOldFont; 
static LOGFONT lf;
static HWND hMain;   // связь с родительским окном

extern DWORD rgbBrushColor; // цвет фона фигуры
extern bool bMode;          // режим вызова - фон фигуры или фон окна

// Строки комбобокса и соответствующие им цвета
extern TCHAR *szStrColors[N_COLORS];
extern DWORD rgbPenColors[N_COLORS];

HWND hStColor1;
HWND hCombo1;

HWND hBtnFonBrshOK;        // Кнопка "OK"
HWND hBtnFonBrshCancel;    // Кнопка "Cancel"

LRESULT CALLBACK FonBrush_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
		HANDLE_MSG(hWnd, WM_CREATE, FonBrush_OnCreate);
		HANDLE_MSG(hWnd, WM_SIZE, FonBrush_OnSize);
		HANDLE_MSG(hWnd, WM_GETMINMAXINFO, FonBrush_OnGetMinMaxInfo);
		HANDLE_MSG(hWnd, WM_CLOSE, FonBrush_OnClose);
		HANDLE_MSG(hWnd, WM_DESTROY, FonBrush_OnDestroy);
		HANDLE_MSG(hWnd, WM_COMMAND, FonBrush_OnCommand);
		HANDLE_MSG(hWnd, WM_CTLCOLORSTATIC, FonBrush_OnCtlColorStatic);

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	} // switch

	return 0;
} // FonBrush_WndProc


BOOL FonBrush_OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
	hMain = lpCreateStruct->hwndParent;

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
	
	INT xPos = 10;
	INT yPos = 10;
	hStColor1 = CreateWindow(_T("static"), _T("Цвет:"), WS_CHILD | WS_VISIBLE,
		xPos, yPos, 150, 25, hWnd, NULL, lpCreateStruct->hInstance, NULL);
	yPos += 20;
	hCombo1 = CreateWindow(_T("combobox"), NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_AUTOHSCROLL | CBS_DROPDOWNLIST,
		xPos, yPos, 150, 230, hWnd, (HMENU)IDC_COMBO_, lpCreateStruct->hInstance, NULL);
	SendMessage(hCombo1, WM_SETFONT, WPARAM(hFontEdit), NULL);
	for (UINT i = 0; i < N_COLORS; i++) {
		SendMessage(hCombo1, CB_ADDSTRING, NULL, (LPARAM)szStrColors[i]);
	} // for i
	SendMessage(hCombo1, CB_SETCURSEL, 0, 0);

	xPos = 10;
	yPos += 80;
	hBtnFonBrshOK = CreateWindow(_T("button"), _T("OK"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 150, 25, hWnd, (HMENU)IDC_OKAY, lpCreateStruct->hInstance, NULL);
	SendMessage(hBtnFonBrshOK, WM_SETFONT, WPARAM(hFontBtn), NULL);
	hBtnFonBrshCancel = CreateWindow(_T("button"), _T("Отмена"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos + 190, yPos, 150, 25, hWnd, (HMENU)IDC_CANCELE, lpCreateStruct->hInstance, NULL);
	SendMessage(hBtnFonBrshCancel, WM_SETFONT, WPARAM(hFontBtn), NULL);

	yPos = 80;
	xPos = 0;
	CreateWindow(_T("button"), NULL, BS_GROUPBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 370, 76, hWnd, NULL, lpCreateStruct->hInstance, NULL);

	return TRUE;
} // FonBrush_OnCreate


void FonBrush_OnCommand(HWND hWnd, INT id, HWND hWndCtl, UINT codeNotify)
{
	INT nColor;
	static HBRUSH hBackColor;

	switch (id) {

	case IDC_OKAY:
		// Получить цвет из комбобокса и установить цвет заливки фигур
		// или фон рабочей области окна
		nColor = SendMessage(hCombo1, CB_GETCURSEL, NULL, NULL);
		if (nColor != CB_ERR) {
			if (bMode)
				rgbBrushColor = rgbPenColors[nColor];
			else {
				hBackColor = CreateSolidBrush(rgbPenColors[nColor]);
				SetClassLongPtr(hMain, GCLP_HBRBACKGROUND, (LONG)hBackColor);
			} // if
		} // if

		ShowWindow(hWnd, HIDE_WINDOW);
		InvalidateRect(hMain, NULL, TRUE);
		break;

	case IDC_CANCELE:
		ShowWindow(hWnd, HIDE_WINDOW);
		break;
	} // switch
} // FonBrush_OnCommand


void FonBrush_OnSize(HWND hWnd, UINT state, INT cx, INT cy)
{
	RECT rect;

	GetClientRect(hWnd, &rect);
	InvalidateRect(hWnd, &rect, TRUE);
} // FonBrush_OnSize


void FonBrush_OnGetMinMaxInfo(HWND hWnd, LPMINMAXINFO lpMinMaxInfo)
{
	lpMinMaxInfo->ptMinTrackSize = { FONBRUSH_WIDTH, FONBRUSH_HEIGHT };
	lpMinMaxInfo->ptMaxTrackSize = { FONBRUSH_WIDTH, FONBRUSH_HEIGHT };
} // FonBrush_OnGetMinMaxInfo


void FonBrush_OnClose(HWND hWnd)
{
	SelectFont(hDC, hOldFont);
	DeleteFont(hFont);
	DeleteFont(hFontStatic);
	DeleteFont(hFontEdit);
	DeleteFont(hFontBtn);
} // FonBrush_OnClose


void FonBrush_OnDestroy(HWND hWnd)
{
	PostQuitMessage(0);
} // FonBrush_OnDestroy


HBRUSH FonBrush_OnCtlColorStatic(HWND, HDC hDC, HWND, INT)
{
	SetBkMode(hDC, TRANSPARENT);
	hOldFont = SelectFont(hDC, hFontStatic);

	SetTextColor(hDC, RGB(0x41, 0x69, 0xE1));
	return CreateSolidBrush(FONBRUSH_BACKGROUND);
} // FonBrush_OnCtlColorStatic