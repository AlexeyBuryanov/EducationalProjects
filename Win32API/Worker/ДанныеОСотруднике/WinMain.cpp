#include "Includes.h"     
#include "MainWindow.h"   


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nCmdShow)
{
	// ���������������� ����� �������� ����
	TCHAR szClassName[] = _T("Employee");			// ����� ����
	TCHAR szTitle[] = _T("������ � ����������");	// ��������� ����

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
	if (!RegisterClass(&wc)) {
		MessageBox(NULL, _T("���������� ���������������� ����� ����!"), _T("������"), MB_ICONERROR);
		return 0;
	} // if

	// ������� ������� ���� ����������
	// ����� � ��������� ����, �����, ���������� �������� ������ ����, ������ ���� (������, ������)
	HWND hMainWnd = CreateWindow(szClassName, szTitle,	
		WS_OVERLAPPED | WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | CS_HREDRAW | CS_VREDRAW,
		15, 15, 875, 385,
		HWND_DESKTOP, NULL, hInstance, NULL);       // ������ ����, ���������� ����, ���������� ����������, ���. ���������

	if (!hMainWnd) {
		MessageBox(NULL, _T("���������� ������� ������� ����!"), _T("������"), MB_ICONERROR);
		return 0;
	} // if

	ShowWindow(hMainWnd, SW_SHOWNORMAL);   // �������� ������� ���� ����������

	// ���� ��������� ���������
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);   // ��������� ����� ��������� �� ����������
		DispatchMessage(&msg);
	} // while

	return 0;
} // WinMain


