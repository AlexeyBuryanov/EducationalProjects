#include "Includes.h"
#include "resource.h"
#include "InputColorBox.h"
#include "MainWindow.h"

BOOL bUp, bDown;	// ��������� ���-������
UINT uRdState;	    // ��������� �����������

void SetInputColorParam(COLOR_CONTROL *Params)
{
	bUp    = Params->bUp;
	bDown  = Params->bDown;

	if (Params->bRed)   uRdState = 0;
	if (Params->bGreen) uRdState = 1;
	if (Params->bBlue)  uRdState = 2;
} // SetInputColorParam


void GetInputColorParam(COLOR_CONTROL *Params)
{
	Params->bUp = bUp;
	Params->bDown = bDown;

	switch (uRdState) {
	case 0:  // �������
		Params->bRed = true;
		Params->bGreen = Params->bBlue = false;
		break;
	case 1:  // �������
		Params->bGreen = true;
		Params->bRed = Params->bBlue = false;
		break;
	case 2:  // �����
		Params->bBlue = true;
		Params->bGreen = Params->bRed = false;
		break;
	} // switch
} // GetInputColorParam


//
//   �������: InputColor(HWND, UINT, WPARAM, LPARAM)
//
//   ����������:  ������������ ��������� � ���������� ���� InputColor.
//
BOOL CALLBACK InputColor(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	switch (msg) {
		HANDLE_MSG(hWnd, WM_INITDIALOG, InputColorOnInitDialog);
		HANDLE_MSG(hWnd, WM_COMMAND,    InputColorOnCommand);

	default:
		return FALSE;
	} // switch
} // InputColor


// ���������� ��������� WM_INITDIALOG
BOOL InputColorOnInitDialog(HWND hWnd, HWND hWndFocus, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(hWndFocus);
	UNREFERENCED_PARAMETER(lParam);

	CheckRadioButton(hWnd, IDC_RDRED, IDC_RDBLUE, IDC_RDRED + uRdState);
	CheckDlgButton(hWnd, IDC_CHECKUP, bUp);
	CheckDlgButton(hWnd, IDC_CHECKDOWN, bDown);
	return TRUE;
} // InputColorOnInitDialog


// ���������� ��������� WM_COMMAND
void InputColorOnCommand(HWND hWnd, int id, HWND hWndCtl, UINT codeNotify)
{
	UNREFERENCED_PARAMETER(codeNotify);

	switch (id) {
	case IDC_CHECKUP:
		bUp = Button_GetCheck(hWndCtl);
		break;

	case IDC_CHECKDOWN:
		bDown = Button_GetCheck(hWndCtl);
		break;

	case IDC_RDRED:
		uRdState = 0;
		break;

	case IDC_RDGREEN:
		uRdState = 1;
		break;

	case IDC_RDBLUE:
		uRdState = 2;
		break;

	case IDOK:
		// ������ ���������� �� ������� �������� �� ��
		EndDialog(hWnd, 1);   
		break;

	case IDCANCEL:
		EndDialog(hWnd, 0);
		break;
	} // switch
} // InputColorOnCommand