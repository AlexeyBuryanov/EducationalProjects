#include "Includes.h"
#include "MainWindow.h"
#include "InputWindow.h" 
#include "Patient.h"

extern HINSTANCE hAppInstance;   // дескриптор экземпляра приложения
extern TCHAR szClassInput[];     // класс окна ввода
extern TCHAR szTitleInput[];     // заголовок окна ввода
extern TCHAR szTitleMain[];

// Переменные и функции для главного окна приложения
static HDC hDC;							   // Хэндл контекста устройства
static HFONT hFont, hFontList, hOldFont;   // Шрифт для вывода
static LOGFONT lf;						   // Структура для создания шрифта

HWND hBtnInput;     // Кнопка "Новый пациент"
HWND hBtnOut;       // Кнопка "Выписать"
HWND hBtnQuit;      // Кнопка "Выход"

HWND hLstPatients;  // список строк - пациенты
INT  nResult;       // номер текущей строк в списке строк listbox

HWND hInput;        // Окно ввода данных о пациенте

InputMode bInputMode;         

list<Patient> List;   // Список пациентов - контейнер
list<Patient>::iterator it;  // глобальный итератор для связи с другими окнами

fstream fs;           // поток ввода/вывода для хранения контейнера
TCHAR *szFileName = _T("patients.dat"); // имя потока ввода/вывода

Patient patient;	   // Экземпляр пациента - нужен для редактирования пациента

