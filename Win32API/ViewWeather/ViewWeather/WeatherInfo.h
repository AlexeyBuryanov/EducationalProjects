#pragma once
#include "Includes.h"

class WeatherInfo
{
public:
	WeatherInfo() {}
	
	~WeatherInfo() {}

	wstring City;			 // Название пункта измерения метеорологических данных
	wstring DirWind;		 // Направление ветра
	double  SpeedWind;		 // Скорость ветра, м/с
	double  MaxDaytimeTemp;  // Максимальная дневная температура, град. Цельсия
	double  MinNightTemp;	 // Минимальная ночная температура, град. Цельсия

	void setFields(TCHAR *str);
};

