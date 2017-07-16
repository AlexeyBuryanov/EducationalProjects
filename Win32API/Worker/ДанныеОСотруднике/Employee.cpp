#include "Employee.h"

// ����������� �������� ���������� - �������
extern HWND hStFamIO, hStRank, hStSkills;

// ������ �������������� ��� ������� � ��������
extern HWND hEditInitial;   

// ����������� ��� ���� ���������
extern HWND hRdButEngineer, hRdButDevelop, hRdButLeadDevelop;

// �������� ��� �������
extern HWND hChBoxC, hChBoxWinApi, hChBoxHard, hChBoxAndroid;

Employee::Employee()
{
	_tcscpy(FamIO, _T("������ �.�."));
	for (int i = 0; i < N_SKILLS; i++) Skills[i] = true;
	Rank = 0;
} // Employee::Employee


Employee::~Employee()
{
} // Employee::~Employee


// ��������� ������ �� ��������� ����������, �����
// � ������� ������ � ����������
void Employee::Show()
{
	// ������������ ������ � ��������� ��������� �� ���� ���������
	TCHAR szRank[50];
	RankToString(szRank);

	// ������������ ������ �� �������� ����������
	TCHAR szSkills[100];
	SkillsToString(szSkills);

	// ���������� �������� �������� � ������� ������
	// �������, ��� ��������
	SendMessage(hStFamIO, WM_SETTEXT, NULL, (LPARAM)FamIO);

	// ���������
	SendMessage(hStRank, WM_SETTEXT, NULL, (LPARAM)szRank);

	// ������ ����������
	SendMessage(hStSkills, WM_SETTEXT, NULL, (LPARAM)szSkills);
} // Employee::Show


// ������������� �������� ���������� �� ��������� ����� ������
void Employee::Setup()
{
	HWND hChecks[] = { hChBoxC, hChBoxWinApi, hChBoxHard, hChBoxAndroid };

	// �������, ��� ��������
	SendMessage(hEditInitial, WM_SETTEXT, NULL, (LPARAM)FamIO);

	// ���������� ���������
	HWND hRdButton = RankToHWND();
	Button_SetCheck(hRdButton, BST_CHECKED);

	// ���������� ������ �� ������� Skills
	for (INT i = 0;i < N_SKILLS; i++) {
		Button_SetCheck(hChecks[i], Skills[i] ? BST_CHECKED : BST_UNCHECKED);
	} // for i
} // Employee::Setup


void Employee::SetFamIO(TCHAR * szBuf)
{
	_tcsncpy(FamIO, szBuf, LEN_FAMIO - 1);
} // Employee::SetFamIO

// ���������� ��� ��������� � ����������� �� �������� 
// nRank - ������ ���������� �����������
void Employee::SetRank(INT nRank)
{
	Rank = nRank;
} // Employee::SetRank


// ���������� �������� ������ � �������� nSkill
// bValue - �������� TRUE ��� FALSE
void Employee::SetSkill(INT nSkill, BOOL bValue)
{
	Skills[nSkill] = bValue;
} // Employee::SetSkill


// ��������� ������ � ��������� ��������� �� �� ����
void Employee::RankToString(TCHAR *szBuf)
{
	switch (Rank) {
	case 0:
		_tcscpy(szBuf, _T("�������"));
		break;
	case 1:
		_tcscpy(szBuf, _T("�����������"));
		break;
	case 2:
		_tcscpy(szBuf, _T("������� �����������"));
		break;
	default:
		_tcscpy(szBuf, _T("����������� ��������"));
		break;
	} // switch
} // Employee::RankToString


// ��������� ������ �� ���� ������
void Employee::SkillToString(INT code, TCHAR * szBuf)
{
	switch (code) {
	case 0:
		_tcscpy(szBuf, _T("C++"));
		break;
	case 1:
		_tcscpy(szBuf, _T("WinAPI"));
		break;
	case 2:
		_tcscpy(szBuf, _T("Hardware"));
		break;
	case 3:
		_tcscpy(szBuf, _T("Android"));
		break;
	default:
		_tcscpy(szBuf, _T("����� �������"));
		break;
	} // switch
} // Employee::SkillToString


// ��������� ������ ������ �� ������� Skills
void Employee::SkillsToString(TCHAR * szBuf)
{
	TCHAR szSkill[20];
	_tcscpy(szBuf, _T("������: "));
	for (INT i = 0; i < N_SKILLS; i++) {
		if (!Skills[i]) continue;
		
		SkillToString(i, szSkill);
		_tcscat(szBuf, szSkill);

		if (i == 3) continue;
		_tcscat(szBuf, _T(", "));
	} // for i
} // Employee::SkillsToString


// ���������� ����� ����������� � ����������� �� ����
// ���������
HWND Employee::RankToHWND()
{
	switch (Rank) {
	case 0:
		return hRdButEngineer;
	case 1:
		return  hRdButDevelop;
	case 2:
		return hRdButLeadDevelop;
	} // switch
	return NULL;
} // Employee::RankToHWND
