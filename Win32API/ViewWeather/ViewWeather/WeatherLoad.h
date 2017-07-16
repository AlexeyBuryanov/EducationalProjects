#pragma once
#include "Includes.h"
#include "WeatherInfo.h"

class WeatherLoad
{
	// Имя файла данных (это текстовый файл)
	wstring sFileName;

public:
	WeatherLoad()
		: sFileName(_T("WeatherLoad.txt")) {}
	WeatherLoad(wstring fileName)
		: sFileName(fileName) {}
	
	~WeatherLoad() {}

	void LoadFromFile();
	void ListView(HWND hListView);

	// Установка имени файла данных
	void SetFileName(wstring fName) { sFileName = fName;  }

	vector<WeatherInfo> data;
};

