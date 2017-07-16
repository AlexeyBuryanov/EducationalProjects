#include "Includes.h"
#include "MainWindow.h"
#include "InputWindow.h"
#include "SortWindow.h"			// выбор сортировки
#include "FieldsOutWindow.h"	// выбор вывода полей
#include "Price.h"

extern HINSTANCE hAppInstance;   // дескриптор экземпляра приложения
extern TCHAR szTitleMain[];
extern TCHAR szClassInput[];     // класс     окна ввода
extern TCHAR szTitleInput[];     // заголовок окна ввода
extern TCHAR szClassSort[];		 // класс     окна для выбора сортировки
extern TCHAR szTitleSort[];		 // заголовок окна для выбора сортировки
extern TCHAR szClassFieldsOut[]; // класс     окна выбора поля для вывода
extern TCHAR szTitleFieldsOut[]; // заголовок окна выбора поля для вывода
extern UINT uStatus;             // режим сортировки, файл SortWindow.cpp 

HWND hInput;        // Окно ввода данных о товаре
HWND hEdit;         // Окно редактирования данных о товаре
HWND hSort;			// Окно выбора сортировки
HWND hFieldsOut;	// Окно выбора полей для вывода

// Переменные и функции для главного окна приложения
static HDC hDC;							   // Хэндл контекста устройства
static HFONT hFont, hFontList, hOldFont;   // Шрифт для вывода
static LOGFONT lf;						   // Структура для создания шрифта

HWND hStLstGoods;
HWND hLstGoods;            // Список строк     - товары
Price price;	           // Экземпляр товара - нужен для редактирования товара
list<Price> List;          // Список товаров   - контейнер
list<Price>::iterator it;  // Глобальный итератор для связи с другими окнами
fstream fs;                             // Поток ввода/вывода для хранения контейнера
TCHAR *szFileName = _T("Goods.dat");    // Имя потока ввода/вывода
TCHAR *szFileNameCombo = _T("Магазины.txt");  // Имя потока ввода/вывода для заполнения комбобокса

INT  nResult;              // Номер текущей строки в списке строк listbox
InputMode bInputMode;      

// Логические флаги для управления отображением столбцов 
BOOL bViewShop, bViewGoods, bViewCost;

HWND hStBar;   // строка состояния программы

// Оконная функция - обработка сообщений, получаемых окном
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
		HANDLE_MSG(hWnd, WM_CREATE,			OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND,		OnCommand);
		HANDLE_MSG(hWnd, WM_SIZE,			OnSize);
		HANDLE_MSG(hWnd, WM_GETMINMAXINFO,  OnGetMinMaxInfo);
		HANDLE_MSG(hWnd, WM_PAINT,			OnPaint);
		HANDLE_MSG(hWnd, WM_CLOSE,			OnClose);
		HANDLE_MSG(hWnd, WM_DESTROY,		OnDestroy);
		HANDLE_MSG(hWnd, WM_CTLCOLORSTATIC, OnCtlColorStatic);
		HANDLE_MSG(hWnd, WM_MENUSELECT,     OnMenuSelect);
	
		// Обработка сообщений для которых не предусмотрена обработка в нашем окне
		default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	} // switch

	return 0;
} // WndProc


HMENU hMainMenu;       // Главное меню
HMENU hGoodsMenu;      // Выпадающее меню "Товар"
HMENU hSettingsMenu;   // Выпадающее меню "Параметры"

