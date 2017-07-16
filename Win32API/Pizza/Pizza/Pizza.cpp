#include "Pizza.h"

// Статические элементы управления - надписи
/*          ФИО        номер т.     скидка      опции   */
extern HWND hStFamIO, hStPNumber, hStDiscount, hStOptions;

// Строки редактирования для инициалов и номера телефона
extern HWND hEditInitial, hEditPhone;

// Радиокнопки для скидки
extern HWND hRdBut0, hRdBut5, hRdBut15;

// Флажки для компонентов пиццы
/*            сыр          оливки       грибы        колбаса    */
extern HWND hChBoxCheese, hChBoxOlive, hChBoxFungi, hChBoxSausage;


Pizza::Pizza()
{
	_tcscpy(szFamIO, _T("Пупкин В.М."));
	_tcscpy(szPhone, _T("+38099322223"));
	for (int i = 0; i < N_AMT; i++) bOptions[i] = true;
	nDiscount = 0;
} // Pizza::Pizza


Pizza::~Pizza()
{
} // Pizza::~Pizza


// Получение данных из элементов управления, вывод
// в область заказа
void Pizza::Show()
{
	// Сформировать строку со скидкой по коду скидки
	TCHAR szDiscount[20];
	DiscountToString(szDiscount);

	// Сформировать строку с опциями заказанной пиццы
	TCHAR szOptions[150];
	OptionsToString(szOptions);

	// Установить значения надписей в области заказа
	// Фамилия, имя отчество
	SendMessage(hStFamIO, WM_SETTEXT, NULL, (LPARAM)szFamIO);

	// Номер телефона
	SendMessage(hStPNumber, WM_SETTEXT, NULL, (LPARAM)szPhone);

	// Скидка
	SendMessage(hStDiscount, WM_SETTEXT, NULL, (LPARAM)szDiscount);

	// Опции пиццы заказчика
	SendMessage(hStOptions, WM_SETTEXT, NULL, (LPARAM)szOptions);
} // Pizza::Show


// Устанавливает элементы управления по значениям полей класса
void Pizza::Setup()
{
	HWND hChecks[] = { hChBoxCheese, hChBoxOlive, hChBoxFungi, hChBoxSausage };

	// Фамилия, имя отчество
	SendMessage(hEditInitial, WM_SETTEXT, NULL, (LPARAM)szFamIO);

	// Номер телефона
	SendMessage(hEditPhone, WM_SETTEXT, NULL, (LPARAM)szPhone);

	// Установить скидку
	HWND hRdButton = DiscountToHWND();
	Button_SetCheck(hRdButton, BST_CHECKED);

	// Установить опции пиццы по массиву bOptions
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


// Установить код скидки в зависимости от значения 
// nDiscount - номера отмеченной радиокнопки
void Pizza::SetDiscount(INT nDiscnt)
{
	this->nDiscount = nDiscnt;
} // Pizza::SetDiscount


// Установить значение ингридиентов с индексом nOption
// bValue - значение TRUE или FALSE
void Pizza::SetOption(INT nOption, BOOL bValue)
{
	bOptions[nOption] = bValue;
} // Pizza::SetOption


// Формирует строку со скидкой по ее коду
void Pizza::DiscountToString(TCHAR *szBuf)
{
	switch (nDiscount) {
	case 0:
		_tcscpy(szBuf, _T("0% скидка"));
		break;
	case 1:
		_tcscpy(szBuf, _T("5% скидка"));
		break;
	case 2:
		_tcscpy(szBuf, _T("15% скидка"));
		break;
	default:
		_tcscpy(szBuf, _T("Бесплатно"));
		break;
	} // switch
} // Pizza::DiscountToString


// Формирует строку из кода опций (компонентов) пиццы
void Pizza::OptionToString(INT code, TCHAR * szBuf)
{
	switch (code) {
	case 0:
		_tcscpy(szBuf, _T("Сыр"));
		break;
	case 1:
		_tcscpy(szBuf, _T("Оливки"));
		break;
	case 2:
		_tcscpy(szBuf, _T("Грибы"));
		break;
	case 3:
		_tcscpy(szBuf, _T("Колбаса"));
		break;
	default:
		_tcscpy(szBuf, _T("Тесто"));
		break;
	} // switch
} // Pizza::OptionToString


// Формирует строку опций из массива bOptions
void Pizza::OptionsToString(TCHAR * szBuf)
{
	TCHAR szSkill[20];
	_tcscpy(szBuf, _T("Опции: "));
	for (INT i = 0; i < N_AMT; i++) {
		if (!bOptions[i]) continue;
		
		OptionToString(i, szSkill);
		_tcscat(szBuf, szSkill);

		if (i == 3) continue;
		_tcscat(szBuf, _T(", "));
	} // for i
} // Pizza::OptionsToString


// Возвращает хэндл радиокнопки в зависимости от кода скидки
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
