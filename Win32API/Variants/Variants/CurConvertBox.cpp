#include "Includes.h"
#include "resource.h"
#include "CurConvertBox.h"

// ������ ��� ������� ���������� ������:
static UINT uRubles;    // ����� � ������ ��� �����������
static UINT uEuros;     // ����� � ����
static UINT uDollars;   // ����� � ��������
static UINT uMode;      // ����� - ���� �������, ��������
// �������� ���� - �� 10% ������

// ���� ���� � �����
static UINT uCourseEuro = 78;
// ���� ������� � �����
static UINT uCourseDollar = 70;

//
//   �������: CurConvert(HWND, UINT, WPARAM, LPARAM)
//
//   ����������:  ������������ ��������� � ���������� ���� CurConvert.
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


// ���������� ��������� WM_INITDIALOG
BOOL CurConvertOnInitDialog(HWND hWnd, HWND hWndFocus, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(hWndFocus);
	UNREFERENCED_PARAMETER(lParam);

	TCHAR szBuf[MAX_LOADSTRING];
	Convert();  // �������������� ����������� ������

	_stprintf(szBuf, _T("%d"), uRubles);
	SetDlgItemText(hWnd, IDC_EDRUB, szBuf);

	_stprintf(szBuf, _T("%d"), uEuros);
	SetDlgItemText(hWnd, IDC_EDEUR, szBuf);

	_stprintf(szBuf, _T("%d"), uDollars);
	SetDlgItemText(hWnd, IDC_EDUSD, szBuf);

	CheckRadioButton(hWnd, IDC_RDNORMCOURSE, IDC_RDPREFCOURSE, IDC_RDNORMCOURSE + uMode);
	return TRUE;
} // TranslateOnInitDialog


// ���������� ��������� WM_COMMAND
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

		// ���������
	case IDC_DOCALC:
		// �������� ������ �� ��������� ����� ����� � ������
		GetDlgItemText(hWnd, IDC_EDRUB, szBuf, MAX_LOADSTRING);

		// ���������� ���� �� ������ � �����
		_stscanf(szBuf, _T("%d"), &uRubles);

		// �������������� � �������, ����
		Convert();

		// ����� ���������� � ������ ����� ��� ��������, ����
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


// �������������� ������ � �������, ���� � ������ ��������
// ��� ��������� ������
void Convert() 
{
	if (uMode == NORM) {
		uDollars = uRubles / uCourseDollar;
		uEuros = uRubles / uCourseEuro;
	} else {
		// �������� ���� - ������ �� 10%
		uDollars = (10*uRubles) / (9*uCourseDollar);
		uEuros = (10*uRubles) / (9*uCourseEuro);
	} // if
} // Convert