// Оконная функция - обработка сообщений, получаемых окном
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_SIZE, OnSize);
		HANDLE_MSG(hWnd, WM_GETMINMAXINFO, OnGetMinMaxInfo);
		HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hWnd, WM_LBUTTONDOWN, OnLButtonDown);
		HANDLE_MSG(hWnd, WM_RBUTTONDOWN, OnRButtonDown);
		HANDLE_MSG(hWnd, WM_CLOSE, OnClose);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
	
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
	//patient = new Patient();
	fs.open(szFileName, ios::in | ios::out /* | ios::app */);
	if (!fs) {
		TCHAR *szBuf = new TCHAR[100];
		_stprintf(szBuf, _T("Файл %s не создан или не доступен.\nПрограмма завершена"), szFileName);
		MessageBox(hWnd, szBuf, szTitleMain, MB_OK | MB_ICONERROR);
		delete[] szBuf;
		exit(0);
	} // if

	ZeroMemory(&lf, sizeof(LOGFONT));
	_tcscpy(lf.lfFaceName, _T("Book Antiqua"));
	lf.lfHeight = 23;
	hFont		= CreateFontIndirect(&lf);
	ZeroMemory(&lf, sizeof(LOGFONT));
	_tcscpy(lf.lfFaceName, _T("Gungsuh"));
	lf.lfHeight = 20;
	hFontList   = CreateFontIndirect(&lf);

	// Список пациентов
	hLstPatients = CreateWindow(_T("listbox"), NULL,  LBS_NOTIFY | WS_VSCROLL | WS_BORDER | WS_CHILD | WS_VISIBLE,
		190, 15, 420, 430, hWnd, (HMENU)IDC_LISTPT, lpCreateStruct->hInstance, NULL);
	SendMessage(hLstPatients, WM_SETFONT, WPARAM(hFontList), NULL);
	
	hBtnInput = CreateWindow(_T("button"), _T("Новый пациент"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		15, 15, 160, 25, hWnd, (HMENU)IDC_BTNNEW, lpCreateStruct->hInstance, NULL);
	SendMessage(hBtnInput, WM_SETFONT, WPARAM(hFont), NULL);

	hBtnOut = CreateWindow(_T("button"), _T("Выписать"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		15, 65, 160, 25, hWnd, (HMENU)IDC_BTNOUT, lpCreateStruct->hInstance, NULL);
	SendMessage(hBtnOut, WM_SETFONT, WPARAM(hFont), NULL);


	hBtnQuit = CreateWindow(_T("button"), _T("Выход"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		15, 410, 160, 25, hWnd, (HMENU)IDC_QUIT, lpCreateStruct->hInstance, NULL);
	SendMessage(hBtnQuit, WM_SETFONT, WPARAM(hFont), NULL);

	// Загрузка данных из потока ввода/вывода в контейнер и в список
	LoadFile();

	return TRUE;
} // OnCreate


// Обработка сообщений WM_COMMAND - они посылаются от элементов управления
// в частности - от кнопок
void OnCommand(HWND hWnd, INT id, HWND hWndCtl, UINT codeNotify)
{
	INT i;        // номер очередной записи в списке

	switch (id) {
		// Открыть окно для ввода данных
	case IDC_BTNNEW:  
		// Создание окна ввода - если оно не создано
		if (!hInput) {
			hInput = CreateWindow(szClassInput, szTitleInput,
				WS_OVERLAPPED | WS_CAPTION | WS_DLGFRAME | WS_SYSMENU,
				150, 150, INPUT_WIDTH, INPUT_HEIGHT, hWnd, NULL, hAppInstance, NULL);
		} // if

		// Режим добавления новой записи в файл данных
		bInputMode = MODE_APPEND;  
		ShowWindow(hInput, SW_SHOWNORMAL);
		break;

		// Удалить из списка выбранную строку - выписка пациента
	case IDC_BTNOUT:
		nResult = SendMessage(hLstPatients, LB_GETCURSEL, NULL, NULL);
		if (nResult == LB_ERR) {
			MessageBox(hWnd, _T("Пациент для выписки не выбран"), _T("Ошибка"), MB_OK | MB_ICONERROR);
			break;
		} // if

		// Удалить из списка строку по ее номеру
		SendMessage(hLstPatients, LB_DELETESTRING, nResult, NULL);

		// Удалить также пациента из контейнера - списка
		i = 0;
		for (list<Patient>::iterator it = List.begin(); it != List.end(); ++it, ++i) {
			if (i == nResult) {
				List.erase(it);
				// Перезаписываем файл данных - не лучшее решение по производительности
				// но наиболее простое в реализации
				fs.close();
				WriteFile();

				// Открываем новый файл
				fs.open(szFileName, ios::in | ios::out /* | ios::app */);
				break;
			} // if
		} // for it

		// Выделить в качестве текущей запись с тем же номером
		SendMessage(hLstPatients, LB_SETCURSEL, nResult, NULL);
		break;

		// Обработка двойного щелчка по списку
	case IDC_LISTPT:
		if (codeNotify == LBN_DBLCLK) {
			// Получить текущий элемент из списка - проверка корректности не нужна
			// т.к. событие возникает только по щелчку на конкретной записи
			nResult = SendMessage(hLstPatients, LB_GETCURSEL, NULL, NULL);
			i = 0;
			for (it = List.begin(); it != List.end(); ++it, ++i) {
				if (i == nResult) {
					patient = *it;  // перегруженное присваивание
					if (!hInput) {
						hInput = CreateWindow(szClassInput, _T("Редактирование данных пациента"),
							WS_OVERLAPPED | WS_CAPTION | WS_DLGFRAME | WS_SYSMENU,
							150, 150, INPUT_WIDTH, INPUT_HEIGHT, hWnd, NULL, hAppInstance, NULL);
					} // if

					// Установить поля ввода окна hInput по значениям полей объекта patient 
					// Режим редактирования существуюющей записи
					bInputMode = MODE_EDIT;
					SetInput();
					ShowWindow(hInput, SW_SHOWNORMAL);
					break;
				} // if
			} // for it
		} // if
		break;

	case IDC_QUIT:   // Выход из приложения
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


// Ограничение минимального размера главного окна приложения
// !! Работает вместе с OnSize !!
void OnGetMinMaxInfo(HWND hWnd, LPMINMAXINFO lpMinMaxInfo)
{
	lpMinMaxInfo->ptMinTrackSize = { MAIN_WIDTH, MAIN_HEIGHT };
	lpMinMaxInfo->ptMaxTrackSize = { MAIN_WIDTH, MAIN_HEIGHT };
} // OnGetMinMaxInfo


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

	EndPaint(hWnd, &ps);            // Освободить контекст для корректной работы системы
} // OnPaint


// Обработчик сообщения WM_CLOSE - обработчик события "При закрытии окна" 
void OnClose(HWND hWnd)
{
	SelectFont(hDC, hOldFont);
	DeleteFont(hFont);
	DeleteFont(hFontList);

	//delete patient;
	DestroyWindow(hWnd);

	// Закрыть файл данных
	fs.close();  
} // OnClose


// Обработчик сообщения WM_DESTROY - обработчик события "При уничтожении окна" 
void OnDestroy(HWND hWnd)
{
	PostQuitMessage(0);
} // OnDestroy


// Загрузка файла данных в контейнер - список и 
// отображение строк в listbox
void LoadFile()
{
	// Получить длину файла в записях
	fs.seekg(0, ios::end);
	UINT uRecords = (UINT) (fs.tellg()) / Patient::LEN_RECORD;
	fs.seekg(0, ios::beg);
	Patient temp;
	TCHAR *szBuf = new TCHAR[Patient::LEN_RECORD];

	// Читать файл в список-контейнер и в список на экране
	for (UINT i = 0; i < uRecords; i++) {
		// fs.seekg(i*Patient::LEN_RECORD);
		temp.Load(fs);
		List.push_back(temp);

		// _stprintf() выводит только C-строки (нуль-терминальные), wstring в принципе
		// не выводится. Но можно получить C-строку из wstring - метод c_str()
		_stprintf(szBuf, _T("%s %u"), temp.getFamIO().c_str(), temp.getWeight());
		SendMessage(hLstPatients, LB_ADDSTRING, NULL, (LPARAM)szBuf);
	} // for

	delete[] szBuf;
} // LoadFile


// "Безопасная" перезапись файла - сбой на любом этапе не приводит
// к потере данных
// 1. Записать список во временнный файл
// 2. Удалить основной файл
// 3. Переименовать временный файл в основной
void WriteFile()
{
	// Конструируем имя временного файла - имяОсновного.tmp
	TCHAR szTempFile[255];
	_tcscpy(szTempFile, szFileName);
	_tcscat(szTempFile, _T(".tmp"));

	// Создать временный файл
	fstream ftmp(szTempFile, ios::out);
	if (!ftmp) {
		MessageBox(HWND_DESKTOP, _T("Не могу завершить выписку - сбой диска"), 
			_T("Ошибка"), MB_OK | MB_ICONERROR);
		return;
	} // if

	// Цикл чтения элемнтов из списка (при помощи итератора) и записи
	// элементов во временный файл
	for (list<Patient>::iterator it = List.begin(); it != List.end(); ++it) {
		it->Save(ftmp);
	} // for it
	ftmp.close();

	// Удалить закрытый файл по имени - DeleteFile(имяФайла)
	DeleteFile(szFileName);
	// Переименовать файл - MoveFile(существующееИмя, новоеИмя)
	MoveFile(szTempFile, szFileName);

} // WriteFile