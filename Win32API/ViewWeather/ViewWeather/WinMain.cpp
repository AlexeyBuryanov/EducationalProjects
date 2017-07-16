#include "Includes.h"  
#include "MainWindow.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nCmdShow)
{
	// ���������������� ����� �������� ����
	TCHAR szClassName[] = _T("Windows");				    // ����� ����
	TCHAR szTitle[] = _T("����������������� ������");		// ��������� ����

	MSG msg;   // ��������� 

	// ��������� ��� ����������� ����
	WNDCLASS wc;

	ZeroMemory(&wc, sizeof(WNDCLASS));				// ��������� ����� ��������� �������� �� ���������

	wc.lpfnWndProc   = WndProc;						// ���������� ������� ��������� ��� �������� ����
	wc.hInstance	 = hInstance;						// ��������� ���������� ����������
	wc.hIcon		 = (HICON)LoadImage(NULL, _T("Icon.ico"), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);	// ������ ����������
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);		// ������ ����������
	wc.hbrBackground = CreateSolidBrush(BACKGROUND);// �������� ����� ��� �������� ���� ����
	wc.lpszClassName = szClassName;					// ������ ����� ����

													// ���������� ����������� ����
	RegisterClass(&wc);

	// ������� ������� ���� ����������
	HWND hwnd = CreateWindow(szClassName, szTitle,	// ����� � ��������� ����
		WS_OVERLAPPEDWINDOW | CS_HREDRAW | CS_VREDRAW, 15, 15, 640, 480,		// �����, ���������� �������� ������ ����, ������ ���� (������, ������)
		HWND_DESKTOP, NULL, hInstance, NULL);       // ������ ����, ���������� ����, ���������� ����������, ���. ���������

	ShowWindow(hwnd, SW_SHOWNORMAL);   // �������� ������� ���� ����������

	// ���� ��������� ���������
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);   // ��������� ����� ��������� �� ����������
		DispatchMessage(&msg);
	} // while

	return 0;
} // WinMain
