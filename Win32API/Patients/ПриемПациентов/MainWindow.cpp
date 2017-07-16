#include "Includes.h"
#include "MainWindow.h"
#include "InputWindow.h" 
#include "Patient.h"

extern HINSTANCE hAppInstance;   // ���������� ���������� ����������
extern TCHAR szClassInput[];     // ����� ���� �����
extern TCHAR szTitleInput[];     // ��������� ���� �����
extern TCHAR szTitleMain[];

// ���������� � ������� ��� �������� ���� ����������
static HDC hDC;							   // ����� ��������� ����������
static HFONT hFont, hFontList, hOldFont;   // ����� ��� ������
static LOGFONT lf;						   // ��������� ��� �������� ������

HWND hBtnInput;     // ������ "����� �������"
HWND hBtnOut;       // ������ "��������"
HWND hBtnQuit;      // ������ "�����"

HWND hLstPatients;  // ������ ����� - ��������
INT  nResult;       // ����� ������� ����� � ������ ����� listbox

HWND hInput;        // ���� ����� ������ � ��������

InputMode bInputMode;         

list<Patient> List;   // ������ ��������� - ���������
list<Patient>::iterator it;  // ���������� �������� ��� ����� � ������� ������

fstream fs;           // ����� �����/������ ��� �������� ����������
TCHAR *szFileName = _T("patients.dat"); // ��� ������ �����/������

Patient patient;	   // ��������� �������� - ����� ��� �������������� ��������

// ������� ������� - ��������� ���������, ���������� �����
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_SIZE, OnSize);
		HANDLE_MSG(hWnd, WM_GETMINMAXINFO, OnGetMinMaxInfo);
		HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hWnd, WM_LBUTTONDOWN, OnLButtonDown);
		HANDLE_MSG(hWnd, WM_RBUTTONDOWN, OnRButtonDown);
		HANDLE_MSG(hWnd, WM_CLOSE, OnClose);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
	
		// ��������� ��������� ��� ������� �� ������������� ��������� � ����� ����
		default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	} // switch

	return 0;
} // WndProc


