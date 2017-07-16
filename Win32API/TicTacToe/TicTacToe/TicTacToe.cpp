#include "WinMain.h"
#include "MainWindow.h"
#include "TicTacToe.h"

TicTacToe::TicTacToe() {
	Clear();
} // TicTacToe


// Изменение в Map, вывод крестика или нолика в экранном отображении игрового поля
// Параметры:
// nRow     - строка в игровом поле
// nCol     - столбец в игровом поле
// nEventID - код события, щелчок ЛКМ или щелчок ПКМ
void TicTacToe::Fill(int nRow, int nCol, int nEventID)
{
	// Запрет записи в занятую ячейку игрового поля
	if (Map[nRow][nCol] != ' ') return;

	if (nEventID == EVENT_LEFT) {
		Map[nRow][nCol] = 'X';
	}
	else if (nEventID == EVENT_RIGHT) {
		Map[nRow][nCol] = 'O';
	} // if
} // TicTacToe::Fill


// Возврат true, если есть строка или столбец или диагональ
// заполненные одним и тем же символом
bool TicTacToe::isFinish()
{
	// Счетчик занятых ячеек игрового поля
	int nOccuped = 0;

	// Проверка на заполнение всего поля
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (Map[i][j] != ' ') nOccuped++;
		} // for j
	} // for i
	if (nOccuped == 9) return true;

	// Проверка строк на заполнение одинаковыми символами
	for (int i = 0; i < 3; i++) {
		// Пропускаем строки, у которых первая ячейка не заполнена
		if (Map[i][0] == ' ') continue;
		nOccuped = 1;
		for (int j = 1; j < 3; j++) {
			if (Map[i][j] == Map[i][0]) nOccuped++;
		} // for j
		if (nOccuped == 3) return true;
	} // for i

	// Проверка столбцов на заполнение одинаковыми символами
	for (int j = 0; j < 3; j++) {
		// Пропускаем столбцы, у которых первая ячейка не заполнена
		if (Map[0][j] == ' ') continue;
		nOccuped = 1;
		for (int i = 1; i < 3; i++) {
			if (Map[i][j] == Map[0][j]) nOccuped++;
		} // for i
		if (nOccuped == 3) return true;
	} // for j

	// Проверка главной диагонали
	nOccuped = 1;
	for (int i = 1; i < 3; i++) {
		if (Map[i][i] == Map[0][0] && Map[0][0] != ' ') nOccuped++;
	} // for i
	if (nOccuped == 3) return true;

	// Проверка побочной диагонали
	nOccuped = 1;
	for (int i = 1; i < 3; i++) {
		if (Map[i][2 - i] == Map[0][2] && Map[0][2] != ' ') nOccuped++;
	} // for i
	if (nOccuped == 3) return true;

	return false;
} // TicTacToe::isFinish


// Возвращаем символ - признак победителя - X или O
// Если ничья, то возвращаем пробел
TCHAR TicTacToe::getWinner()
{
	// Счетчик занятых ячеек
	int nOccuped;

	// Проверка строк на заполнение одинаковыми символами
	for (int i = 0; i < 3; i++) {
		// Пропускаем строки, у которых первая ячейка не заполнена
		if (Map[i][0] == ' ') continue;
		nOccuped = 1;
		for (int j = 1; j < 3; j++) {
			if (Map[i][j] == Map[i][0]) nOccuped++;
		} // for j
		if (nOccuped == 3) return Map[i][0];
	} // for i

	// Проверка столбцов на заполнение одинаковыми символами
	for (int j = 0; j < 3; j++) {
		// Пропускаем столбцы, у которых первая ячейка не заполнена
		if (Map[0][j] == ' ') continue;
		nOccuped = 1;
		for (int i = 1; i < 3; i++) {
			if (Map[i][j] == Map[0][j]) nOccuped++;
		} // for i
		if (nOccuped == 3) return Map[0][j];
	} // for j

	// Проверка главной диагонали
	nOccuped = 1;
	for (int i = 1; i < 3; i++) {
		if (Map[i][i] == Map[0][0] && Map[0][0] != ' ') nOccuped++;
	} // for i
	if (nOccuped == 3) return Map[0][0];

	// Проверка побочной диагонали
	nOccuped = 1;
	for (int i = 1; i < 3; i++) {
		if (Map[i][2 - i] == Map[0][2] && Map[0][2] != ' ') nOccuped++;
	} // for i
	if (nOccuped == 3) return Map[0][2];

	return ' ';
} // TicTacToe::getWinner


// Очистка игрового поля
void TicTacToe::Clear()
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			Map[i][j] = _T(' ');
} // TicTacToe::Clear
