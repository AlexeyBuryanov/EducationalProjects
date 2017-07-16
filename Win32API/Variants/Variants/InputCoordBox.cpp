#include "Includes.h"
#include "resource.h"
#include "InputCoordBox.h"

extern ParamV14 *pParam;

//
//   ФУНКЦИЯ: InputCoord(HWND, UINT, WPARAM, LPARAM)
//
//   НАЗНАЧЕНИЕ:  обрабатывает сообщения в диалоговом окне InputCoord.
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


// Обработчик сообщения WM_INITDIALOG
BOOL InputCoordOnInitDialog(HWND hWnd, HWND hWndFocus, LPARAM lParam)
{
	TCHAR szBuf[50];
	UNREFERENCED_PARAMETER(hWndFocus);
	UNREFERENCED_PARAMETER(lParam);

	// Заполняем управляющие элементы значениями
	_stprintf(szBuf, _T("%.1lf %.1lf"), pParam->Point1.x, pParam->Point1.y);
	SetDlgItemText(hWnd, IDC_EDCOORD_1, szBuf);

	_stprintf(szBuf, _T("%.1lf %.1lf"), pParam->Point2.x, pParam->Point2.y);
	SetDlgItemText(hWnd, IDC_EDCOORD_2, szBuf);

	CheckDlgButton(hWnd, IDC_CHLENGTH, pParam->bLength);
	CheckDlgButton(hWnd, IDC_CHKOEF,   pParam->bKoef);
	return TRUE;
} // InputCoordOnInitDialog


// Обработчик сообщения WM_COMMAND
void InputCoordOnCommand(HWND hWnd, int id, HWND hWndCtl, UINT codeNotify)
{
	UNREFERENCED_PARAMETER(codeNotify);
	const INT32 LENZ_BUF = 50;
	TCHAR szBuf[LENZ_BUF];

	switch (id) {
	case IDC_CHLENGTH:
		// Запоминаем значение флага сразу в точке вызова - т.е.
		// никакой вспомогательной переменной не требуется
		pParam->bLength = Button_GetCheck(hWndCtl);
		break;

	case IDC_CHKOEF:
		// Запоминаем значение флага сразу в точке вызова - т.е.
		// никакой вспомогательной переменной не требуется
		pParam->bKoef = Button_GetCheck(hWndCtl);
		break;

	case IDC_EDCOORD_1:
		break;

	case IDC_EDCOORD_2:
		break;

	case IDOK:
		// Получить и сохранить координаты точек из строк ввода 
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