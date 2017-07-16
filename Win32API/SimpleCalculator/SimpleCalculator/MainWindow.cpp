#include "Includes.h"
#include "MainWindow.h"

// Переменные и функции для главного окна приложения
static HDC hDC;     // Хэндл контекста устройства

HWND hBtnPlus;      // Кнопка для команды "+"
HWND hBtnMinus;     // Кнопка для команды "-"
HWND hBtnMultiply;  // Кнопка для команды "*"
HWND hBtnDivide;    // Кнопка для команды "/"
HWND hBtnReset;		// Кнопка для команды "Сброс"
HWND hBtnQuit;		// Кнопка для команды "Выход"

HWND hStat1;        // Надпись
HWND hStat2;        // Надпись
HWND hStat3;        // Надпись

HWND hEdit1;        // Строка редактирования первого числа
HWND hEdit2;        // Строка редактирования второго числа
HWND hEditResult;	// Строка редактирования результата

// Данные для обработки
INT nNumber1 = 0;
INT nNumber2 = 0;
INT nResult  = 0;

static TCHAR szBuf1[256];
static TCHAR szBuf2[256];
static TCHAR szBufRes[256];

// Оконная функция - обработка сообщений, получаемых окном
// hwnd	  - дескриптор окна
// msg	  - числовой код сообщения
// wParam - первая часть параметров сообщения
// lParam - вторая часть параметров сообщения
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);  // создание окна
		HANDLE_MSG(hWnd, WM_SIZE, OnSize);      // Изменение размера экрана
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
	TCHAR szBuf[50];

	hDC = GetDC(hWnd);
	GetTextMetrics(hDC, &tm);

	yPos = 20;
	xPos = 10;
	hStat1 = CreateWindow(_T("static"), _T("Число №1:"), WS_CHILD | WS_VISIBLE,
		xPos, yPos, 110, tm.tmHeight, hWnd, NULL, NULL, NULL);

	_stprintf(szBuf, _T("%d"), nNumber1);  // Формировать начальную строку для отображения в редакторе 
	yPos += (tm.tmHeight + 2);
	hEdit1 = CreateWindow(_T("edit"), szBuf, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
		xPos, yPos, 110, tm.tmHeight + 8, hWnd, (HMENU)IDC_EDIT1, NULL, NULL);

	xPos += 150;
	yPos = 20;
	hStat2 = CreateWindow(_T("static"), _T("Число №2:"), WS_CHILD | WS_VISIBLE,
		xPos, yPos, 110, tm.tmHeight, hWnd, NULL, NULL, NULL);

	yPos += (tm.tmHeight + 2);
	_stprintf(szBuf, _T("%d"), nNumber2); 
	hEdit2 = CreateWindow(_T("edit"), szBuf, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
		xPos, yPos, 110, tm.tmHeight + 8, hWnd, (HMENU)IDC_EDIT2, NULL, NULL);
	
	xPos = 10;
	yPos = 80;
	hStat3 = CreateWindow(_T("static"), _T("Результат:"), WS_CHILD | WS_VISIBLE,
		xPos, yPos, 260, tm.tmHeight, hWnd, NULL, NULL, NULL);

	yPos += (tm.tmHeight + 2);
	_stprintf(szBuf, _T("%d"), nResult); 
	hEditResult = CreateWindow(_T("edit"), szBuf, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
		xPos, yPos, 260, tm.tmHeight + 8, hWnd, (HMENU)IDC_EDIT2, NULL, NULL);

	yPos += (tm.tmHeight + 30);
	hBtnPlus = CreateWindow(_T("button"), _T("+"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 50, 25, hWnd, (HMENU)IDC_PLUS, NULL, NULL);

	xPos += 70;
	hBtnMinus = CreateWindow(_T("button"), _T("-"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 50, 25, hWnd, (HMENU)IDC_MINUS, NULL, NULL);

	xPos += 70;
	hBtnMinus = CreateWindow(_T("button"), _T("*"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 50, 25, hWnd, (HMENU)IDC_MULTIPLY, NULL, NULL);

	xPos += 70;
	hBtnMinus = CreateWindow(_T("button"), _T("/"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 50, 25, hWnd, (HMENU)IDC_DIVIDE, NULL, NULL);

	xPos = 10;
	yPos += 50;
	hBtnReset = CreateWindow(_T("button"), _T("Сброс"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 120, 25, hWnd, (HMENU)IDC_RESET, NULL, NULL);

	xPos += 140;
	hBtnQuit = CreateWindow(_T("button"), _T("Выход"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 120, 25, hWnd, (HMENU)IDC_QUIT, NULL, NULL);

	return TRUE;
} // OnCreate


// Обработчик сообщения WM_SIZE - обработчик события "При изменении размера" 
// нашего окна
void OnSize(HWND hwnd, UINT state, int cx, int cy)
{
	RECT rect;       // Прямоугольник - для хранения координат рабочей области окна 

	GetClientRect(hwnd, &rect);         // Задать область окна для перерисовки
	InvalidateRect(hwnd, &rect, TRUE);  // Объявить область недействительной => формируется WM_PAINT
} // OnSize


// Обработчик сообщения WM_CLOSE - обработчик события "При закрытии окна" 
void OnClose(HWND hwnd)
{
	DestroyWindow(hwnd);
} // OnClose


// Обработчик сообщения WM_DESTROY - обработчик события "При уничтожении окна" 
void OnDestroy(HWND hwnd)
{
	PostQuitMessage(0);
} // OnDestroy


// Обработка сообщений WM_COMMAND - они посылаются от элементов управления
// в частности - от кнопок
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	INT nReply; // Ответ пользователя

 	switch (id) {
	
	// Плюс
	case IDC_PLUS:
		Plus();
		break;

	// Минус
	case IDC_MINUS:
		Minus();
		break;

	// Умножить
	case IDC_MULTIPLY:
		Multiply();
		break;

	// Разделить
	case IDC_DIVIDE:
		Divide();
		break;

	// Сброс
	case IDC_RESET:
		Reset();
		break;

	// Выход
	case IDC_QUIT:
		//SendMessage(hwndCtl, WM_SETTEXT, 0, (LPARAM)_T("И всё тут"));
		nReply = MessageBox(hwnd, _T("Вы действительно хотите выйти?"), _T("Выход"), MB_YESNO | MB_ICONQUESTION);
		if (nReply == IDYES) {
			PostQuitMessage(0);
		} else {
			Reset();
		} // if
		break;
	} // switch
} // OnCommand


// Отрисовка фона статического управляющего элемента
// Фон - совпадает с фоном рабочей области окна
HBRUSH OnCtlColorStatic(HWND, HDC hDC, HWND, INT)
{
	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(0x7F, 0xFF, 0x00));
	return CreateSolidBrush(BACKGROUND);
} // OnCtlColorStatic


void Plus()
{
	// Чтение введенной строки из редактора hEdit1 и hEdit2
	SendMessage(hEdit1, WM_GETTEXT, (WPARAM)256, (LPARAM)szBuf1);
	SendMessage(hEdit2, WM_GETTEXT, (WPARAM)256, (LPARAM)szBuf2);

	// Преобразовать введенную строку в значение переменной типа int
	_stscanf(szBuf1, _T("%d"), &nNumber1);
	_stscanf(szBuf2, _T("%d"), &nNumber2);
	nResult = nNumber1 + nNumber2;

	// Формируем новую строку с измененным значением переменной
	_stprintf(szBufRes, _T("%d"), nResult);

	// Отправляем эту строку в редактор текста результата
	SendMessage(hEditResult, WM_SETTEXT, 0, (LPARAM)szBufRes);
} // Plus


void Minus()
{
	// Чтение введенной строки из редактора hEdit1 и hEdit2
	SendMessage(hEdit1, WM_GETTEXT, (WPARAM)256, (LPARAM)szBuf1);
	SendMessage(hEdit2, WM_GETTEXT, (WPARAM)256, (LPARAM)szBuf2);

	// Преобразовать введенную строку в значение переменной типа int
	_stscanf(szBuf1, _T("%d"), &nNumber1);
	_stscanf(szBuf2, _T("%d"), &nNumber2);
	nResult = nNumber1 - nNumber2;

	// Формируем новую строку с измененным значением переменной
	_stprintf(szBufRes, _T("%d"), nResult);

	// Отправляем эту строку в редактор текста результата
	SendMessage(hEditResult, WM_SETTEXT, 0, (LPARAM)szBufRes);
} // Minus


void Multiply()
{
	// Чтение введенной строки из редактора hEdit1 и hEdit2
	SendMessage(hEdit1, WM_GETTEXT, (WPARAM)256, (LPARAM)szBuf1);
	SendMessage(hEdit2, WM_GETTEXT, (WPARAM)256, (LPARAM)szBuf2);

	// Преобразовать введенную строку в значение переменной типа int
	_stscanf(szBuf1, _T("%d"), &nNumber1);
	_stscanf(szBuf2, _T("%d"), &nNumber2);
	nResult = nNumber1 * nNumber2;

	// Формируем новую строку с измененным значением переменной
	_stprintf(szBufRes, _T("%d"), nResult);

	// Отправляем эту строку в редактор текста результата
	SendMessage(hEditResult, WM_SETTEXT, 0, (LPARAM)szBufRes);
} // Multiply


void Divide()
{
	// Чтение введенной строки из редактора hEdit1 и hEdit2
	SendMessage(hEdit1, WM_GETTEXT, (WPARAM)256, (LPARAM)szBuf1);
	SendMessage(hEdit2, WM_GETTEXT, (WPARAM)256, (LPARAM)szBuf2);

	// Преобразовать введенную строку в значение переменной типа int
	_stscanf(szBuf1, _T("%d"), &nNumber1);
	_stscanf(szBuf2, _T("%d"), &nNumber2);

	if (nNumber2 != 0) {
		nResult = nNumber1 / nNumber2;

		// Формируем новую строку с измененным значением переменной
		_stprintf(szBufRes, _T("%d"), nResult);
	}
	else {
		_stprintf(szBufRes, _T("Деление на ноль"));
	} // if

	// Отправляем эту строку в редактор текста результата
	SendMessage(hEditResult, WM_SETTEXT, 0, (LPARAM)szBufRes);
} // Divide


void Reset()
{
	nNumber1 = nNumber2 = nResult = 0;
	SendMessage(hEdit1, WM_SETTEXT, 0, NULL);
	SendMessage(hEdit2, WM_SETTEXT, 0, NULL);
	SendMessage(hEditResult, WM_SETTEXT, 0, NULL);
} // Reset