// Обработчик сообщения WM_CREATE - обработчик события "При создании" 
// нашего окна
BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
	// Файл данных должен открываться в двоичном режиме !!!
	fs.open(szFileName, ios::in | ios::out | ios::binary);
	if (!fs) {
		TCHAR *szBuf = new TCHAR[100];
		_stprintf(szBuf, _T("Файл %s не создан или не доступен.\nПрограмма завершена"), szFileName);
		MessageBox(hWnd, szBuf, szTitleMain, MB_OK | MB_ICONERROR);
		delete[] szBuf;
		exit(0);
	} // if

	ZeroMemory(&lf, sizeof(LOGFONT));
	_tcscpy(lf.lfFaceName, _T("Book Antiqua"));
	lf.lfHeight = 28;
	hFont		= CreateFontIndirect(&lf);
	
	ZeroMemory(&lf, sizeof(LOGFONT));
	_tcscpy(lf.lfFaceName, _T("Courier"));
	lf.lfHeight = -14;
	hFontList   = CreateFontIndirect(&lf);

	// Создание меню
	hMainMenu     = CreateMenu();
	hGoodsMenu    = CreatePopupMenu();
	hSettingsMenu = CreatePopupMenu();

	AppendMenu(hMainMenu, MF_STRING | MF_POPUP, (UINT_PTR)hGoodsMenu, _T("&Товар"));
	AppendMenu(hGoodsMenu, MF_STRING, IDC_MAIN_NEW, _T("&Новый..."));
	AppendMenu(hGoodsMenu, MF_STRING, IDC_MAIN_DEL, _T("&Удалить"));
	AppendMenu(hGoodsMenu, MF_SEPARATOR, NULL, _T(""));
	AppendMenu(hGoodsMenu, MF_STRING, IDC_MAIN_QUIT, _T("Вы&ход"));

	AppendMenu(hMainMenu, MF_STRING | MF_POPUP, (UINT_PTR)hSettingsMenu, _T("&Параметры"));
	AppendMenu(hSettingsMenu, MF_STRING, IDC_MAIN_SETSORT, _T("&Сортировка..."));
	AppendMenu(hSettingsMenu, MF_STRING, IDC_MAIN_SETVIEW, _T("Настро&йка..."));

	SetMenu(hWnd, hMainMenu);

	// Создание строки состояния
	hStBar = CreateStatusWindow(WS_CHILD | WS_VISIBLE, _T("Готово"), hWnd, IDC_MAIN_STBAR);

	// Поделить строку состояния на три панели
	// Массив координат границ между панелями
	int pParts[3] = {360, 450, lpCreateStruct->cx };
	SendMessage(hStBar, SB_SETPARTS, (WPARAM)3, (LPARAM)pParts);
	SendMessage(hStBar, SB_SETTEXT, 1, (LPARAM)_T("Записей: 7"));   // Пример вывода в панель 1
	SendMessage(hStBar, SB_SETTEXT, 2, (LPARAM)_T("Магазинов: 15"));   // Пример вывода в панель 2

	// Создания списка товаров
	INT xPos = 15;
	INT yPos = 10;
	// Список товаров
	hStLstGoods = CreateWindow(_T("static"), _T("Список товаров"), WS_CHILD | WS_VISIBLE,
		xPos + 190, yPos, 200, 25, hWnd, NULL, lpCreateStruct->hInstance, NULL);
	yPos += 30;
	hLstGoods = CreateWindow(_T("listbox"), NULL,  LBS_NOTIFY | WS_VSCROLL | WS_BORDER | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 590, 400, hWnd, (HMENU)IDC_MAIN_LISTGDS, lpCreateStruct->hInstance, NULL);
	SendMessage(hLstGoods, WM_SETFONT, WPARAM(hFontList), NULL);

	// Отображать все столбцы
	bViewShop = bViewGoods = bViewCost = TRUE;

	// Загрузка данных из потока ввода/вывода в контейнер и в список
	LoadFile();

	return TRUE;
} // OnCreate


