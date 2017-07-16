#include "Includes.h"      
#include "MainWindow.h"   
#include "FonBrushWindow.h"
#include "PenSettingsWindow.h"

HINSTANCE hAppInstance;                                     // дескриптор экземпляра приложения

TCHAR szClassMain[]  = _T("MainWindow");					// класс главного окна
TCHAR szTitleMain[]  = _T("Меню | Комбобокс | Рисование");	// заголовок главного окна

TCHAR szClassFonBrush[] = _T("FonBrushWindow");				// класс окна настройки цвета фона и цвета кисти
TCHAR szTitleFonBrush[] = _T("Выбор цвета кисти");			// заголовок окна настройки цвета фона и цвета кисти

TCHAR szClassPenSettings[] = _T("PenWindow");				// класс окна параметров пера
TCHAR szTitlePenSettings[] = _T("Параметры пера");			// заголовок окна параметров пера

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, INT nCmdShow)
{
	WNDCLASS wc; // Структура для регистрации окна

	/*****************************Главное окно***********************************/
	ZeroMemory(&wc, sizeof(WNDCLASS));					// установка полям структуры значений по умолчанию

	wc.lpfnWndProc	 = WndProc;							// назначение оконной процедуры для главного окна
	wc.hInstance	 = hInstance;						// сохранили дескриптор приложения
	wc.hIcon		 = (HICON)LoadImage(NULL, _T("Icon.ico"), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);	// иконка приложения
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);		// курсор приложения
	wc.hbrBackground = CreateSolidBrush(BACKGROUND);	// получить кисть для закраски фона окна
	wc.lpszClassName = szClassMain;						// задать класс окна

	// Выполнение регистрации окна
	if (!RegisterClass(&wc)) {
		MessageBox(NULL, _T("Невозможно зарегистрировать класс главного окна!"), _T("Ошибка"), MB_ICONERROR);
		return 0;
	} // if

	// Создать главное окно приложения
	HWND hMainWnd = CreateWindow(szClassMain, szTitleMain,
		WS_OVERLAPPED | WS_CAPTION | WS_BORDER | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | CS_HREDRAW | CS_VREDRAW,
		20, 20, MAIN_WIDTH, MAIN_HEIGHT, HWND_DESKTOP, NULL, hInstance, NULL);

	// Проверка на успешное создание
	if (!hMainWnd) {
		MessageBox(NULL, _T("Невозможно создать главное окно!"), _T("Ошибка"), MB_ICONERROR);
		return 0;
	} // if

	/***********************Окно настроек фона и кисти***************************/
	ZeroMemory(&wc, sizeof(WNDCLASS));				

	wc.lpfnWndProc   = FonBrush_WndProc;
	wc.hInstance     = hInstance;						
	wc.hIcon	     = (HICON)LoadImage(NULL, _T("IconFonBrush.ico"), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	wc.hCursor	     = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = CreateSolidBrush(FONBRUSH_BACKGROUND);
	wc.lpszClassName = szClassFonBrush;
	
	if (!RegisterClass(&wc)) {
		MessageBox(NULL, _T("Невозможно зарегистрировать класс дочернего окна!"), _T("Ошибка"), MB_ICONERROR);
		return 0;
	} // if

	/***************************Окно настройки пера******************************/
	ZeroMemory(&wc, sizeof(WNDCLASS));

	wc.lpfnWndProc   = PenSettings_WndProc;
	wc.hInstance     = hInstance;
	wc.hIcon         = (HICON)LoadImage(NULL, _T("IconPenSettings.ico"), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = CreateSolidBrush(PENSETTINGS_BACKGROUND);
	wc.lpszClassName = szClassPenSettings;

	if (!RegisterClass(&wc)) {
		MessageBox(NULL, _T("Невозможно зарегистрировать класс дочернего окна!"), _T("Ошибка"), MB_ICONERROR);
		return 0;
	} // if

	/****************************************************************************/
	MSG msg;								// Сообщение 
	ShowWindow(hMainWnd, SW_SHOWNORMAL);    // Показать главное окно приложения
									   
	while (GetMessage(&msg, NULL, 0, 0)) {  // Цикл обработки сообщений
		TranslateMessage(&msg);				// Разрешаем прием сообщений от клавиатуры
		DispatchMessage(&msg);
	} // while

	return 0;
} // WinMain
