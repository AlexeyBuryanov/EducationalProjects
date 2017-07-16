#include "Includes.h"
#include "MainWindow.h"
#include "FonBrushWindow.h" 
#include "PenSettingsWindow.h"

extern HINSTANCE hAppInstance;     // дескриптор экземпляра приложения
extern TCHAR szTitleMain[];        // заголовок главного окна
extern TCHAR szClassFonBrush[];    // класс     окна настроек фона и кисти
extern TCHAR szTitleFonBrush[];    // заголовок окна настроек фона и кисти
extern TCHAR szClassPenSettings[]; // класс     окна настроек пера
extern TCHAR szTitlePenSettings[]; // заголовок окна настроек пера

// Переменные и функции для главного окна приложения
static HDC hDC;							   // Хэндл контекста устройства
static HFONT hOldFont;					   // Шрифт для вывода
static LOGFONT lf;						   // Структура для создания шрифта

// Переменные для отрисовки фигуры
static Figures figure; // Тип фигуры
UINT  uPenWidth;       // Толщина пера
DWORD rgbPenColor;     // Цвет пера
DWORD rgbBrushColor;   // Цвет кисти

// Дочерние окна ввода параметров
HWND hWndPenSet;       // параметры пера для фигуры  
HWND hWndSetColor;     // парметры кисти для фигуры
HWND hWndSetColor2;    // парметры кисти фона рабочей области окна
bool bMode; // Режим вызова окна параметров: true - фон фигуры, false - фон рабочей области

// Оконная функция - обработка сообщений, получаемых окном
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_SIZE, OnSize);
		HANDLE_MSG(hWnd, WM_GETMINMAXINFO, OnGetMinMaxInfo);
		HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hWnd, WM_CLOSE, OnClose);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
	
		// Обработка сообщений для которых не предусмотрена обработка в нашем окне
		default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	} // switch

	return 0;
} // WndProc

HMENU hMainMenu;       // Главное меню
HMENU hFigureMenu;     // Выпадающее меню "Фигура"
HMENU hSettingsMenu;   // Выпадающее меню "Настройки"

// Обработчик сообщения WM_CREATE - обработчик события "При создании" 
// нашего окна
BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
	// Не рисовать никакой фигуры, выставить стартовые значения
	// параметров пера и кистей для фона фигуры, окна 
	figure = FIG_NONE;
	rgbPenColor = RGB(0, 0, 0);
	uPenWidth = 2;
	rgbBrushColor = RGB(0xFF, 0x7F, 0x24);

	// Создание меню
	hMainMenu     = CreateMenu();
	hFigureMenu   = CreatePopupMenu();
	hSettingsMenu = CreatePopupMenu();

	AppendMenu(hMainMenu, MF_STRING | MF_POPUP, (UINT)hFigureMenu, _T("&Фигура"));
	AppendMenu(hFigureMenu, MF_STRING, IDC_CIRCLE, _T("&Круг"));
	AppendMenu(hFigureMenu, MF_STRING, IDC_TRIANGLE, _T("Тре&угольник"));
	AppendMenu(hFigureMenu, MF_STRING, IDC_RECTANGLE, _T("&Прямоугольник"));
	AppendMenu(hFigureMenu, MF_STRING, IDC_TRAPEZE, _T("&Трапеция"));
	AppendMenu(hFigureMenu, MF_SEPARATOR, NULL, _T(""));
	AppendMenu(hFigureMenu, MF_STRING, IDC_QUIT, _T("Вы&ход"));

	AppendMenu(hMainMenu, MF_STRING | MF_POPUP, (UINT)hSettingsMenu, _T("&Настройки"));
	AppendMenu(hSettingsMenu, MF_STRING, IDC_SETTINGSPEN, _T("&Параметры пера"));
	AppendMenu(hSettingsMenu, MF_STRING, IDC_COLORBRSH, _T("Цвет &кисти"));
	AppendMenu(hSettingsMenu, MF_STRING, IDC_COLORFON, _T("Цвет &фона"));

	SetMenu(hWnd, hMainMenu);

	return TRUE;
} // OnCreate


