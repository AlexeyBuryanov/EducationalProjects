#include "Includes.h"  
#include "MainWindow.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nCmdShow)
{
	// Зарегистрировать класс главного окна
	TCHAR szClassName[] = _T("Windows");				    // класс окна
	TCHAR szTitle[] = _T("Метеорологические данные");		// заголовок окна

	MSG msg;   // Сообщение 

	// Структура для регистрации окна
	WNDCLASS wc;

	ZeroMemory(&wc, sizeof(WNDCLASS));				// установка полям структуры значений по умолчанию

	wc.lpfnWndProc   = WndProc;						// назначение оконной процедуры для главного окна
	wc.hInstance	 = hInstance;						// сохранили дескриптор приложения
	wc.hIcon		 = (HICON)LoadImage(NULL, _T("Icon.ico"), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);	// иконка приложения
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);		// курсор приложения
	wc.hbrBackground = CreateSolidBrush(BACKGROUND);// получить кисть для закраски фона окна
	wc.lpszClassName = szClassName;					// задать класс окна

													// Выполнение регистрации окна
	RegisterClass(&wc);

	// Создать главное окно приложения
	HWND hwnd = CreateWindow(szClassName, szTitle,	// класс и заголовок окна
		WS_OVERLAPPEDWINDOW | CS_HREDRAW | CS_VREDRAW, 15, 15, 640, 480,		// стиль, координаты верхнего левого угла, размер окна (ширина, высота)
		HWND_DESKTOP, NULL, hInstance, NULL);       // хозяин окна, дескриптор меню, дескриптор приложения, доп. параметры

	ShowWindow(hwnd, SW_SHOWNORMAL);   // Показать главное окно приложения

	// Цикл обработки сообщений
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);   // Разрешаем прием сообщений от клавиатуры
		DispatchMessage(&msg);
	} // while

	return 0;
} // WinMain
