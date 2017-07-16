#include "Includes.h"
#include "resource.h"
#include "InputCoordBox.h"

extern ParamV14 *pParam;

//
//   �������: InputCoord(HWND, UINT, WPARAM, LPARAM)
//
//   ����������:  ������������ ��������� � ���������� ���� InputCoord.
//
BOOL CALLBACK InputCoord(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	switch (msg) {
		HANDLE_MSG(hWnd, WM_INITDIALOG, InputCoordOnInitDialog);
		HANDLE_MSG(hWnd, WM_COMMAND,    InputCoordOnCommand);

	default:
		return FALSE;
	} // switch
} // InputCoord


// ���������� ��������� WM_INITDIALOG
BOOL InputCoordOnInitDialog(HWND hWnd, HWND hWndFocus, LPARAM lParam)
{
	TCHAR szBuf[50];
	UNREFERENCED_PARAMETER(hWndFocus);
	UNREFERENCED_PARAMETER(lParam);

	// ��������� ����������� �������� ����������
	_stprintf(szBuf, _T("%.1lf %.1lf"), pParam->Point1.x, pParam->Point1.y);
	SetDlgItemText(hWnd, IDC_EDCOORD_1, szBuf);

	_stprintf(szBuf, _T("%.1lf %.1lf"), pParam->Point2.x, pParam->Point2.y);
	SetDlgItemText(hWnd, IDC_EDCOORD_2, szBuf);

	CheckDlgButton(hWnd, IDC_CHLENGTH, pParam->bLength);
	CheckDlgButton(hWnd, IDC_CHKOEF,   pParam->bKoef);
	return TRUE;
} // InputCoordOnInitDialog


// ���������� ��������� WM_COMMAND
void InputCoordOnCommand(HWND hWnd, int id, HWND hWndCtl, UINT codeNotify)
{
	UNREFERENCED_PARAMETER(codeNotify);
	const INT32 LENZ_BUF = 50;
	TCHAR szBuf[LENZ_BUF];

	switch (id) {
	case IDC_CHLENGTH:
		// ���������� �������� ����� ����� � ����� ������ - �.�.
		// ������� ��������������� ���������� �� ���������
		pParam->bLength = Button_GetCheck(hWndCtl);
		break;

	case IDC_CHKOEF:
		// ���������� �������� ����� ����� � ����� ������ - �.�.
		// ������� ��������������� ���������� �� ���������
		pParam->bKoef = Button_GetCheck(hWndCtl);
		break;

	case IDC_EDCOORD_1:
		break;

	case IDC_EDCOORD_2:
		break;

	case IDOK:
		// �������� � ��������� ���������� ����� �� ����� ����� 
		GetDlgItemText(hWnd, IDC_EDCOORD_1, szBuf, LENZ_BUF);
		_stscanf(szBuf, _T("%lf %lf"), &pParam->Point1.x, &pParam->Point1.y);
		GetDlgItemText(hWnd, IDC_EDCOORD_2, szBuf, LENZ_BUF);
		_stscanf(szBuf, _T("%lf %lf"), &pParam->Point2.x, &pParam->Point2.y);
		EndDialog(hWnd, 1);
		break;

	case IDCANCEL:
		EndDialog(hWnd, 0);
		break;
	} // switch
} // InputCoordOnCommand