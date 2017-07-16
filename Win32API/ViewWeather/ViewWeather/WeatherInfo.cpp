#include "WeatherInfo.h"

// »з строки разделенной символами "," извлечь подстроки
void WeatherInfo::setFields(TCHAR * str)
{
	wstring s(str);
	
	// ѕозици€ зап€той в строке - pos
	int pos  = s.find(_T(","));
	City.assign(s.substr(0, pos));   // вз€ть подстроку до зап€той
	s = s.substr(pos + 1);           // оставили хвостик после зап€той дл€ дальнейшей обработки

	// ѕовторить дл€ отсальных параметров
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
