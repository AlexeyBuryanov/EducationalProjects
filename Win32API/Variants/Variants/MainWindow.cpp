#include "Includes.h"
#include "resource.h"
#include "MainWindow.h"
#include "AboutBox.h"
#include "InputColorBox.h"
#include "TranslateBox.h"
#include "ReverseBox.h"
#include "InputCoordBox.h"
#include "ShowResultBox.h"
#include "CurConvertBox.h"

extern HINSTANCE hAppInstance;

COLOR_CONTROL Params;

HPEN   hOldPen, hPen, hPenRed, hPenGreen, hPenBlue;
HBRUSH hOldBrush, hRedBrush, hGreenBrush, hBlueBrush;

// Прикладная часть варианта 14 - переменная для хранения параметров
ParamV14 *pParam;

//
//   ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//   НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
		HANDLE_MSG(hWnd, WM_CREATE,			OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND,		OnCommand);
		HANDLE_MSG(hWnd, WM_SIZE,			OnSize);
		HANDLE_MSG(hWnd, WM_GETMINMAXINFO,  OnGetMinMaxInfo);
		HANDLE_MSG(hWnd, WM_PAINT,			OnPaint);
		HANDLE_MSG(hWnd, WM_CLOSE,			OnClose);
		HANDLE_MSG(hWnd, WM_DESTROY,		OnDestroy);
		HANDLE_MSG(hWnd, WM_CTLCOLORSTATIC, OnCtlColorStatic);

	// Обработка сообщений для которых не предусмотрена обработка в нашем окне
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	} // switch

	return 0;
} // CALLBACK WndProc


// Обработчик сообщения WM_CREATE - обработчик события "При создании" 
// нашего окна
BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
	UNREFERENCED_PARAMETER(lpCreateStruct);
	
	hPen		= CreatePen(PS_SOLID, 0, RGB(0xFF, 0xFF, 0xFF));
	hPenRed		= CreatePen(PS_SOLID, 0, RGB(0xFF, 0x00, 0x00));
	hPenGreen	= CreatePen(PS_SOLID, 0, RGB(0x00, 0xEE, 0x00));
	hPenBlue	= CreatePen(PS_SOLID, 0, RGB(0x00, 0x00, 0xEE));

	hRedBrush   = CreateSolidBrush(RGB(0xFF, 0x00, 0x00));
	hGreenBrush = CreateSolidBrush(RGB(0x00, 0xEE, 0x00));
	hBlueBrush  = CreateSolidBrush(RGB(0x00, 0x00, 0xEE));

	Params.bRed = Params.bGreen = Params.bBlue = false;
	Params.bUp  = Params.bDown  = true;

	// Создание параметров для варианта 14 и установка начальных
	// значений параметров
	pParam = new ParamV14;
	ZeroMemory(pParam, sizeof(ParamV14));

	return TRUE;
} // OnCreate


// Обработка сообщений WM_COMMAND - они посылаются от элементов управления
// в частности - от кнопок
RECT rect;       // Прямоугольник - для хранения координат рабочей области окна 
HDC hDC;		 // Хэндл контекста устройства
void OnCommand(HWND hWnd, int id, HWND hWndCtl, UINT codeNotify)
{
	UNREFERENCED_PARAMETER(hWndCtl);
	UNREFERENCED_PARAMETER(codeNotify);

	switch (id) {
	case IDM_ABOUT:
		DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_DIALOG_ABOUT), hWnd, About);
		break;

	case IDM_INPUTCOLOR:
		SetInputColorParam(&Params);
		if (DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_DIALOG_INPUTCOLOR), hWnd, InputColor) == IDOK) {
			GetInputColorParam(&Params);
		} // if
		break;

		// Изменить
	case IDM_CHANGE:
		InvalidateRect(hWnd, &rect, TRUE);
		break;

		// Вернуть прежний цвет
	case IDM_CLEAR:
		// Выбрать кисть исходного фона, указать перерисовку всего окна
		// отключить цвет, выбранный пользователем 
		SelectBrush(hDC, hOldBrush);
		Params.bUp  = Params.bDown  = true;
		Params.bRed = Params.bGreen = Params.bBlue = false;
		InvalidateRect(hWnd, &rect, TRUE);
		break;

	case IDM_TRANSLATE:
		DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_DIALOG_TRANSLATE), hWnd, Translate);
		break;

	case IDM_REVERSE:
		DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_DIALOG_REVERSE), hWnd, Reverse);
		break;

	case IDM_INPUTCOORD:
		DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_DIALOG_INPUTCOORD), hWnd, InputCoord);
		break;

	case IDM_SHOWCOORDRES:
		DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_DIALOG_SHOWRES), hWnd, ShowResult);
		break;

	case IDM_CURCONVERT:
		DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_DIALOG_CURCONVERT), hWnd, CurConvert);
		break;

	case IDM_EXIT:
		PostQuitMessage(0);
		break;
	} // switch
} // OnCommand


