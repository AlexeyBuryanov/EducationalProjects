#pragma once
#include "WinMain.h"

class TicTacToe {
	TCHAR Map[3][3]; // игровое поле

public:
	TicTacToe();

	TCHAR getMap(int i, int j) 
	{
		if (i < 0 || i >= 3 || j < 0 || j >= 3) return ' ';
		return Map[i][j];
	} // getMap

	void Fill(int nRow, int nCol, int nEventID);
	bool isFinish();
	TCHAR getWinner();

	void Clear();
};