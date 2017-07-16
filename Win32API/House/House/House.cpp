#include <Windows.h>
#include <windowsx.h>
#include <tchar.h>


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nCmdShow)
{
	// Зарегистрировать класс главного окна
	TCHAR szClassName[] = _T("WindowName");				// класс окна
	TCHAR szTitle[] = _T("Дом");	// заголовок окна

	// Сообщение 
	MSG msg;

	// Структура для регистрации окна
	WNDCLASS wc;

	ZeroMemory(&wc, sizeof(WNDCLASS));					// установка полям структуры значений по умолчанию
	
	wc.lpfnWndProc	 = WndProc;							// назначение оконной процедуры для главного окна
	wc.hInstance	 = hInstance;					    // сохранили дескриптор приложения
	wc.hIcon		 = LoadIcon(NULL, IDI_INFORMATION);	// иконка приложения
	wc.hCursor		 = LoadCursor(NULL, IDC_IBEAM);		// курсор приложения
	wc.hbrBackground = GetStockBrush(WHITE_BRUSH);		// получить кисть для закраски фона окна
	wc.lpszClassName = szClassName;						// задать класс окна

	// Выполнение регистрации окна
	RegisterClass(&wc);

	// Создать главное окно приложения
	HWND hwnd = CreateWindow(szClassName, szTitle,	// класс и заголовок окна
		WS_OVERLAPPED | WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, 15, 15, 740, 580,		// стиль, координаты верхнего левого угла, размер окна (ширина, высота)
		HWND_DESKTOP, NULL, hInstance, NULL);       // хозяин окна, дескриптор меню, дескриптор приложения, доп. параметры

	// Показать главное окно приложения
	ShowWindow(hwnd, SW_SHOWNORMAL);

	// Цикл обработки сообщений
	while (GetMessage(&msg, NULL, 0, 0)) {
		DispatchMessage(&msg);
	} // while

	return 0;
} // WinMain