// Обработка сообщений WM_COMMAND - они посылаются от элементов управления
// в частности - от кнопок
void OnCommand(HWND hWnd, INT id, HWND hWndCtl, UINT codeNotify)
{
	INT i;  // номер очередной записи в списке

	switch (id) {

	case IDC_MAIN_NEW:
		if (!hInput) {
			hInput = CreateWindow(szClassInput, szTitleInput,
				WS_OVERLAPPED | WS_CAPTION | WS_DLGFRAME | WS_SYSMENU,
				150, 150, INPUT_WIDTH, INPUT_HEIGHT, hWnd, NULL, hAppInstance, NULL);
		} // if

		// Режим добавления новой записи в файл данных
		bInputMode = MODE_APPEND;  
		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("Ввод данных"));
		ShowWindow(hInput, SW_SHOWNORMAL);
		break;

		// Обработка двойного щелчка по списку
	case IDC_MAIN_LISTGDS:
		if (codeNotify == LBN_DBLCLK) {
			// Получить текущий элемент из списка - проверка корректности не нужна
			// т.к. событие возникает только по щелчку на конкретной записи
			nResult = (INT)SendMessage(hLstGoods, LB_GETCURSEL, NULL, NULL);
			i = 0;
			for (it = List.begin(); it != List.end(); ++it, ++i) {
				if (i == nResult) {
					price = *it;  // перегруженное присваивание
					if (!hEdit) {
						hEdit = CreateWindow(szClassInput, _T("Редактирование товара"),
							WS_OVERLAPPED | WS_CAPTION | WS_DLGFRAME | WS_SYSMENU,
							150, 150, INPUT_WIDTH, INPUT_HEIGHT, hWnd, NULL, hAppInstance, NULL);
					} // if

					// Установить поля ввода окна hInput по значениям полей объекта price 
					// Режим редактирования существующей записи
					bInputMode = MODE_EDIT;
					SetInput();
					SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("Редактирование записи"));
					ShowWindow(hEdit, SW_SHOWNORMAL);
					break;
				} // if
			} // for it
		} // if
		break;

	// Удалить из списка выбранную строку - удаление товара
	case IDC_MAIN_DEL:
		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("Удалене записи"));
		nResult = (INT)SendMessage(hLstGoods, LB_GETCURSEL, NULL, NULL);
		if (nResult == LB_ERR) {
			MessageBox(hWnd, _T("Товар для удаления не выбран!"), _T("Ошибка"), MB_OK | MB_ICONERROR);
			SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("Готово. Запись не удалена"));
			break;
		} // if

		// Запрос на подтверждание удаления записи
		i = MessageBox(HWND_DESKTOP, _T("Вы собираетесь удалить запись данных. "
			"Это действие невозможно отменить\n\nВы уверены?"), _T("Подтверждение удаления"),
			MB_YESNO | MB_ICONQUESTION);
		if (i == IDNO) {
			SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("Готово. Запись не удалена"));
			break;
		} // if

		// Удалить из списка строку по ее номеру
		SendMessage(hLstGoods, LB_DELETESTRING, nResult, NULL);

		// Удалить также товар из контейнера - списка
		i = 0;
		for (list<Price>::iterator it = List.begin(); it != List.end(); ++it, ++i) {
			if (i == nResult) {
				List.erase(it);
				// Перезаписываем файл данных - не лучшее решение по производительности
				// но наиболее простое в реализации
				fs.close();
				WriteFile();

				// Открываем новый файл
				fs.open(szFileName, ios::in | ios::out);
				break;
			} // if
		} // for it

		  // Выделить в качестве текущей запись с тем же номером
		SendMessage(hLstGoods, LB_SETCURSEL, nResult, NULL);
		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("Готово. Запись удалена"));
		break;

		// Сортировка...
	case IDC_MAIN_SETSORT:
		if (!hSort) {
			hSort = CreateWindow(szClassSort, szTitleSort,
				WS_OVERLAPPED | WS_CAPTION | WS_DLGFRAME | WS_SYSMENU,
				150, 150, SORT_WIDTH, SORT_HEIGHT, hWnd, NULL, hAppInstance, NULL);
		} // if

		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("Выбор режима сортировки"));
		ShowWindow(hSort, SW_SHOWNORMAL);
		break;

		// Выбор полей...
	case IDC_MAIN_SETVIEW:
		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("Выбор столбцов для отображения"));
		if (!hFieldsOut) {
			hFieldsOut = CreateWindow(szClassFieldsOut, szTitleFieldsOut,
				WS_OVERLAPPED | WS_CAPTION | WS_DLGFRAME | WS_SYSMENU,
				150, 150, FIELDSOUT_WIDTH, FIELDSOUT_HEIGHT, hWnd, NULL, hAppInstance, NULL);
		} // if
		ShowWindow(hFieldsOut, SW_SHOWNORMAL);
		break;

	case IDC_MAIN_QUIT:   // Выход из приложения
		// Если была выполнена сортировка и порядок записей
		// отличается от исходного, запросим сохранения нового
		// порядка записей
		if (uStatus != 3) {
			i = MessageBox(HWND_DESKTOP, 
				_T("Порядок записей в списке изменен.\nСохранить в файле?"),
				_T("Сохранение файла данных"), 
				MB_YESNO | MB_ICONQUESTION);
			if (i == IDYES) { // Закрыть файл данных
				fs.close();   // и выполнить безопасную
				WriteFile();  // перезапись файла
			} // if
		} // if
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

	DestroyWindow(hWnd);

	// Закрыть файл данных
	fs.close();  
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
	SelectFont(hDC, hFont);
	SetTextColor(hDC, RGB(0x41, 0x69, 0xE1));
	return CreateSolidBrush(BACKGROUND);
} // OnCtlColorStatic


