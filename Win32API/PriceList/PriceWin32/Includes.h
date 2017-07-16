#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define BACKGROUND RGB(0xDC, 0xDC, 0xDC)

#include <Windows.h>
#include <windowsx.h>
#include <CommCtrl.h>
#pragma comment (lib, "comctl32.lib")
#include <tchar.h>
#include <string>
#include <list>
#include <fstream>

using std::wstring;
using std::list;
using std::fstream;
using std::wifstream;
using std::ios;

// Режим вызова (пустой, новый товар, редактирование товара) 
enum InputMode { MODE_NONE, MODE_APPEND, MODE_EDIT };