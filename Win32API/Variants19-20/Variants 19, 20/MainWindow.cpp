#include "Includes.h"
#include "resource.h"
#include "MainWindow.h"
#include "AboutBox.h"
#include "InputLineSegBox.h"
#include "InputSizeRectBox.h"

extern HINSTANCE hAppInstance;

// ���������� ����� �������� 19, 20:
ParamV19 *pParamV19;
ParamV20 *pParamV20;

static RECT rect;   // ���������� ������� ����
HWND hStBar;		// ������-���

HPEN   hOldPen, hPenRed, hPenGreen, hPenBlue;
HBRUSH hOldBrush, hBrush;

//
//   �������: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//   ����������:  ������������ ��������� � ������� ����.
//
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
} // CALLBACK WndProc


// ���������� ��������� WM_CREATE - ���������� ������� "��� ��������" ����
BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
	UNREFERENCED_PARAMETER(lpCreateStruct);

	hStBar = CreateStatusWindow(WS_CHILD | WS_VISIBLE, _T("����� ����������"), hWnd, IDC_STATUSBAR);

	hPenRed   = CreatePen(PS_SOLID, 5, RGB(0xFF, 0x00, 0x00));
	hPenGreen = CreatePen(PS_SOLID, 5, RGB(0x00, 0xEE, 0x00));
	hPenBlue  = CreatePen(PS_SOLID, 5, RGB(0x00, 0x00, 0xEE));
	hBrush	  = CreateSolidBrush(RGB(0xFF, 0xD3, 0x00));

	// �������� ���������� ��� ���� ��������� � ��������� ��������� ��������:
	pParamV19 = new ParamV19;
	pParamV19->color = NO_COLOR;
	ZeroMemory(pParamV19, sizeof(ParamV19));
	pParamV20 = new ParamV20;
	ZeroMemory(pParamV20, sizeof(ParamV20));

	// TODO:
	#pragma region �������������
	GetClientRect(hWnd, &rect);			 // �������� ������ ���������� �������
	InvalidateRect(hWnd, &rect, TRUE);   // �������� ������� ����������������

	RECT temp;					  // ��������������� ���������� ��� ������� ������� ��������������
	GetClientRect(hStBar, &temp); // �������� ������-��� �� ���������� �������

	// ���� ������������� �� ����� ������ (������� ���������)
	// �� ������ ����� ������� 100 (��������� ��������� �� �������)
	if (pParamV20->rect.top  == pParamV20->rect.bottom &&
		pParamV20->rect.left == pParamV20->rect.right) {

		// ������ ���������� ������� ����:
		UINT uWidth  = rect.right  - rect.left;
		// ������ ���������� ������� ����:
		UINT uHeight = rect.bottom - rect.top - (temp.bottom - temp.top);   

		// ���������� �������� 100 � 100 � ������ ����:
		pParamV20->rect.left   = uWidth / 2 - 50;
		pParamV20->rect.right  = pParamV20->rect.left + 100;
		pParamV20->rect.top    = uHeight / 2 - 50;
		pParamV20->rect.bottom = pParamV20->rect.top + 100;

		// ��� ������ ������������� ������ ���� �������:
		pParamV20->view = pParamV20->rect;  
	} // if
	#pragma endregion

	pParamV19->bDraw = FALSE;   // ���������� ���� ��������� ������� false

	return TRUE;
} // OnCreate