// Обработка сообщений WM_COMMAND - они посылаются от элементов управления
// в частности - от кнопок
void OnCommand(HWND hWnd, INT id, HWND hWndCtl, UINT codeNotify)
{
	switch (id) {

		// Рисуем круг
	case IDC_CIRCLE:
		figure = FIG_CIRCLE;
		break;

		// Рисуем треугольник
	case IDC_TRIANGLE:
		figure = FIG_TRIANGLE;
		break;

		// Рисуем прямоугольник
	case IDC_RECTANGLE:
		figure = FIG_RECT;
		break;

		// Рисуем равнобедренную трапецию
	case IDC_TRAPEZE:
		figure = FIG_TRAPEZE;
		break;

		// Настройка пера
	case IDC_SETTINGSPEN:
		if (!hWndPenSet) {
			hWndPenSet = CreateWindow(szClassPenSettings, szTitlePenSettings,
				WS_OVERLAPPED | WS_CAPTION | WS_BORDER | WS_DLGFRAME | WS_SYSMENU,
				150, 150, PENSETTINGS_WIDTH, PENSETTINGS_HEIGHT, hWnd, NULL, hAppInstance, NULL);
		} // if
		ShowWindow(hWndPenSet, SW_SHOWNORMAL);
		break;

		// Настройка цвета кисти для фигур
	case IDC_COLORBRSH:
		if (!hWndSetColor) {
			hWndSetColor = CreateWindow(szClassFonBrush, szTitleFonBrush,
				WS_OVERLAPPED | WS_CAPTION | WS_BORDER | WS_DLGFRAME | WS_SYSMENU,
				150, 150, FONBRUSH_WIDTH, FONBRUSH_HEIGHT, hWnd, NULL, hAppInstance, NULL);
		} // if
		bMode = true;
		ShowWindow(hWndSetColor, SW_SHOWNORMAL);
		break;

		// Настройка фона рабочей области
	case IDC_COLORFON:
		if (!hWndSetColor2) {
			hWndSetColor2 = CreateWindow(szClassFonBrush, _T("Выбор цвета фона"),
				WS_OVERLAPPED | WS_CAPTION | WS_BORDER | WS_DLGFRAME | WS_SYSMENU,
				150, 150, FONBRUSH_WIDTH, FONBRUSH_HEIGHT, hWnd, NULL, hAppInstance, NULL);
		} // if
		bMode = false;
		ShowWindow(hWndSetColor2, SW_SHOWNORMAL);
		break;

	case IDC_QUIT:   // Выход из приложения
		PostQuitMessage(0);
		break;

	} // switch
	InvalidateRect(hWnd, NULL, TRUE);
} // OnCommand


// Обработчик сообщения WM_PAINT - обработчик события "При отрисовке" 
void OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;  // Параметры контекста устройства
	RECT rect;       // Прямоугольник - для хранения координат рабочей области окна 

	hDC = BeginPaint(hWnd, &ps);    // Получить хэндл контекста устройства
	GetClientRect(hWnd, &rect);     // Получить координаты области для рисования

	// Создать перо и кисть, параметры вводим в дочерних окнах
	HPEN hPen = CreatePen(PS_SOLID, uPenWidth, rgbPenColor);
	HPEN hOldPen = SelectPen(hDC, hPen);

	HBRUSH hBrush = CreateSolidBrush(rgbBrushColor);
	HBRUSH hOldBrush = SelectBrush(hDC, hBrush);

	// Массивы точек для треугольника и трапеции
	const UINT N_POINTS1 = 3, N_POINTS2 = 4;
	POINT apt1[N_POINTS1] = { 
		{ rect.left + 100, rect.left + 270 },
		{ rect.top + 320, rect.top + 60 },
		{ rect.right - 100, rect.left + 270 } 
	};

	POINT apt2[N_POINTS2] = { 
		{ rect.left + 100, rect.left + 270 }, 
		{ rect.top + 180, rect.top + 90 },
		{ rect.top + 450, rect.top + 90 },
		{ rect.right - 100, rect.left + 270 } 
	};

	switch (figure)
	{
	case FIG_CIRCLE:
		Ellipse(hDC, rect.left + 180, rect.top + 100, rect.right - 180, rect.bottom - 100);
		break;
	case FIG_TRIANGLE:
		Polygon(hDC, apt1, N_POINTS1);
		break;
	case FIG_RECT:
		Rectangle(hDC, rect.left + 120, rect.top + 120, rect.right - 120, rect.bottom - 120);
		break;
	case FIG_TRAPEZE:
		Polygon(hDC, apt2, N_POINTS2);
		break;
	} // switch

	// Освобождаем ресурсы - перо и кисть
	SelectPen(hDC, hOldPen);
	DeletePen(hPen);
	SelectBrush(hDC, hOldBrush);
	DeleteBrush(hBrush);
	EndPaint(hWnd, &ps);            // Освободить контекст для корректной работы системы
} // OnPaint


// Обработчик сообщения WM_SIZE - обработчик события "При изменении размера" 
// нашего окна
void OnSize(HWND hWnd, UINT state, INT cx, INT cy)
{
	RECT rect;       // Прямоугольник - для хранения координат рабочей области окна 

	GetClientRect(hWnd, &rect);         // Задать область окна для перерисовки
	InvalidateRect(hWnd, &rect, TRUE);  // Объявить область недействительной => формируется WM_PAINT
} // OnSize


// Ограничение минимального размера главного окна приложения
// !! Работает вместе с OnSize !!
void OnGetMinMaxInfo(HWND hWnd, LPMINMAXINFO lpMinMaxInfo)
{
	lpMinMaxInfo->ptMinTrackSize = { MAIN_WIDTH, MAIN_HEIGHT };
	lpMinMaxInfo->ptMaxTrackSize = { MAIN_WIDTH, MAIN_HEIGHT };
} // OnGetMinMaxInfo


// Обработчик сообщения WM_CLOSE - обработчик события "При закрытии окна" 
void OnClose(HWND hWnd)
{
	SelectFont(hDC, hOldFont);

	DestroyWindow(hWnd); 
} // OnClose


// Обработчик сообщения WM_DESTROY - обработчик события "При уничтожении окна" 
void OnDestroy(HWND hWnd)
{
	PostQuitMessage(0);
} // OnDestroy


