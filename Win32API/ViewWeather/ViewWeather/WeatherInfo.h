#pragma once
#include "Includes.h"

class WeatherInfo
{
public:
	WeatherInfo() {}
	
	~WeatherInfo() {}

	wstring City;			 // �������� ������ ��������� ����������������� ������
	wstring DirWind;		 // ����������� �����
	double  SpeedWind;		 // �������� �����, �/�
	double  MaxDaytimeTemp;  // ������������ ������� �����������, ����. �������
	double  MinNightTemp;	 // ����������� ������ �����������, ����. �������

	void setFields(TCHAR *str);
};

