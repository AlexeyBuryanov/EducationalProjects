#include "Patient.h"
#include "InputWindow.h"

//extern Patient patient;
//extern HWND hEdFamIO;        // ���� ����� �������
//extern HWND hEdWeight;       // ���� ����� ����
//extern HWND hLstPatients;    // ������ ����� - ��������

Patient Patient::operator=(const Patient & patient)
{
	// �������� �� ����������������
	if (this == &patient) {
		return *this;
	} // if

	wsFamIO = patient.wsFamIO;
	uWeight = patient.uWeight;

	return *this;
} // operator=


// ��������� ������ �� ��������� ����������, �����
// � ������� ������
void Patient::Show()
{
	//TCHAR szBuf1[100];
	//TCHAR szBuf2[100];
	//UINT weight;	    // ��������������� ���������� ��� ������ � �����

	//SendMessage(hEdFamIO, WM_GETTEXT, (WPARAM)100, (LPARAM)szBuf1);	
	//if (_tcslen(szBuf1) == 0) return;									
	//patient.setFamIO(szBuf1);											

	//SendMessage(hEdWeight, WM_GETTEXT, NULL, (LPARAM)szBuf2);
	//if (_tcslen(szBuf1) == 0) return;
	//_stscanf(szBuf2, _T("%u"), &weight);
	//patient.setWeight(weight);

	//SendMessage(hLstPatients, LB_ADDSTRING, NULL, (LPARAM)szBuf1);   
	//SendMessage(hLstPatients, LB_ADDSTRING, NULL, (LPARAM)szBuf2);   
	//SendMessage(hEdFamIO, WM_SETTEXT, NULL, NULL);                   
	//SendMessage(hEdWeight, WM_SETTEXT, NULL, NULL);                  
} // Show


// ���������� ����� ������ ������� � �������� ������
// (�������� ������������)
// append - ���� true, �� ��������� �������� � ���� ������ ��������
// ������� ������ ������� � ����� �����
// ���� false - �� ������������� ������� ������ (�� ������� ������
// ��������� ��������� �������� ��������)
void Patient::Save(fstream &fs, bool append)
{
	if (append) fs.seekp(0, ios::end);

	// ����� ������
	TCHAR *szBuf = new TCHAR[LEN_FAMIO];
	
	// ������� ������ �� �������� ��������
	ZeroMemory(szBuf, LEN_FAMIO * sizeof(TCHAR));

	// �������� ������ � ������ ������
	_tcscpy(szBuf, wsFamIO.c_str());

	fs.write((char *)szBuf, LEN_FAMIO * sizeof(TCHAR));
	fs.write((char *)&uWeight, sizeof(UINT));

	delete[] szBuf;
} // Patient::Save


// �������� ����� ������ ������� �� ��������� ������
// (�������� ��������������)
void Patient::Load(fstream &fs)
{
	// ����� �����
	TCHAR *szBuf = new TCHAR[LEN_FAMIO];

	// ������� ������ �� �������� ��������
	ZeroMemory(szBuf, LEN_FAMIO * sizeof(TCHAR));

	fs.read((char *)szBuf, LEN_FAMIO * sizeof(TCHAR));
	fs.read((char *)&uWeight, sizeof(UINT));

	// ���������� ����� ����� � ������ �������� TCHAR
	wsFamIO.assign(szBuf);
	delete[] szBuf;
} // Patient::Load
