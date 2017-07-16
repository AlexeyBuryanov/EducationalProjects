#include "Includes.h"
#include "MainWindow.h"
#include "FonBrushWindow.h" 
#include "PenSettingsWindow.h"

extern HINSTANCE hAppInstance;     // ���������� ���������� ����������
extern TCHAR szTitleMain[];        // ��������� �������� ����
extern TCHAR szClassFonBrush[];    // �����     ���� �������� ���� � �����
extern TCHAR szTitleFonBrush[];    // ��������� ���� �������� ���� � �����
extern TCHAR szClassPenSettings[]; // �����     ���� �������� ����
extern TCHAR szTitlePenSettings[]; // ��������� ���� �������� ����

// ���������� � ������� ��� �������� ���� ����������
static HDC hDC;							   // ����� ��������� ����������
static HFONT hOldFont;					   // ����� ��� ������
static LOGFONT lf;						   // ��������� ��� �������� ������

// ���������� ��� ��������� ������
static Figures figure; // ��� ������
UINT  uPenWidth;       // ������� ����
DWORD rgbPenColor;     // ���� ����
DWORD rgbBrushColor;   // ���� �����

// �������� ���� ����� ����������
HWND hWndPenSet;       // ��������� ���� ��� ������  
HWND hWndSetColor;     // �������� ����� ��� ������
HWND hWndSetColor2;    // �������� ����� ���� ������� ������� ����
bool bMode; // ����� ������ ���� ����������: true - ��� ������, false - ��� ������� �������

// ������� ������� - ��������� ���������, ���������� �����
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_SIZE, OnSize);
		HANDLE_MSG(hWnd, WM_GETMINMAXINFO, OnGetMinMaxInfo);
		HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hWnd, WM_CLOSE, OnClose);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
	
		// ��������� ��������� ��� ������� �� ������������� ��������� � ����� ����
		default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	} // switch

	return 0;
} // WndProc

HMENU hMainMenu;       // ������� ����
HMENU hFigureMenu;     // ���������� ���� "������"
HMENU hSettingsMenu;   // ���������� ���� "���������"

// ���������� ��������� WM_CREATE - ���������� ������� "��� ��������" 
// ������ ����
BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
	// �� �������� ������� ������, ��������� ��������� ��������
	// ���������� ���� � ������ ��� ���� ������, ���� 
	figure = FIG_NONE;
	rgbPenColor = RGB(0, 0, 0);
	uPenWidth = 2;
	rgbBrushColor = RGB(0xFF, 0x7F, 0x24);

	// �������� ����
	hMainMenu     = CreateMenu();
	hFigureMenu   = CreatePopupMenu();
	hSettingsMenu = CreatePopupMenu();

	AppendMenu(hMainMenu, MF_STRING | MF_POPUP, (UINT)hFigureMenu, _T("&������"));
	AppendMenu(hFigureMenu, MF_STRING, IDC_CIRCLE, _T("&����"));
	AppendMenu(hFigureMenu, MF_STRING, IDC_TRIANGLE, _T("���&��������"));
	AppendMenu(hFigureMenu, MF_STRING, IDC_RECTANGLE, _T("&�������������"));
	AppendMenu(hFigureMenu, MF_STRING, IDC_TRAPEZE, _T("&��������"));
	AppendMenu(hFigureMenu, MF_SEPARATOR, NULL, _T(""));
	AppendMenu(hFigureMenu, MF_STRING, IDC_QUIT, _T("��&���"));

	AppendMenu(hMainMenu, MF_STRING | MF_POPUP, (UINT)hSettingsMenu, _T("&���������"));
	AppendMenu(hSettingsMenu, MF_STRING, IDC_SETTINGSPEN, _T("&��������� ����"));
	AppendMenu(hSettingsMenu, MF_STRING, IDC_COLORBRSH, _T("���� &�����"));
	AppendMenu(hSettingsMenu, MF_STRING, IDC_COLORFON, _T("���� &����"));

	SetMenu(hWnd, hMainMenu);

	return TRUE;
} // OnCreate


