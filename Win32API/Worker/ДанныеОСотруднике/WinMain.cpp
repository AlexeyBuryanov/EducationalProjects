#include "Includes.h"     
#include "MainWindow.h"   


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nCmdShow)
{
	// «арегистрировать класс главного окна
	TCHAR szClassName[] = _T("Employee");			// класс окна
	TCHAR szTitle[] = _T("ƒанные о сотруднике");	// заголовок окна

	MSG msg;   // —ообщение 

	// —труктура дл€ регистрации окна
	WNDCLASS wc;

	ZeroMemory(&wc, sizeof(WNDCLASS));					// установка пол€м структуры значений по умолчанию

	wc.lpfnWndProc   = WndProc;							// назначение оконной процедуры дл€ главного окна
	wc.hInstance	 = hInstance;						// сохранили дескриптор приложени€
	wc.hIcon		 = (HICON)LoadImage(NULL, _T("Icon.ico"), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);	// иконка приложени€
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);		// курсор приложени€
	wc.hbrBackground = CreateSolidBrush(BACKGROUND);	// получить кисть дл€ закраски фона окна
	wc.lpszClassName = szClassName;						// задать класс окна

	// ¬ыполнение регистрации окна
	if (!RegisterClass(&wc)) {
		MessageBox(NULL, _T("Ќевозможно зарегистрировать класс окна!"), _T("ќшибка"), MB_ICONERROR);
		return 0;
	} // if

	// —оздать главное окно приложени€
	// класс и заголовок окна, стиль, координаты верхнего левого угла, размер окна (ширина, высота)
	HWND hMainWnd = CreateWindow(szClassName, szTitle,	
		WS_OVERLAPPED | WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | CS_HREDRAW | CS_VREDRAW,
		15, 15, 875, 385,
		HWND_DESKTOP, NULL, hInstance, NULL);       // хоз€ин окна, дескриптор меню, дескриптор приложени€, доп. параметры

	if (!hMainWnd) {
		MessageBox(NULL, _T("Ќевозможно создать главное окно!"), _T("ќшибка"), MB_ICONERROR);
		return 0;
	} // if

	ShowWindow(hMainWnd, SW_SHOWNORMAL);   // ѕоказать главное окно приложени€

	// ÷икл обработки сообщений
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);   // –азрешаем прием сообщений от клавиатуры
		DispatchMessage(&msg);
	} // while

	return 0;
} // WinMain


