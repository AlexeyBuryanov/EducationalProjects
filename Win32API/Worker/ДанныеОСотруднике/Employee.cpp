#include "Employee.h"

// Статические элементы управления - надписи
extern HWND hStFamIO, hStRank, hStSkills;

// строка редактирования для фамилии и иницалов
extern HWND hEditInitial;   

// Радиокнопки для кода должности
extern HWND hRdButEngineer, hRdButDevelop, hRdButLeadDevelop;

// Чекбоксы для навыков
extern HWND hChBoxC, hChBoxWinApi, hChBoxHard, hChBoxAndroid;

Employee::Employee()
{
	_tcscpy(FamIO, _T("Пупкин В.М."));
	for (int i = 0; i < N_SKILLS; i++) Skills[i] = true;
	Rank = 0;
} // Employee::Employee


Employee::~Employee()
{
} // Employee::~Employee


// Получение данных из элементов управления, вывод
// в область отчета о сотруднике
void Employee::Show()
{
	// Сформировать строку с названием должности по коду должности
	TCHAR szRank[50];
	RankToString(szRank);

	// Сформировать строку со знаниями сотрудника
	TCHAR szSkills[100];
	SkillsToString(szSkills);

	// Установить значения надписей в области отчета
	// Фамилия, имя отчество
	SendMessage(hStFamIO, WM_SETTEXT, NULL, (LPARAM)FamIO);

	// Должность
	SendMessage(hStRank, WM_SETTEXT, NULL, (LPARAM)szRank);

	// Знания сотрудника
	SendMessage(hStSkills, WM_SETTEXT, NULL, (LPARAM)szSkills);
} // Employee::Show


// Устанавливает элементы управления по значениям полей класса
void Employee::Setup()
{
	HWND hChecks[] = { hChBoxC, hChBoxWinApi, hChBoxHard, hChBoxAndroid };

	// Фамилия, имя отчество
	SendMessage(hEditInitial, WM_SETTEXT, NULL, (LPARAM)FamIO);

	// Установить должность
	HWND hRdButton = RankToHWND();
	Button_SetCheck(hRdButton, BST_CHECKED);

	// Установить знания по массиву Skills
	for (INT i = 0;i < N_SKILLS; i++) {
		Button_SetCheck(hChecks[i], Skills[i] ? BST_CHECKED : BST_UNCHECKED);
	} // for i
} // Employee::Setup


void Employee::SetFamIO(TCHAR * szBuf)
{
	_tcsncpy(FamIO, szBuf, LEN_FAMIO - 1);
} // Employee::SetFamIO

// Установить код должности в зависимости от значения 
// nRank - номера отмеченной радиокнопки
void Employee::SetRank(INT nRank)
{
	Rank = nRank;
} // Employee::SetRank


// Установить значение знания с индексом nSkill
// bValue - значение TRUE или FALSE
void Employee::SetSkill(INT nSkill, BOOL bValue)
{
	Skills[nSkill] = bValue;
} // Employee::SetSkill


// Формирует строку с названием должности по ее коду
void Employee::RankToString(TCHAR *szBuf)
{
	switch (Rank) {
	case 0:
		_tcscpy(szBuf, _T("Инженер"));
		break;
	case 1:
		_tcscpy(szBuf, _T("Программист"));
		break;
	case 2:
		_tcscpy(szBuf, _T("Старший программист"));
		break;
	default:
		_tcscpy(szBuf, _T("Эффективный менеджер"));
		break;
	} // switch
} // Employee::RankToString


// Формирует строку из кода знания
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
		_tcscpy(szBuf, _T("жарка яичницы"));
		break;
	} // switch
} // Employee::SkillToString


// Формирует строку знаний из массива Skills
void Employee::SkillsToString(TCHAR * szBuf)
{
	TCHAR szSkill[20];
	_tcscpy(szBuf, _T("Знания: "));
	for (INT i = 0; i < N_SKILLS; i++) {
		if (!Skills[i]) continue;
		
		SkillToString(i, szSkill);
		_tcscat(szBuf, szSkill);

		if (i == 3) continue;
		_tcscat(szBuf, _T(", "));
	} // for i
} // Employee::SkillsToString


// Возвращает хэндл радиокнопки в зависимости от кода
// должности
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
