#include "Includes.h"
#include "MainWindow.h"
#include "WeatherInfo.h"
#include "WeatherLoad.h"
 
// Переменные и функции для главного окна приложения
static HDC hdc; // хэндл контекста устройства                          

// Меню окна и подменю "Файл", "Вид" 
HMENU hMainMenu, hFileMenu, hViewMenu;

// Высота строки меню в пикселях - для перестроения окна 
static INT32 nMenuHeight;   

// Элемент ListView 
HWND hLstWeather;

// Вектор данных для обработки - вектор объектов класса Student 
WeatherLoad weather;

// Стандартный диалог открытия файла 
OPENFILENAME ofn;

LOGFONT lf;
COLORREF colfont;
CHOOSEFONT cfont;
HFONT font;
HANDLE hOldFont;

CHOOSECOLOR ccol;
COLORREF clf;
COLORREF clfusers[16];

// Оконная функция - обработка сообщений, получаемых окном
// hwnd - дескриптор окна
// msg - числовой код сообщения
// wParam - первая часть параметров сообщения
// lParam - вторая часть параметров сообщения 
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
		HANDLE_MSG(hwnd, WM_CREATE, OnCreate);  // создание окна 
		HANDLE_MSG(hwnd, WM_SIZE, OnSize);      // Изменение размера экрана 
		HANDLE_MSG(hwnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hwnd, WM_CLOSE, OnClose);
		HANDLE_MSG(hwnd, WM_DESTROY, OnDestroy);
		HANDLE_MSG(hwnd, WM_GETMINMAXINFO, OnGetMinMaxInfo);
		HANDLE_MSG(hwnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hwnd, WM_CTLCOLORSTATIC, OnCtlColorStatic);
	
		// Обработка сообщений для которых не предусмотрена обработка в нашем окне 
		default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	} // switch

	return 0;
} // WndProc


// Обработчик сообщения WM_CREATE - обработчик события "При создании"
// нашего окна 
BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
	RECT rect;
	GetClientRect(hwnd, &rect);

	#pragma region Ñîçäàíèå ìåíþ
	hMainMenu = CreateMenu();
	hFileMenu = CreatePopupMenu();
	hViewMenu = CreatePopupMenu();

	AppendMenu(hMainMenu, MF_STRING | MF_POPUP, (UINT_PTR)hFileMenu, _T("&Файл"));
	AppendMenu(hFileMenu, MF_STRING, IDC_OPEN, _T("&Открыть..."));
	AppendMenu(hFileMenu, MF_SEPARATOR, NULL, _T(""));
	AppendMenu(hFileMenu, MF_STRING, IDC_QUIT, _T("Вы&ход"));

	AppendMenu(hMainMenu, MF_STRING | MF_POPUP, (UINT_PTR)hViewMenu, _T("&Вид"));
	AppendMenu(hViewMenu, MF_STRING, IDC_FONT, _T("&Шрифт текста"));
	AppendMenu(hViewMenu, MF_STRING, IDC_COLOR, _T("Ц&вет фона..."));
	SetMenu(hwnd, hMainMenu);

	// Получить высоту строки меню в пикселах
	nMenuHeight = GetSystemMetrics(SM_CYMENU);
	#pragma endregion

	#pragma region Создание элемента ListView
	hLstWeather = CreateWindowEx(0, WC_LISTVIEW, NULL,
		WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_REPORT | LVS_ALIGNLEFT,
		rect.left + 10, rect.top + 10, rect.right - 20, rect.bottom - nMenuHeight, 
		hwnd, (HMENU)IDC_LISTVIEW, lpCreateStruct->hInstance, NULL);
	// SendMessage(hLstStudents, WM_SETFONT, WPARAM(hFontList), NULL);

	// Добавление столбцов
	LV_COLUMN lvCol;
	ZeroMemory(&lvCol, sizeof(LV_COLUMN));

	// Добавление 0-го столбца - Фамилия и инициалы
	lvCol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvCol.fmt  = LVCFMT_LEFT;
	lvCol.cx   = (rect.right - rect.left - 20) / 5;

	lvCol.iSubItem = 0;
	lvCol.pszText  = _T("Город");
	ListView_InsertColumn(hLstWeather, 0, &lvCol);

	// Теперь добавляем подэлементы
	lvCol.iSubItem = 1;
	lvCol.pszText  = _T("Направление ветра");
	ListView_InsertColumn(hLstWeather, 1, &lvCol);

	lvCol.iSubItem = 2;
	lvCol.pszText  = _T("Скорость ветра, м/с");
	ListView_InsertColumn(hLstWeather, 2, &lvCol);

	lvCol.iSubItem = 3;
	lvCol.pszText  = _T("Макс. днев. темпер.");
	ListView_InsertColumn(hLstWeather, 3, &lvCol);

	lvCol.iSubItem = 4;
	lvCol.pszText  = _T("Мин. ноч. темпер.");
	ListView_InsertColumn(hLstWeather, 4, &lvCol);

	ListView_SetExtendedListViewStyle(hLstWeather,
		ListView_GetExtendedListViewStyle(hLstWeather) | LVS_EX_FULLROWSELECT);
	#pragma endregion
	
	// Загрузка данных из файла
	weather = WeatherLoad(_T("Метеоданные.txt"));
	weather.LoadFromFile();

	// Вывод вектора студентов в элемент ListView
	weather.ListView(hLstWeather);

	#pragma region Создание диалога открытия файла
	static TCHAR fileName[256];
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = sizeof(fileName);
	ofn.lpstrFilter = _T("Текстовые файлы (*.txt)\0*.txt\0CSV-файлы (*.csv)\0*.csv\0Все файлы (*.*)\0*.*\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrInitialDir = _T(".");  // текущий каталог/текущая папка
	ofn.lpstrDefExt = _T("txt");
	#pragma endregion

	#pragma region Создание диалога выбора шрифта
	colfont = RGB(0, 0, 0);
	lf.lfHeight = 13;
	lf.lfWidth = 13;
	lf.lfEscapement = 0;
	lf.lfOrientation = 0;
	lf.lfItalic = 0;
	lf.lfUnderline = 0;
	lf.lfStrikeOut = 0;
	lf.lfWeight = FW_NORMAL;
	lf.lfCharSet = RUSSIAN_CHARSET;
	_tcscpy(lf.lfFaceName, _T("Calibri"));
	cfont.lStructSize = sizeof(CHOOSEFONT);
	cfont.Flags = CF_SCREENFONTS | CF_EFFECTS | CF_INITTOLOGFONTSTRUCT;
	#pragma endregion

	#pragma region Создание диалога выбора цвета
	ccol.lStructSize = sizeof(CHOOSECOLOR);
	ccol.Flags = CC_RGBINIT;
	ccol.lpCustColors = clfusers;
	clf = RGB(255, 255, 255);
	#pragma endregion

	return TRUE;
} // OnCreate


