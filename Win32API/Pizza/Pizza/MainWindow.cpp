#include "Includes.h"
#include "MainWindow.h"
#include "Pizza.h"

// Экземпляр объекта для описания заказа
static Pizza *pizza;

// Переменные и функции для главного окна приложения
static HDC hDC;                 // Хэндл контекста устройства
static HFONT hFont, hOldFont;   // Шрифт для вывода
static LOGFONT lf;              // Структура для создания шрифта

static TCHAR szBufFio[256];	    // Строка ввода ФИО
static TCHAR szBufPhone[15];	// Строка ввода номера телефона

HWND hBtnQuit;					// Выход
HWND hBtnOrder;					// Заказать

// Статические элементы управления
//    инициалы      номер
HWND hStInitials, hStPhone;

// Строки редактирования для инициалов и номера телефона
HWND hEditInitial, hEditPhone;

/*   ФИО        номер т.     скидка      опции   */
HWND hStFamIO, hStPNumber, hStDiscount, hStOptions;

// Радиокнопки для скидки
HWND hRdBut0, hRdBut5, hRdBut15;

// Флажки для компонентов пиццы
/*       сыр     ,   оливки   ,    грибы   ,    колбаса  */
HWND hChBoxCheese, hChBoxOlive, hChBoxFungi, hChBoxSausage;

