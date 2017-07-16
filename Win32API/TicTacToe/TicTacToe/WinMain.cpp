#include "WinMain.h"   
#include "MainWindow.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nCmdShow)
{
	// ���������������� ����� �������� ����
	TCHAR szClassName[] = _T("TicTacToe");				        // ����� ����
	TCHAR szTitle[] = _T("��������-������ - ������ �������");	// ��������� ����

	MSG msg;   // ��������� 

	// ��������� ��� ����������� ����
	WNDCLASS wc;

	ZeroMemory(&wc, sizeof(WNDCLASS));				// ��������� ����� ��������� �������� �� ���������
	wc.lpfnWndProc = WndProc;						// ���������� ������� ��������� ��� �������� ����
	wc.hInstance = hInstance;						// ��������� ���������� ����������
	wc.hIcon   = (HICON)LoadImage(NULL, _T("Icon.ico"), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);	// ������ ����������
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);		// ������ ����������
	wc.hbrBackground = CreateSolidBrush(RGB(0x22, 0xbb, 0xaa));		// �������� ����� ��� �������� ���� ����
	wc.lpszClassName = szClassName;					// ������ ����� ����

	// ���������� ����������� ����
	RegisterClass(&wc);

	// ������� ������� ���� ����������
	HWND hwnd = CreateWindow(szClassName, szTitle,	// ����� � ��������� ����
		WS_OVERLAPPEDWINDOW, 15, 15, 640, 480,		// �����, ���������� �������� ������ ����, ������ ���� (������, ������)
		HWND_DESKTOP, NULL, hInstance, NULL);       // ������ ����, ���������� ����, ���������� ����������, ���. ���������

	ShowWindow(hwnd, SW_SHOWNORMAL);   // �������� ������� ���� ����������

	// ���� ��������� ���������
	while (GetMessage(&msg, NULL, 0, 0)) {
		DispatchMessage(&msg);
	} // while

	return 0;
} // WinMain


