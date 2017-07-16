#include "Includes.h"
#include "resource.h"
#include "MainWindow.h"
#include "AboutBox.h"
#include "InputColorBox.h"
#include "TranslateBox.h"
#include "ReverseBox.h"
#include "InputCoordBox.h"
#include "ShowResultBox.h"
#include "CurConvertBox.h"

extern HINSTANCE hAppInstance;

COLOR_CONTROL Params;

HPEN   hOldPen, hPen, hPenRed, hPenGreen, hPenBlue;
HBRUSH hOldBrush, hRedBrush, hGreenBrush, hBlueBrush;

// ���������� ����� �������� 14 - ���������� ��� �������� ����������
ParamV14 *pParam;

//
//   �������: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//   ����������:  ������������ ��������� � ������� ����.
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
		HANDLE_MSG(hWnd, WM_CREATE,			OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND,		OnCommand);
		HANDLE_MSG(hWnd, WM_SIZE,			OnSize);
		HANDLE_MSG(hWnd, WM_GETMINMAXINFO,  OnGetMinMaxInfo);
		HANDLE_MSG(hWnd, WM_PAINT,			OnPaint);
		HANDLE_MSG(hWnd, WM_CLOSE,			OnClose);
		HANDLE_MSG(hWnd, WM_DESTROY,		OnDestroy);
		HANDLE_MSG(hWnd, WM_CTLCOLORSTATIC, OnCtlColorStatic);

	// ��������� ��������� ��� ������� �� ������������� ��������� � ����� ����
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	} // switch

	return 0;
} // CALLBACK WndProc


// ���������� ��������� WM_CREATE - ���������� ������� "��� ��������" 
// ������ ����
BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
	UNREFERENCED_PARAMETER(lpCreateStruct);
	
	hPen		= CreatePen(PS_SOLID, 0, RGB(0xFF, 0xFF, 0xFF));
	hPenRed		= CreatePen(PS_SOLID, 0, RGB(0xFF, 0x00, 0x00));
	hPenGreen	= CreatePen(PS_SOLID, 0, RGB(0x00, 0xEE, 0x00));
	hPenBlue	= CreatePen(PS_SOLID, 0, RGB(0x00, 0x00, 0xEE));

	hRedBrush   = CreateSolidBrush(RGB(0xFF, 0x00, 0x00));
	hGreenBrush = CreateSolidBrush(RGB(0x00, 0xEE, 0x00));
	hBlueBrush  = CreateSolidBrush(RGB(0x00, 0x00, 0xEE));

	Params.bRed = Params.bGreen = Params.bBlue = false;
	Params.bUp  = Params.bDown  = true;

	// �������� ���������� ��� �������� 14 � ��������� ���������
	// �������� ����������
	pParam = new ParamV14;
	ZeroMemory(pParam, sizeof(ParamV14));

	return TRUE;
} // OnCreate


// ��������� ��������� WM_COMMAND - ��� ���������� �� ��������� ����������
// � ��������� - �� ������
RECT rect;       // ������������� - ��� �������� ��������� ������� ������� ���� 
HDC hDC;		 // ����� ��������� ����������
void OnCommand(HWND hWnd, int id, HWND hWndCtl, UINT codeNotify)
{
	UNREFERENCED_PARAMETER(hWndCtl);
	UNREFERENCED_PARAMETER(codeNotify);

	switch (id) {
	case IDM_ABOUT:
		DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_DIALOG_ABOUT), hWnd, About);
		break;

	case IDM_INPUTCOLOR:
		SetInputColorParam(&Params);
		if (DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_DIALOG_INPUTCOLOR), hWnd, InputColor) == IDOK) {
			GetInputColorParam(&Params);
		} // if
		break;

		// ��������
	case IDM_CHANGE:
		InvalidateRect(hWnd, &rect, TRUE);
		break;

		// ������� ������� ����
	case IDM_CLEAR:
		// ������� ����� ��������� ����, ������� ����������� ����� ����
		// ��������� ����, ��������� ������������� 
		SelectBrush(hDC, hOldBrush);
		Params.bUp  = Params.bDown  = true;
		Params.bRed = Params.bGreen = Params.bBlue = false;
		InvalidateRect(hWnd, &rect, TRUE);
		break;

	case IDM_TRANSLATE:
		DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_DIALOG_TRANSLATE), hWnd, Translate);
		break;

	case IDM_REVERSE:
		DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_DIALOG_REVERSE), hWnd, Reverse);
		break;

	case IDM_INPUTCOORD:
		DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_DIALOG_INPUTCOORD), hWnd, InputCoord);
		break;

	case IDM_SHOWCOORDRES:
		DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_DIALOG_SHOWRES), hWnd, ShowResult);
		break;

	case IDM_CURCONVERT:
		DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_DIALOG_CURCONVERT), hWnd, CurConvert);
		break;

	case IDM_EXIT:
		PostQuitMessage(0);
		break;
	} // switch
} // OnCommand


