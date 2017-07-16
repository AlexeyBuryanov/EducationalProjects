#pragma once
#include "Includes.h"

class Pizza
{
public:
	static const INT N_AMT     = 4;    // размер массива ингридиентов пиццы
	static const INT LEN_FAMIO = 150;  // размер строки для ввода фамилии, инициалов
	static const INT LEN_PHONE = 20;   // размер строки для ввода номера телефона заказчика

private:
	TCHAR szFamIO[LEN_FAMIO];		   // фамилия и инициалы
	TCHAR szPhone[LEN_PHONE];	       // телефон
	BOOL  bOptions[N_AMT];             // набор опций
	INT   nDiscount;			       // скидка

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

