#include "WinMain.h"
#include "MainWindow.h"
#include "TicTacToe.h"

// ���������� � ������� ��� �������� ���� ����������
static HDC hdc;                    // ����� ��������� ����������
static HPEN hPen, hOldPen;		   // ����� ��� ���������
static HFONT hFont, hOldFont;      // ����� ��� ������
static short xPos, yPos;           // ���������� ������ ���
static int nEventID = EVENT_NONE;  // ������������� �������
static LOGFONT lf;                 // ��������� ��� �������� ������

static TicTacToe *game;   // ���������� ��� ������ � ����������� ���������-�������

static int nMargin = 10;  // ������ ��� ������ ����� �������� ����

// ������� ������� - ��������� ���������, ���������� �����
// hwnd	  - ���������� ����
// msg	  - �������� ��� ���������
// wParam - ������ ����� ���������� ���������
// lParam - ������ ����� ���������� ���������
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
		HANDLE_MSG(hwnd, WM_CREATE,		   OnCreate);  // �������� ����
		HANDLE_MSG(hwnd, WM_SIZE,		   OnSize);    // ��������� ������� ������
		HANDLE_MSG(hwnd, WM_LBUTTONDOWN,   OnLButtonDown);
		HANDLE_MSG(hwnd, WM_RBUTTONDOWN,   OnRButtonDown);
		HANDLE_MSG(hwnd, WM_PAINT,		   OnPaint);
		HANDLE_MSG(hwnd, WM_CLOSE,		   OnClose);
		HANDLE_MSG(hwnd, WM_DESTROY,	   OnDestroy);
		HANDLE_MSG(hwnd, WM_GETMINMAXINFO, OnGetMinMaxInfo);
	
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
	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

	game = new TicTacToe();
	return TRUE;
} // OnCreate


// ���������� ��������� WM_SIZE - ���������� ������� "��� ��������� �������" 
// ������ ����
void OnSize(HWND hwnd, UINT state, int cx, int cy)
{
	RECT rect;       // ������������� - ��� �������� ��������� ������� ������� ���� 

	GetClientRect(hwnd, &rect);         // ������ ������� ���� ��� �����������
	InvalidateRect(hwnd, &rect, TRUE);  // �������� ������� ���������������� => ����������� WM_PAINT
} // OnSize


// ���������� ��������� WM_LBUTTONDOWN - ���������� ������� "������ ���" 
void OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
	RECT rect;       // ������������� - ��� �������� ��������� ������� ������� ���� 

	GetClientRect(hwnd, &rect);
	nEventID = EVENT_LEFT;
	xPos = x;
	yPos = y;
	InvalidateRect(hwnd, &rect, TRUE);  // !!!!! �������������� �� ����� ������ !!!!!
} // OnLButtonDown


// ���������� ��������� WM_RBUTTONDOWN - ���������� ������� "������ ���" 
void OnRButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
	RECT rect;       // ������������� - ��� �������� ��������� ������� ������� ���� 

	GetClientRect(hwnd, &rect);
	nEventID = EVENT_RIGHT;
	xPos = x;
	yPos = y;
	InvalidateRect(hwnd, &rect, TRUE);  // !!!!! �������������� �� ����� ������ !!!!!
} // OnRButtonDown


