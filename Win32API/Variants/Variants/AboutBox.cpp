#include "Includes.h"
#include "resource.h"
#include "AboutBox.h"

//
//   ФУНКЦИЯ: About(HWND, UINT, WPARAM, LPARAM)
//
//   НАЗНАЧЕНИЕ:  обрабатывает сообщения в диалоговом окне About.
//
BOOL CALLBACK About(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	switch (msg) {
		HANDLE_MSG(hWnd, WM_INITDIALOG, AboutOnInitDialog);
		HANDLE_MSG(hWnd, WM_COMMAND,    AboutOnCommand);

	default:
		return FALSE;
	} // switch
} // About


// Обработчик сообщения WM_INITDIALOG
BOOL AboutOnInitDialog(HWND hWnd, HWND hWndFocus, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(hWnd);
	UNREFERENCED_PARAMETER(hWndFocus);
	UNREFERENCED_PARAMETER(lParam);

	return TRUE;
} // AboutOnInitDialog


// Обработчик сообщения WM_COMMAND
void AboutOnCommand(HWND hWnd, int id, HWND hWndCtl, UINT codeNotify)
{
	UNREFERENCED_PARAMETER(hWndCtl);
	UNREFERENCED_PARAMETER(codeNotify);

	switch (id) {
	case IDOK:
	case IDCANCEL:
		EndDialog(hWnd, 0);
	} // switch
} // AboutOnCommand