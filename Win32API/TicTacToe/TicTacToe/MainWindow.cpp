#include "WinMain.h"
#include "MainWindow.h"
#include "TicTacToe.h"

// Переменные и функции для главного окна приложения
static HDC hdc;                    // Хэндл контекста устройства
static HPEN hPen, hOldPen;		   // Перья для рисования
static HFONT hFont, hOldFont;      // шрифт для вывода
static short xPos, yPos;           // Координаты щелчка ЛКМ
static int nEventID = EVENT_NONE;  // Идентификатор события
static LOGFONT lf;                 // Структура для создания шрифта

static TicTacToe *game;   // Переменная для работы с экземпляром крестиков-ноликов

static int nMargin = 10;  // Отступ для вывода линий игрового поля

// Оконная функция - обработка сообщений, получаемых окном
// hwnd	  - дескриптор окна
// msg	  - числовой код сообщения
// wParam - первая часть параметров сообщения
// lParam - вторая часть параметров сообщения
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
		HANDLE_MSG(hwnd, WM_CREATE,		   OnCreate);  // создание окна
		HANDLE_MSG(hwnd, WM_SIZE,		   OnSize);    // Изменение размера экрана
		HANDLE_MSG(hwnd, WM_LBUTTONDOWN,   OnLButtonDown);
		HANDLE_MSG(hwnd, WM_RBUTTONDOWN,   OnRButtonDown);
		HANDLE_MSG(hwnd, WM_PAINT,		   OnPaint);
		HANDLE_MSG(hwnd, WM_CLOSE,		   OnClose);
		HANDLE_MSG(hwnd, WM_DESTROY,	   OnDestroy);
		HANDLE_MSG(hwnd, WM_GETMINMAXINFO, OnGetMinMaxInfo);
	
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
	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

	game = new TicTacToe();
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


// Обработчик сообщения WM_LBUTTONDOWN - обработчик события "Щелчок ЛКМ" 
void OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
	RECT rect;       // Прямоугольник - для хранения координат рабочей области окна 

	GetClientRect(hwnd, &rect);
	nEventID = EVENT_LEFT;
	xPos = x;
	yPos = y;
	InvalidateRect(hwnd, &rect, TRUE);  // !!!!! Перерисовываем по этому вызову !!!!!
} // OnLButtonDown


// Обработчик сообщения WM_RBUTTONDOWN - обработчик события "Щелчок ПКМ" 
void OnRButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
	RECT rect;       // Прямоугольник - для хранения координат рабочей области окна 

	GetClientRect(hwnd, &rect);
	nEventID = EVENT_RIGHT;
	xPos = x;
	yPos = y;
	InvalidateRect(hwnd, &rect, TRUE);  // !!!!! Перерисовываем по этому вызову !!!!!
} // OnRButtonDown