// ���������� ��������� WM_PAINT - ���������� ������� "��� ���������" 
void OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;  // ��������� ��������� ����������
	RECT rect;       // ������������� - ��� �������� ��������� ������� ������� ���� 

	hdc = BeginPaint(hwnd, &ps);    // �������� ����� ��������� ����������
	GetClientRect(hwnd, &rect);     // �������� ���������� ������� ��� ���������

	// ����� ��������� ��� ��������� 
	hOldPen = SelectPen(hdc, hPen);

	// ������ ����� - ������� �������� ����
	int nWidth = rect.right - rect.left - 2 * nMargin;
	int nHeight = rect.bottom - rect.top - 2 * nMargin;

	int x = nMargin, y = nMargin;  // ������� ����� ���� �������� ����

	// ����� �������������� �����
	for (int i = 0; i <= 3; i++) {
		MoveToEx(hdc, x, y, NULL);
		LineTo(hdc, x + nWidth, y);
		y += nHeight / 3;
	} // for i

	// ����� ������������ �����
	x = y = nMargin;
	for (int i = 0; i <= 3; i++) {
		MoveToEx(hdc, x, y, NULL);
		LineTo(hdc, x, y + nHeight);
		x += nWidth / 3;
	} // for i

	SIZE  size;  // ������ ������ �������� ����
	COORD ltc;   // ������� ����� ���� ������ �������� ����
	size.cx = nWidth / 3;
	size.cy = nHeight / 3;
	int nCol = (xPos - nMargin) / size.cx;  // ����� �������
	int nRow = (yPos - nMargin) / size.cy;  // ����� ������

	// ��������� "������� ��������", "�������� ����"
	// ���������� ��������� ������ - ��������� ��������� ��� ����
	game->Fill(nRow, nCol, nEventID);

	// ����������� ������� �����, �������� ����
	ZeroMemory(&lf, sizeof(LOGFONT));
	_tcscpy(lf.lfFaceName, _T("Georgia"));
	lf.lfHeight = -size.cy;
	
	hFont = CreateFontIndirect(&lf);
	
	hOldFont = SelectFont(hdc, hFont); // ����� ������ ��� ���������
	SetBkMode(hdc, TRANSPARENT);       // ���������� ��� ��� ������ ������

	TEXTMETRIC tm;                // �������� �������, ��������������
	GetTextMetrics(hdc, &tm);     // ������ (��������� ������)

	ltc.Y = nMargin;
	TCHAR szCeil[2] = _T(""); // ������ ��� ������ �������� ��� ������
	for (int i = 0; i < 3; i++, ltc.Y += (SHORT)size.cy) {
		ltc.X = nMargin;
		for (int j = 0; j < 3; j++, ltc.X += (SHORT)size.cx) {
			if (game->getMap(i, j) == ' ') continue;
			szCeil[0] = game->getMap(i, j);

			// ���� ��������� �������� - �������� ������� ������� ������,
			// ������ ������� ����� ������
			SetTextColor(hdc, szCeil[0] == _T('X')?RGB(200, 0, 0):RGB(0, 0, 200));

			// ������ �������� �� ����������� ����� � ������
			int x = (size.cx - tm.tmAveCharWidth) / 4;
			TextOut(hdc, ltc.X + x, ltc.Y, szCeil, 1);
		} // for j
	} // for i

	SelectFont(hdc, hOldFont);
	DeleteFont(hFont);
	EndPaint(hwnd, &ps);            // ���������� �������� ��� ���������� ������ �������

	// �������� - �� ��������� �� ������
	if (game->isFinish()) {
		ProcFinish(hwnd, rect);
	} // if
} // OnPaint


// ���������� ��������� WM_CLOSE - ���������� ������� "��� �������� ����" 
void OnClose(HWND hwnd)
{
	// ������������ ������� �� ��������� ��� ��������������
	SelectPen(hdc, hOldPen);
	DeletePen(hPen);

	delete game;
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


// ��������� ���������� ���� - ����������� ����������
// ������ �� ����������� ����
void ProcFinish(HWND hwnd, RECT rect) 
{
	TCHAR szMessage[200];
	TCHAR szResult[50]; // ��������� ����
	int nReply;         // ����� ������������

	// ��������� ��������� ���� - ��� ���������� ��� �����
	TCHAR c = game->getWinner();

	// ������������ ������ � �����������
	if (c == _T('X')) {
		_tcscpy(szResult, _T("���������� - X"));
	} else if (c == _T('O')) {
		_tcscpy(szResult, _T("���������� - O"));
	} else {
		_tcscpy(szResult, _T("�����"));
	} // if
	_stprintf(szMessage, _T("���� ��������. %s.\n�����, ��� �������?"), szResult);

	// ����� ���� � �������� � ������������ � ��������� ������
	nReply = MessageBox(HWND_DESKTOP, szMessage, _T("� ��������"), MB_YESNO | MB_ICONINFORMATION);
	if (nReply == IDYES) {
		game->Clear();                      // ������� ������� ����
		nEventID = EVENT_NONE;              // ��� ����
		InvalidateRect(hwnd, &rect, TRUE);  // ������������ ������ ����
	} else {
		PostQuitMessage(0);
	} // if
} // ProcFinish