#include "Price.h"
#include "InputWindow.h"

Price Price::operator=(const Price &price)
{
	// �������� �� ����������������
	if (this == &price) {
		return *this;
	} // if

	wsGoods = price.wsGoods;
	wsShop  = price.wsShop;
	uCost   = price.uCost;

	return *this;
} // operator=


// ���������� ����� ������ ������� � �������� ������
// (�������� ������������)
void Price::Save(fstream &fs, bool append)
{
	if (append) fs.seekp(0, ios::end);

	// ����� ������
	TCHAR *szBuf1 = new TCHAR[LEN_SHOP];
	TCHAR *szBuf2 = new TCHAR[LEN_GOODS];

	// ������� ������ �� �������� ��������
	ZeroMemory(szBuf1, LEN_SHOP * sizeof(TCHAR));
	ZeroMemory(szBuf2, LEN_GOODS * sizeof(TCHAR));

	// �������� ������ � ������ ������
	_tcscpy(szBuf1, wsShop.c_str());
	_tcscpy(szBuf2, wsGoods.c_str());

	fs.write((char *)szBuf1, LEN_GOODS * sizeof(TCHAR));
	fs.write((char *)szBuf2, LEN_SHOP * sizeof(TCHAR));
	fs.write((char *)&uCost, sizeof(UINT));

	delete[] szBuf1;
	delete[] szBuf2;
} // Price::Save


// �������� ����� ������ ������� �� ��������� ������
// (�������� ��������������)
void Price::Load(fstream &fs)
{
	// ����� �����
	TCHAR *szBuf1 = new TCHAR[LEN_SHOP];
	TCHAR *szBuf2 = new TCHAR[LEN_GOODS];

	// ������� ������ �� �������� ��������
	ZeroMemory(szBuf1, LEN_SHOP * sizeof(TCHAR));
	ZeroMemory(szBuf2, LEN_GOODS * sizeof(TCHAR));

	fs.read((char *)szBuf1, LEN_SHOP * sizeof(TCHAR));
	fs.read((char *)szBuf2, LEN_GOODS * sizeof(TCHAR));
	fs.read((char *)&uCost, sizeof(UINT));

	// ���������� ����� ����� � ������ �������� TCHAR
	wsShop.assign(szBuf1);
	wsGoods.assign(szBuf2);

	delete[] szBuf1;
	delete[] szBuf2;
} // Price::Load
