#include "Includes.h"      
#include "MainWindow.h"   
#include "InputWindow.h"

HINSTANCE hAppInstance;   // ���������� ���������� ����������

TCHAR szClassMain[]  = _T("MainWindow");			// ����� �������� ����
TCHAR szTitleMain[]  = _T("����� ���������");		// ��������� �������� ����

TCHAR szClassInput[] = _T("InputWindow");			// ����� ���� �����
TCHAR szTitleInput[] = _T("���� ������ ��������");	// ��������� ���� �����

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, INT nCmdShow)
{
	MSG msg;     // ��������� 
	WNDCLASS wc; // ��������� ��� ����������� ����

	/*****************************������� ����***********************************/
	ZeroMemory(&wc, sizeof(WNDCLASS));					// ��������� ����� ��������� �������� �� ���������

	wc.lpfnWndProc	 = WndProc;							// ���������� ������� ��������� ��� �������� ����
	wc.hInstance	 = hInstance;						// ��������� ���������� ����������
	wc.hIcon		 = (HICON)LoadImage(NULL, _T("Icon.ico"), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);	// ������ ����������
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);		// ������ ����������
	wc.hbrBackground = CreateSolidBrush(BACKGROUND);	// �������� ����� ��� �������� ���� ����
	wc.lpszClassName = szClassMain;						// ������ ����� ����

	// ���������� ����������� ����
	if (!RegisterClass(&wc)) {
		MessageBox(NULL, _T("���������� ���������������� ����� �������� ����!"), _T("������"), MB_ICONERROR);
		return 0;
	} // if

	// ������� ������� ���� ����������
	HWND hMainWnd = CreateWindow(szClassMain, szTitleMain,
		WS_OVERLAPPED | WS_CAPTION | WS_BORDER | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | CS_HREDRAW | CS_VREDRAW,
		15, 15, MAIN_WIDTH, MAIN_HEIGHT, HWND_DESKTOP, NULL, hInstance, NULL);

	// �������� �� �������� ��������
	if (!hMainWnd) {
		MessageBox(NULL, _T("���������� ������� ������� ����!"), _T("������"), MB_ICONERROR);
		return 0;
	} // if

	/********************************���� �����**********************************/
	ZeroMemory(&wc, sizeof(WNDCLASS));				

	wc.lpfnWndProc   = Input_WndProc;						
	wc.hInstance     = hInstance;						
	wc.hIcon	     = (HICON)LoadImage(NULL, _T("IconInput.ico"), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	wc.hCursor	     = LoadCursor(NULL, IDC_IBEAM);		
	wc.hbrBackground = CreateSolidBrush(INPUT_BACKGROUND);
	wc.lpszClassName = szClassInput;					
	
	if (!RegisterClass(&wc)) {
		MessageBox(NULL, _T("���������� ���������������� ����� ���� �����!"), _T("������"), MB_ICONERROR);
		return 0;
	} // if

	/****************************************************************************/
	ShowWindow(hMainWnd, SW_SHOWNORMAL);    // �������� ������� ���� ����������
									   
	while (GetMessage(&msg, NULL, 0, 0)) {  // ���� ��������� ���������
		TranslateMessage(&msg);				// ��������� ����� ��������� �� ����������
		DispatchMessage(&msg);
	} // while

	return 0;
} // WinMain
