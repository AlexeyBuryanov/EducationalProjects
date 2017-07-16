#include "Includes.h"
#include "resource.h"
#include "MainWindow.h"
#include "AboutBox.h"
#include "InputLineSegBox.h"
#include "InputSizeRectBox.h"

extern HINSTANCE hAppInstance;

// Прикладная часть варианта 19, 20:
ParamV19 *pParamV19;
ParamV20 *pParamV20;

static RECT rect;   // Клиентская область окна
HWND hStBar;		// Статус-бар

HPEN   hOldPen, hPenRed, hPenGreen, hPenBlue;
HBRUSH hOldBrush, hBrush;

//
//   ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//   НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
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
} // CALLBACK WndProc


// Обработчик сообщения WM_CREATE - обработчик события "При создании" окна
BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
	UNREFERENCED_PARAMETER(lpCreateStruct);

	hStBar = CreateStatusWindow(WS_CHILD | WS_VISIBLE, _T("Добро пожаловать"), hWnd, IDC_STATUSBAR);

	hPenRed   = CreatePen(PS_SOLID, 5, RGB(0xFF, 0x00, 0x00));
	hPenGreen = CreatePen(PS_SOLID, 5, RGB(0x00, 0xEE, 0x00));
	hPenBlue  = CreatePen(PS_SOLID, 5, RGB(0x00, 0x00, 0xEE));
	hBrush	  = CreateSolidBrush(RGB(0xFF, 0xD3, 0x00));

	// Создание параметров для всех вариантов и установка начальных значений:
	pParamV19 = new ParamV19;
	pParamV19->color = NO_COLOR;
	ZeroMemory(pParamV19, sizeof(ParamV19));
	pParamV20 = new ParamV20;
	ZeroMemory(pParamV20, sizeof(ParamV20));

	// TODO:
	#pragma region Прямоугольник
	GetClientRect(hWnd, &rect);			 // Получить размер клиентской области
	InvalidateRect(hWnd, &rect, TRUE);   // Объявить область недействительной

	RECT temp;					  // Вспомогательная переменная для расчета размера прямоугольника
	GetClientRect(hStBar, &temp); // Вычитаем статус-бар из клиентской границы

	// Если прямоугольник не имеет сторон (вершины совпадают)
	// то задать длину стороны 100 (начальное состояние по условию)
	if (pParamV20->rect.top  == pParamV20->rect.bottom &&
		pParamV20->rect.left == pParamV20->rect.right) {

		// Ширина клиенсткой области окна:
		UINT uWidth  = rect.right  - rect.left;
		// Высота клиентской области окна:
		UINT uHeight = rect.bottom - rect.top - (temp.bottom - temp.top);   

		// Координаты квадрата 100 х 100 в центре окна:
		pParamV20->rect.left   = uWidth / 2 - 50;
		pParamV20->rect.right  = pParamV20->rect.left + 100;
		pParamV20->rect.top    = uHeight / 2 - 50;
		pParamV20->rect.bottom = pParamV20->rect.top + 100;

		// При старте прямоугольник должен быть выведен:
		pParamV20->view = pParamV20->rect;  
	} // if
	#pragma endregion

	pParamV19->bDraw = FALSE;   // Изначально флаг отрисовки отрезка false

	return TRUE;
} // OnCreate


