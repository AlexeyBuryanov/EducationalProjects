#include "Includes.h"
#include "resource.h"
#include "ReverseBox.h"

// длина строки с нуль-терминалом (буква Z это показывает)
static const INT32 LENZ_STR = 150; 
static BOOL bUpperCase, bReverse;
static TCHAR szStr[LENZ_STR];

//
//   ФУНКЦИЯ: Reverse(HWND, UINT, WPARAM, LPARAM)
//
//   НАЗНАЧЕНИЕ:  обрабатывает сообщения в диалоговом окне Reverse.
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


// Обработчик сообщения WM_INITDIALOG
BOOL ReverseOnInitDialog(HWND hWnd, HWND hWndFocus, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(hWndFocus);
	UNREFERENCED_PARAMETER(lParam);

	SetDlgItemText(hWnd, IDC_EDREVERSE, szStr);
	CheckDlgButton(hWnd, IDC_CHUPCASE,  bUpperCase);
	CheckDlgButton(hWnd, IDC_CHREVERSE, bReverse);
	return TRUE;
} // ReverseOnInitDialog


// Обработчик сообщения WM_COMMAND
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
		if (bReverse) _tcsrev(szStr);    // реврес строки
		if (bUpperCase) RUpper(szStr);   // перевод строки в верхний регистр
		SetDlgItemText(hWnd, IDC_EDREVERSE, szStr);
		break;

	case IDOK:
	case IDCANCEL:
		EndDialog(hWnd, 0);
		break;
	} // switch
} // ReverseOnCommand


// Функция для перевода букв в строке в верхний регистр 
TCHAR *RUpper(TCHAR *szStr) {
	_tcsupr(szStr); // перевод для латинских символов

	// перевод для русских символов
	for (int i = 0; szStr[i]; i++) {
		if (szStr[i] >= _T('а') && szStr[i] <= _T('я')) szStr[i] -= 32;
	} // for i

	return szStr;
} // RUpper