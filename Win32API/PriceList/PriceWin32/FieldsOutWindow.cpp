#include "Includes.h"
#include "FieldsOutWindow.h"
#include "MainWindow.h"
#include "Price.h"

static HDC hDC;            // Хэндл контекста устройства
static HFONT hFont, hFontStatic, hFontEdit, hFontBtn, hOldFont;
static LOGFONT lf;         // Структура для создания шрифта

// Чекбоксы
HWND hChBoxNmShop, hChBoxNmGoods, hChBoxCost;
BOOL CheckMode = true;   // для управления чек-боксом
UINT CheckNumber;

HWND hBtnFldsOutOK;      // Кнопка "OK"
HWND hBtnFldsOutCancel;  // Кнопка "Отмена"

extern HWND hStBar;     // Строка состояния главного окна 

// Параметры вывода, управляемые чек-боксами
// Логические флаги для управления отображением столбцов 
extern BOOL bViewShop, bViewGoods, bViewCost;

LRESULT CALLBACK FieldsOut_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
		HANDLE_MSG(hWnd, WM_CREATE,			FieldsOut_OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND,		FieldsOut_OnCommand);
		HANDLE_MSG(hWnd, WM_SIZE,			FieldsOut_OnSize);
		HANDLE_MSG(hWnd, WM_GETMINMAXINFO,  FieldsOut_OnGetMinMaxInfo);
		HANDLE_MSG(hWnd, WM_CLOSE,			FieldsOut_OnClose);
		HANDLE_MSG(hWnd, WM_DESTROY,		FieldsOut_OnDestroy);
		HANDLE_MSG(hWnd, WM_CTLCOLORSTATIC, FieldsOut_OnCtlColorStatic);

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	} // switch

	return 0;
} // FieldsOut_WndProc


BOOL FieldsOut_OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
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
	lf.lfHeight = 18;
	hFontBtn    = CreateFontIndirect(&lf);

	INT xPos = 30;
	INT yPos = 60;
	hChBoxNmShop = CreateWindow(_T("button"), _T("Название магазина"), BS_AUTOCHECKBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 200, 25, hWnd, (HMENU)IDC_FIELDSOUT_CHBOXNMSHOP, lpCreateStruct->hInstance, NULL);
	yPos += 30;
	hChBoxNmGoods = CreateWindow(_T("button"), _T("Название товара"), BS_AUTOCHECKBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 200, 25, hWnd, (HMENU)IDC_FIELDSOUT_CHBOXNMGOODS, lpCreateStruct->hInstance, NULL);
	yPos += 30;
	hChBoxCost = CreateWindow(_T("button"), _T("Цена товара"), BS_AUTOCHECKBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 200, 25, hWnd, (HMENU)IDC_FIELDSOUT_CHBOXCOST, lpCreateStruct->hInstance, NULL);

	yPos = 40;
	xPos = 20;
	CreateWindow(_T("button"), NULL, BS_GROUPBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 250, 120, hWnd, NULL, lpCreateStruct->hInstance, NULL);

	yPos += 170;
	hBtnFldsOutOK = CreateWindow(_T("button"), _T("OK"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos + 17, yPos, 100, 25, hWnd, (HMENU)IDC_FIELDSOUT_OK, lpCreateStruct->hInstance, NULL);
	SendMessage(hBtnFldsOutOK, WM_SETFONT, WPARAM(hFontBtn), NULL);
	hBtnFldsOutCancel = CreateWindow(_T("button"), _T("Отмена"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos + 130, yPos, 100, 25, hWnd, (HMENU)IDC_FIELDSOUT_CANCEL, lpCreateStruct->hInstance, NULL);
	SendMessage(hBtnFldsOutCancel, WM_SETFONT, WPARAM(hFontBtn), NULL);

	yPos = 189;
	xPos = 20;
	CreateWindow(_T("button"), NULL, BS_GROUPBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 250, 60, hWnd, NULL, lpCreateStruct->hInstance, NULL);

	// Установить значение чекбоксов по умолчанию
	SendMessage(hChBoxNmShop, BM_SETCHECK, bViewShop, NULL);
	SendMessage(hChBoxNmGoods, BM_SETCHECK, bViewGoods, NULL);
	SendMessage(hChBoxCost, BM_SETCHECK, bViewCost, NULL);

	return TRUE;
} // FieldsOut_OnCreate


void FieldsOut_OnCommand(HWND hWnd, INT id, HWND hWndCtl, UINT codeNotify)
{
	switch (id) {

		// Отмена
	case IDC_FIELDSOUT_CANCEL:
		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("Готово. Выбор столбцов не выполнен"));
		ShowWindow(hWnd, HIDE_WINDOW);
		break;

		// Опросить чек-боксы, установить логические
		// флаги для управления выводом в лист-бокс
		// главного окна
	case IDC_FIELDSOUT_OK:
		ShowWindow(hWnd, HIDE_WINDOW);
		// Мы должны повторно вывести список в этом месте кода,
		// т.к. главное окно очень сложно известить о закрытии
		// окна ввода
		ListToListbox();
		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("Готово. Выбраны столбцы для вывода"));
		break;

		// Вывод поля "Название магазина"
	case IDC_FIELDSOUT_CHBOXNMSHOP:
		bViewShop = Button_GetCheck(hWndCtl);
		break;

		// Вывод поля "Название товара"
	case IDC_FIELDSOUT_CHBOXNMGOODS:
		bViewGoods = Button_GetCheck(hWndCtl);
		break;

		// Вывод поля "Цена"
	case IDC_FIELDSOUT_CHBOXCOST:
		bViewCost = Button_GetCheck(hWndCtl);
		break;
	} // switch
} // FieldsOut_OnCommand


void FieldsOut_OnSize(HWND hWnd, UINT state, INT cx, INT cy)
{
	RECT rect;

	GetClientRect(hWnd, &rect);
	InvalidateRect(hWnd, &rect, TRUE);
} // FieldsOut_OnSize


void FieldsOut_OnGetMinMaxInfo(HWND hWnd, LPMINMAXINFO lpMinMaxInfo)
{
	lpMinMaxInfo->ptMinTrackSize = { FIELDSOUT_WIDTH, FIELDSOUT_HEIGHT };
	lpMinMaxInfo->ptMaxTrackSize = { FIELDSOUT_WIDTH, FIELDSOUT_HEIGHT };
} // FieldsOut_OnGetMinMaxInfo


void FieldsOut_OnClose(HWND hWnd)
{
	SelectFont(hDC, hOldFont);
	DeleteFont(hFont);
	DeleteFont(hFontStatic);
	DeleteFont(hFontEdit);
	DeleteFont(hFontBtn);

	ShowWindow(hWnd, HIDE_WINDOW);
} // FieldsOut_OnClose


void FieldsOut_OnDestroy(HWND hWnd)
{
	PostQuitMessage(0);
} // FieldsOut_OnDestroy


HBRUSH FieldsOut_OnCtlColorStatic(HWND, HDC hDC, HWND, INT)
{
	SetBkMode(hDC, TRANSPARENT);
	SelectFont(hDC, hFontStatic);
	SetTextColor(hDC, RGB(0x41, 0x69, 0xE1));
	return CreateSolidBrush(FIELDSOUT_BACKGROUND);
} // FieldsOut_OnCtlColorStatic


void SetFieldsOut()
{

} // SetSort