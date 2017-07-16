#pragma once
#include "Includes.h"

#define IDC_QUIT		1000  /* Команда "Выход"    */
#define IDC_OPEN        1001  /* Команда "Открыть"  */
#define IDC_FONT        1002  /* Команда "Шрифт"    */
#define IDC_COLOR       1003  /* Команда "Цвет"     */

#define IDC_LISTVIEW    2000  /* Элемент ListView   */


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
void OnSize(HWND hwnd, UINT state, int cx, int cy);
void OnPaint(HWND hwnd);
void OnClose(HWND hwnd);
void OnDestroy(HWND hwnd);
void OnGetMinMaxInfo(HWND hwnd, LPMINMAXINFO lpMinMaxInfo);
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
HBRUSH OnCtlColorStatic(HWND, HDC hdc, HWND, int);