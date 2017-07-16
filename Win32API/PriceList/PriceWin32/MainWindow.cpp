#include "Includes.h"
#include "MainWindow.h"
#include "InputWindow.h"
#include "SortWindow.h"			// ����� ����������
#include "FieldsOutWindow.h"	// ����� ������ �����
#include "Price.h"

extern HINSTANCE hAppInstance;   // ���������� ���������� ����������
extern TCHAR szTitleMain[];
extern TCHAR szClassInput[];     // �����     ���� �����
extern TCHAR szTitleInput[];     // ��������� ���� �����
extern TCHAR szClassSort[];		 // �����     ���� ��� ������ ����������
extern TCHAR szTitleSort[];		 // ��������� ���� ��� ������ ����������
extern TCHAR szClassFieldsOut[]; // �����     ���� ������ ���� ��� ������
extern TCHAR szTitleFieldsOut[]; // ��������� ���� ������ ���� ��� ������
extern UINT uStatus;             // ����� ����������, ���� SortWindow.cpp 

HWND hInput;        // ���� ����� ������ � ������
HWND hEdit;         // ���� �������������� ������ � ������
HWND hSort;			// ���� ������ ����������
HWND hFieldsOut;	// ���� ������ ����� ��� ������

// ���������� � ������� ��� �������� ���� ����������
static HDC hDC;							   // ����� ��������� ����������
static HFONT hFont, hFontList, hOldFont;   // ����� ��� ������
static LOGFONT lf;						   // ��������� ��� �������� ������

HWND hStLstGoods;
HWND hLstGoods;            // ������ �����     - ������
Price price;	           // ��������� ������ - ����� ��� �������������� ������
list<Price> List;          // ������ �������   - ���������
list<Price>::iterator it;  // ���������� �������� ��� ����� � ������� ������
fstream fs;                             // ����� �����/������ ��� �������� ����������
TCHAR *szFileName = _T("Goods.dat");    // ��� ������ �����/������
TCHAR *szFileNameCombo = _T("��������.txt");  // ��� ������ �����/������ ��� ���������� ����������

INT  nResult;              // ����� ������� ������ � ������ ����� listbox
InputMode bInputMode;      

// ���������� ����� ��� ���������� ������������ �������� 
BOOL bViewShop, bViewGoods, bViewCost;

HWND hStBar;   // ������ ��������� ���������

// ������� ������� - ��������� ���������, ���������� �����
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
		HANDLE_MSG(hWnd, WM_CREATE,			OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND,		OnCommand);
		HANDLE_MSG(hWnd, WM_SIZE,			OnSize);
		HANDLE_MSG(hWnd, WM_GETMINMAXINFO,  OnGetMinMaxInfo);
		HANDLE_MSG(hWnd, WM_PAINT,			OnPaint);
		HANDLE_MSG(hWnd, WM_CLOSE,			OnClose);
		HANDLE_MSG(hWnd, WM_DESTROY,		OnDestroy);
		HANDLE_MSG(hWnd, WM_CTLCOLORSTATIC, OnCtlColorStatic);
		HANDLE_MSG(hWnd, WM_MENUSELECT,     OnMenuSelect);
	
		// ��������� ��������� ��� ������� �� ������������� ��������� � ����� ����
		default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	} // switch

	return 0;
} // WndProc


HMENU hMainMenu;       // ������� ����
HMENU hGoodsMenu;      // ���������� ���� "�����"
HMENU hSettingsMenu;   // ���������� ���� "���������"

