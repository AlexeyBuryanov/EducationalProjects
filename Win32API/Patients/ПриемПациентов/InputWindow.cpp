#include "Includes.h"
#include "InputWindow.h"
#include "Patient.h"

extern HWND hLstPatients;  // список строк - пациенты

extern Patient patient;	           // Экземпляр пациента
extern list<Patient>::iterator it; // Итератор, указывает на текущий элемент списка
extern INT nResult;                // Номер текущей строки, соответсвующей итератору 
extern InputMode bInputMode; // Режим работы окна - ввод/редактирование

static HDC hDC;            // Хэндл контекста устройства
static HFONT hFont, hFontStatic, hFontEdit, hFontBtn, hOldFont;   // Шрифт для вывода
static LOGFONT lf;         // Структура для создания шрифта

HWND hStFamIO;        // Надписи к полю ввода фамилии
HWND hStWeight;       // Надписи к полю ввода веса

HWND hEdFamIO;        // Поле ввода фамилии
HWND hEdWeight;       // Поле ввода веса

HWND hBtnInputWrite;  // Кнопка "Записать"
HWND hBtnInputClose;  // Кнопка "Закрыть"

extern fstream fs;    // Поток ввода/вывода

// Для доступа к списку пациентов
extern list<Patient> List;

LRESULT CALLBACK Input_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
		HANDLE_MSG(hWnd, WM_CREATE, Input_OnCreate);  // создание окна
		HANDLE_MSG(hWnd, WM_SIZE, Input_OnSize);      // Изменение размера экрана
		HANDLE_MSG(hWnd, WM_GETMINMAXINFO, Input_OnGetMinMaxInfo);
		HANDLE_MSG(hWnd, WM_CLOSE, Input_OnClose);
		HANDLE_MSG(hWnd, WM_DESTROY, Input_OnDestroy);
		HANDLE_MSG(hWnd, WM_COMMAND, Input_OnCommand);
		HANDLE_MSG(hWnd, WM_CTLCOLORSTATIC, Input_OnCtlColorStatic);

		// Обработка сообщений для которых не предусмотрена обработка в нашем окне
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	} // switch

	return 0;
} // Input_WndProc


