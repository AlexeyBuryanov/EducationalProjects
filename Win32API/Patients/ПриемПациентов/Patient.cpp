#include "Patient.h"
#include "InputWindow.h"

//extern Patient patient;
//extern HWND hEdFamIO;        // Поле ввода фамилии
//extern HWND hEdWeight;       // Поле ввода веса
//extern HWND hLstPatients;    // список строк - пациенты

Patient Patient::operator=(const Patient & patient)
{
	// проверка на самоприсваивание
	if (this == &patient) {
		return *this;
	} // if

	wsFamIO = patient.wsFamIO;
	uWeight = patient.uWeight;

	return *this;
} // operator=


// Получение данных из элементов управления, вывод
// в область заказа
void Patient::Show()
{
	//TCHAR szBuf1[100];
	//TCHAR szBuf2[100];
	//UINT weight;	    // вспомогательная переменная для работы с весом

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


// Сохранение полей данных объекта в двоичном потоке
// (двоичная сериализация)
// append - если true, то требуется дозапись в файл нового пациента
// поэтому делаем переход в конец файла
// если false - то перезаписывем текущую запись (на которую сейчас
// указывает указатель файловой операции)
void Patient::Save(fstream &fs, bool append)
{
	if (append) fs.seekp(0, ios::end);

	// Буфер вывода
	TCHAR *szBuf = new TCHAR[LEN_FAMIO];
	
	// Очистка буфера от мусорных символов
	ZeroMemory(szBuf, LEN_FAMIO * sizeof(TCHAR));

	// Получить строку в буфере вывода
	_tcscpy(szBuf, wsFamIO.c_str());

	fs.write((char *)szBuf, LEN_FAMIO * sizeof(TCHAR));
	fs.write((char *)&uWeight, sizeof(UINT));

	delete[] szBuf;
} // Patient::Save


// Загрузка полей данных объекта из двоичного потока
// (двоичная десериализация)
void Patient::Load(fstream &fs)
{
	// Буфер ввода
	TCHAR *szBuf = new TCHAR[LEN_FAMIO];

	// Очистка буфера от мусорных символов
	ZeroMemory(szBuf, LEN_FAMIO * sizeof(TCHAR));

	fs.read((char *)szBuf, LEN_FAMIO * sizeof(TCHAR));
	fs.read((char *)&uWeight, sizeof(UINT));

	// Копировать буфер ввода в строку символов TCHAR
	wsFamIO.assign(szBuf);
	delete[] szBuf;
} // Patient::Load