// ���������� ��������� WM_CREATE - ���������� ������� "��� ��������" 
// ������ ����
BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
	// ���� ������ ������ ����������� � �������� ������ !!!
	fs.open(szFileName, ios::in | ios::out | ios::binary);
	if (!fs) {
		TCHAR *szBuf = new TCHAR[100];
		_stprintf(szBuf, _T("���� %s �� ������ ��� �� ��������.\n��������� ���������"), szFileName);
		MessageBox(hWnd, szBuf, szTitleMain, MB_OK | MB_ICONERROR);
		delete[] szBuf;
		exit(0);
	} // if

	ZeroMemory(&lf, sizeof(LOGFONT));
	_tcscpy(lf.lfFaceName, _T("Book Antiqua"));
	lf.lfHeight = 28;
	hFont		= CreateFontIndirect(&lf);
	
	ZeroMemory(&lf, sizeof(LOGFONT));
	_tcscpy(lf.lfFaceName, _T("Courier"));
	lf.lfHeight = -14;
	hFontList   = CreateFontIndirect(&lf);

	// �������� ����
	hMainMenu     = CreateMenu();
	hGoodsMenu    = CreatePopupMenu();
	hSettingsMenu = CreatePopupMenu();

	AppendMenu(hMainMenu, MF_STRING | MF_POPUP, (UINT_PTR)hGoodsMenu, _T("&�����"));
	AppendMenu(hGoodsMenu, MF_STRING, IDC_MAIN_NEW, _T("&�����..."));
	AppendMenu(hGoodsMenu, MF_STRING, IDC_MAIN_DEL, _T("&�������"));
	AppendMenu(hGoodsMenu, MF_SEPARATOR, NULL, _T(""));
	AppendMenu(hGoodsMenu, MF_STRING, IDC_MAIN_QUIT, _T("��&���"));

	AppendMenu(hMainMenu, MF_STRING | MF_POPUP, (UINT_PTR)hSettingsMenu, _T("&���������"));
	AppendMenu(hSettingsMenu, MF_STRING, IDC_MAIN_SETSORT, _T("&����������..."));
	AppendMenu(hSettingsMenu, MF_STRING, IDC_MAIN_SETVIEW, _T("������&���..."));

	SetMenu(hWnd, hMainMenu);

	// �������� ������ ���������
	hStBar = CreateStatusWindow(WS_CHILD | WS_VISIBLE, _T("������"), hWnd, IDC_MAIN_STBAR);

	// �������� ������ ��������� �� ��� ������
	// ������ ��������� ������ ����� ��������
	int pParts[3] = {360, 450, lpCreateStruct->cx };
	SendMessage(hStBar, SB_SETPARTS, (WPARAM)3, (LPARAM)pParts);
	SendMessage(hStBar, SB_SETTEXT, 1, (LPARAM)_T("�������: 7"));   // ������ ������ � ������ 1
	SendMessage(hStBar, SB_SETTEXT, 2, (LPARAM)_T("���������: 15"));   // ������ ������ � ������ 2

	// �������� ������ �������
	INT xPos = 15;
	INT yPos = 10;
	// ������ �������
	hStLstGoods = CreateWindow(_T("static"), _T("������ �������"), WS_CHILD | WS_VISIBLE,
		xPos + 190, yPos, 200, 25, hWnd, NULL, lpCreateStruct->hInstance, NULL);
	yPos += 30;
	hLstGoods = CreateWindow(_T("listbox"), NULL,  LBS_NOTIFY | WS_VSCROLL | WS_BORDER | WS_CHILD | WS_VISIBLE,
		xPos, yPos, 590, 400, hWnd, (HMENU)IDC_MAIN_LISTGDS, lpCreateStruct->hInstance, NULL);
	SendMessage(hLstGoods, WM_SETFONT, WPARAM(hFontList), NULL);

	// ���������� ��� �������
	bViewShop = bViewGoods = bViewCost = TRUE;

	// �������� ������ �� ������ �����/������ � ��������� � � ������
	LoadFile();

	return TRUE;
} // OnCreate