// Обработчик сообщения WM_CREATE - обработчик события "При создании" 
// нашего окна
BOOL Input_OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
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
	lf.lfHeight = 22;
	hFontBtn    = CreateFontIndirect(&lf);
	
	// Поля ввода - описываем парой "надпись" - "редактор" / "static" - "edit"
	INT xPos = 10;
	INT yPos = 10;
	hStFamIO = CreateWindow(_T("static"), _T("Фамилия И.О.:"), WS_CHILD | WS_VISIBLE,
		xPos, yPos, 150, 25, hWnd, NULL, lpCreateStruct->hInstance, NULL);
	yPos += 20;
	hEdFamIO = CreateWindow(_T("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
		xPos, yPos, 340, 25, hWnd, (HMENU)IDC_INPUT_EDFAMIO, lpCreateStruct->hInstance, NULL);
	SendMessage(hEdFamIO, WM_SETFONT, WPARAM(hFontEdit), NULL);


	yPos += 45;
	hStFamIO = CreateWindow(_T("static"), _T("Вес (кг):"), WS_CHILD | WS_VISIBLE,
		xPos, yPos, 150, 25, hWnd, NULL, lpCreateStruct->hInstance, NULL);
	yPos += 20;
	hEdWeight = CreateWindow(_T("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
		xPos, yPos, 340, 25, hWnd, (HMENU)IDC_INPUT_EDWEIGHT, lpCreateStruct->hInstance, NULL);
	SendMessage(hEdWeight, WM_SETFONT, WPARAM(hFontEdit), NULL);

	// Управляющие кнопки
	yPos += 60;
	hBtnInputWrite = CreateWindow(_T("button"), _T("Записать"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 160, 25, hWnd, (HMENU)IDC_INPUT_WRITE, lpCreateStruct->hInstance, NULL);
	SendMessage(hBtnInputWrite, WM_SETFONT, WPARAM(hFontBtn), NULL);
	hBtnInputClose = CreateWindow(_T("button"), _T("Закрыть"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		xPos + 180, yPos, 160, 25, hWnd, (HMENU)IDC_INPUT_CLOSE, lpCreateStruct->hInstance, NULL);
	SendMessage(hBtnInputClose, WM_SETFONT, WPARAM(hFontBtn), NULL);

	// Фокус ввода ставим в поле ввода фамилии и инициалов
	SetFocus(hEdFamIO);

	return TRUE;
} // Input_OnCreate


// Обработка сообщений WM_COMMAND - они посылаются от элементов управления
// в частности - от кнопок
void Input_OnCommand(HWND hWnd, INT id, HWND hWndCtl, UINT codeNotify)
{
	TCHAR szBuf1[100];
	TCHAR szBuf2[100];
	UINT  weight;	    // вспомогательная переменная для работы с весом

	switch (id) {

		// Закрыть
	case IDC_INPUT_CLOSE:
		// Этот вызов сворачивает окно, свернутое окно
		// остается на рабочем столе ((
		// Решение проблемы - см. ниже
		// CloseWindow(hWnd);

		// Для скрытия окна - именно показать окна в режиме
		// скрытия ))) привет от MS
		ShowWindow(hWnd, HIDE_WINDOW);
		break;

		// Записать
	case IDC_INPUT_WRITE:
		SendMessage(hEdFamIO, WM_GETTEXT, (WPARAM)100, (LPARAM)szBuf1);		
		if (_tcslen(szBuf1) == 0) return;									
		patient.setFamIO(szBuf1);											

		SendMessage(hEdWeight, WM_GETTEXT, (WPARAM)100, (LPARAM)szBuf2);
		if (_tcslen(szBuf2) == 0) return;
		_stscanf(szBuf2, _T("%u"), &weight);	// преобразовать строку в беззнаковое целое
		patient.setWeight(weight);

		_tcscat(szBuf1, _T(" "));
		_tcscat(szBuf1, szBuf2);

		if (bInputMode == MODE_APPEND) {
			SendMessage(hLstPatients, LB_ADDSTRING, NULL, (LPARAM)szBuf1);

			// Очистка полей ввода, подготовка для ввода данных 
			// следующего пациента
			SendMessage(hEdFamIO, WM_SETTEXT, NULL, NULL);
			SendMessage(hEdWeight, WM_SETTEXT, NULL, NULL);
			// SendMessage(hEdFamIO, WM_SETFOCUS, NULL, NULL);

			// Добавить очередного пациента в контейнер - список
			List.push_back(patient);
			patient.Save(fs, true);   // true - т.е. дозапись в конец файла
		} else {
			// Заменить выбранный элемент в списке-контейнере, и в списке на экране
			*it = patient;
			SendMessage(hLstPatients, LB_DELETESTRING, nResult, NULL);
			SendMessage(hLstPatients, LB_INSERTSTRING, nResult, (LPARAM)szBuf1);

			// Изменить запись в файле
			fs.seekp(nResult*Patient::LEN_RECORD, ios::beg);
			fs.seekg(nResult*Patient::LEN_RECORD, ios::beg);
			patient.Save(fs);

			// Исправить - в списке должна остаться текущей та же строка
			SendMessage(hLstPatients, LB_SETCURSEL, nResult, NULL);
		} // if

		break;
	} // switch
} // Input_OnCommand


// Обработчик сообщения WM_SIZE - обработчик события "При изменении размера" 
// нашего окна
void Input_OnSize(HWND hWnd, UINT state, INT cx, INT cy)
{
	RECT rect;       // Прямоугольник - для хранения координат рабочей области окна 

	GetClientRect(hWnd, &rect);         // Задать область окна для перерисовки
	InvalidateRect(hWnd, &rect, TRUE);  // Объявить область недействительной => формируется WM_PAINT
} // Input_OnSize


// Ограничение минимального размера главного окна приложения
// !! Работает вместе с OnSize !!
void Input_OnGetMinMaxInfo(HWND hWnd, LPMINMAXINFO lpMinMaxInfo)
{
	lpMinMaxInfo->ptMinTrackSize = { INPUT_WIDTH, INPUT_HEIGHT };
	lpMinMaxInfo->ptMaxTrackSize = { INPUT_WIDTH, INPUT_HEIGHT };
} // Input_OnGetMinMaxInfo


// Обработчик сообщения WM_CLOSE - обработчик события "При закрытии окна" 
void Input_OnClose(HWND hWnd)
{
	SelectFont(hDC, hOldFont);
	DeleteFont(hFont);
	DeleteFont(hFontStatic);
	DeleteFont(hFontEdit);
	DeleteFont(hFontBtn);
	
	// CloseWindow(hWnd);
} // Input_OnClose


// Обработчик сообщения WM_DESTROY - обработчик события "При уничтожении окна" 
void Input_OnDestroy(HWND hWnd)
{
	PostQuitMessage(0);
} // OnDestroy


// Отрисовка фона статического управляющего элемента
// Фон - совпадает с фоном рабочей области окна
HBRUSH Input_OnCtlColorStatic(HWND, HDC hDC, HWND, INT)
{
	SetBkMode(hDC, TRANSPARENT);
	hOldFont = SelectFont(hDC, hFontStatic);

	SetTextColor(hDC, RGB(0x41, 0x69, 0xE1));
	return CreateSolidBrush(INPUT_BACKGROUND);
} // Input_OnCtlColorStatic


// Устанавливаем поля ввода по значениям полей объекта patient 
void SetInput()
{
	// Получим вес в форме строки
	TCHAR szBuf[20];
	_stprintf(szBuf, _T("%d"), patient.getWeight());

	// Установить значения текстовых полей ввода
	SendMessage(hEdFamIO, WM_SETTEXT, NULL, (LPARAM)patient.getFamIO().c_str());
	SendMessage(hEdWeight, WM_SETTEXT, NULL, (LPARAM)szBuf);
} // SetInput