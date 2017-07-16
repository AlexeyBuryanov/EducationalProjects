#include "Includes.h"
#include "SortWindow.h"
#include "MainWindow.h"
#include "Price.h"
#include <algorithm>
#include <vector>

using std::vector;
using std::sort;

static HDC hDC;       // Хэндл контекста устройства
static HFONT hFont, hFontStatic, hFontEdit, hFontBtn, hOldFont;
static LOGFONT lf;    // Структура для создания шрифта

// Радиокнопки
HWND hRdButNmShop, hRdButNmGoods, hRdButCost, hRdButNativ;
UINT uStatus = 3;	  // для управления состоянием радиокнопок

HWND hBtnSortOK;      // Кнопка "OK"
HWND hBtnSortCancel;  // Кнопка "Отмена"

// Связь со списком товаров и магазинов в памяти
extern list<Price> List;
extern fstream fs;
extern TCHAR *szFileName;

// Строка состояния
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
	hRdButNmShop = CreateWindow(_T("button"), _T("По названию магазина"), BS_AUTORADIOBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 240, 25, hWnd, (HMENU)IDC_SORT_RDBTNNMSHOP, lpCreateStruct->hInstance, NULL);
	yPos += 30;
	hRdButNmGoods = CreateWindow(_T("button"), _T("По названию товара"), BS_AUTORADIOBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 240, 25, hWnd, (HMENU)IDC_SORT_RDBTNGOODS, lpCreateStruct->hInstance, NULL);
	yPos += 30;
	hRdButCost = CreateWindow(_T("button"), _T("По цене товара"), BS_AUTORADIOBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 200, 25, hWnd, (HMENU)IDC_SORT_RDBTNCOST, lpCreateStruct->hInstance, NULL);
	yPos += 30;
	hRdButNativ = CreateWindow(_T("button"), _T("Без сортировки"), BS_AUTORADIOBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 200, 25, hWnd, (HMENU)IDC_SORT_RDBTNNATIV, lpCreateStruct->hInstance, NULL);

	yPos = 40;
	xPos = 20;
	CreateWindow(_T("button"), NULL, BS_GROUPBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 250, 150, hWnd, NULL, lpCreateStruct->hInstance, NULL);

	yPos += 200;
	hBtnSortOK = CreateWindow(_T("button"), _T("OK"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos + 17, yPos, 100, 25, hWnd, (HMENU)IDC_SORT_OK, lpCreateStruct->hInstance, NULL);
	SendMessage(hBtnSortOK, WM_SETFONT, WPARAM(hFontBtn), NULL);
	hBtnSortCancel = CreateWindow(_T("button"), _T("Отмена"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos + 130, yPos, 100, 25, hWnd, (HMENU)IDC_SORT_CANCEL, lpCreateStruct->hInstance, NULL);
	SendMessage(hBtnSortCancel, WM_SETFONT, WPARAM(hFontBtn), NULL);

	yPos = 216;
	xPos = 20;
	CreateWindow(_T("button"), NULL, BS_GROUPBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 250, 60, hWnd, NULL, lpCreateStruct->hInstance, NULL);

	// Установить значение радиокнопки по умолчанию
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

		// Отмена
	case IDC_SORT_CANCEL:
		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("Готово. Выбор сортировки не выполнен"));
		ShowWindow(hWnd, HIDE_WINDOW);
		break;

		// Окай
	case IDC_SORT_OK:
		// Подготовка к сортировке - записать список в вектор
		// т.к. список не сортируется алгоритмом sort 
		if (uStatus >= 0 && uStatus < 3) {
			for (auto it = List.begin(); it != List.end(); ++it) {
				vec.push_back(*it);
			} // for it
		} // if

		// Выполнение сортировки списка List
		switch (uStatus) {
		case 0:
			sort(vec.begin(), vec.end(), cmpShop);
			status = _T("Готово. Сортировка по названиям магазинов");
			break;
		case 1:
			sort(vec.begin(), vec.end(), cmpGoods);
			status = _T("Готово. Сортировка по названиям товаров");
			break;
		case 2:
			sort(vec.begin(), vec.end(), cmpPrice);
			status = _T("Готово. Сортировка по ценам товаров");
			break;
		} // switch

		// Очистка списка перед формированием нового списка
		List.clear();

		// Если была сортировка, то загрузить список List новой последовательностью
		// из отсортированного вектора
		if (uStatus >= 0 && uStatus < 3) {
			for (auto it = vec.begin(); it != vec.end(); ++it) {
				List.push_back(*it);
			} // for it
		} else {
			// Перечитать из файла в список - переоткрыть файл!!!
			fs.close();
			fs.open(szFileName, ios::in | ios::out | ios::binary);
			LoadFile();
		} // if

		// Вывести новый список в главное окно
		ListToListbox();
		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)status.c_str());
		ShowWindow(hWnd, HIDE_WINDOW);
		break;

		// По названиям магазинов (по алфавиту)
	case IDC_SORT_RDBTNNMSHOP:
		uStatus = 0;
		break;

		// По наименованиям товаров (по алфавиту)
	case IDC_SORT_RDBTNGOODS:
		uStatus = 1;
		break;

		// По цене товара (по убыванию)
	case IDC_SORT_RDBTNCOST:
		uStatus = 2;
		break;

		// Вернуться к исходному порядку записей:
		// перечитать из файла
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