// Обработка выбора позиции меню - вывод текста в строку состояния
void OnMenuSelect(HWND hwnd, HMENU hmenu, int item, HMENU hmenuPopup, UINT flags)
{
	switch (item) {
	case IDC_MAIN_NEW:
		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("Создать новую запись"));
		break;
	case IDC_MAIN_DEL:
		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("Удалить запись (в т.ч. из файла)"));
		break;
	case IDC_MAIN_QUIT:
		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("Выход. Конец работы приложения"));
		break;
	case IDC_MAIN_SETSORT:
		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("Задать режимы сортировки"));
		break;
	case IDC_MAIN_SETVIEW:
		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("Выбрать отображаемые столбцы"));
		break;
	default:
		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("Готово"));
		break;
	} // switch
} // OnMenuSelect


// Загрузка файла данных в контейнер - список и 
// отображение строк в listbox
void LoadFile()
{
	// Получить длину файла в записях
	fs.seekg(0, ios::end);
	UINT uRecords = (UINT) (fs.tellg()) / Price::LEN_RECORD;
	fs.seekg(0, ios::beg);
	
	Price temp;
	TCHAR *szBuf = new TCHAR[Price::LEN_RECORD];

	// Читать файл в список-контейнер и в список на экране
	for (UINT i = 0; i < uRecords; i++) {
		temp.Load(fs);
		List.push_back(temp);

		MakeOutStr(szBuf, temp);
		SendMessage(hLstGoods, LB_ADDSTRING, NULL, (LPARAM)szBuf);
	} // for

	delete[] szBuf;
} // LoadFile


// "Безопасная" перезапись файла данных 
//  - сбой на любом этапе не приводит к потере данных
//  - файл данных должен быть закрыт!!!
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
		MessageBox(HWND_DESKTOP, _T("Невозможно завершить удаление!"), 
			_T("Ошибка"), MB_OK | MB_ICONERROR);
		return;
	} // if

	// Цикл чтения элемнтов из списка (при помощи итератора) и записи
	// элементов во временный файл
	for (list<Price>::iterator it = List.begin(); it != List.end(); ++it) {
		it->Save(ftmp);
	} // for it
	ftmp.close();

	// Удалить закрытый файл по имени - DeleteFile(имяФайла)
	DeleteFile(szFileName);
	// Переименовать файл - MoveFile(существующееИмя, новоеИмя)
	MoveFile(szTempFile, szFileName);
} // WriteFile


// Формирование строки для вывода в список главного окна
void MakeOutStr(TCHAR *szBuf, Price price) 
{
	TCHAR szTemp[50];
	_tcscpy(szBuf, _T(""));

	if (bViewShop)
		_stprintf(szTemp, _T("%-25s | "), price.getShop().c_str());
	else
		_tcscpy(szTemp, _T("                          | "));
	_tcscat(szBuf, szTemp);

	if (bViewGoods)
		_stprintf(szTemp, _T("%-32s | "), price.getGoods().c_str());
	else
		_tcscpy(szTemp, _T("                                 | "));
	_tcscat(szBuf, szTemp);

	if (bViewCost) {
		_stprintf(szTemp, _T("%10u"), price.getCost());
		_tcscat(szBuf, szTemp);
	} // if
} // MakeOutStr


// Вывод из списка товаров в список строк главного окна приложения
void ListToListbox() {
	TCHAR *szBuf = new TCHAR[Price::LEN_RECORD];

	SendMessage(hLstGoods, LB_RESETCONTENT, NULL, NULL);
	for (list<Price>::iterator it = List.begin(); it != List.end(); ++it) {
		MakeOutStr(szBuf, *it);
		SendMessage(hLstGoods, LB_ADDSTRING, NULL, (LPARAM)szBuf);
	} // for it

	delete[] szBuf;
} // ListToListbox