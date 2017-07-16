#include "Includes.h"
#include "resource.h"
#include "TranslateBox.h"

// Данные для решения прикладной задачи:
static UINT uNumber;   // Число для перевода
static UINT uMode;     // Режим перевода - в какую систему счисления

//
//   ФУНКЦИЯ: Translate(HWND, UINT, WPARAM, LPARAM)
//
//   НАЗНАЧЕНИЕ:  обрабатывает сообщения в диалоговом окне Translate.
//
BOOL CALLBACK Translate(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	switch (msg) {
		HANDLE_MSG(hWnd, WM_INITDIALOG, TranslateOnInitDialog);
		HANDLE_MSG(hWnd, WM_COMMAND,    TranslateOnCommand);

	default:
		return FALSE;
	} // switch
} // Translate


// Обработчик сообщения WM_INITDIALOG
BOOL TranslateOnInitDialog(HWND hWnd, HWND hWndFocus, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(hWndFocus);
	UNREFERENCED_PARAMETER(lParam);

	TCHAR szBuf[33];
	TCHAR *lpszTail; // часть (хвост) строки, начинающаяся с '1'
	UINT32 uMask = 0x80000000;  // 1000 0000 0000 0000 ... 0000
	ZeroMemory(szBuf, 33 * sizeof(TCHAR));

	// Массив szBuf:  0   1  2  3  4  5  6...  31   индексы элементов
	// Число:        31  30 29 28 27 26 25...   0   разряды числа
	// Построение строки - битового образа числа выполняем начиная
	// старшего разряда
	for (int i = 0; i < 32; i++) {
		szBuf[i] = ((uNumber & uMask) != 0) ? '1' : '0';  // Анализ очередного разряда числа
		uMask >>= 1; // Переход к следующему разряду
	} // for i

	// Решение проблемы ведущих нулей
	// Найти первое вхождение символа '1' и копировать строку в поле вывода
	// с этого символа
	// Если символа '1' нет (число == 0), то копировать в строку ввода один символ '0'
	lpszTail = _tcschr(szBuf, '1');
	if (lpszTail == NULL) lpszTail = szBuf + 31; // адрес крайнего правого символа '0' 

	// Начальное состояние элементов управления - 
	// 1) число в двоичной системе счисления
	// 2) радиокнопки выбора системы счисления
	SetDlgItemText(hWnd, IDC_EDNUMBER, lpszTail);
	CheckRadioButton(hWnd, IDC_RDOCT, IDC_RDHEX, IDC_RDOCT + uMode);
	return TRUE;
} // TranslateOnInitDialog


// Обработчик сообщения WM_COMMAND
void TranslateOnCommand(HWND hWnd, int id, HWND hWndCtl, UINT codeNotify)
{
	UNREFERENCED_PARAMETER(hWndCtl);

	TCHAR szBuf[120];   // строковый буфер
	TCHAR szFmt[10];    // формат вывода
	TCHAR c;            // вспом. переменная
	INT32 nLen;         // длина строки ввода

	switch (id) {
		// Для строки ввода можно перехватить уведомления - например, об изменении строки
		// ввода. Код уведомления - в параметре codeNotufy
	case IDC_EDNUMBER:
		// По изменению строки ввода -- проверить послелний введенный символ
		// Если это не 1, не 0 и не пробел, то стереть этот символ
		if (codeNotify == EN_CHANGE) {
			SendDlgItemMessage(hWnd, IDC_EDNUMBER, WM_GETTEXT, 120, (LPARAM)szBuf);
			// Получить позцию ввода в строке-редакторе
			// SendDlgItemMessage(hWnd, IDC_EDNUMBER, EM_GETSEL, (WPARAM)&nLen, NULL);
			nLen = _tcslen(szBuf);
			if (nLen == 0) break;  // не обрабатывать пустую строку

			c = szBuf[nLen - 1];
			if (c != '1' && c != '0'/* && c != ' '*/) szBuf[nLen - 1] = '\0';
			SendDlgItemMessage(hWnd, IDC_EDNUMBER, WM_SETTEXT, 0, (LPARAM)szBuf);

			// Перемещение каретки ввода в указанную позцию строки
			// EM_SETSEL - перемещение картеки ввода
			// (WPARAM), (LPARAM) - одно и то же читсло - позиция ввода
			SendDlgItemMessage(hWnd, IDC_EDNUMBER, EM_SETSEL, (WPARAM)nLen, (LPARAM)nLen);
		} // if
		break;

	case IDC_RDOCT:
		uMode = OCTAL;
		break;

	case IDC_RDDEC:
		uMode = DEC;
		break;

	case IDC_RDHEX:
		uMode = HEXADECIMAL;
		break;

		// Преобразование в выбранную систему счисления
	case IDC_DOTRANSLATE:
		// Сохраняем число (строку 0 и 1) из строки ввода исходных данных 
		// и преобразуем его в машинный формат
		// 1010101
		// 7 позиций => вес старшей цифры 2^(7-1)
		// uNumber += 2^(Len - i - 1)
		SendDlgItemMessage(hWnd, IDC_EDNUMBER, WM_GETTEXT, 120, (LPARAM)szBuf);
		uNumber = 0;
		nLen = _tcslen(szBuf);
		for (int i = 0; i < nLen; i++) {
			//         (2  ^ (nLen - i - 1))
			uNumber += (1 << (nLen - i - 1)) * (szBuf[i] - '0');
		} // for i

		// Вывод результата в заданной системе счисления
		// Определить строку формата вывода в зависимости  
		// от выбранной системы счисленеия
		switch (uMode) {
		case OCTAL:
			_tcscpy(szFmt, _T("%o"));
			break;

		case DEC:
			_tcscpy(szFmt, _T("%d"));
			break;

		case HEXADECIMAL:
			_tcscpy(szFmt, _T("%x"));
			break;
		} // switch

		  // Сформировать строку результата и вывести ее в соответствуюший edit
		_stprintf(szBuf, szFmt, uNumber);
		SendDlgItemMessage(hWnd, IDC_EDRESULT, WM_SETTEXT, 0, (LPARAM)szBuf);
		break;

	case IDOK:
	case IDCANCEL:
		EndDialog(hWnd, 0);
	} // switch
} // TranslateOnCommand