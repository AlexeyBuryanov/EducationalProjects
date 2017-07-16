#pragma once
#include "Includes.h"

class Price
{
	static const int LEN_GOODS = 60;
	static const int LEN_SHOP  = 60;
	wstring wsShop;		// магазин
	wstring wsGoods;	// товар
	UINT    uCost;		// стоимость

public:
	Price()
		: wsShop(_T("АТБ")), wsGoods(_T("Кока-кола")), uCost() {}
	Price(wstring wsShop, wstring wsGoods,  UINT uCost)
		: wsShop(wsShop), wsGoods(wsGoods),  uCost(uCost) {}
	Price(const Price &price)
		: wsShop(price.wsShop), wsGoods(price.wsGoods),  uCost(price.uCost) {}

	~Price() {}

	Price operator=(const Price &price);
	
	wstring getShop()const           { return wsShop; }
	void    setShop(wstring  wsShop) { this->wsShop = wsShop; }

	wstring getGoods() const   	       { return wsGoods; }
	void    setGoods(wstring  wsGoods) { this->wsGoods = wsGoods; }

	UINT getCost() const     { return uCost; }
	void setCost(UINT uCost) { this->uCost = uCost; }

	void Save(fstream &fs, bool append = false);
	void Load(fstream &fs);

	static const UINT LEN_RECORD = (LEN_SHOP * sizeof(TCHAR)) + (LEN_GOODS * sizeof(TCHAR)) + sizeof(UINT);
};

