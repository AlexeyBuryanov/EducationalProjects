#include "WeatherLoad.h"
#include "WeatherInfo.h"

// Загрузка данных из файла данных в вектор
void WeatherLoad::LoadFromFile()
{
	TCHAR szBuf[255];
	WeatherInfo weather;

	// Очистить данные - чтобы не было накопления при 
	// загрузке данных из нескольких файлов
	data.clear();

	// Открытие файла данных
	FILE *fin = _tfopen(sFileName.c_str(), _T("r, ccs=UTF-8"));
	if (!fin) {
		_stprintf(szBuf, _T("Файл данных \"%s\" не открыт"), sFileName.c_str());
		MessageBox(HWND_DESKTOP, szBuf, _T("Ошибка"), MB_OK | MB_ICONERROR);
		return;
	} // if

	// Чтение из файла и добавление в вектор
	while (!feof(fin)) {
		_fgetts(szBuf, 255, fin);    // читать строку из файла
		weather.setFields(szBuf);    // заполнить поля объекта из строки
		data.push_back(weather);     // добавить объект в вектор
	} // while

	fclose(fin);
} // WeatherLoad::LoadFromFile


// Вывод элементов вектора студентов в ListView 
void WeatherLoad::ListView(HWND hListView)
{
	// Очистка Listview перед заполнением новыми данными - чтобы
	// не было накопления
	ListView_DeleteAllItems(hListView);

	LV_ITEM lvItem;
	static INT32 nCounter;

	// Буферные строки для добавления данных в ListView
	TCHAR szBuf1[50];
	TCHAR szBuf2[50];
	TCHAR szBuf3[50];
	TCHAR szBuf4[50];
	TCHAR szBuf5[50];

	// Читать из вектора, выводить в ListView
	nCounter = 0;
	for (auto it = data.begin(); it != data.end(); ++it) {
		_stprintf(szBuf1, _T("%s"), it->City.c_str());
		_stprintf(szBuf2, _T("%s"), it->DirWind.c_str());
		_stprintf(szBuf3, _T("%8.2lf"), it->SpeedWind);
		_stprintf(szBuf4, _T("%8.2lf"), it->MaxDaytimeTemp);
		_stprintf(szBuf5, _T("%8.2lf"), it->MinNightTemp);

		ZeroMemory(&lvItem, sizeof(LV_ITEM));
		lvItem.mask       = LVIF_TEXT;
		lvItem.pszText    = szBuf1;
		lvItem.iItem      = nCounter;
		lvItem.iSubItem   = 0;
		lvItem.cchTextMax = 30;
		ListView_InsertItem(hListView, &lvItem);
		ListView_SetItemText(hListView, nCounter, 1, szBuf2);
		ListView_SetItemText(hListView, nCounter, 2, szBuf3);
		ListView_SetItemText(hListView, nCounter, 3, szBuf4);
		ListView_SetItemText(hListView, nCounter, 4, szBuf5);
		nCounter++;
	} // for
} // WeatherLoad::ListView
