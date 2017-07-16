#pragma once
#include "Includes.h"

class Employee
{
public:
	static const int N_SKILLS = 4;    // ������ ������� �������
	static const int LEN_FAMIO = 150; // ������ ������ ��� ����� �������, ���������

private:
	TCHAR FamIO[LEN_FAMIO];	// ������� � ��������
	BOOL  Skills[N_SKILLS];	// ������
	INT   Rank;			    // ���������

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

