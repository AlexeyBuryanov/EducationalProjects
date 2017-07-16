#pragma once
#include "Includes.h"
#include "Price.h"

#define SORT_WIDTH   310   /* ������ ���� */
#define SORT_HEIGHT  340   /* ������ ���� */
#define SORT_BACKGROUND  RGB(0xFF, 0xFF, 0xFF)

#define IDC_SORT_CANCEL    10100
#define IDC_SORT_OK        10101

// ����������� ������� ���������� 
#define IDC_SORT_RDBTNNMSHOP  10500
#define IDC_SORT_RDBTNGOODS   10501
#define IDC_SORT_RDBTNCOST    10502
#define IDC_SORT_RDBTNNATIV   10503

LRESULT CALLBACK Sort_WndProc(HWND, UINT, WPARAM, LPARAM);

BOOL   Sort_OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct);
void   Sort_OnCommand(HWND hWnd, INT id, HWND hWndCtl, UINT codeNotify);
void   Sort_OnSize(HWND hWnd, UINT state, INT cx, INT cy);
void   Sort_OnGetMinMaxInfo(HWND hwnd, LPMINMAXINFO lpMinMaxInfo);
void   Sort_OnClose(HWND hWnd);
void   Sort_OnDestroy(HWND hWnd);
HBRUSH Sort_OnCtlColorStatic(HWND, HDC hDC, HWND, INT);


//////////////////// �������� ��� ��������� ���������� ////////////////////////////
//
// ������� - �����, ���������� ������ ������� (���� �������) 

// ���������� �� �������� ��������� - �� ��������
struct CmpShop
{
	// ������������� ���������� ����� � ����� C - _tcscmp(s1, s2)
	// xxxx.c_str() - �������� ������ � ����� C
	// s1 <  s2 --> nResult = -1
	// s1 == s2 --> nResult =  0
	// s1 >  s2 --> nResult =  1
	bool operator() (const Price &obj1, const Price &obj2) {
		int nResult = _tcscmp(obj1.getShop().c_str(), obj2.getShop().c_str());
		return nResult < 0;
	} // operator
};


// ���������� �� �������� ������� - �� ��������
struct CmpGoods
{
	// ������ �� �������� � ���������� �������, �� ���������
	bool operator() (const Price &obj1, const Price &obj2) {
		return _tcscmp(obj1.getGoods().c_str(), obj2.getGoods().c_str()) < 0;
	}
}; // cmpGoods


// ���������� �� �������� ����
struct CmpPrice
{
	bool operator() (const Price &obj1, const Price &obj2) {
		return obj1.getCost() < obj2.getCost();
	}
}; // cmpPrice