// ���������� ��������� WM_SIZE - ���������� ������� "��� ��������� �������" 
// ������ ����
void OnSize(HWND hWnd, UINT state, int cx, int cy)
{
	UNREFERENCED_PARAMETER(state);
	UNREFERENCED_PARAMETER(cx);
	UNREFERENCED_PARAMETER(cy);

	GetClientRect(hWnd, &rect);         // ������ ������� ���� ��� �����������
	InvalidateRect(hWnd, &rect, TRUE);  // �������� ������� ���������������� => ����������� WM_PAINT
} // OnSize


// ����������� ������������ ������� �������� ���� ����������
// !! �������� ������ � OnSize !!
void OnGetMinMaxInfo(HWND hWnd, LPMINMAXINFO lpMinMaxInfo)
{
	UNREFERENCED_PARAMETER(hWnd);

	lpMinMaxInfo->ptMinTrackSize = { 550, 400 };
	// lpMinMaxInfo->ptMaxTrackSize = {  };
} // OnGetMinMaxInfo


// ���������� ��������� WM_PAINT - ���������� ������� "��� ���������"
void OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;  // ��������� ��������� ����������
	RECT rect;       // ������������� - ��� �������� ��������� ������� ������� ���� 

	hDC = BeginPaint(hWnd, &ps);    // �������� ����� ��������� ����������
	GetClientRect(hWnd, &rect);     // �������� ���������� ������� ��� ���������

	// ������������� ���������� ��� ��������� ������!!! 
	// ������� ����������� ��� ��������� �����, � �����
	// ������ ��������� ���������� ������ ������
	SelectPen(hDC, hPen);
	SelectBrush(hDC, hOldBrush);
	Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom / 2);
	Rectangle(hDC, rect.left, rect.bottom / 2, rect.right, rect.bottom);

	if (Params.bRed) {
		SelectBrush(hDC, hRedBrush);
		SelectPen(hDC, hPenRed);
	} // if
	if (Params.bGreen) {
		SelectBrush(hDC, hGreenBrush);
		SelectPen(hDC,   hPenGreen);
	} // if
	if (Params.bBlue) {
		SelectBrush(hDC, hBlueBrush);
		SelectPen(hDC, hPenBlue);
	} // if
	
	if (Params.bUp) {
		Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom / 2);
	} // if 
	if (Params.bDown) {
		Rectangle(hDC, rect.left, rect.bottom / 2, rect.right, rect.bottom);
	} // if
	EndPaint(hWnd, &ps);    // ���������� �������� ��� ���������� ������ �������
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
	DeletePen(hPen);

	SelectBrush(hDC, hOldBrush);
	DeleteBrush(hRedBrush);
	DeleteBrush(hGreenBrush);
	DeleteBrush(hBlueBrush);

	delete pParam;

	PostQuitMessage(0);
} // OnDestroy


// ��������� ���� ������������ ������������ ��������
// ��� - ��������� � ����� ������� ������� ����
HBRUSH OnCtlColorStatic(HWND hWnd, HDC hDC, HWND hWndChild, int type)
{
	UNREFERENCED_PARAMETER(hWnd);
	UNREFERENCED_PARAMETER(hWndChild);
	UNREFERENCED_PARAMETER(type);

	SetBkMode(hDC, TRANSPARENT);
	return CreateSolidBrush(BACKGROUND);
} // OnCtlColorStatic