#include "WinMain.h"
#include "MainWindow.h"
#include "TicTacToe.h"

TicTacToe::TicTacToe() {
	Clear();
} // TicTacToe


// ��������� � Map, ����� �������� ��� ������ � �������� ����������� �������� ����
// ���������:
// nRow     - ������ � ������� ����
// nCol     - ������� � ������� ����
// nEventID - ��� �������, ������ ��� ��� ������ ���
void TicTacToe::Fill(int nRow, int nCol, int nEventID)
{
	// ������ ������ � ������� ������ �������� ����
	if (Map[nRow][nCol] != ' ') return;

	if (nEventID == EVENT_LEFT) {
		Map[nRow][nCol] = 'X';
	}
	else if (nEventID == EVENT_RIGHT) {
		Map[nRow][nCol] = 'O';
	} // if
} // TicTacToe::Fill


// ������� true, ���� ���� ������ ��� ������� ��� ���������
// ����������� ����� � ��� �� ��������
bool TicTacToe::isFinish()
{
	// ������� ������� ����� �������� ����
	int nOccuped = 0;

	// �������� �� ���������� ����� ����
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (Map[i][j] != ' ') nOccuped++;
		} // for j
	} // for i
	if (nOccuped == 9) return true;

	// �������� ����� �� ���������� ����������� ���������
	for (int i = 0; i < 3; i++) {
		// ���������� ������, � ������� ������ ������ �� ���������
		if (Map[i][0] == ' ') continue;
		nOccuped = 1;
		for (int j = 1; j < 3; j++) {
			if (Map[i][j] == Map[i][0]) nOccuped++;
		} // for j
		if (nOccuped == 3) return true;
	} // for i

	// �������� �������� �� ���������� ����������� ���������
	for (int j = 0; j < 3; j++) {
		// ���������� �������, � ������� ������ ������ �� ���������
		if (Map[0][j] == ' ') continue;
		nOccuped = 1;
		for (int i = 1; i < 3; i++) {
			if (Map[i][j] == Map[0][j]) nOccuped++;
		} // for i
		if (nOccuped == 3) return true;
	} // for j

	// �������� ������� ���������
	nOccuped = 1;
	for (int i = 1; i < 3; i++) {
		if (Map[i][i] == Map[0][0] && Map[0][0] != ' ') nOccuped++;
	} // for i
	if (nOccuped == 3) return true;

	// �������� �������� ���������
	nOccuped = 1;
	for (int i = 1; i < 3; i++) {
		if (Map[i][2 - i] == Map[0][2] && Map[0][2] != ' ') nOccuped++;
	} // for i
	if (nOccuped == 3) return true;

	return false;
} // TicTacToe::isFinish


// ���������� ������ - ������� ���������� - X ��� O
// ���� �����, �� ���������� ������
TCHAR TicTacToe::getWinner()
{
	// ������� ������� �����
	int nOccuped;

	// �������� ����� �� ���������� ����������� ���������
	for (int i = 0; i < 3; i++) {
		// ���������� ������, � ������� ������ ������ �� ���������
		if (Map[i][0] == ' ') continue;
		nOccuped = 1;
		for (int j = 1; j < 3; j++) {
			if (Map[i][j] == Map[i][0]) nOccuped++;
		} // for j
		if (nOccuped == 3) return Map[i][0];
	} // for i

	// �������� �������� �� ���������� ����������� ���������
	for (int j = 0; j < 3; j++) {
		// ���������� �������, � ������� ������ ������ �� ���������
		if (Map[0][j] == ' ') continue;
		nOccuped = 1;
		for (int i = 1; i < 3; i++) {
			if (Map[i][j] == Map[0][j]) nOccuped++;
		} // for i
		if (nOccuped == 3) return Map[0][j];
	} // for j

	// �������� ������� ���������
	nOccuped = 1;
	for (int i = 1; i < 3; i++) {
		if (Map[i][i] == Map[0][0] && Map[0][0] != ' ') nOccuped++;
	} // for i
	if (nOccuped == 3) return Map[0][0];

	// �������� �������� ���������
	nOccuped = 1;
	for (int i = 1; i < 3; i++) {
		if (Map[i][2 - i] == Map[0][2] && Map[0][2] != ' ') nOccuped++;
	} // for i
	if (nOccuped == 3) return Map[0][2];

	return ' ';
} // TicTacToe::getWinner


// ������� �������� ����
void TicTacToe::Clear()
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			Map[i][j] = _T(' ');
} // TicTacToe::Clear
