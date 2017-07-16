#include "Includes.h"  
#include "resource.h"
#include "WinMain.h"
#include "MainWindow.h"

HINSTANCE hAppInstance;							// Дескриптор экземпляра приложения
TCHAR	  szMainWindowTitle[MAX_LOADSTRING];	// Текст строки заголовка
TCHAR	  szMainWindowClass[MAX_LOADSTRING];    // Имя класса главного окна


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
					  _In_opt_ HINSTANCE hPrevInstance,
					  _In_ LPWSTR    lpCmdLine,
					  _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Инициализация глобальных строк:
	LoadStringW(hInstance, IDS_APP_TITLE, szMainWindowTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_APP_CLASS, szMainWindowClass, MAX_LOADSTRING);
	RegisterMainClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance(hInstance, nCmdShow)) {
		MessageBox(NULL, _T("Невозможно выполнить инициализацию приложения!"), _T("Ошибка"), MB_ICONERROR);
		return FALSE;
	} // if

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32ACCEL));

	MSG msg;
	// Цикл основного сообщения:
	while (GetMessage(&msg, nullptr, 0, 0)) {
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} // if
	} // while

	return (int)msg.wParam;
} // WinMain


//
//   ФУНКЦИЯ: RegisterMainClass()
//
//   НАЗНАЧЕНИЕ: регистрирует класс главного окна.
//
ATOM RegisterMainClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style		   = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc   = WndProc;
	wcex.cbClsExtra    = 0;
	wcex.cbWndExtra    = 0;
	wcex.hInstance     = hInstance;
	wcex.hIcon		   = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BIG));
	wcex.hIconSm	   = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	wcex.hCursor	   = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = CreateSolidBrush(BACKGROUND);
	wcex.lpszMenuName  = MAKEINTRESOURCE(IDC_WIN32MENU);
	wcex.lpszClassName = szMainWindowClass;

	return RegisterClassEx(&wcex);
} // RegisterMainClass


//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hAppInstance = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

	HWND hMainWnd = CreateWindow(szMainWindowClass, szMainWindowTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, MAIN_WIDTH, MAIN_HEIGHT, nullptr, nullptr, hInstance, nullptr);
	
	if (!hMainWnd) {
		MessageBox(NULL, _T("Невозможно создать главное окно!"), _T("Ошибка"), MB_ICONERROR);
		return FALSE;
	} // if

	ShowWindow(hMainWnd, nCmdShow);
	UpdateWindow(hMainWnd);

	return TRUE;
} // InitInstance