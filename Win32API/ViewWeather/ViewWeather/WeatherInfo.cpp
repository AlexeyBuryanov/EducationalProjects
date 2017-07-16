#include "WeatherInfo.h"

// �� ������ ����������� ��������� "," ������� ���������
void WeatherInfo::setFields(TCHAR * str)
{
	wstring s(str);
	
	// ������� ������� � ������ - pos
	int pos  = s.find(_T(","));
	City.assign(s.substr(0, pos));   // ����� ��������� �� �������
	s = s.substr(pos + 1);           // �������� ������� ����� ������� ��� ���������� ���������

	// ��������� ��� ��������� ����������
	pos = s.find(_T(","));
	DirWind.assign(s.substr(0, pos));
	s = s.substr(pos + 1);

	pos = s.find(_T(","));
	_stscanf(s.substr(0, pos).c_str(), _T("%lf"), &SpeedWind);
	s = s.substr(pos + 1);

	pos = s.find(_T(","));
	_stscanf(s.substr(0, pos).c_str(), _T("%lf"), &MaxDaytimeTemp);
	s = s.substr(pos + 1);

	pos = s.find(_T(","));
	_stscanf(s.substr(0, pos).c_str(), _T("%lf"), &MinNightTemp);
	s = s.substr(pos + 1);
} // Student::setFields
