#include "Includes.h"
#include "MainWindow.h"
#include "Employee.h"

// Экземпляр объекта для описания сотрудника
Employee person;

// Переменные и функции для главного окна приложения
static HDC hDC;             // Хэндл контекста устройства
static TCHAR szBuf[100];
static TCHAR szBuf1[256];	// строка ввода ФИО

static HFONT hFont, hOldFont;       // шрифт для вывода
static LOGFONT lf;                  // Структура для создания шрифта

HWND hBtnQuit;	  // выход
HWND hBtnReport;  // отчёт

// Статические элементы управления - надписи
HWND hStInitials;    // инициалы
HWND hStFamIO, hStRank, hStSkills;

HWND hEditInitial;   // строка редактирования для инициалов

// Радиокнопки
HWND hRdButEngineer;
HWND hRdButDevelop;
HWND hRdButLeadDevelop;

HWND hChBoxC, hChBoxWinApi, hChBoxHard, hChBoxAndroid;

// Переменная для управления флажком (чек-боксом)
BOOL Mode = true; 

// Переменная для управления состоянием переключателей(радиокнопок)
// 0 - IDC_RDBTNENG, 1 - IDC_RDBTNDEV, 2 - IDC_RDBTNLEAD
UINT uNumber = 1;

// Оконная функция - обработка сообщений, получаемых окном
// hWnd	  - дескриптор окна
// msg	  - числовой код сообщения
// wParam - первая часть параметров сообщения
// lParam - вторая часть параметров сообщения
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);  // создание окна
		HANDLE_MSG(hWnd, WM_SIZE, OnSize);      // Изменение размера экрана
		HANDLE_MSG(hWnd, WM_LBUTTONDOWN, OnLButtonDown);
		HANDLE_MSG(hWnd, WM_RBUTTONDOWN, OnRButtonDown);
		HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hWnd, WM_CLOSE, OnClose);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_CTLCOLORSTATIC, OnCtlColorStatic);
	
		// Обработка сообщений для которых не предусмотрена обработка в нашем окне
		default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	} // switch

	return 0;
} // WndProc


