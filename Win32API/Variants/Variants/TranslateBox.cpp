#include "Includes.h"
#include "resource.h"
#include "TranslateBox.h"

// ������ ��� ������� ���������� ������:
static UINT uNumber;   // ����� ��� ��������
static UINT uMode;     // ����� �������� - � ����� ������� ���������

//
//   �������: Translate(HWND, UINT, WPARAM, LPARAM)
//
//   ����������:  ������������ ��������� � ���������� ���� Translate.
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


// ���������� ��������� WM_INITDIALOG
BOOL TranslateOnInitDialog(HWND hWnd, HWND hWndFocus, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(hWndFocus);
	UNREFERENCED_PARAMETER(lParam);

	TCHAR szBuf[33];
	TCHAR *lpszTail; // ����� (�����) ������, ������������ � '1'
	UINT32 uMask = 0x80000000;  // 1000 0000 0000 0000 ... 0000
	ZeroMemory(szBuf, 33 * sizeof(TCHAR));

	// ������ szBuf:  0   1  2  3  4  5  6...  31   ������� ���������
	// �����:        31  30 29 28 27 26 25...   0   ������� �����
	// ���������� ������ - �������� ������ ����� ��������� �������
	// �������� �������
	for (int i = 0; i < 32; i++) {
		szBuf[i] = ((uNumber & uMask) != 0) ? '1' : '0';  // ������ ���������� ������� �����
		uMask >>= 1; // ������� � ���������� �������
	} // for i

	// ������� �������� ������� �����
	// ����� ������ ��������� ������� '1' � ���������� ������ � ���� ������
	// � ����� �������
	// ���� ������� '1' ��� (����� == 0), �� ���������� � ������ ����� ���� ������ '0'
	lpszTail = _tcschr(szBuf, '1');
	if (lpszTail == NULL) lpszTail = szBuf + 31; // ����� �������� ������� ������� '0' 

	// ��������� ��������� ��������� ���������� - 
	// 1) ����� � �������� ������� ���������
	// 2) ����������� ������ ������� ���������
	SetDlgItemText(hWnd, IDC_EDNUMBER, lpszTail);
	CheckRadioButton(hWnd, IDC_RDOCT, IDC_RDHEX, IDC_RDOCT + uMode);
	return TRUE;
} // TranslateOnInitDialog


// ���������� ��������� WM_COMMAND
void TranslateOnCommand(HWND hWnd, int id, HWND hWndCtl, UINT codeNotify)
{
	UNREFERENCED_PARAMETER(hWndCtl);

	TCHAR szBuf[120];   // ��������� �����
	TCHAR szFmt[10];    // ������ ������
	TCHAR c;            // �����. ����������
	INT32 nLen;         // ����� ������ �����

	switch (id) {
		// ��� ������ ����� ����� ����������� ����������� - ��������, �� ��������� ������
		// �����. ��� ����������� - � ��������� codeNotufy
	case IDC_EDNUMBER:
		// �� ��������� ������ ����� -- ��������� ��������� ��������� ������
		// ���� ��� �� 1, �� 0 � �� ������, �� ������� ���� ������
		if (codeNotify == EN_CHANGE) {
			SendDlgItemMessage(hWnd, IDC_EDNUMBER, WM_GETTEXT, 120, (LPARAM)szBuf);
			// �������� ������ ����� � ������-���������
			// SendDlgItemMessage(hWnd, IDC_EDNUMBER, EM_GETSEL, (WPARAM)&nLen, NULL);
			nLen = _tcslen(szBuf);
			if (nLen == 0) break;  // �� ������������ ������ ������

			c = szBuf[nLen - 1];
			if (c != '1' && c != '0'/* && c != ' '*/) szBuf[nLen - 1] = '\0';
			SendDlgItemMessage(hWnd, IDC_EDNUMBER, WM_SETTEXT, 0, (LPARAM)szBuf);

			// ����������� ������� ����� � ��������� ������ ������
			// EM_SETSEL - ����������� ������� �����
			// (WPARAM), (LPARAM) - ���� � �� �� ������ - ������� �����
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

		// �������������� � ��������� ������� ���������
	case IDC_DOTRANSLATE:
		// ��������� ����� (������ 0 � 1) �� ������ ����� �������� ������ 
		// � ����������� ��� � �������� ������
		// 1010101
		// 7 ������� => ��� ������� ����� 2^(7-1)
		// uNumber += 2^(Len - i - 1)
		SendDlgItemMessage(hWnd, IDC_EDNUMBER, WM_GETTEXT, 120, (LPARAM)szBuf);
		uNumber = 0;
		nLen = _tcslen(szBuf);
		for (int i = 0; i < nLen; i++) {
			//         (2  ^ (nLen - i - 1))
			uNumber += (1 << (nLen - i - 1)) * (szBuf[i] - '0');
		} // for i

		// ����� ���������� � �������� ������� ���������
		// ���������� ������ ������� ������ � �����������  
		// �� ��������� ������� ����������
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

		  // ������������ ������ ���������� � ������� �� � ��������������� edit
		_stprintf(szBuf, szFmt, uNumber);
		SendDlgItemMessage(hWnd, IDC_EDRESULT, WM_SETTEXT, 0, (LPARAM)szBuf);
		break;

	case IDOK:
	case IDCANCEL:
		EndDialog(hWnd, 0);
	} // switch
} // TranslateOnCommand