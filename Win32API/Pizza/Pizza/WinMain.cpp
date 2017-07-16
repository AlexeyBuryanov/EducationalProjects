#include "Includes.h"     /* Главный фаайл определений для WinAPI-приложения */
#include "MainWindow.h"   /* Опредления для окна. Каждому окну - свой файл определений */


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nCmdShow)
{
	// Зарегистрировать класс главного окна
	TCHAR szClassName[] = _T("Pizza");		// класс окна
	TCHAR szTitle[] = _T("Заказ пиццы");	// заголовок окна

	MSG msg;   // Сообщение 

	// Структура для регистрации окна
	WNDCLASS wc;

	ZeroMemory(&wc, sizeof(WNDCLASS));					// установка полям структуры значений по умолчанию

	wc.lpfnWndProc   = WndProc;							// назначение оконной процедуры для главного окна
	wc.hInstance	 = hInstance;						// сохранили дескриптор приложения
	wc.hIcon		 = (HICON)LoadImage(NULL, _T("Icon.ico"), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);	// иконка приложения
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);		// курсор приложения
	wc.hbrBackground = CreateSolidBrush(BACKGROUND);	// получить кисть для закраски фона окна
	wc.lpszClassName = szClassName;						// задать класс окна

	// Выполнение регистрации окна
	if (!RegisterClass(&wc)) {
		MessageBox(NULL, _T("Невозможно зарегистрировать класс окна!"), _T("Ошибка"), MB_ICONERROR);
		return 0;
	} // if

	// Создать главное окно приложения
	// класс и заголовок окна, стиль, координаты верхнего левого угла, размер окна (ширина, высота)
	HWND hMainWnd = CreateWindow(szClassName, szTitle,	
		WS_OVERLAPPED | WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | CS_HREDRAW | CS_VREDRAW,
		15, 15, 575, 385,
		HWND_DESKTOP, NULL, hInstance, NULL);       // хозяин окна, дескриптор меню, дескриптор приложения, доп. параметры

	if (!hMainWnd) {
		MessageBox(NULL, _T("Невозможно создать главное окно!"), _T("Ошибка"), MB_ICONERROR);
		return 0;
	} // if

	ShowWindow(hMainWnd, SW_SHOWNORMAL);   // Показать главное окно приложения

	// Цикл обработки сообщений
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);   // Разрешаем прием сообщений от клавиатуры
		DispatchMessage(&msg);
	} // while

	return 0;
} // WinMain