// Обработчик сообщения WM_SIZE - обработчик события "При изменении размера"
// нашего окна
void OnSize(HWND hwnd, UINT state, int cx, int cy)
{
	RECT rect; // Прямоугольник - для хранения координат рабочей области окна
	INT32 nWidth; // Ширина столбца элемента ListView

	GetClientRect(hwnd, &rect);         // Задать область окна для перерисовки

	// Новый размер ListView
	MoveWindow(hLstWeather, 10, 10, rect.right - 20, rect.bottom - nMenuHeight - 10, TRUE);

	// Послать сообщения ListView для установки ширины столбцов
	nWidth = (rect.right - 20) / 5;
	for (size_t i = 0; i < 5; i++)
		ListView_SetColumnWidth(hLstWeather, i, nWidth);

	InvalidateRect(hwnd, &rect, TRUE);   // Объявить область недействительной => формируется WM_PAINT
} // OnSize


// Обработчик сообщения WM_PAINT - обработчик события "При отрисовке" 
void OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps; // Параметры контекста устройства
	RECT rect; // Прямоугольник - для хранения координат рабочей области окна

	hdc = BeginPaint(hwnd, &ps); // Получить хэндл контекста устройства

	font = CreateFontIndirect(&lf);
	hOldFont = SelectObject(hdc, font);
	SetTextColor(hdc, colfont);
	TextOut(hdc, 20, 20, lf.lfFaceName, _tcslen(lf.lfFaceName));
	SelectObject(hdc, hOldFont);
	DeleteObject(font);

	GetClientRect(hwnd, &rect); // Получить координаты области для рисования

	EndPaint(hwnd, &ps); // Освободить контекст для корректной работы системыû
} // OnPaint


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


// Ограничение минимального размера главного окна приложения
// !! Работает вместе с OnSize !!
void OnGetMinMaxInfo(HWND hwnd, LPMINMAXINFO lpMinMaxInfo)
{
	lpMinMaxInfo->ptMinTrackSize = { 480, 240 };
} // OnGetMinMaxInfo


// Обработка сообщений WM_COMMAND - они посылаются от элементов управления
// в частности - от кнопок
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	BOOL bResult;

	switch (id) {
		// Выбор файла данных при помощи стандартного диалога и
		// вывод данных из этого файла
	case IDC_OPEN:
		ofn.Flags = OFN_EXPLORER;
		bResult = GetOpenFileName(&ofn);
		if (!bResult) break;

		weather.SetFileName(wstring(ofn.lpstrFile));
		weather.LoadFromFile();
		weather.ListView(hLstWeather);
		break;

		// Выбор шрифта для вывода текста в ListView и установка шрифта
	case IDC_FONT:
		cfont.lpLogFont = &lf;
		cfont.rgbColors = colfont;
		if (ChooseFont(&cfont)) {
			lf = *cfont.lpLogFont;
			colfont = cfont.rgbColors;
			ListView_SetTextColor(hLstWeather, colfont);
			SendMessage(hLstWeather, WM_SETFONT, (WPARAM)CreateFontIndirect(&lf), TRUE);
		} // if
		break;

		// Выбор цвета для вывода текста в ListtView и установка цвета
	case IDC_COLOR:
		ccol.rgbResult = clf;
		if (ChooseColor(&ccol)) {
			clf = ccol.rgbResult;
			ListView_SetTextBkColor(hLstWeather, clf);
			RECT rt;
			GetClientRect(hLstWeather, &rt);
			InvalidateRect(hLstWeather, &rt, TRUE);
		} // if
		break;

	case IDC_QUIT:
		PostQuitMessage(0);
		break;
	} // switch
} // OnCommand


// Отрисовка фона статического управляющего элемента
// Фон - совпадает с фоном рабочей области окна
HBRUSH OnCtlColorStatic(HWND, HDC hdc, HWND, int)
{
	SetBkMode(hdc, TRANSPARENT);
	return CreateSolidBrush(BACKGROUND);
} // OnCtlColorStatic
