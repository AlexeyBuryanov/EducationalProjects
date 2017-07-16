#pragma once
#include "Includes.h"

class Employee
{
public:
	static const int N_SKILLS = 4;    // размер массива навыков
	static const int LEN_FAMIO = 150; // размер строки для ввода фамилии, инициалов

private:
	TCHAR FamIO[LEN_FAMIO];	// фамилия и инициалы
	BOOL  Skills[N_SKILLS];	// навыки
	INT   Rank;			    // должность

	void RankToString(TCHAR *szBuf);
	void SkillToString(INT code, TCHAR *szBuf);
	void SkillsToString(TCHAR *szBuf);

	HWND RankToHWND();

public:
	Employee();
	~Employee();

	void Show();
	void Setup();

	void SetFamIO(TCHAR *szBuf);
	void SetRank(INT nRank);
	void SetSkill(INT nSkill, BOOL bValue);
};