// Обработка сообщений WM_COMMAND - они посылаются от элементов управления
void OnCommand(HWND hWnd, int id, HWND hWndCtl, UINT codeNotify)
{
	UNREFERENCED_PARAMETER(hWndCtl);
	UNREFERENCED_PARAMETER(codeNotify);
	
	HMENU hMenu = GetMenu(hWnd);   // Получить дескриптор меню

	switch (id) {
		// О программе:
	case ID_ABOUT:
		DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_ABOUT), hWnd, About);
		break;

		// Ввод координат для отрезка:
	case ID_INPUT_COORD:
		if (DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_INPUT_COORD), hWnd, InputLineSeg) == IDOK) {
			EnableMenuItem(hMenu, ID_DRAW,  MF_ENABLED);
		} // if
		break;

		// Рисовать:
	case ID_DRAW:
		pParamV19->bDraw = TRUE;
		InvalidateRect(hWnd, NULL, TRUE);
		EnableMenuItem(hMenu, ID_DRAW,  MF_GRAYED);
		EnableMenuItem(hMenu, ID_CLEAR, MF_ENABLED);
		break;

		// Очистить:
	case ID_CLEAR:
		pParamV19->bDraw = FALSE;				  // Не рисовать
		pParamV19->color = NO_COLOR;			  // Сбросить цвет
		ZeroMemory(pParamV19, sizeof(ParamV19));  // Обнулить параметры
		InvalidateRect(hWnd, NULL, TRUE);		  // Объявить область недействительной (перерисовать)
		EnableMenuItem(hMenu, ID_DRAW,  MF_GRAYED);
		EnableMenuItem(hMenu, ID_CLEAR, MF_GRAYED);
		break;
		
		// Параметры прямоугольника (ввод сторон X, Y для преобразования):
	case ID_INPUT_RECT:
		if (DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_INPUT_RECT), hWnd, InputSizeRect) == IDOK) {
			EnableMenuItem(hMenu, ID_CHANGE_RECT, MF_ENABLED);
			
			int nDeltaX = pParamV20->size.cx / 2;
			int nDeltaY = pParamV20->size.cy / 2;

			// Получить размер клиентской области окна:
			GetClientRect(hWnd, &rect);

			// Переключатель режима преобразования:
			switch (pParamV20->mode) {
			case INCREASE:
				// Увеличить размер прямоугольника, сохраняя цетровку:
				pParamV20->rect.left   -= nDeltaX;
				pParamV20->rect.right  += nDeltaX;
				pParamV20->rect.top    -= nDeltaY;
				pParamV20->rect.bottom += nDeltaY;

				// Контроль за увеличением размера больше клиентской области:
				if (pParamV20->rect.right  - pParamV20->rect.left > rect.right  - rect.left ||
					pParamV20->rect.bottom - pParamV20->rect.top  > rect.bottom - rect.top) {
					pParamV20->rect = pParamV20->view;   // Вернуть исходные размеры
					SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("Слишком большой прямоугольник, увеличение отменено"));
				} // if
				break;
			case DECREASE:
				// Уменьшить размер прямоугольника:
				pParamV20->rect.left   += nDeltaX;
				pParamV20->rect.right  -= nDeltaX;
				pParamV20->rect.top    += nDeltaY;
				pParamV20->rect.bottom -= nDeltaY;

				// Контроль за уменьшением ниже размера 10 по ширине или по высоте:
				if (pParamV20->rect.right  - pParamV20->rect.left < 10 ||
					pParamV20->rect.bottom - pParamV20->rect.top  < 10) {
					pParamV20->rect = pParamV20->view;   // Вернуть исходные размеры
					SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("Слишком маленькая сторона, уменьшение отменено"));
				} // if
				break;
			} // switch
		} // if
		break;

		// Изменить прямоугольник:
	case ID_CHANGE_RECT:
		// Сохранить значения для выводимого прямоугольника
		// Такая двойная работа обеспечивает вывод прямоугольника с новым
		// размером только по команде изменения размера
		pParamV20->view = pParamV20->rect;
		InvalidateRect(hWnd, NULL, TRUE);
		EnableMenuItem(hMenu, ID_CHANGE_RECT, MF_GRAYED);
		break;

	case ID_EXIT:
		PostQuitMessage(0);
		break;
	} // switch
} // OnCommand


// Обработчик сообщения WM_SIZE - обработчик события "При изменении размера" окна
void OnSize(HWND hWnd, UINT state, int cx, int cy)
{
	UNREFERENCED_PARAMETER(state);
	UNREFERENCED_PARAMETER(cx);
	UNREFERENCED_PARAMETER(cy);

	// Двигаем статус-бар вместе с изменением размера окна:
	MoveWindow(hStBar, NULL, NULL, NULL, NULL, TRUE);

	GetClientRect(hWnd, &rect);         // Задать область окна для перерисовки
	InvalidateRect(hWnd, &rect, TRUE);  // Объявить область недействительной => формируется WM_PAINT
} // OnSize


// Ограничение минимального размера главного окна приложения
void OnGetMinMaxInfo(HWND hWnd, LPMINMAXINFO lpMinMaxInfo)
{
	UNREFERENCED_PARAMETER(hWnd);

	lpMinMaxInfo->ptMinTrackSize = { 600, 400 };
} // OnGetMinMaxInfo


