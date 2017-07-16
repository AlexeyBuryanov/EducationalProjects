#include "Includes.h"
#include "resource.h"
#include "ReverseBox.h"

// ����� ������ � ����-���������� (����� Z ��� ����������)
static const INT32 LENZ_STR = 150; 
static BOOL bUpperCase, bReverse;
static TCHAR szStr[LENZ_STR];

//
//   �������: Reverse(HWND, UINT, WPARAM, LPARAM)
//
//   ����������:  ������������ ��������� � ���������� ���� Reverse.
//
BOOL CALLBACK Reverse(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	switch (msg) {
		HANDLE_MSG(hWnd, WM_INITDIALOG, ReverseOnInitDialog);
		HANDLE_MSG(hWnd, WM_COMMAND,    ReverseOnCommand);

	default:
		return FALSE;
	} // switch
} // Reverse


// ���������� ��������� WM_INITDIALOG
BOOL ReverseOnInitDialog(HWND hWnd, HWND hWndFocus, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(hWndFocus);
	UNREFERENCED_PARAMETER(lParam);

	SetDlgItemText(hWnd, IDC_EDREVERSE, szStr);
	CheckDlgButton(hWnd, IDC_CHUPCASE,  bUpperCase);
	CheckDlgButton(hWnd, IDC_CHREVERSE, bReverse);
	return TRUE;
} // ReverseOnInitDialog


// ���������� ��������� WM_COMMAND
void ReverseOnCommand(HWND hWnd, int id, HWND hWndCtl, UINT codeNotify)
{
	UNREFERENCED_PARAMETER(codeNotify);

	switch (id) {
	case IDC_CHUPCASE:
		bUpperCase = Button_GetCheck(hWndCtl);
		break;

	case IDC_CHREVERSE:
		bReverse = Button_GetCheck(hWndCtl);
		break;

	case IDC_BTNSTRAPPLY:
		GetDlgItemText(hWnd, IDC_EDREVERSE, szStr, LENZ_STR);
		if (bReverse) _tcsrev(szStr);    // ������ ������
		if (bUpperCase) RUpper(szStr);   // ������� ������ � ������� �������
		SetDlgItemText(hWnd, IDC_EDREVERSE, szStr);
		break;

	case IDOK:
	case IDCANCEL:
		EndDialog(hWnd, 0);
		break;
	} // switch
} // ReverseOnCommand


// ������� ��� �������� ���� � ������ � ������� ������� 
TCHAR *RUpper(TCHAR *szStr) {
	_tcsupr(szStr); // ������� ��� ��������� ��������

	// ������� ��� ������� ��������
	for (int i = 0; szStr[i]; i++) {
		if (szStr[i] >= _T('�') && szStr[i] <= _T('�')) szStr[i] -= 32;
	} // for i

	return szStr;
} // RUpper