// ��������� ��������� WM_COMMAND - ��� ���������� �� ��������� ����������
void OnCommand(HWND hWnd, int id, HWND hWndCtl, UINT codeNotify)
{
	UNREFERENCED_PARAMETER(hWndCtl);
	UNREFERENCED_PARAMETER(codeNotify);
	
	HMENU hMenu = GetMenu(hWnd);   // �������� ���������� ����

	switch (id) {
		// � ���������:
	case ID_ABOUT:
		DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_ABOUT), hWnd, About);
		break;

		// ���� ��������� ��� �������:
	case ID_INPUT_COORD:
		if (DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_INPUT_COORD), hWnd, InputLineSeg) == IDOK) {
			EnableMenuItem(hMenu, ID_DRAW,  MF_ENABLED);
		} // if
		break;

		// ��������:
	case ID_DRAW:
		pParamV19->bDraw = TRUE;
		InvalidateRect(hWnd, NULL, TRUE);
		EnableMenuItem(hMenu, ID_DRAW,  MF_GRAYED);
		EnableMenuItem(hMenu, ID_CLEAR, MF_ENABLED);
		break;

		// ��������:
	case ID_CLEAR:
		pParamV19->bDraw = FALSE;				  // �� ��������
		pParamV19->color = NO_COLOR;			  // �������� ����
		ZeroMemory(pParamV19, sizeof(ParamV19));  // �������� ���������
		InvalidateRect(hWnd, NULL, TRUE);		  // �������� ������� ���������������� (������������)
		EnableMenuItem(hMenu, ID_DRAW,  MF_GRAYED);
		EnableMenuItem(hMenu, ID_CLEAR, MF_GRAYED);
		break;
		
		// ��������� �������������� (���� ������ X, Y ��� ��������������):
	case ID_INPUT_RECT:
		if (DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_INPUT_RECT), hWnd, InputSizeRect) == IDOK) {
			EnableMenuItem(hMenu, ID_CHANGE_RECT, MF_ENABLED);
			
			int nDeltaX = pParamV20->size.cx / 2;
			int nDeltaY = pParamV20->size.cy / 2;

			// �������� ������ ���������� ������� ����:
			GetClientRect(hWnd, &rect);

			// ������������� ������ ��������������:
			switch (pParamV20->mode) {
			case INCREASE:
				// ��������� ������ ��������������, �������� ��������:
				pParamV20->rect.left   -= nDeltaX;
				pParamV20->rect.right  += nDeltaX;
				pParamV20->rect.top    -= nDeltaY;
				pParamV20->rect.bottom += nDeltaY;

				// �������� �� ����������� ������� ������ ���������� �������:
				if (pParamV20->rect.right  - pParamV20->rect.left > rect.right  - rect.left ||
					pParamV20->rect.bottom - pParamV20->rect.top  > rect.bottom - rect.top) {
					pParamV20->rect = pParamV20->view;   // ������� �������� �������
					SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("������� ������� �������������, ���������� ��������"));
				} // if
				break;
			case DECREASE:
				// ��������� ������ ��������������:
				pParamV20->rect.left   += nDeltaX;
				pParamV20->rect.right  -= nDeltaX;
				pParamV20->rect.top    += nDeltaY;
				pParamV20->rect.bottom -= nDeltaY;

				// �������� �� ����������� ���� ������� 10 �� ������ ��� �� ������:
				if (pParamV20->rect.right  - pParamV20->rect.left < 10 ||
					pParamV20->rect.bottom - pParamV20->rect.top  < 10) {
					pParamV20->rect = pParamV20->view;   // ������� �������� �������
					SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("������� ��������� �������, ���������� ��������"));
				} // if
				break;
			} // switch
		} // if
		break;

		// �������� �������������:
	case ID_CHANGE_RECT:
		// ��������� �������� ��� ���������� ��������������
		// ����� ������� ������ ������������ ����� �������������� � �����
		// �������� ������ �� ������� ��������� �������
		pParamV20->view = pParamV20->rect;
		InvalidateRect(hWnd, NULL, TRUE);
		EnableMenuItem(hMenu, ID_CHANGE_RECT, MF_GRAYED);
		break;

	case ID_EXIT:
		PostQuitMessage(0);
		break;
	} // switch
} // OnCommand


// ���������� ��������� WM_SIZE - ���������� ������� "��� ��������� �������" ����
void OnSize(HWND hWnd, UINT state, int cx, int cy)
{
	UNREFERENCED_PARAMETER(state);
	UNREFERENCED_PARAMETER(cx);
	UNREFERENCED_PARAMETER(cy);

	// ������� ������-��� ������ � ���������� ������� ����:
	MoveWindow(hStBar, NULL, NULL, NULL, NULL, TRUE);

	GetClientRect(hWnd, &rect);         // ������ ������� ���� ��� �����������
	InvalidateRect(hWnd, &rect, TRUE);  // �������� ������� ���������������� => ����������� WM_PAINT
} // OnSize


// ����������� ������������ ������� �������� ���� ����������
void OnGetMinMaxInfo(HWND hWnd, LPMINMAXINFO lpMinMaxInfo)
{
	UNREFERENCED_PARAMETER(hWnd);

	lpMinMaxInfo->ptMinTrackSize = { 600, 400 };
} // OnGetMinMaxInfo


