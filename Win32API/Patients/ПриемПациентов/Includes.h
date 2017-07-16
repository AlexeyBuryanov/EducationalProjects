#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define BACKGROUND RGB(0xDC, 0xDC, 0xDC)

#include <Windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <string>
#include <list>
#include <fstream>

using std::list;
using std::fstream;
using std::ios;

// Режим вызова (пустой, новый пациент, редактирование пациента) 
enum InputMode { MODE_NONE, MODE_APPEND, MODE_EDIT };