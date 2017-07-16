#include "Includes.h"      
#include "MainWindow.h"   
#include "FonBrushWindow.h"
#include "PenSettingsWindow.h"

HINSTANCE hAppInstance;                                     // ���������� ���������� ����������

TCHAR szClassMain[]  = _T("MainWindow");					// ����� �������� ����
TCHAR szTitleMain[]  = _T("���� | ��������� | ���������");	// ��������� �������� ����

TCHAR szClassFonBrush[] = _T("FonBrushWindow");				// ����� ���� ��������� ����� ���� � ����� �����
TCHAR szTitleFonBrush[] = _T("����� ����� �����");			// ��������� ���� ��������� ����� ���� � ����� �����

TCHAR szClassPenSettings[] = _T("PenWindow");				// ����� ���� ���������� ����
TCHAR szTitlePenSettings[] = _T("��������� ����");			// ��������� ���� ���������� ����

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, INT nCmdShow)
{
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
		20, 20, MAIN_WIDTH, MAIN_HEIGHT, HWND_DESKTOP, NULL, hInstance, NULL);

	// �������� �� �������� ��������
	if (!hMainWnd) {
		MessageBox(NULL, _T("���������� ������� ������� ����!"), _T("������"), MB_ICONERROR);
		return 0;
	} // if

	/***********************���� �������� ���� � �����***************************/
	ZeroMemory(&wc, sizeof(WNDCLASS));				

	wc.lpfnWndProc   = FonBrush_WndProc;
	wc.hInstance     = hInstance;						
	wc.hIcon	     = (HICON)LoadImage(NULL, _T("IconFonBrush.ico"), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	wc.hCursor	     = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = CreateSolidBrush(FONBRUSH_BACKGROUND);
	wc.lpszClassName = szClassFonBrush;
	
	if (!RegisterClass(&wc)) {
		MessageBox(NULL, _T("���������� ���������������� ����� ��������� ����!"), _T("������"), MB_ICONERROR);
		return 0;
	} // if

	/***************************���� ��������� ����******************************/
	ZeroMemory(&wc, sizeof(WNDCLASS));

	wc.lpfnWndProc   = PenSettings_WndProc;
	wc.hInstance     = hInstance;
	wc.hIcon         = (HICON)LoadImage(NULL, _T("IconPenSettings.ico"), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = CreateSolidBrush(PENSETTINGS_BACKGROUND);
	wc.lpszClassName = szClassPenSettings;

	if (!RegisterClass(&wc)) {
		MessageBox(NULL, _T("���������� ���������������� ����� ��������� ����!"), _T("������"), MB_ICONERROR);
		return 0;
	} // if

	/****************************************************************************/
	MSG msg;								// ��������� 
	ShowWindow(hMainWnd, SW_SHOWNORMAL);    // �������� ������� ���� ����������
									   
	while (GetMessage(&msg, NULL, 0, 0)) {  // ���� ��������� ���������
		TranslateMessage(&msg);				// ��������� ����� ��������� �� ����������
		DispatchMessage(&msg);
	} // while

	return 0;
} // WinMain
