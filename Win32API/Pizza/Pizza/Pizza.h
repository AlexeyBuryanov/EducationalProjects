#pragma once
#include "Includes.h"

class Pizza
{
public:
	static const INT N_AMT     = 4;    // ������ ������� ������������ �����
	static const INT LEN_FAMIO = 150;  // ������ ������ ��� ����� �������, ���������
	static const INT LEN_PHONE = 20;   // ������ ������ ��� ����� ������ �������� ���������

private:
	TCHAR szFamIO[LEN_FAMIO];		   // ������� � ��������
	TCHAR szPhone[LEN_PHONE];	       // �������
	BOOL  bOptions[N_AMT];             // ����� �����
	INT   nDiscount;			       // ������

	void DiscountToString(TCHAR *szBuf);
	void OptionToString(INT code, TCHAR *szBuf);
	void OptionsToString(TCHAR *szBuf);

	HWND DiscountToHWND();

public:
	Pizza();
	~Pizza();

	void Show();
	void Setup();

	void SetFamIO(TCHAR *szBuf);
	void SetPhone(TCHAR *szBuf);
	void SetDiscount(INT nDiscnt);
	void SetOption(INT nOption, BOOL bValue);
};

