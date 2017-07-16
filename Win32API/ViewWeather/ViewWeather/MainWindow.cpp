#include "Includes.h"
#include "MainWindow.h"
#include "WeatherInfo.h"
#include "WeatherLoad.h"

// ���������� � ������� ��� �������� ���� ����������
static HDC hdc; // ����� ��������� ����������                         

// ���� ���� � ������� "����", "���"
HMENU hMainMenu, hFileMenu, hViewMenu;

// ������ ������ ���� � �������� - ��� ������������ ����
static INT32 nMenuHeight;   

// ������� ListView
HWND hLstWeather;

// ������ ������ ��� ��������� - ������ �������� ������ Student
WeatherLoad weather;

// ����������� ������ �������� �����
OPENFILENAME ofn;

LOGFONT lf;
COLORREF colfont;
CHOOSEFONT cfont;
HFONT font;
HANDLE hOldFont;

CHOOSECOLOR ccol;
COLORREF clf;
COLORREF clfusers[16];

// ������� ������� - ��������� ���������, ���������� �����
// hwnd	  - ���������� ����
// msg	  - �������� ��� ���������
// wParam - ������ ����� ���������� ���������
// lParam - ������ ����� ���������� ���������
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
		HANDLE_MSG(hwnd, WM_CREATE, OnCreate);  // �������� ����
		HANDLE_MSG(hwnd, WM_SIZE, OnSize);      // ��������� ������� ������
		HANDLE_MSG(hwnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hwnd, WM_CLOSE, OnClose);
		HANDLE_MSG(hwnd, WM_DESTROY, OnDestroy);
		HANDLE_MSG(hwnd, WM_GETMINMAXINFO, OnGetMinMaxInfo);
		HANDLE_MSG(hwnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hwnd, WM_CTLCOLORSTATIC, OnCtlColorStatic);
	
		// ��������� ��������� ��� ������� �� ������������� ��������� � ����� ����
		default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	} // switch

	return 0;
} // WndProc


// ���������� ��������� WM_CREATE - ���������� ������� "��� ��������" 
// ������ ����
BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
	RECT rect;
	GetClientRect(hwnd, &rect);

	#pragma region �������� ����
	hMainMenu = CreateMenu();
	hFileMenu = CreatePopupMenu();
	hViewMenu = CreatePopupMenu();

	AppendMenu(hMainMenu, MF_STRING | MF_POPUP, (UINT_PTR)hFileMenu, _T("&����"));
	AppendMenu(hFileMenu, MF_STRING, IDC_OPEN, _T("&�������..."));
	AppendMenu(hFileMenu, MF_SEPARATOR, NULL, _T(""));
	AppendMenu(hFileMenu, MF_STRING, IDC_QUIT, _T("��&���"));

	AppendMenu(hMainMenu, MF_STRING | MF_POPUP, (UINT_PTR)hViewMenu, _T("&���"));
	AppendMenu(hViewMenu, MF_STRING, IDC_FONT, _T("��&��� ������..."));
	AppendMenu(hViewMenu, MF_STRING, IDC_COLOR, _T("�&��� ����..."));
	SetMenu(hwnd, hMainMenu);

	// �������� ������ ������ ���� � ��������
	nMenuHeight = GetSystemMetrics(SM_CYMENU);
	#pragma endregion

	#pragma region �������� �������� ListView
	hLstWeather = CreateWindowEx(0, WC_LISTVIEW, NULL,
		WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_REPORT | LVS_ALIGNLEFT,
		rect.left + 10, rect.top + 10, rect.right - 20, rect.bottom - nMenuHeight, 
		hwnd, (HMENU)IDC_LISTVIEW, lpCreateStruct->hInstance, NULL);
	// SendMessage(hLstStudents, WM_SETFONT, WPARAM(hFontList), NULL);

	// ���������� ��������
	LV_COLUMN lvCol;
	ZeroMemory(&lvCol, sizeof(LV_COLUMN));

	// ���������� 0-�� ������� - ������� � ��������
	lvCol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvCol.fmt  = LVCFMT_LEFT;
	lvCol.cx   = (rect.right - rect.left - 20) / 5;

	lvCol.iSubItem = 0;
	lvCol.pszText  = _T("�����");
	ListView_InsertColumn(hLstWeather, 0, &lvCol);

	// ������ ��������� �����������
	lvCol.iSubItem = 1;
	lvCol.pszText  = _T("����������� �����");
	ListView_InsertColumn(hLstWeather, 1, &lvCol);

	lvCol.iSubItem = 2;
	lvCol.pszText  = _T("�������� �����, �/�");
	ListView_InsertColumn(hLstWeather, 2, &lvCol);

	lvCol.iSubItem = 3;
	lvCol.pszText  = _T("����. ����. ������.");
	ListView_InsertColumn(hLstWeather, 3, &lvCol);

	lvCol.iSubItem = 4;
	lvCol.pszText  = _T("���. ���. ������.");
	ListView_InsertColumn(hLstWeather, 4, &lvCol);

	ListView_SetExtendedListViewStyle(hLstWeather,
		ListView_GetExtendedListViewStyle(hLstWeather) | LVS_EX_FULLROWSELECT);
	#pragma endregion
	
	// �������� ������ �� �����
	weather = WeatherLoad(_T("�����������.txt"));
	weather.LoadFromFile();

	// ����� ������� ��������� � ������� ListView
	weather.ListView(hLstWeather);

	#pragma region �������� ������� �������� �����
	static TCHAR fileName[256];
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = sizeof(fileName);
	ofn.lpstrFilter = _T("��������� ����� (*.txt)\0*.txt\0CSV-����� (*.csv)\0*.csv\0��� ����� (*.*)\0*.*\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrInitialDir = _T(".");  // ������� �������/������� �����
	ofn.lpstrDefExt = _T("txt");
	#pragma endregion

	#pragma region �������� ������� ������ ������
	colfont = RGB(0, 0, 0);
	lf.lfHeight = 13;
	lf.lfWidth = 13;
	lf.lfEscapement = 0;
	lf.lfOrientation = 0;
	lf.lfItalic = 0;
	lf.lfUnderline = 0;
	lf.lfStrikeOut = 0;
	lf.lfWeight = FW_NORMAL;
	lf.lfCharSet = RUSSIAN_CHARSET;
	_tcscpy(lf.lfFaceName, _T("Calibri"));
	cfont.lStructSize = sizeof(CHOOSEFONT);
	cfont.Flags = CF_SCREENFONTS | CF_EFFECTS | CF_INITTOLOGFONTSTRUCT;
	#pragma endregion

	#pragma region �������� ������� ������ �����
	ccol.lStructSize = sizeof(CHOOSECOLOR);
	ccol.Flags = CC_RGBINIT;
	ccol.lpCustColors = clfusers;
	clf = RGB(255, 255, 255);
	#pragma endregion

	return TRUE;
} // OnCreate