// ���������� ��������� WM_CREATE - ���������� ������� "��� ��������" 
// ������ ����
BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
	//patient = new Patient();
	fs.open(szFileName, ios::in | ios::out /* | ios::app */);
	if (!fs) {
		TCHAR *szBuf = new TCHAR[100];
		_stprintf(szBuf, _T("���� %s �� ������ ��� �� ��������.\n��������� ���������"), szFileName);
		MessageBox(hWnd, szBuf, szTitleMain, MB_OK | MB_ICONERROR);
		delete[] szBuf;
		exit(0);
	} // if

	ZeroMemory(&lf, sizeof(LOGFONT));
	_tcscpy(lf.lfFaceName, _T("Book Antiqua"));
	lf.lfHeight = 23;
	hFont		= CreateFontIndirect(&lf);
	ZeroMemory(&lf, sizeof(LOGFONT));
	_tcscpy(lf.lfFaceName, _T("Gungsuh"));
	lf.lfHeight = 20;
	hFontList   = CreateFontIndirect(&lf);

	// ������ ���������
	hLstPatients = CreateWindow(_T("listbox"), NULL,  LBS_NOTIFY | WS_VSCROLL | WS_BORDER | WS_CHILD | WS_VISIBLE,
		190, 15, 420, 430, hWnd, (HMENU)IDC_LISTPT, lpCreateStruct->hInstance, NULL);
	SendMessage(hLstPatients, WM_SETFONT, WPARAM(hFontList), NULL);
	
	hBtnInput = CreateWindow(_T("button"), _T("����� �������"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		15, 15, 160, 25, hWnd, (HMENU)IDC_BTNNEW, lpCreateStruct->hInstance, NULL);
	SendMessage(hBtnInput, WM_SETFONT, WPARAM(hFont), NULL);

	hBtnOut = CreateWindow(_T("button"), _T("��������"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		15, 65, 160, 25, hWnd, (HMENU)IDC_BTNOUT, lpCreateStruct->hInstance, NULL);
	SendMessage(hBtnOut, WM_SETFONT, WPARAM(hFont), NULL);


	hBtnQuit = CreateWindow(_T("button"), _T("�����"), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		15, 410, 160, 25, hWnd, (HMENU)IDC_QUIT, lpCreateStruct->hInstance, NULL);
	SendMessage(hBtnQuit, WM_SETFONT, WPARAM(hFont), NULL);

	// �������� ������ �� ������ �����/������ � ��������� � � ������
	LoadFile();

	return TRUE;
} // OnCreate


// ��������� ��������� WM_COMMAND - ��� ���������� �� ��������� ����������
// � ��������� - �� ������
void OnCommand(HWND hWnd, INT id, HWND hWndCtl, UINT codeNotify)
{
	INT i;        // ����� ��������� ������ � ������

	switch (id) {
		// ������� ���� ��� ����� ������
	case IDC_BTNNEW:  
		// �������� ���� ����� - ���� ��� �� �������
		if (!hInput) {
			hInput = CreateWindow(szClassInput, szTitleInput,
				WS_OVERLAPPED | WS_CAPTION | WS_DLGFRAME | WS_SYSMENU,
				150, 150, INPUT_WIDTH, INPUT_HEIGHT, hWnd, NULL, hAppInstance, NULL);
		} // if

		// ����� ���������� ����� ������ � ���� ������
		bInputMode = MODE_APPEND;  
		ShowWindow(hInput, SW_SHOWNORMAL);
		break;

		// ������� �� ������ ��������� ������ - ������� ��������
	case IDC_BTNOUT:
		nResult = SendMessage(hLstPatients, LB_GETCURSEL, NULL, NULL);
		if (nResult == LB_ERR) {
			MessageBox(hWnd, _T("������� ��� ������� �� ������"), _T("������"), MB_OK | MB_ICONERROR);
			break;
		} // if

		// ������� �� ������ ������ �� �� ������
		SendMessage(hLstPatients, LB_DELETESTRING, nResult, NULL);

		// ������� ����� �������� �� ���������� - ������
		i = 0;
		for (list<Patient>::iterator it = List.begin(); it != List.end(); ++it, ++i) {
			if (i == nResult) {
				List.erase(it);
				// �������������� ���� ������ - �� ������ ������� �� ������������������
				// �� �������� ������� � ����������
				fs.close();
				WriteFile();

				// ��������� ����� ����
				fs.open(szFileName, ios::in | ios::out /* | ios::app */);
				break;
			} // if
		} // for it

		// �������� � �������� ������� ������ � ��� �� �������
		SendMessage(hLstPatients, LB_SETCURSEL, nResult, NULL);
		break;

		// ��������� �������� ������ �� ������
	case IDC_LISTPT:
		if (codeNotify == LBN_DBLCLK) {
			// �������� ������� ������� �� ������ - �������� ������������ �� �����
			// �.�. ������� ��������� ������ �� ������ �� ���������� ������
			nResult = SendMessage(hLstPatients, LB_GETCURSEL, NULL, NULL);
			i = 0;
			for (it = List.begin(); it != List.end(); ++it, ++i) {
				if (i == nResult) {
					patient = *it;  // ������������� ������������
					if (!hInput) {
						hInput = CreateWindow(szClassInput, _T("�������������� ������ ��������"),
							WS_OVERLAPPED | WS_CAPTION | WS_DLGFRAME | WS_SYSMENU,
							150, 150, INPUT_WIDTH, INPUT_HEIGHT, hWnd, NULL, hAppInstance, NULL);
					} // if

					// ���������� ���� ����� ���� hInput �� ��������� ����� ������� patient 
					// ����� �������������� ������������� ������
					bInputMode = MODE_EDIT;
					SetInput();
					ShowWindow(hInput, SW_SHOWNORMAL);
					break;
				} // if
			} // for it
		} // if
		break;

	case IDC_QUIT:   // ����� �� ����������
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


// ���������� ��������� WM_LBUTTONDOWN - ���������� ������� "������ ���" 
void OnLButtonDown(HWND hWnd, BOOL fDoubleClick, INT x, INT y, UINT keyFlags)
{
	RECT rect;       // ������������� - ��� �������� ��������� ������� ������� ���� 

	GetClientRect(hWnd, &rect);
	InvalidateRect(hWnd, &rect, TRUE);  // !!!!! �������������� �� ����� ������ !!!!!
} // OnLButtonDown


// ���������� ��������� WM_RBUTTONDOWN - ���������� ������� "������ ���" 
void OnRButtonDown(HWND hWnd, BOOL fDoubleClick, INT x, INT y, UINT keyFlags)
{
	RECT rect;       // ������������� - ��� �������� ��������� ������� ������� ���� 

	GetClientRect(hWnd, &rect);
	InvalidateRect(hWnd, &rect, TRUE);  // !!!!! �������������� �� ����� ������ !!!!!
} // OnRButtonDown


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

	//delete patient;
	DestroyWindow(hWnd);

	// ������� ���� ������
	fs.close();  
} // OnClose


// ���������� ��������� WM_DESTROY - ���������� ������� "��� ����������� ����" 
void OnDestroy(HWND hWnd)
{
	PostQuitMessage(0);
} // OnDestroy


// �������� ����� ������ � ��������� - ������ � 
// ����������� ����� � listbox
void LoadFile()
{
	// �������� ����� ����� � �������
	fs.seekg(0, ios::end);
	UINT uRecords = (UINT) (fs.tellg()) / Patient::LEN_RECORD;
	fs.seekg(0, ios::beg);
	Patient temp;
	TCHAR *szBuf = new TCHAR[Patient::LEN_RECORD];

	// ������ ���� � ������-��������� � � ������ �� ������
	for (UINT i = 0; i < uRecords; i++) {
		// fs.seekg(i*Patient::LEN_RECORD);
		temp.Load(fs);
		List.push_back(temp);

		// _stprintf() ������� ������ C-������ (����-������������), wstring � ��������
		// �� ���������. �� ����� �������� C-������ �� wstring - ����� c_str()
		_stprintf(szBuf, _T("%s %u"), temp.getFamIO().c_str(), temp.getWeight());
		SendMessage(hLstPatients, LB_ADDSTRING, NULL, (LPARAM)szBuf);
	} // for

	delete[] szBuf;
} // LoadFile


// "����������" ���������� ����� - ���� �� ����� ����� �� ��������
// � ������ ������
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
		MessageBox(HWND_DESKTOP, _T("�� ���� ��������� ������� - ���� �����"), 
			_T("������"), MB_OK | MB_ICONERROR);
		return;
	} // if

	// ���� ������ �������� �� ������ (��� ������ ���������) � ������
	// ��������� �� ��������� ����
	for (list<Patient>::iterator it = List.begin(); it != List.end(); ++it) {
		it->Save(ftmp);
	} // for it
	ftmp.close();

	// ������� �������� ���� �� ����� - DeleteFile(��������)
	DeleteFile(szFileName);
	// ������������� ���� - MoveFile(���������������, ��������)
	MoveFile(szTempFile, szFileName);

} // WriteFile