// ���������� ��������� WM_PAINT - ���������� ������� "��� ���������"
static HDC hDC, hCompatibleDC;   // ���������� ��������� ���������� � ���������� ��������
void OnPaint(HWND hWnd)
{	
	PAINTSTRUCT ps;			     // ��������� ��������� ����������
	HANDLE hBitmap, hOldBitmap;
	BITMAP Bitmap;

	hDC = BeginPaint(hWnd, &ps);    // �������� ���������� ��������� ����������
	
	#pragma region ������, ��� ��� ������� ������� ����
	// ��������� bitmap, ������� ����� ������������ � ����, �� ��������:
	hBitmap = LoadBitmap(hAppInstance, MAKEINTRESOURCE(IDB_BACKGROUND));

	// ����� ����� ��������� ������ �� �����:
	// hBitmap = LoadImage(NULL, _T("Background.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	
	// �������� ����������� ������������ bitmap'a:
	GetObject(hBitmap, sizeof(BITMAP), &Bitmap);

	// ������� ���������� � ���������� ���� �������� � ������:
	hCompatibleDC = CreateCompatibleDC(hDC);

	// ������ ����������� �� ����� bitmap ������� � ����������� ���������:
	hOldBitmap = SelectObject(hCompatibleDC, hBitmap);

	// ���������� ������ ������� ������� ����:
	GetClientRect(hWnd, &rect);

	// �������� bitmap � ������������ �� �������� �������� � ����������������:
	StretchBlt(hDC, NULL, NULL, rect.right, rect.bottom, hCompatibleDC, NULL, NULL, Bitmap.bmWidth, Bitmap.bmHeight, SRCCOPY);
	
	// ����� ������ ������ bitmap �������:
	SelectObject(hCompatibleDC, hOldBitmap);

	// ������� ����������� � ����� bitmap:
	DeleteObject(hBitmap);

	// ������� ���������� ��������:
	DeleteDC(hCompatibleDC);
	#pragma endregion

	// ������� ������� view:
	SelectBrush(hDC, hBrush);
	Rectangle(hDC, pParamV20->view.left, pParamV20->view.top, pParamV20->view.right, pParamV20->view.bottom);

	// ��������� ��������:
	if (pParamV19->bDraw) {
		// ������������� �����:
		switch (pParamV19->color) {
		case RED:
			SelectPen(hDC, hPenRed);
			break;
		case GREEN:
			SelectPen(hDC, hPenGreen);
			break;
		case BLUE:
			SelectPen(hDC, hPenBlue);
			break;
		} // switch
		
		// ������� ������� ������ ����� ��������:
		MoveToEx(hDC, pParamV19->point.X = 30, pParamV19->point.Y = 30, NULL);
		// ������:
		LineTo(hDC, pParamV19->point1.X, pParamV19->point1.Y);
	} // if

	EndPaint(hWnd, &ps);   // ���������� �������� ��� ���������� ������ �������
} // OnPaint


// ���������� ��������� WM_CLOSE - ���������� ������� "��� �������� ����" 
void OnClose(HWND hWnd)
{
	DestroyWindow(hWnd);
} // OnClose


// ���������� ��������� WM_DESTROY - ���������� ������� "��� ����������� ����" 
void OnDestroy(HWND hWnd)
{
	UNREFERENCED_PARAMETER(hWnd);

	SelectPen(hDC, hOldPen);
	DeletePen(hPenRed);
	DeletePen(hPenGreen);
	DeletePen(hPenBlue);

	SelectBrush(hDC, hOldBrush);
	DeleteBrush(hBrush);

	delete pParamV19;
	delete pParamV20;

	PostQuitMessage(0);
} // OnDestroy


// ��������� ���� ������������ ������������ ��������
HBRUSH OnCtlColorStatic(HWND hWnd, HDC hDC, HWND hWndChild, int type)
{
	UNREFERENCED_PARAMETER(hWnd);
	UNREFERENCED_PARAMETER(hWndChild);
	UNREFERENCED_PARAMETER(type);

	SetBkMode(hDC, TRANSPARENT);
	return CreateSolidBrush(BACKGROUND);
} // OnCtlColorStatic


// ��������� ������ ������� ���� - ����� ������ � ������ ���������
void OnMenuSelect(HWND hWnd, HMENU hMenu, int item, HMENU hMenuPopup, UINT flags)
{
	UNREFERENCED_PARAMETER(hWnd);
	UNREFERENCED_PARAMETER(hMenu);
	UNREFERENCED_PARAMETER(hMenuPopup);
	UNREFERENCED_PARAMETER(flags);
	
	switch (item) {
	case ID_EXIT:
		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("��������� ������ � ����� �� ����������"));
		break;
	case ID_ABOUT:
		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("���������� � ��������� � ������������..."));
		break;
	case ID_INPUT_COORD:
		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("������ ���������� � ��������� �������..."));
		break;
	case ID_DRAW:
		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("���������� ������� � ���������� �����������"));
		break;
	case ID_CLEAR:
		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("�������� ������������ ������� � �������� ���������"));
		break;
	case ID_INPUT_RECT:
		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("������ ������ �������� � ������ �������� ����..."));
		break;
	case ID_CHANGE_RECT:
		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("�������� �������"));
		break;
	default:
		SendMessage(hStBar, SB_SETTEXT, 0, (LPARAM)_T("����� ����������"));
		break;
	} // switch
} // OnMenuSelect