// ���������� ��������� WM_SIZE - ���������� ������� "��� ��������� �������" 
// ������ ����
void OnSize(HWND hwnd, UINT state, int cx, int cy)
{
	RECT rect;       // ������������� - ��� �������� ��������� ������� ������� ���� 
	INT32 nWidth;    // ������ ������� �������� ListView

	GetClientRect(hwnd, &rect);         // ������ ������� ���� ��� �����������

	// ����� ������ ListView
	MoveWindow(hLstWeather, 10, 10, rect.right - 20, rect.bottom - nMenuHeight - 10, TRUE);

	// ������� ��������� ListView ��� ��������� ������ ��������
	nWidth = (rect.right - 20) / 5;
	for (size_t i = 0; i < 5; i++)
		ListView_SetColumnWidth(hLstWeather, i, nWidth);

	InvalidateRect(hwnd, &rect, TRUE);  // �������� ������� ���������������� => ����������� WM_PAINT
} // OnSize


// ���������� ��������� WM_PAINT - ���������� ������� "��� ���������" 
void OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;  // ��������� ��������� ����������
	RECT rect;       // ������������� - ��� �������� ��������� ������� ������� ���� 

	hdc = BeginPaint(hwnd, &ps);    // �������� ����� ��������� ����������
	
	font = CreateFontIndirect(&lf);
	hOldFont = SelectObject(hdc, font);
	SetTextColor(hdc, colfont);
	TextOut(hdc, 20, 20, lf.lfFaceName, _tcslen(lf.lfFaceName));
	SelectObject(hdc, hOldFont);
	DeleteObject(font);

	GetClientRect(hwnd, &rect);     // �������� ���������� ������� ��� ���������

	EndPaint(hwnd, &ps);            // ���������� �������� ��� ���������� ������ �������
} // OnPaint


// ���������� ��������� WM_CLOSE - ���������� ������� "��� �������� ����" 
void OnClose(HWND hwnd)
{
	DestroyWindow(hwnd);
} // OnClose


// ���������� ��������� WM_DESTROY - ���������� ������� "��� ����������� ����" 
void OnDestroy(HWND hwnd)
{
	PostQuitMessage(0);
} // OnDestroy


// ����������� ������������ ������� �������� ���� ����������
// !! �������� ������ � OnSize !!
void OnGetMinMaxInfo(HWND hwnd, LPMINMAXINFO lpMinMaxInfo)
{
	lpMinMaxInfo->ptMinTrackSize = { 480, 240 };
} // OnGetMinMaxInfo


// ��������� ��������� WM_COMMAND - ��� ���������� �� ��������� ����������
// � ��������� - �� ������
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	BOOL bResult;

	switch (id) {
		// ����� ����� ������ ��� ������ ������������ ������� �
		// ����� ������ �� ����� �����
	case IDC_OPEN:
		ofn.Flags = OFN_EXPLORER;
		bResult = GetOpenFileName(&ofn);
		if (!bResult) break;

		weather.SetFileName(wstring(ofn.lpstrFile));
		weather.LoadFromFile();
		weather.ListView(hLstWeather);
		break;

		// ����� ������ ��� ������ ������ � ListView � ��������� ������
	case IDC_FONT:
		cfont.lpLogFont = &lf;
		cfont.rgbColors = colfont;
		if (ChooseFont(&cfont)) {
			lf = *cfont.lpLogFont;
			colfont = cfont.rgbColors;
			ListView_SetTextColor(hLstWeather, colfont);
			SendMessage(hLstWeather, WM_SETFONT, (WPARAM)CreateFontIndirect(&lf), TRUE);
		} // if
		break;

		// ����� ����� ��� ������ ������ � ListtView � ��������� �����
	case IDC_COLOR:
		ccol.rgbResult = clf;
		if (ChooseColor(&ccol)) {
			clf = ccol.rgbResult;
			ListView_SetTextBkColor(hLstWeather, clf);
			RECT rt;
			GetClientRect(hLstWeather, &rt);
			InvalidateRect(hLstWeather, &rt, TRUE);
		} // if
		break;

	case IDC_QUIT:
		PostQuitMessage(0);
		break;
	} // switch
} // OnCommand


// ��������� ���� ������������ ������������ ��������
// ��� - ��������� � ����� ������� ������� ����
HBRUSH OnCtlColorStatic(HWND, HDC hdc, HWND, int)
{
	SetBkMode(hdc, TRANSPARENT);
	return CreateSolidBrush(BACKGROUND);
} // OnCtlColorStatic