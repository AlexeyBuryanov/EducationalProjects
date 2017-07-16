#include "Includes.h"
#include "resource.h"
#include "InputLineSegBox.h"

extern ParamV19 *pParamV19;
static const INT32 LENZ_BUF = 50;
static TCHAR szBuf[LENZ_BUF];

//
//   �������: InputLineSeg(HWND, UINT, WPARAM, LPARAM)
//
//   ����������:  ������������ ��������� � ���������� ���� InputLineSeg.
//
BOOL CALLBACK InputLineSeg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	switch (msg) {
		HANDLE_MSG(hWnd, WM_INITDIALOG, InputLineSegOnInitDialog);
		HANDLE_MSG(hWnd, WM_COMMAND,    InputLineSegOnCommand);

	default:
		return FALSE;
	} // switch
} // InputLineSeg


// ���������� ��������� WM_INITDIALOG
BOOL InputLineSegOnInitDialog(HWND hWnd, HWND hWndFocus, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(hWndFocus);
	UNREFERENCED_PARAMETER(lParam);

	// ��������� ����������� �������� ����������:
	SetDlgItemInt(hWnd, IDC_EDIT_COORD_X, pParamV19->point1.X, FALSE);
	SetDlgItemInt(hWnd, IDC_EDIT_COORD_Y, pParamV19->point1.Y, FALSE);
	
	CheckRadioButton(hWnd, IDC_RADIO_RED, IDC_RADIO_BLUE, IDC_RADIO_RED + pParamV19->color);
	return TRUE;
} // InputLineSegOnInitDialog


// ���������� ��������� WM_COMMAND
void InputLineSegOnCommand(HWND hWnd, int id, HWND hWndCtl, UINT codeNotify)
{
	UNREFERENCED_PARAMETER(hWndCtl);
	UNREFERENCED_PARAMETER(codeNotify);

	switch (id) {

	case IDC_RADIO_RED:
		pParamV19->color = RED;
		break;

	case IDC_RADIO_GREEN:
		pParamV19->color = GREEN;
		break;

	case IDC_RADIO_BLUE:
		pParamV19->color = BLUE;
		break;

	case IDOK:
		// �������� � ��������� ���������� �� ����� �����:
		pParamV19->point1.X = GetDlgItemInt(hWnd, IDC_EDIT_COORD_X, NULL, FALSE);
		pParamV19->point1.Y = GetDlgItemInt(hWnd, IDC_EDIT_COORD_Y, NULL, FALSE);
		EndDialog(hWnd, TRUE);
		break;
		
	case IDCANCEL:
		EndDialog(hWnd, FALSE);
		break;
	} // switch
} // InputLineSegOnCommand