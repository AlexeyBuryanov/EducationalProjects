#include "Includes.h"
#include "resource.h"
#include "ShowResultBox.h"

extern ParamV14 *pParam;

//
//   ФУНКЦИЯ: ShowResult(HWND, UINT, WPARAM, LPARAM)
//
//   НАЗНАЧЕНИЕ:  обрабатывает сообщения в диалоговом окне ShowResult.
//
BOOL CALLBACK ShowResult(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	switch (msg) {
		HANDLE_MSG(hWnd, WM_INITDIALOG, ShowResultOnInitDialog);
		HANDLE_MSG(hWnd, WM_COMMAND,	ShowResultOnCommand);

	default:
		return FALSE;
	} // switch
} // ShowResult


// Обработчик сообщения WM_INITDIALOG
BOOL ShowResultOnInitDialog(HWND hWnd, HWND hWndFocus, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(hWndFocus);
	UNREFERENCED_PARAMETER(lParam);

	TCHAR szBuf[80];

	// Это прикладная часть!!! Лучше вынести в отдельный класс!!! 
	if (pParam->bLength) {
		double Length = sqrt(pow(pParam->Point1.x - pParam->Point2.x, 2) + pow(pParam->Point1.y - pParam->Point2.y, 2));
		_stprintf(szBuf, _T("Расстояние между точками (%.2lf, %.2lf) и (%.2lf, %.2lf)\n\nравно %.2lf"),
			pParam->Point1.x, pParam->Point2.y, pParam->Point2.x, pParam->Point2.y, Length);
	} else {
		_stprintf(szBuf, _T("Расчет расстояния не затребован"));
	} //if
	SetDlgItemText(hWnd, IDC_STRESLENGTH, szBuf);

	if (pParam->bKoef) {
		double Koef = abs(pParam->Point1.y - pParam->Point2.y)/abs(pParam->Point1.x - pParam->Point2.x);
		_stprintf(szBuf, _T("Угловой коэффициент для точек (%.2lf, %.2lf) и (%.2lf, %.2lf)\n\nравен %.2lf"),
			pParam->Point1.x, pParam->Point2.y, pParam->Point2.x, pParam->Point2.y, Koef);
	} else {
		_stprintf(szBuf, _T("Расчет коэффициента не затребован"));
	} //if
	SetDlgItemText(hWnd, IDC_STRESKOEF, szBuf);

	return TRUE;
} // ShowResultOnInitDialog


// Обработчик сообщения WM_COMMAND
void ShowResultOnCommand(HWND hWnd, int id, HWND hWndCtl, UINT codeNotify)
{
	UNREFERENCED_PARAMETER(codeNotify);

	switch (id) {
	case IDOK:
	case IDCANCEL:
		EndDialog(hWnd, 0);
		break;
	} // switch
} // ShowResultOnCommand