#include "Includes.h"      
#include "MainWindow.h"   
#include "InputWindow.h"
#include "SortWindow.h"
#include "FieldsOutWindow.h"

HINSTANCE hAppInstance;									// дескриптор экземпляра приложения

TCHAR szClassMain[]  = _T("MainWindow");				// класс главного окна
TCHAR szTitleMain[]  = _T("Прайс-лист");				// заголовок главного окна

TCHAR szClassInput[] = _T("InputWindow");				// класс окна ввода
TCHAR szTitleInput[] = _T("Ввод товара");				// заголовок окна ввода

TCHAR szClassSort[] = _T("SortWindow");					// класс окна выбора поля для сортировки
TCHAR szTitleSort[] = _T("Выбор поля сортировки");		// заголовок окна выбора поля для сортировки

TCHAR szClassFieldsOut[] = _T("FieldsOutWindow");		// класс окна выбора поля для вывода
TCHAR szTitleFieldsOut[] = _T("Выбор полей для вывода");// заголовок окна выбора поля для вывода

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

	//********************************Окно ввода**********************************/
	ZeroMemory(&wc, sizeof(WNDCLASS));

	wc.lpfnWndProc   = Input_WndProc;
	wc.hInstance     = hInstance;
	wc.hIcon         = (HICON)LoadImage(NULL, _T("IconInput.ico"), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	wc.hCursor       = LoadCursor(NULL, IDC_IBEAM);
	wc.hbrBackground = CreateSolidBrush(INPUT_BACKGROUND);
	wc.lpszClassName = szClassInput;

	if (!RegisterClass(&wc)) {
		MessageBox(NULL, _T("Невозможно зарегистрировать класс дочернего окна!"), _T("Ошибка"), MB_ICONERROR);
		return 0;
	} // if

	/*************************Окно выбора сортировки*****************************/
	ZeroMemory(&wc, sizeof(WNDCLASS));

	wc.lpfnWndProc   = Sort_WndProc;
	wc.hInstance     = hInstance;
	wc.hIcon         = (HICON)LoadImage(NULL, _T("IconSort.ico"), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = CreateSolidBrush(SORT_BACKGROUND);
	wc.lpszClassName = szClassSort;

	if (!RegisterClass(&wc)) {
		MessageBox(NULL, _T("Невозможно зарегистрировать класс дочернего окна!"), _T("Ошибка"), MB_ICONERROR);
		return 0;
	} // if

	/***********************Окно выбора полей для вывода*************************/
	ZeroMemory(&wc, sizeof(WNDCLASS));

	wc.lpfnWndProc   = FieldsOut_WndProc;
	wc.hInstance     = hInstance;
	wc.hIcon         = (HICON)LoadImage(NULL, _T("IconFieldsOut.ico"), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = CreateSolidBrush(FIELDSOUT_BACKGROUND);
	wc.lpszClassName = szClassFieldsOut;

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
