#include "Pizza.h"

// ����������� �������� ���������� - �������
/*          ���        ����� �.     ������      �����   */
extern HWND hStFamIO, hStPNumber, hStDiscount, hStOptions;

// ������ �������������� ��� ��������� � ������ ��������
extern HWND hEditInitial, hEditPhone;

// ����������� ��� ������
extern HWND hRdBut0, hRdBut5, hRdBut15;

// ������ ��� ����������� �����
/*            ���          ������       �����        �������    */
extern HWND hChBoxCheese, hChBoxOlive, hChBoxFungi, hChBoxSausage;


Pizza::Pizza()
{
	_tcscpy(szFamIO, _T("������ �.�."));
	_tcscpy(szPhone, _T("+38099322223"));
	for (int i = 0; i < N_AMT; i++) bOptions[i] = true;
	nDiscount = 0;
} // Pizza::Pizza


Pizza::~Pizza()
{
} // Pizza::~Pizza


// ��������� ������ �� ��������� ����������, �����
// � ������� ������
void Pizza::Show()
{
	// ������������ ������ �� ������� �� ���� ������
	TCHAR szDiscount[20];
	DiscountToString(szDiscount);

	// ������������ ������ � ������� ���������� �����
	TCHAR szOptions[150];
	OptionsToString(szOptions);

	// ���������� �������� �������� � ������� ������
	// �������, ��� ��������
	SendMessage(hStFamIO, WM_SETTEXT, NULL, (LPARAM)szFamIO);

	// ����� ��������
	SendMessage(hStPNumber, WM_SETTEXT, NULL, (LPARAM)szPhone);

	// ������
	SendMessage(hStDiscount, WM_SETTEXT, NULL, (LPARAM)szDiscount);

	// ����� ����� ���������
	SendMessage(hStOptions, WM_SETTEXT, NULL, (LPARAM)szOptions);
} // Pizza::Show


// ������������� �������� ���������� �� ��������� ����� ������
void Pizza::Setup()
{
	HWND hChecks[] = { hChBoxCheese, hChBoxOlive, hChBoxFungi, hChBoxSausage };

	// �������, ��� ��������
	SendMessage(hEditInitial, WM_SETTEXT, NULL, (LPARAM)szFamIO);

	// ����� ��������
	SendMessage(hEditPhone, WM_SETTEXT, NULL, (LPARAM)szPhone);

	// ���������� ������
	HWND hRdButton = DiscountToHWND();
	Button_SetCheck(hRdButton, BST_CHECKED);

	// ���������� ����� ����� �� ������� bOptions
	for (INT i = 0;i < N_AMT; i++) {
		Button_SetCheck(hChecks[i], bOptions[i] ? BST_CHECKED : BST_UNCHECKED);
	} // for i
} // Pizza::Setup


void Pizza::SetFamIO(TCHAR * szBuf)
{
	_tcsncpy(szFamIO, szBuf, LEN_FAMIO - 1);
} // Pizza::SetFamIO


void Pizza::SetPhone(TCHAR *szBuf)
{
	_tcsncpy(szPhone, szBuf, LEN_PHONE - 1);
} // Pizza::SetPhone


// ���������� ��� ������ � ����������� �� �������� 
// nDiscount - ������ ���������� �����������
void Pizza::SetDiscount(INT nDiscnt)
{
	this->nDiscount = nDiscnt;
} // Pizza::SetDiscount


// ���������� �������� ������������ � �������� nOption
// bValue - �������� TRUE ��� FALSE
void Pizza::SetOption(INT nOption, BOOL bValue)
{
	bOptions[nOption] = bValue;
} // Pizza::SetOption


// ��������� ������ �� ������� �� �� ����
void Pizza::DiscountToString(TCHAR *szBuf)
{
	switch (nDiscount) {
	case 0:
		_tcscpy(szBuf, _T("0% ������"));
		break;
	case 1:
		_tcscpy(szBuf, _T("5% ������"));
		break;
	case 2:
		_tcscpy(szBuf, _T("15% ������"));
		break;
	default:
		_tcscpy(szBuf, _T("���������"));
		break;
	} // switch
} // Pizza::DiscountToString


// ��������� ������ �� ���� ����� (�����������) �����
void Pizza::OptionToString(INT code, TCHAR * szBuf)
{
	switch (code) {
	case 0:
		_tcscpy(szBuf, _T("���"));
		break;
	case 1:
		_tcscpy(szBuf, _T("������"));
		break;
	case 2:
		_tcscpy(szBuf, _T("�����"));
		break;
	case 3:
		_tcscpy(szBuf, _T("�������"));
		break;
	default:
		_tcscpy(szBuf, _T("�����"));
		break;
	} // switch
} // Pizza::OptionToString


// ��������� ������ ����� �� ������� bOptions
void Pizza::OptionsToString(TCHAR * szBuf)
{
	TCHAR szSkill[20];
	_tcscpy(szBuf, _T("�����: "));
	for (INT i = 0; i < N_AMT; i++) {
		if (!bOptions[i]) continue;
		
		OptionToString(i, szSkill);
		_tcscat(szBuf, szSkill);

		if (i == 3) continue;
		_tcscat(szBuf, _T(", "));
	} // for i
} // Pizza::OptionsToString


// ���������� ����� ����������� � ����������� �� ���� ������
HWND Pizza::DiscountToHWND()
{
	switch (nDiscount) {
	case 0:
		return hRdBut0;
	case 1:
		return hRdBut5;
	case 2:
		return hRdBut15;
	} // switch
	return NULL;
} // Pizza::DiscountToHWND