// ��������� ��������� WM_COMMAND - ��� ���������� �� ��������� ����������
// � ��������� - �� ������
void OnCommand(HWND hWnd, INT id, HWND hWndCtl, UINT codeNotify)
{
	INT i;  // ����� ��������� ������ � ������

	switch (id) {

	case IDC_MAIN_NEW:
		if (!hInput) {
			hInput = CreateWindow(szClassInput, szTitleInput,
				WS_OVERLAPPED | WS_CAPTION | WS_DLGFRAME | WS_SYSMENU,
				150, 150, INPUT_WIDTH, INPUT_HEIGHT, hWnd, NULL, hAppInstance, NULL);
		} // if

		// ����� ���������� ����� ������ � ���� ������
		bInputMode = MODE_APPEND;  
		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("���� ������"));
		ShowWindow(hInput, SW_SHOWNORMAL);
		break;

		// ��������� �������� ������ �� ������
	case IDC_MAIN_LISTGDS:
		if (codeNotify == LBN_DBLCLK) {
			// �������� ������� ������� �� ������ - �������� ������������ �� �����
			// �.�. ������� ��������� ������ �� ������ �� ���������� ������
			nResult = (INT)SendMessage(hLstGoods, LB_GETCURSEL, NULL, NULL);
			i = 0;
			for (it = List.begin(); it != List.end(); ++it, ++i) {
				if (i == nResult) {
					price = *it;  // ������������� ������������
					if (!hEdit) {
						hEdit = CreateWindow(szClassInput, _T("�������������� ������"),
							WS_OVERLAPPED | WS_CAPTION | WS_DLGFRAME | WS_SYSMENU,
							150, 150, INPUT_WIDTH, INPUT_HEIGHT, hWnd, NULL, hAppInstance, NULL);
					} // if

					// ���������� ���� ����� ���� hInput �� ��������� ����� ������� price 
					// ����� �������������� ������������ ������
					bInputMode = MODE_EDIT;
					SetInput();
					SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("�������������� ������"));
					ShowWindow(hEdit, SW_SHOWNORMAL);
					break;
				} // if
			} // for it
		} // if
		break;

	// ������� �� ������ ��������� ������ - �������� ������
	case IDC_MAIN_DEL:
		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("������� ������"));
		nResult = (INT)SendMessage(hLstGoods, LB_GETCURSEL, NULL, NULL);
		if (nResult == LB_ERR) {
			MessageBox(hWnd, _T("����� ��� �������� �� ������!"), _T("������"), MB_OK | MB_ICONERROR);
			SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("������. ������ �� �������"));
			break;
		} // if

		// ������ �� ������������� �������� ������
		i = MessageBox(HWND_DESKTOP, _T("�� ����������� ������� ������ ������. "
			"��� �������� ���������� ��������\n\n�� �������?"), _T("������������� ��������"),
			MB_YESNO | MB_ICONQUESTION);
		if (i == IDNO) {
			SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("������. ������ �� �������"));
			break;
		} // if

		// ������� �� ������ ������ �� �� ������
		SendMessage(hLstGoods, LB_DELETESTRING, nResult, NULL);

		// ������� ����� ����� �� ���������� - ������
		i = 0;
		for (list<Price>::iterator it = List.begin(); it != List.end(); ++it, ++i) {
			if (i == nResult) {
				List.erase(it);
				// �������������� ���� ������ - �� ������ ������� �� ������������������
				// �� �������� ������� � ����������
				fs.close();
				WriteFile();

				// ��������� ����� ����
				fs.open(szFileName, ios::in | ios::out);
				break;
			} // if
		} // for it

		  // �������� � �������� ������� ������ � ��� �� �������
		SendMessage(hLstGoods, LB_SETCURSEL, nResult, NULL);
		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("������. ������ �������"));
		break;

		// ����������...
	case IDC_MAIN_SETSORT:
		if (!hSort) {
			hSort = CreateWindow(szClassSort, szTitleSort,
				WS_OVERLAPPED | WS_CAPTION | WS_DLGFRAME | WS_SYSMENU,
				150, 150, SORT_WIDTH, SORT_HEIGHT, hWnd, NULL, hAppInstance, NULL);
		} // if

		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("����� ������ ����������"));
		ShowWindow(hSort, SW_SHOWNORMAL);
		break;

		// ����� �����...
	case IDC_MAIN_SETVIEW:
		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("����� �������� ��� �����������"));
		if (!hFieldsOut) {
			hFieldsOut = CreateWindow(szClassFieldsOut, szTitleFieldsOut,
				WS_OVERLAPPED | WS_CAPTION | WS_DLGFRAME | WS_SYSMENU,
				150, 150, FIELDSOUT_WIDTH, FIELDSOUT_HEIGHT, hWnd, NULL, hAppInstance, NULL);
		} // if
		ShowWindow(hFieldsOut, SW_SHOWNORMAL);
		break;

	case IDC_MAIN_QUIT:   // ����� �� ����������
		// ���� ���� ��������� ���������� � ������� �������
		// ���������� �� ���������, �������� ���������� ������
		// ������� �������
		if (uStatus != 3) {
			i = MessageBox(HWND_DESKTOP, 
				_T("������� ������� � ������ �������.\n��������� � �����?"),
				_T("���������� ����� ������"), 
				MB_YESNO | MB_ICONQUESTION);
			if (i == IDYES) { // ������� ���� ������
				fs.close();   // � ��������� ����������
				WriteFile();  // ���������� �����
			} // if
		} // if
		PostQuitMessage(0);
		break;
	} // switch
} // OnCommand


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


// ���������� ��������� WM_PAINT - ���������� ������� "��� ���������" 
void OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;  // ��������� ��������� ����������
	RECT rect;       // ������������� - ��� �������� ��������� ������� ������� ���� 

	hDC = BeginPaint(hWnd, &ps);    // �������� ����� ��������� ����������
	GetClientRect(hWnd, &rect);     // �������� ���������� ������� ��� ���������

	EndPaint(hWnd, &ps);            // ���������� �������� ��� ���������� ������ �������
} // OnPaint


// ���������� ��������� WM_CLOSE - ���������� ������� "��� �������� ����" 
void OnClose(HWND hWnd)
{
	SelectFont(hDC, hOldFont);
	DeleteFont(hFont);
	DeleteFont(hFontList);

	DestroyWindow(hWnd);

	// ������� ���� ������
	fs.close();  
} // OnClose


// ���������� ��������� WM_DESTROY - ���������� ������� "��� ����������� ����" 
void OnDestroy(HWND hWnd)
{
	PostQuitMessage(0);
} // OnDestroy