// Переменная для управления режимом
BOOL Mode = true;

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
		//HANDLE_MSG(hWnd, WM_GETMINMAXINFO, OnGetMinMaxInfo);
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
	pizza = new Pizza();

	TEXTMETRIC tm;
	INT yPos, xPos;
	hDC = GetDC(hWnd);
	GetTextMetrics(hDC, &tm);

	hFont = CreateFontIndirect(&lf);

	/*********************************Ф.И.О.*************************************/
	yPos = 30;
	xPos = 30;
	hStInitials = CreateWindow(_T("static"), _T("ФИО заказчика пиццы:"), WS_CHILD | WS_VISIBLE,
		xPos, yPos, 180, 25, hWnd, NULL, NULL, NULL);

	yPos += (tm.tmHeight + 2);
	hEditInitial = CreateWindow(_T("edit"), _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
		xPos, yPos, 200, tm.tmHeight + 8, hWnd, (HMENU)IDC_EDTINIT, NULL, NULL);
	SetFocus(hEditInitial);

	/******************************Номер телефона********************************/
	yPos = 30;
	xPos = 300;
	hStPhone = CreateWindow(_T("static"), _T("Номер телефона:"), WS_CHILD | WS_VISIBLE,
		xPos, yPos, 180, 25, hWnd, NULL, NULL, NULL);

	yPos += (tm.tmHeight + 2);
	hEditPhone = CreateWindow(_T("edit"), _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
		xPos, yPos, 200, tm.tmHeight + 8, hWnd, (HMENU)IDC_EDTINIT, NULL, NULL);

	/*******************************Радиокнопки**********************************/
	yPos = 100;
	xPos = 30;
	// Рамка вокруг радиокнопок
	CreateWindow(_T("button"), _T(" Скидка "), BS_GROUPBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 75, 110, hWnd, NULL, NULL, NULL);

	xPos = 45;
	// Группа радиокнопок (переключателей)
	hRdBut0 = CreateWindow(_T("button"), _T("0%"), BS_AUTORADIOBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, 125, 50, 25, hWnd, (HMENU)IDC_RDBTN0, NULL, NULL);
	hRdBut5 = CreateWindow(_T("button"), _T("5%"), BS_AUTORADIOBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, 150, 50, 25, hWnd, (HMENU)IDC_RDBTN5, NULL, NULL);
	hRdBut15 = CreateWindow(_T("button"), _T("15%"), BS_AUTORADIOBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, 175, 50, 25, hWnd, (HMENU)IDC_RDBTN15, NULL, NULL);

	/********************************Чек-боксы***********************************/
	// Рамка вокруг флажков
	yPos = 100;
	xPos = 385;
	CreateWindow(_T("button"), _T(" Ингредиенты "), BS_GROUPBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 115, 110, hWnd, NULL, NULL, NULL);

	// Флажки
	yPos = 120;
	xPos = 405;
	hChBoxCheese = CreateWindow(_T("button"), _T("Сыр"), BS_AUTOCHECKBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 70, 25, hWnd, (HMENU)IDC_CHBOXCHEESE, NULL, NULL);
	yPos = 140;
	xPos = 405;
	hChBoxOlive = CreateWindow(_T("button"), _T("Оливки"), BS_AUTOCHECKBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 70, 25, hWnd, (HMENU)IDC_CHBOXOLIVE, NULL, NULL);
	yPos = 160;
	xPos = 405;
	hChBoxFungi = CreateWindow(_T("button"), _T("Грибы"), BS_AUTOCHECKBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 70, 25, hWnd, (HMENU)IDC_CHBOXFUNGI, NULL, NULL);
	yPos = 180;
	xPos = 405;
	hChBoxSausage = CreateWindow(_T("button"), _T("Колбаса"), BS_AUTOCHECKBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 80, 25, hWnd, (HMENU)IDC_CHBOXSAUSAGE, NULL, NULL);

	/********************************Состояние***********************************/
	yPos = 100;
	xPos = 110;
	// Рамка вокруг надписей
	CreateWindow(_T("button"), _T(" Заказ "), BS_GROUPBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 270, 110, hWnd, NULL, NULL, NULL);

	// Фамилия И.О.
	yPos = 120;
	xPos = 125;
	hStFamIO = CreateWindow(_T("static"), szBufFio, WS_CHILD | WS_VISIBLE,
		xPos, yPos, 240, 25, hWnd, NULL, NULL, NULL);
	
	// Номер телефона
	yPos = 140;
	xPos = 125;
	hStPNumber = CreateWindow(_T("static"), szBufPhone, WS_CHILD | WS_VISIBLE,
		xPos, yPos, 240, 25, hWnd, NULL, NULL, NULL);

	// Скидка
	yPos = 160;
	xPos = 125;
	hStDiscount = CreateWindow(_T("static"), _T(" "), WS_CHILD | WS_VISIBLE,
		xPos, yPos, 240, 25, hWnd, NULL, NULL, NULL);

	// Опции
	yPos = 180;
	xPos = 125;
	hStOptions = CreateWindow(_T("static"), _T(" "), WS_CHILD | WS_VISIBLE,
		xPos, yPos, 240, 25, hWnd, NULL, NULL, NULL);

	/**********************************Заказ*************************************/
	yPos = 265;
	xPos = 50;
	hBtnOrder = CreateWindow(_T("button"), _T("Заказать"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 180, 25, hWnd, (HMENU)IDC_ORDER, NULL, NULL);

	/**********************************Выход*************************************/
	yPos = 265;
	xPos = 297;
	hBtnQuit = CreateWindow(_T("button"), _T("Выход"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 180, 25, hWnd, (HMENU)IDC_QUIT, NULL, NULL);

	// Рамка вокруг кнопок выход и заказ
	yPos = 240;
	xPos = 30;
	CreateWindow(_T("button"), NULL, BS_GROUPBOX | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 470, 65, hWnd, NULL, NULL, NULL);

	// Установить управляющие элементы в соответствии с полями объекта
	pizza->Setup();
	return TRUE;
} // OnCreate


// Обработка сообщений WM_COMMAND - они посылаются от элементов управления
// в частности - от кнопок
void OnCommand(HWND hWnd, INT id, HWND hWndCtl, UINT codeNotify)
{
	INT nReply;
	LRESULT cbState;
	TCHAR szBuf1[200];
	TCHAR szBuf2[20];

	switch (id) {

	case IDC_CHBOXCHEESE:
		cbState = Button_GetCheck(hWndCtl);
		pizza->SetOption(0, (cbState == BST_CHECKED) ? TRUE : FALSE);
		break;
	case IDC_CHBOXOLIVE:
		cbState = Button_GetCheck(hWndCtl);
		pizza->SetOption(1, (cbState == BST_CHECKED) ? TRUE : FALSE);
		break;
	case IDC_CHBOXFUNGI:
		cbState = Button_GetCheck(hWndCtl);
		pizza->SetOption(2, (cbState == BST_CHECKED) ? TRUE : FALSE);
		break;
	case IDC_CHBOXSAUSAGE:
		cbState = Button_GetCheck(hWndCtl);
		pizza->SetOption(3, (cbState == BST_CHECKED) ? TRUE : FALSE);
		break;

		// получить номер установленной радиокнопки - код опции
	case IDC_RDBTN0:
		pizza->SetDiscount(0);
		break;
	case IDC_RDBTN5:
		pizza->SetDiscount(1);
		break;
	case IDC_RDBTN15:
		pizza->SetDiscount(2);
		break;

		// Обработка нажатия кнопки "Заказать"
	case IDC_ORDER:
		SendMessage(hEditInitial, WM_GETTEXT, (WPARAM)100, (LPARAM)szBuf1);
		pizza->SetFamIO(szBuf1);

		SendMessage(hEditPhone, WM_GETTEXT, (WPARAM)100, (LPARAM)szBuf2);
		pizza->SetPhone(szBuf2);

		pizza->Show();
		break;

	case IDC_QUIT:
		nReply = MessageBox(hWnd, _T("Вы действительно хотите выйти?"), _T("Выход"), MB_YESNO | MB_ICONEXCLAMATION);
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
	_tcscpy(lf.lfFaceName, _T("Cambria"));

	EndPaint(hWnd, &ps);            // Освободить контекст для корректной работы системы
} // OnPaint


// Обработчик сообщения WM_CLOSE - обработчик события "При закрытии окна" 
void OnClose(HWND hWnd)
{
	SelectFont(hDC, hOldFont);
	DeleteFont(hFont);

	delete pizza;
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

	SetTextColor(hDC, RGB(0xB9, 0xD3, 0xEE));
	return CreateSolidBrush(BACKGROUND);
} // OnCtlColorStatic
  

// Ограничение минимального размера главного окна приложения
// !! Работает вместе с OnSize !!
//void OnGetMinMaxInfo(hWnd hWnd, LPMINMAXINFO lpMinMaxInfo)
//{
//	lpMinMaxInfo->ptMintrackSize = { 480, 240 };
//} // OnGetMinMaxInfo