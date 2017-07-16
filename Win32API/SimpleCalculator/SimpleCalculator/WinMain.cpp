#include "Includes.h"  
#include "MainWindow.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nCmdShow)
{
	// ���������������� ����� �������� ����
	TCHAR szClassName[] = _T("Calculate");		    // ����� ����
	TCHAR szTitle[] = _T("����������� ver. 0.1");	// ��������� ����

	MSG msg;   // ��������� 

	// ��������� ��� ����������� ����
	WNDCLASS wc;

	ZeroMemory(&wc, sizeof(WNDCLASS));					// ��������� ����� ��������� �������� �� ���������

	wc.lpfnWndProc   = WndProc;							// ���������� ������� ��������� ��� �������� ����
	wc.hInstance	 = hInstance;						// ��������� ���������� ����������
	wc.hIcon		 = (HICON)LoadImage(NULL, _T("Icon.ico"), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);	// ������ ����������
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);		// ������ ����������
	wc.hbrBackground = CreateSolidBrush(BACKGROUND);	// �������� ����� ��� �������� ���� ����
	wc.lpszClassName = szClassName;						// ������ ����� ����

	// ���������� ����������� ����
	RegisterClass(&wc);

	// ������� ������� ���� ����������
	// ����� � ��������� ����, �����, ���������� �������� ������ ����, ������ ���� (������, ������)
	HWND hWnd = CreateWindow(szClassName, szTitle,	
		WS_OVERLAPPED | WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, 15, 15, 297, 290,
		HWND_DESKTOP, NULL, hInstance, NULL);       // ������ ����, ���������� ����, ���������� ����������, ���. ���������

	ShowWindow(hWnd, SW_SHOWNORMAL);   // �������� ������� ���� ����������

	// ���� ��������� ���������
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);   // ��������� ����� ��������� �� ����������
		DispatchMessage(&msg);
	} // while

	return 0;
} // WinMain