// Обработчик сообщения WM_CREATE - обработчик события "При создании" 
// нашего окна
BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
	TEXTMETRIC tm;
	INT yPos, xPos;
	hDC = GetDC(hWnd);
	GetTextMetrics(hDC, &tm);

	hFont = CreateFontIndirect(&lf);

	/*********************************Ф.И.О.*************************************/
	yPos = 30;
	xPos = 30;
	hStInitials = CreateWindow(_T("static"), _T("Фамилия и инициалы:"), WS_CHILD | WS_VISIBLE,
		xPos, yPos, 255, 25, hWnd, NULL, NULL, NULL);

	yPos += (tm.tmHeight + 2);
	hEditInitial = CreateWindow(_T("edit"), _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
		xPos, yPos, 430, tm.tmHeight + 8, hWnd, (HMENU)IDC_EDTINIT, NULL, NULL);
	SetFocus(hEditInitial);

	/*******************************Радиокнопки**********************************/
	yPos = 100;
	xPos = 30;
	// Рамка вокруг радиокнопок
	CreateWindow(_T("button"), _T(" Должность "), BS_GROUPBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 200, 110, hWnd, NULL, NULL, NULL);

	xPos = 45;
	// Группа радиокнопок (переключателей)
	hRdButEngineer = CreateWindow(_T("button"), _T("Инженер"), BS_AUTORADIOBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, 125, 120, 25, hWnd, (HMENU)IDC_RDBTNENG, NULL, NULL);
	hRdButDevelop = CreateWindow(_T("button"), _T("Программист"), BS_AUTORADIOBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, 150, 120, 25, hWnd, (HMENU)IDC_RDBTNDEV, NULL, NULL);
	hRdButLeadDevelop = CreateWindow(_T("button"), _T("Старший программист"), BS_AUTORADIOBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, 175, 170, 25, hWnd, (HMENU)IDC_RDBTNLEAD, NULL, NULL);


	/********************************Чек-боксы***********************************/
	// Рамка вокруг флажков
	yPos = 100;
	xPos = 260;
	CreateWindow(_T("button"), _T(" Знания "), BS_GROUPBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 200, 110, hWnd, NULL, NULL, NULL);

	// Флажки
	yPos = 120;
	xPos = 280;
	hChBoxC = CreateWindow(_T("button"), _T("Знает C++"), BS_AUTOCHECKBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 150, 25, hWnd, (HMENU)IDC_CHBOXC, NULL, NULL);
	yPos = 140;
	xPos = 280;
	hChBoxWinApi = CreateWindow(_T("button"), _T("Знает WinAPI"), BS_AUTOCHECKBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 150, 25, hWnd, (HMENU)IDC_CHBOXWINAPI, NULL, NULL);
	yPos = 160;
	xPos = 280;
	hChBoxHard = CreateWindow(_T("button"), _T("Знает Hardware"), BS_AUTOCHECKBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 150, 25, hWnd, (HMENU)IDC_CHBOXHARD, NULL, NULL);
	yPos = 180;
	xPos = 280;
	hChBoxAndroid = CreateWindow(_T("button"), _T("Знает Android"), BS_AUTOCHECKBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 150, 25, hWnd, (HMENU)IDC_CHBOXANDROID, NULL, NULL);


	/********************************Состояние***********************************/
	yPos = 40;
	xPos = 490;
	// Рамка вокруг надписей
	CreateWindow(_T("button"), _T(" Данные "), BS_GROUPBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 330, 265, hWnd, NULL, NULL, NULL);

	// Фамилия И.О.
	yPos = 70;
	xPos = 510;
	hStFamIO = CreateWindow(_T("static"), szBuf1, WS_CHILD | WS_VISIBLE,
		xPos, yPos, 255, 25, hWnd, NULL, NULL, NULL);

	// Должность
	yPos = 90;
	xPos = 510;
	hStRank = CreateWindow(_T("static"), _T(" "), WS_CHILD | WS_VISIBLE,
		xPos, yPos, 255, 25, hWnd, NULL, NULL, NULL);

	// Навыки
	yPos = 110;
	xPos = 510;
	hStSkills = CreateWindow(_T("static"), _T(" "), WS_CHILD | WS_VISIBLE,
		xPos, yPos, 255, 25, hWnd, NULL, NULL, NULL);

	/**********************************Отчёт*************************************/
	yPos = 265;
	xPos = 50;
	hBtnReport = CreateWindow(_T("button"), _T("Отчёт"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 180, 25, hWnd, (HMENU)IDC_REPORT, NULL, NULL);

	/**********************************Выход*************************************/
	yPos = 265;
	xPos = 260;
	hBtnQuit = CreateWindow(_T("button"), _T("Выход"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 180, 25, hWnd, (HMENU)IDC_QUIT, NULL, NULL);

	// Рамка вокруг кнопок выход и отчёт
	yPos = 240;
	xPos = 30;
	CreateWindow(_T("button"), NULL, BS_GROUPBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 430, 65, hWnd, NULL, NULL, NULL);

	// Установить управляющие элементы в соответствии с полями объекта
	person.Setup();
	return TRUE;
} // OnCreate


// Обработка сообщений WM_COMMAND - они посылаются от элементов управления
// в частности - от кнопок
void OnCommand(HWND hWnd, INT id, HWND hWndCtl, UINT codeNotify)
{
	LRESULT cbState;
	TCHAR szBuf[100];

	switch (id) {

	case IDC_CHBOXC:
		cbState = Button_GetCheck(hWndCtl);
		person.SetSkill(0, (cbState == BST_CHECKED) ? TRUE : FALSE);
		break;

	case IDC_CHBOXWINAPI:
		cbState = Button_GetCheck(hWndCtl);
		person.SetSkill(1, (cbState == BST_CHECKED) ? TRUE : FALSE);
		break;

	case IDC_CHBOXHARD:
		cbState = Button_GetCheck(hWndCtl);
		person.SetSkill(2, (cbState == BST_CHECKED) ? TRUE : FALSE);
		break;

	case IDC_CHBOXANDROID:
		cbState = Button_GetCheck(hWndCtl);
		person.SetSkill(3, (cbState == BST_CHECKED) ? TRUE : FALSE);
		break;

		// получить номер установленной радиокнопки - код должности
	case IDC_RDBTNENG:
		person.SetRank(0);
		break;
	case IDC_RDBTNDEV:
		person.SetRank(1);
		break;
	case IDC_RDBTNLEAD:
		person.SetRank(2);
		break;

		// Обработка нажатия кнопки "Отчет"
	case IDC_REPORT:
		SendMessage(hEditInitial, WM_GETTEXT, (WPARAM)100, (LPARAM)szBuf);
		person.SetFamIO(szBuf);

		person.Show();
		break;

	case IDC_QUIT:
		int nReply = MessageBox(hWnd, _T("Вы действительно хотите выйти?"), _T("Выход"), MB_YESNO | MB_ICONQUESTION);
		if (nReply == IDYES)
		PostQuitMessage(0);
		break;
	} // switch
} // OnCommand


// Обработчик сообщения WM_SIZE - обработчик события "При изменении размера" 
// нашего окна
void OnSize(HWND hWnd, UINT state, INT cx, INT cy)
{
	RECT rect;       // Прямоугольник - для хранения координат рабочей области окна 

	GetClientRect(hWnd, &rect);         // Задать область окна для перерисовки
	InvalidateRect(hWnd, &rect, TRUE);  // Объявить область недействительной => формируется WM_PAINT
} // OnSize


// Обработчик сообщения WM_LBUTTONDOWN - обработчик события "Щелчок ЛКМ" 
void OnLButtonDown(HWND hWnd, BOOL fDoubleClick, INT x, INT y, UINT keyFlags)
{
	RECT rect;       // Прямоугольник - для хранения координат рабочей области окна 

	GetClientRect(hWnd, &rect);
	InvalidateRect(hWnd, &rect, TRUE);  // !!!!! Перерисовываем по этому вызову !!!!!
} // OnLButtonDown


// Обработчик сообщения WM_RBUTTONDOWN - обработчик события "Щелчок ПКМ" 
void OnRButtonDown(HWND hWnd, BOOL fDoubleClick, INT x, INT y, UINT keyFlags)
{
	RECT rect;       // Прямоугольник - для хранения координат рабочей области окна 

	GetClientRect(hWnd, &rect);
	InvalidateRect(hWnd, &rect, TRUE);  // !!!!! Перерисовываем по этому вызову !!!!!
} // OnRButtonDown


// Обработчик сообщения WM_PAINT - обработчик события "При отрисовке" 
void OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;  // Параметры контекста устройства
	RECT rect;       // Прямоугольник - для хранения координат рабочей области окна 

	hDC = BeginPaint(hWnd, &ps);    // Получить хэндл контекста устройства
	GetClientRect(hWnd, &rect);     // Получить координаты области для рисования

	ZeroMemory(&lf, sizeof(LOGFONT));
	_tcscpy(lf.lfFaceName, _T("Consolas"));

	EndPaint(hWnd, &ps);            // Освободить контекст для корректной работы системы
} // OnPaint


// Обработчик сообщения WM_CLOSE - обработчик события "При закрытии окна" 
void OnClose(HWND hWnd)
{
	SelectFont(hDC, hOldFont);
	DeleteFont(hFont);

	DestroyWindow(hWnd);
} // OnClose


// Обработчик сообщения WM_DESTROY - обработчик события "При уничтожении окна" 
void OnDestroy(HWND hWnd)
{
	PostQuitMessage(0);
} // OnDestroy


// Отрисовка фона статического управляющего элемента
// Фон - совпадает с фоном рабочей области окна
HBRUSH OnCtlColorStatic(HWND, HDC hDC, HWND, INT)
{
	SetBkMode(hDC, TRANSPARENT);
	hOldFont = SelectFont(hDC, hFont);

	SetTextColor(hDC, RGB(0x00, 0x00, 0x80));
	return CreateSolidBrush(BACKGROUND);
} // OnCtlColorStatic