// Оконная функция - обработка сообщений, получаемых окном
// hwnd	  - дескриптор окна
// msg	  - числовой код сообщения
// wParam - первая часть параметров сообщения
// lParam - вторая часть параметров сообщения
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;         // Хэндл контекста устройства
	PAINTSTRUCT ps;  // Параметры контекста устройства
	RECT rect;       // Прямоугольник - для хранения координат рабочей области окна 
	//POINT point;     // Координата точки, нужна функции MoveToEx

	const UINT N_POINTS = 3;
	POINT apt[N_POINTS] = { {30, 200}, {370, 30}, {700, 200} };

	TCHAR str[] = _T("House");
	TCHAR str1[] = _T("О"); // ручка двери

	// Перья для рисования
	HPEN hPen, hPenRect, hPenSkyblue, hOldPen;
	// Кисти для закраски
	HBRUSH hRectBrushGreen, hRectBrushBlue;	// для летнего фона
	HBRUSH hRedBrush, hGreyBrush, hBlackBrush, hBrownBrush, hTanBrush, hWhiteBrush, hOrangeRedBrush, hOldBrush;    

	switch (msg) {

	case WM_SIZE:   // Изменение размера экрана
		GetClientRect(hwnd, &rect);         // Задать область окна для перерисовки
		InvalidateRect(hwnd, &rect, TRUE);  // Объявить область недействительной => формируется WM_PAINT
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);    // Получить хэндл контекста устройства
		GetClientRect(hwnd, &rect);     // Получить координаты области для рисования

		// Создание карандаша и выбор карандаша для рисования 
		hPen		 = CreatePen(PS_SOLID, 1, RGB(85, 26, 139));   // для фигур
		hPenRect	 = CreatePen(PS_SOLID, 2, RGB(28, 28, 28));    // для рамки окна
		hPenSkyblue  = CreatePen(PS_SOLID, 9, RGB(135, 206, 235)); // для "окна" дома

		// Закраска фона - при помощи кисти
		hRectBrushGreen = CreateSolidBrush(RGB(127, 255, 0));
		hRectBrushBlue  = CreateSolidBrush(RGB(0, 192, 255));
		hRedBrush		= CreateSolidBrush(RGB(0xcc, 0, 0));
		hGreyBrush		= CreateSolidBrush(RGB(220, 220, 220));
		hBlackBrush		= CreateSolidBrush(RGB(28, 28, 28));
		hBrownBrush		= CreateSolidBrush(RGB(139, 69, 19));
		hTanBrush		= CreateSolidBrush(RGB(205, 133, 63));
		hWhiteBrush		= CreateSolidBrush(RGB(255, 255, 255));
		hOrangeRedBrush = CreateSolidBrush(RGB(139, 37, 0));

		hOldPen   = SelectPen(hdc, hPenRect); // выбираем карандаш для очертаний рамки окна
		// небо
		hOldBrush = SelectBrush(hdc, hRectBrushBlue);				      
		Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
		// трава
		hOldBrush = SelectBrush(hdc, hRectBrushGreen);				   
		Rectangle(hdc, rect.left, rect.top + 380, rect.right, rect.bottom);

		// Выбираем карандаш для рисовки основ дома
		hOldPen = SelectPen(hdc, hPen);

		// Основа дома
		hOldBrush = SelectBrush(hdc, hGreyBrush);
		Rectangle(hdc, rect.left + 50, rect.top + 200, rect.right - 50, rect.bottom - 50);

		// Выбираем красную кисть для закраски крыши нашего дома
		hOldBrush = SelectBrush(hdc, hRedBrush);
		Polygon(hdc, apt, N_POINTS);

		// Фундамент
		hOldBrush = SelectBrush(hdc, hBlackBrush);
		Rectangle(hdc, rect.left + 35, rect.top + 450, rect.right - 35, rect.bottom - 50);
		
		// Двери
		hOldBrush = SelectBrush(hdc, hBrownBrush);
		Rectangle(hdc, rect.left + 400, rect.top + 310, rect.right - 200, rect.bottom - 50);
		hOldBrush = SelectBrush(hdc, hTanBrush);
		Rectangle(hdc, rect.left + 420, rect.top + 330, rect.right - 220, rect.bottom - 50);

		// Окно
		hOldPen   = SelectPen(hdc, hPenSkyblue);    // Выбираем карандаш с подходящей обводкой
		hOldBrush = SelectBrush(hdc, hWhiteBrush);	// Фон
		Rectangle(hdc, rect.left + 120, rect.top + 250, rect.right - 420, rect.bottom - 200);
		/* Хотел нарисовать 2 линии сверху вниз с помощью LineTo(), но не понял, как это сделать
		Пришлось просто: */
		Rectangle(hdc, rect.left + 180, rect.top + 250, rect.right - 480, rect.bottom - 200);
		hOldPen = SelectPen(hdc, hPen);

		// Труба
		hOldBrush = SelectBrush(hdc, hOrangeRedBrush);
		Rectangle(hdc, rect.left + 180, rect.top + 60, rect.right - 480, rect.bottom - 400);

		TextOut(hdc, rect.left + 342, rect.top + 10, str, _tcslen(str));	// выводим текст
		TextOut(hdc, rect.left + 430, rect.top + 400, str1, _tcslen(str1));	// выводим ручку

		// Освобождение ресурса по окончании его использования
		SelectPen(hdc, hOldPen);
		DeletePen(hPen);
		DeletePen(hPenRect);
		DeletePen(hPenSkyblue);

		SelectBrush(hdc, hOldBrush);
		DeleteBrush(hRectBrushGreen);
		DeleteBrush(hRectBrushBlue);
		DeleteBrush(hRedBrush);
		DeleteBrush(hGreyBrush);
		DeleteBrush(hBlackBrush);
		DeleteBrush(hBrownBrush);
		DeleteBrush(hTanBrush);
		DeleteBrush(hWhiteBrush);
		DeleteBrush(hOrangeRedBrush);

		// Освободить контекст для корректной работы системы
		EndPaint(hwnd, &ps);
		break;

	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:		// сообщение "Завершить работу"
		PostQuitMessage(0);	// отправка сообщения "Конец работы" для выхода из цикла сообщений
		break;

	// Обработка сообщений для которых не предусмотрена обработка в нашем окне
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	} // switch

	return 0;
} // WndProce