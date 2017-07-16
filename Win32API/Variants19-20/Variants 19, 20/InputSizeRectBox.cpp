#include "Includes.h"
#include "resource.h"
#include "InputSizeRectBox.h"

extern ParamV20 *pParamV20;
static const INT32 LENZ_BUF = 50;
static TCHAR szBuf[LENZ_BUF];

//
//   ФУНКЦИЯ: InputSizeRect(HWND, UINT, WPARAM, LPARAM)
//
//   НАЗНАЧЕНИЕ:  обрабатывает сообщения в диалоговом окне InputSizeRect.
//
BOOL CALLBACK InputSizeRect(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	switch (msg) {
		HANDLE_MSG(hWnd, WM_INITDIALOG, InputSizeRectOnInitDialog);
		HANDLE_MSG(hWnd, WM_COMMAND,    InputSizeRectOnCommand);

	default:
		return FALSE;
	} // switch
} // InputSizeRect


// Обработчик сообщения WM_INITDIALOG
BOOL InputSizeRectOnInitDialog(HWND hWnd, HWND hWndFocus, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(hWnd);
	UNREFERENCED_PARAMETER(hWndFocus);
	UNREFERENCED_PARAMETER(lParam);

	// Заполняем управляющие элементы значениями:
	SetDlgItemInt(hWnd, IDC_EDIT_X, pParamV20->size.cx, FALSE);
	SetDlgItemInt(hWnd, IDC_EDIT_Y, pParamV20->size.cy, FALSE);
	
	CheckRadioButton(hWnd, IDC_RADIO_INC, IDC_RADIO_DEC, IDC_RADIO_INC + pParamV20->mode);
	return TRUE;
} // InputSizeRectOnInitDialog


// Обработчик сообщения WM_COMMAND
void InputSizeRectOnCommand(HWND hWnd, int id, HWND hWndCtl, UINT codeNotify)
{
	UNREFERENCED_PARAMETER(hWndCtl);
	UNREFERENCED_PARAMETER(codeNotify);

	switch (id) {

	case IDC_RADIO_INC:
		pParamV20->mode = INCREASE;
		break;

	case IDC_RADIO_DEC:
		pParamV20->mode = DECREASE;
		break;
	
	case IDOK:
		// Получить и сохранить координаты сторон прямоугольника из строк ввода:
		pParamV20->size.cx = GetDlgItemInt(hWnd, IDC_EDIT_X, NULL, FALSE);
		pParamV20->size.cy = GetDlgItemInt(hWnd, IDC_EDIT_Y, NULL, FALSE);
		EndDialog(hWnd, TRUE);
		break;

	case IDCANCEL:
		EndDialog(hWnd, FALSE);
		break;
	} // switch
} // InputSizeRectOnCommand