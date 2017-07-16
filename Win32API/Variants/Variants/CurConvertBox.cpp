#include "Includes.h"
#include "resource.h"
#include "CurConvertBox.h"

// Данные для решения прикладной задачи:
static UINT uRubles;    // Сумма в рублях для конвертации
static UINT uEuros;     // Сумма в евро
static UINT uDollars;   // Сумма в долларах
static UINT uMode;      // Режим - курс обычный, льготный
// Льготный курс - на 10% меньше

// Курс Евро к Рублю
static UINT uCourseEuro = 78;
// Курс Доллара к Рублю
static UINT uCourseDollar = 70;

//
//   ФУНКЦИЯ: CurConvert(HWND, UINT, WPARAM, LPARAM)
//
//   НАЗНАЧЕНИЕ:  обрабатывает сообщения в диалоговом окне CurConvert.
//
BOOL CALLBACK CurConvert(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	switch (msg) {
		HANDLE_MSG(hWnd, WM_INITDIALOG, CurConvertOnInitDialog);
		HANDLE_MSG(hWnd, WM_COMMAND,    CurConvertOnCommand);

	default:
		return FALSE;
	} // switch
} // CurConvert


// Обработчик сообщения WM_INITDIALOG
BOOL CurConvertOnInitDialog(HWND hWnd, HWND hWndFocus, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(hWndFocus);
	UNREFERENCED_PARAMETER(lParam);

	TCHAR szBuf[MAX_LOADSTRING];
	Convert();  // Преобразование сохраненных данных

	_stprintf(szBuf, _T("%d"), uRubles);
	SetDlgItemText(hWnd, IDC_EDRUB, szBuf);

	_stprintf(szBuf, _T("%d"), uEuros);
	SetDlgItemText(hWnd, IDC_EDEUR, szBuf);

	_stprintf(szBuf, _T("%d"), uDollars);
	SetDlgItemText(hWnd, IDC_EDUSD, szBuf);

	CheckRadioButton(hWnd, IDC_RDNORMCOURSE, IDC_RDPREFCOURSE, IDC_RDNORMCOURSE + uMode);
	return TRUE;
} // TranslateOnInitDialog


// Обработчик сообщения WM_COMMAND
void CurConvertOnCommand(HWND hWnd, int id, HWND hWndCtl, UINT codeNotify)
{
	UNREFERENCED_PARAMETER(hWndCtl);

	TCHAR szBuf[MAX_LOADSTRING];

	switch (id) {
	case IDC_EDRUB:
		GetDlgItemText(hWnd, IDC_EDNUMBER, szBuf, MAX_LOADSTRING);
		break;

	case IDC_RDNORMCOURSE:
		uMode = NORM;
		break;

	case IDC_RDPREFCOURSE:
		uMode = PREFERENTIAL;
		break;

		// Расчитать
	case IDC_DOCALC:
		// Получить строку из редактора ввода суммы в рублях
		GetDlgItemText(hWnd, IDC_EDRUB, szBuf, MAX_LOADSTRING);

		// Собственно ввод из строки в число
		_stscanf(szBuf, _T("%d"), &uRubles);

		// Преобразование в доллары, евро
		Convert();

		// Вывод результата в строки ввода для долларов, евро
		_stprintf(szBuf, _T("%d"), uDollars);
		SetDlgItemText(hWnd, IDC_EDUSD, szBuf);

		_stprintf(szBuf, _T("%d"), uEuros);
		SetDlgItemText(hWnd, IDC_EDEUR, szBuf);
		break;

	case IDOK:
	case IDCANCEL:
		EndDialog(hWnd, 0);
	} // switch
} // TranslateOnCommand


// Преобразование рублей в доллары, евро с учетом обычного
// или льготного курсов
void Convert() 
{
	if (uMode == NORM) {
		uDollars = uRubles / uCourseDollar;
		uEuros = uRubles / uCourseEuro;
	} else {
		// Льготный курс - меньше на 10%
		uDollars = (10*uRubles) / (9*uCourseDollar);
		uEuros = (10*uRubles) / (9*uCourseEuro);
	} // if
} // Convert