// ��������� ��������� WM_COMMAND - ��� ���������� �� ��������� ����������
// � ��������� - �� ������
void OnCommand(HWND hWnd, INT id, HWND hWndCtl, UINT codeNotify)
{
	switch (id) {

		// ������ ����
	case IDC_CIRCLE:
		figure = FIG_CIRCLE;
		break;

		// ������ �����������
	case IDC_TRIANGLE:
		figure = FIG_TRIANGLE;
		break;

		// ������ �������������
	case IDC_RECTANGLE:
		figure = FIG_RECT;
		break;

		// ������ �������������� ��������
	case IDC_TRAPEZE:
		figure = FIG_TRAPEZE;
		break;

		// ��������� ����
	case IDC_SETTINGSPEN:
		if (!hWndPenSet) {
			hWndPenSet = CreateWindow(szClassPenSettings, szTitlePenSettings,
				WS_OVERLAPPED | WS_CAPTION | WS_BORDER | WS_DLGFRAME | WS_SYSMENU,
				150, 150, PENSETTINGS_WIDTH, PENSETTINGS_HEIGHT, hWnd, NULL, hAppInstance, NULL);
		} // if
		ShowWindow(hWndPenSet, SW_SHOWNORMAL);
		break;

		// ��������� ����� ����� ��� �����
	case IDC_COLORBRSH:
		if (!hWndSetColor) {
			hWndSetColor = CreateWindow(szClassFonBrush, szTitleFonBrush,
				WS_OVERLAPPED | WS_CAPTION | WS_BORDER | WS_DLGFRAME | WS_SYSMENU,
				150, 150, FONBRUSH_WIDTH, FONBRUSH_HEIGHT, hWnd, NULL, hAppInstance, NULL);
		} // if
		bMode = true;
		ShowWindow(hWndSetColor, SW_SHOWNORMAL);
		break;

		// ��������� ���� ������� �������
	case IDC_COLORFON:
		if (!hWndSetColor2) {
			hWndSetColor2 = CreateWindow(szClassFonBrush, _T("����� ����� ����"),
				WS_OVERLAPPED | WS_CAPTION | WS_BORDER | WS_DLGFRAME | WS_SYSMENU,
				150, 150, FONBRUSH_WIDTH, FONBRUSH_HEIGHT, hWnd, NULL, hAppInstance, NULL);
		} // if
		bMode = false;
		ShowWindow(hWndSetColor2, SW_SHOWNORMAL);
		break;

	case IDC_QUIT:   // ����� �� ����������
		PostQuitMessage(0);
		break;

	} // switch
	InvalidateRect(hWnd, NULL, TRUE);
} // OnCommand


// ���������� ��������� WM_PAINT - ���������� ������� "��� ���������" 
void OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;  // ��������� ��������� ����������
	RECT rect;       // ������������� - ��� �������� ��������� ������� ������� ���� 

	hDC = BeginPaint(hWnd, &ps);    // �������� ����� ��������� ����������
	GetClientRect(hWnd, &rect);     // �������� ���������� ������� ��� ���������

	// ������� ���� � �����, ��������� ������ � �������� �����
	HPEN hPen = CreatePen(PS_SOLID, uPenWidth, rgbPenColor);
	HPEN hOldPen = SelectPen(hDC, hPen);

	HBRUSH hBrush = CreateSolidBrush(rgbBrushColor);
	HBRUSH hOldBrush = SelectBrush(hDC, hBrush);

	// ������� ����� ��� ������������ � ��������
	const UINT N_POINTS1 = 3, N_POINTS2 = 4;
	POINT apt1[N_POINTS1] = { 
		{ rect.left + 100, rect.left + 270 },
		{ rect.top + 320, rect.top + 60 },
		{ rect.right - 100, rect.left + 270 } 
	};

	POINT apt2[N_POINTS2] = { 
		{ rect.left + 100, rect.left + 270 }, 
		{ rect.top + 180, rect.top + 90 },
		{ rect.top + 450, rect.top + 90 },
		{ rect.right - 100, rect.left + 270 } 
	};

	switch (figure)
	{
	case FIG_CIRCLE:
		Ellipse(hDC, rect.left + 180, rect.top + 100, rect.right - 180, rect.bottom - 100);
		break;
	case FIG_TRIANGLE:
		Polygon(hDC, apt1, N_POINTS1);
		break;
	case FIG_RECT:
		Rectangle(hDC, rect.left + 120, rect.top + 120, rect.right - 120, rect.bottom - 120);
		break;
	case FIG_TRAPEZE:
		Polygon(hDC, apt2, N_POINTS2);
		break;
	} // switch

	// ����������� ������� - ���� � �����
	SelectPen(hDC, hOldPen);
	DeletePen(hPen);
	SelectBrush(hDC, hOldBrush);
	DeleteBrush(hBrush);
	EndPaint(hWnd, &ps);            // ���������� �������� ��� ���������� ������ �������
} // OnPaint


// ���������� ��������� WM_SIZE - ���������� ������� "��� ��������� �������" 
// ������ ����
void OnSize(HWND hWnd, UINT state, INT cx, INT cy)
{
	RECT rect;       // ������������� - ��� �������� ��������� ������� ������� ���� 

	GetClientRect(hWnd, &rect);         // ������ ������� ���� ��� �����������
	InvalidateRect(hWnd, &rect, TRUE);  // �������� ������� ���������������� => ����������� WM_PAINT
} // OnSize


// ����������� ������������ ������� �������� ���� ����������
// !! �������� ������ � OnSize !!
void OnGetMinMaxInfo(HWND hWnd, LPMINMAXINFO lpMinMaxInfo)
{
	lpMinMaxInfo->ptMinTrackSize = { MAIN_WIDTH, MAIN_HEIGHT };
	lpMinMaxInfo->ptMaxTrackSize = { MAIN_WIDTH, MAIN_HEIGHT };
} // OnGetMinMaxInfo


// ���������� ��������� WM_CLOSE - ���������� ������� "��� �������� ����" 
void OnClose(HWND hWnd)
{
	SelectFont(hDC, hOldFont);

	DestroyWindow(hWnd); 
} // OnClose


// ���������� ��������� WM_DESTROY - ���������� ������� "��� ����������� ����" 
void OnDestroy(HWND hWnd)
{
	PostQuitMessage(0);
} // OnDestroy


