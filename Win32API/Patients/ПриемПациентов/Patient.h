#pragma once
#include "Includes.h"

using std::wstring;

class Patient
{
	// ������������ ����� ���� � �������� (TCHAR - ������, 1 ��� 2 �����)
	static const int LEN_FAMIO = 60;  
	wstring wsFamIO;
	UINT uWeight;

public:
	Patient() : wsFamIO(_T("������ �.�.")), uWeight() {}
	Patient(wstring wsFamIO, UINT uWeight) : wsFamIO(wsFamIO), uWeight(uWeight) {}
	Patient(const Patient &patient) : wsFamIO(patient.wsFamIO), uWeight(patient.uWeight) {}

	~Patient() {}

	Patient operator=(const Patient &patient);

	UINT getWeight() { return uWeight; }
	void setWeight(UINT uWeight) { this->uWeight = uWeight >= 3 ? uWeight : 3; }

	wstring getFamIO() { return wsFamIO; }
	void    setFamIO(wstring  sFamIO) { this->wsFamIO = sFamIO; }

	void Show();
	void Save(fstream &fs, bool append = false);
	void Load(fstream &fs);

	static const UINT LEN_RECORD = LEN_FAMIO * sizeof(TCHAR) + sizeof(UINT);
};