// Обработчик сообщения WM_SIZE - обработчик события "При изменении размера" 
// нашего окна
void OnSize(HWND hWnd, UINT state, int cx, int cy)
{
	UNREFERENCED_PARAMETER(state);
	UNREFERENCED_PARAMETER(cx);
	UNREFERENCED_PARAMETER(cy);

	GetClientRect(hWnd, &rect);         // Задать область окна для перерисовки
	InvalidateRect(hWnd, &rect, TRUE);  // Объявить область недействительной => формируется WM_PAINT
} // OnSize


// Ограничение минимального размера главного окна приложения
// !! Работает вместе с OnSize !!
void OnGetMinMaxInfo(HWND hWnd, LPMINMAXINFO lpMinMaxInfo)
{
	UNREFERENCED_PARAMETER(hWnd);

	lpMinMaxInfo->ptMinTrackSize = { 550, 400 };
	// lpMinMaxInfo->ptMaxTrackSize = {  };
} // OnGetMinMaxInfo


// Обработчик сообщения WM_PAINT - обработчик события "При отрисовке"
void OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;  // Параметры контекста устройства
	RECT rect;       // Прямоугольник - для хранения координат рабочей области окна 

	hDC = BeginPaint(hWnd, &ps);    // Получить хэндл контекста устройства
	GetClientRect(hWnd, &rect);     // Получить координаты области для рисования

	// Прорисовывать необходимо обе половинки экрана!!! 
	// Поэтому закрашиваем обе половинкт фоном, а затем
	// нужная половинка заливается нужным цветом
	SelectPen(hDC, hPen);
	SelectBrush(hDC, hOldBrush);
	Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom / 2);
	Rectangle(hDC, rect.left, rect.bottom / 2, rect.right, rect.bottom);

	if (Params.bRed) {
		SelectBrush(hDC, hRedBrush);
		SelectPen(hDC, hPenRed);
	} // if
	if (Params.bGreen) {
		SelectBrush(hDC, hGreenBrush);
		SelectPen(hDC,   hPenGreen);
	} // if
	if (Params.bBlue) {
		SelectBrush(hDC, hBlueBrush);
		SelectPen(hDC, hPenBlue);
	} // if
	
	if (Params.bUp) {
		Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom / 2);
	} // if 
	if (Params.bDown) {
		Rectangle(hDC, rect.left, rect.bottom / 2, rect.right, rect.bottom);
	} // if
	EndPaint(hWnd, &ps);    // Освободить контекст для корректной работы системы
} // OnPaint


// Обработчик сообщения WM_CLOSE - обработчик события "При закрытии окна" 
void OnClose(HWND hWnd)
{
	DestroyWindow(hWnd);
} // OnClose


// Обработчик сообщения WM_DESTROY - обработчик события "При уничтожении окна" 
void OnDestroy(HWND hWnd)
{
	UNREFERENCED_PARAMETER(hWnd);

	SelectPen(hDC, hOldPen);
	DeletePen(hPen);

	SelectBrush(hDC, hOldBrush);
	DeleteBrush(hRedBrush);
	DeleteBrush(hGreenBrush);
	DeleteBrush(hBlueBrush);

	delete pParam;

	PostQuitMessage(0);
} // OnDestroy


// Отрисовка фона статического управляющего элемента
// Фон - совпадает с фоном рабочей области окна
HBRUSH OnCtlColorStatic(HWND hWnd, HDC hDC, HWND hWndChild, int type)
{
	UNREFERENCED_PARAMETER(hWnd);
	UNREFERENCED_PARAMETER(hWndChild);
	UNREFERENCED_PARAMETER(type);

	SetBkMode(hDC, TRANSPARENT);
	return CreateSolidBrush(BACKGROUND);
} // OnCtlColorStatic