// ��������� ���� ������������ ������������ ��������
// ��� - ��������� � ����� ������� ������� ����
HBRUSH OnCtlColorStatic(HWND, HDC hDC, HWND, INT)
{
	SetBkMode(hDC, TRANSPARENT);
	SelectFont(hDC, hFont);
	SetTextColor(hDC, RGB(0x41, 0x69, 0xE1));
	return CreateSolidBrush(BACKGROUND);
} // OnCtlColorStatic


// ��������� ������ ������� ���� - ����� ������ � ������ ���������
void OnMenuSelect(HWND hwnd, HMENU hmenu, int item, HMENU hmenuPopup, UINT flags)
{
	switch (item) {
	case IDC_MAIN_NEW:
		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("������� ����� ������"));
		break;
	case IDC_MAIN_DEL:
		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("������� ������ (� �.�. �� �����)"));
		break;
	case IDC_MAIN_QUIT:
		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("�����. ����� ������ ����������"));
		break;
	case IDC_MAIN_SETSORT:
		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("������ ������ ����������"));
		break;
	case IDC_MAIN_SETVIEW:
		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("������� ������������ �������"));
		break;
	default:
		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("������"));
		break;
	} // switch
} // OnMenuSelect


// �������� ����� ������ � ��������� - ������ � 
// ����������� ����� � listbox
void LoadFile()
{
	// �������� ����� ����� � �������
	fs.seekg(0, ios::end);
	UINT uRecords = (UINT) (fs.tellg()) / Price::LEN_RECORD;
	fs.seekg(0, ios::beg);
	
	Price temp;
	TCHAR *szBuf = new TCHAR[Price::LEN_RECORD];

	// ������ ���� � ������-��������� � � ������ �� ������
	for (UINT i = 0; i < uRecords; i++) {
		temp.Load(fs);
		List.push_back(temp);

		MakeOutStr(szBuf, temp);
		SendMessage(hLstGoods, LB_ADDSTRING, NULL, (LPARAM)szBuf);
	} // for

	delete[] szBuf;
} // LoadFile


// "����������" ���������� ����� ������ 
//  - ���� �� ����� ����� �� �������� � ������ ������
//  - ���� ������ ������ ���� ������!!!
// 1. �������� ������ �� ���������� ����
// 2. ������� �������� ����
// 3. ������������� ��������� ���� � ��������
void WriteFile()
{
	// ������������ ��� ���������� ����� - ������������.tmp
	TCHAR szTempFile[255];
	_tcscpy(szTempFile, szFileName);
	_tcscat(szTempFile, _T(".tmp"));

	// ������� ��������� ����
	fstream ftmp(szTempFile, ios::out);
	if (!ftmp) {
		MessageBox(HWND_DESKTOP, _T("���������� ��������� ��������!"), 
			_T("������"), MB_OK | MB_ICONERROR);
		return;
	} // if

	// ���� ������ �������� �� ������ (��� ������ ���������) � ������
	// ��������� �� ��������� ����
	for (list<Price>::iterator it = List.begin(); it != List.end(); ++it) {
		it->Save(ftmp);
	} // for it
	ftmp.close();

	// ������� �������� ���� �� ����� - DeleteFile(��������)
	DeleteFile(szFileName);
	// ������������� ���� - MoveFile(���������������, ��������)
	MoveFile(szTempFile, szFileName);
} // WriteFile


// ������������ ������ ��� ������ � ������ �������� ����
void MakeOutStr(TCHAR *szBuf, Price price) 
{
	TCHAR szTemp[50];
	_tcscpy(szBuf, _T(""));

	if (bViewShop)
		_stprintf(szTemp, _T("%-25s | "), price.getShop().c_str());
	else
		_tcscpy(szTemp, _T("                          | "));
	_tcscat(szBuf, szTemp);

	if (bViewGoods)
		_stprintf(szTemp, _T("%-32s | "), price.getGoods().c_str());
	else
		_tcscpy(szTemp, _T("                                 | "));
	_tcscat(szBuf, szTemp);

	if (bViewCost) {
		_stprintf(szTemp, _T("%10u"), price.getCost());
		_tcscat(szBuf, szTemp);
	} // if
} // MakeOutStr


// ����� �� ������ ������� � ������ ����� �������� ���� ����������
void ListToListbox() {
	TCHAR *szBuf = new TCHAR[Price::LEN_RECORD];

	SendMessage(hLstGoods, LB_RESETCONTENT, NULL, NULL);
	for (list<Price>::iterator it = List.begin(); it != List.end(); ++it) {
		MakeOutStr(szBuf, *it);
		SendMessage(hLstGoods, LB_ADDSTRING, NULL, (LPARAM)szBuf);
	} // for it

	delete[] szBuf;
} // ListToListbox