// Обработчик сообщения WM_PAINT - обработчик события "При отрисовке"
static HDC hDC, hCompatibleDC;   // Дескриптор контекста устройства и совместный контекст
void OnPaint(HWND hWnd)
{	
	PAINTSTRUCT ps;			     // Параметры контекста устройства
	HANDLE hBitmap, hOldBitmap;
	BITMAP Bitmap;

	hDC = BeginPaint(hWnd, &ps);    // Получить дескриптор контекста устройства
	
	#pragma region Битмап, как фон рабочей области окна
	// Загружаем bitmap, который будет отображаться в окне, из ресурсов:
	hBitmap = LoadBitmap(hAppInstance, MAKEINTRESOURCE(IDB_BACKGROUND));

	// Можно также загрузить просто из файла:
	// hBitmap = LoadImage(NULL, _T("Background.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	
	// Получаем размерность загруженного bitmap'a:
	GetObject(hBitmap, sizeof(BITMAP), &Bitmap);

	// Создаем совместный с контекстом окна контекст в памяти:
	hCompatibleDC = CreateCompatibleDC(hDC);

	// Делаем загруженный из файла bitmap текущим в совместимом контексте:
	hOldBitmap = SelectObject(hCompatibleDC, hBitmap);

	// Определяем размер рабочей области окна:
	GetClientRect(hWnd, &rect);

	// Копируем bitmap с совместимого на основной контекст с масштабированием:
	StretchBlt(hDC, NULL, NULL, rect.right, rect.bottom, hCompatibleDC, NULL, NULL, Bitmap.bmWidth, Bitmap.bmHeight, SRCCOPY);
	
	// Вновь делаем старый bitmap текущим:
	SelectObject(hCompatibleDC, hOldBitmap);

	// Удаляем загруженный с диска bitmap:
	DeleteObject(hBitmap);

	// Удаляем совместный контекст:
	DeleteDC(hCompatibleDC);
	#pragma endregion

	// Вывести квадрат view:
	SelectBrush(hDC, hBrush);
	Rectangle(hDC, pParamV20->view.left, pParamV20->view.top, pParamV20->view.right, pParamV20->view.bottom);

	// Рисование отрезков:
	if (pParamV19->bDraw) {
		// Переключатель цвета:
		switch (pParamV19->color) {
		case RED:
			SelectPen(hDC, hPenRed);
			break;
		case GREEN:
			SelectPen(hDC, hPenGreen);
			break;
		case BLUE:
			SelectPen(hDC, hPenBlue);
			break;
		} // switch
		
		// Смещаем позицию откуда будем рисовать:
		MoveToEx(hDC, pParamV19->point.X = 30, pParamV19->point.Y = 30, NULL);
		// Рисуем:
		LineTo(hDC, pParamV19->point1.X, pParamV19->point1.Y);
	} // if

	EndPaint(hWnd, &ps);   // Освободить контекст для корректной работы системы
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
	DeletePen(hPenRed);
	DeletePen(hPenGreen);
	DeletePen(hPenBlue);

	SelectBrush(hDC, hOldBrush);
	DeleteBrush(hBrush);

	delete pParamV19;
	delete pParamV20;

	PostQuitMessage(0);
} // OnDestroy


// Отрисовка фона статического управляющего элемента
HBRUSH OnCtlColorStatic(HWND hWnd, HDC hDC, HWND hWndChild, int type)
{
	UNREFERENCED_PARAMETER(hWnd);
	UNREFERENCED_PARAMETER(hWndChild);
	UNREFERENCED_PARAMETER(type);

	SetBkMode(hDC, TRANSPARENT);
	return CreateSolidBrush(BACKGROUND);
} // OnCtlColorStatic


// Обработка выбора позиции меню - вывод текста в строку состояния
void OnMenuSelect(HWND hWnd, HMENU hMenu, int item, HMENU hMenuPopup, UINT flags)
{
	UNREFERENCED_PARAMETER(hWnd);
	UNREFERENCED_PARAMETER(hMenu);
	UNREFERENCED_PARAMETER(hMenuPopup);
	UNREFERENCED_PARAMETER(flags);
	
	switch (item) {
	case ID_EXIT:
		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("Завершить работу и выйти из приложения"));
		break;
	case ID_ABOUT:
		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("Информация о программе и разработчике..."));
		break;
	case ID_INPUT_COORD:
		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("Ввести координаты и параметры отрезка..."));
		break;
	case ID_DRAW:
		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("Нарисовать отрезок с выбранными параметрами"));
		break;
	case ID_CLEAR:
		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("Очистить нарисованный отрезок и сбросить параметры"));
		break;
	case ID_INPUT_RECT:
		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("Задать размер квадрату в центре главного окна..."));
		break;
	case ID_CHANGE_RECT:
		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("Изменить квадрат"));
		break;
	default:
		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("Добро пожаловать"));
		break;
	} // switch
} // OnMenuSelect