// Обработчик сообщения WM_PAINT - обработчик события "При отрисовке" 
void OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;  // Параметры контекста устройства
	RECT rect;       // Прямоугольник - для хранения координат рабочей области окна 

	hdc = BeginPaint(hwnd, &ps);    // Получить хэндл контекста устройства
	GetClientRect(hwnd, &rect);     // Получить координаты области для рисования

	// Выбор карандаша для рисования 
	hOldPen = SelectPen(hdc, hPen);

	// Рисуем линии - границы игрового поля
	int nWidth = rect.right - rect.left - 2 * nMargin;
	int nHeight = rect.bottom - rect.top - 2 * nMargin;

	int x = nMargin, y = nMargin;  // Верхний левый угол игрового поля

	// Вывод горизонтальных линий
	for (int i = 0; i <= 3; i++) {
		MoveToEx(hdc, x, y, NULL);
		LineTo(hdc, x + nWidth, y);
		y += nHeight / 3;
	} // for i

	// Вывод вертикальных линий
	x = y = nMargin;
	for (int i = 0; i <= 3; i++) {
		MoveToEx(hdc, x, y, NULL);
		LineTo(hdc, x, y + nHeight);
		x += nWidth / 3;
	} // for i

	SIZE  size;  // размер ячейки игрового поля
	COORD ltc;   // верхний левый угол ячейки игрового поля
	size.cx = nWidth / 3;
	size.cy = nHeight / 3;
	int nCol = (xPos - nMargin) / size.cx;  // номер столбца
	int nRow = (yPos - nMargin) / size.cy;  // номер строки

	// Отрисовка "игровой ситуации", "игрового поля"
	// Заполнение очередной ячейки - выполняем очередной ход игры
	game->Fill(nRow, nCol, nEventID);

	// Отображение игровой карты, игрового поля
	ZeroMemory(&lf, sizeof(LOGFONT));
	_tcscpy(lf.lfFaceName, _T("Georgia"));
	lf.lfHeight = -size.cy;
	
	hFont = CreateFontIndirect(&lf);
	
	hOldFont = SelectFont(hdc, hFont); // Выбор шрифта для отрисовки
	SetBkMode(hdc, TRANSPARENT);       // Прозрачный фон при выводе текста

	TEXTMETRIC tm;                // Получить метрики, характеристики
	GetTextMetrics(hdc, &tm);     // шрифта (параметры текста)

	ltc.Y = nMargin;
	TCHAR szCeil[2] = _T(""); // Строка для вывода крестика или нолика
	for (int i = 0; i < 3; i++, ltc.Y += (SHORT)size.cy) {
		ltc.X = nMargin;
		for (int j = 0; j < 3; j++, ltc.X += (SHORT)size.cx) {
			if (game->getMap(i, j) == ' ') continue;
			szCeil[0] = game->getMap(i, j);

			// Цвет выводимых символов - крестики выводим красным цветом,
			// нолики выводим синим цветом
			SetTextColor(hdc, szCeil[0] == _T('X')?RGB(200, 0, 0):RGB(0, 0, 200));

			// Расчет смещения по горизонтали буквы в ячейке
			int x = (size.cx - tm.tmAveCharWidth) / 4;
			TextOut(hdc, ltc.X + x, ltc.Y, szCeil, 1);
		} // for j
	} // for i

	SelectFont(hdc, hOldFont);
	DeleteFont(hFont);
	EndPaint(hwnd, &ps);            // Освободить контекст для корректной работы системы

	// Проверка - не завершена ли партия
	if (game->isFinish()) {
		ProcFinish(hwnd, rect);
	} // if
} // OnPaint


// Обработчик сообщения WM_CLOSE - обработчик события "При закрытии окна" 
void OnClose(HWND hwnd)
{
	// Освобождение ресурса по окончании его использоввания
	SelectPen(hdc, hOldPen);
	DeletePen(hPen);

	delete game;
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


// Обработка завершения игры - определение победителя
// Запрос на продолжение игры
void ProcFinish(HWND hwnd, RECT rect) 
{
	TCHAR szMessage[200];
	TCHAR szResult[50]; // Результат игры
	int nReply;         // Ответ пользователя

	// Определим результат игры - кто победитель или ничья
	TCHAR c = game->getWinner();

	// Сформировать строку с результатом
	if (c == _T('X')) {
		_tcscpy(szResult, _T("Победитель - X"));
	} else if (c == _T('O')) {
		_tcscpy(szResult, _T("Победитель - O"));
	} else {
		_tcscpy(szResult, _T("Ничья"));
	} // if
	_stprintf(szMessage, _T("Игра окончена. %s.\nМожет, еще сыграем?"), szResult);

	// Вывод окна с запросом к пользователю и обработка ответа
	nReply = MessageBox(HWND_DESKTOP, szMessage, _T("К сведению"), MB_YESNO | MB_ICONINFORMATION);
	if (nReply == IDYES) {
		game->Clear();                      // Очистка игровго поля
		nEventID = EVENT_NONE;              // Нет хода
		InvalidateRect(hwnd, &rect, TRUE);  // Перерисовать игрвое поле
	} else {
		PostQuitMessage(0);
	} // if
} // ProcFinish