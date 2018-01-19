#include "Includes.h"
#include "MainWindow.h"
#include "WeatherInfo.h"
#include "WeatherLoad.h"
 
// Ïåðåìåííûå è ôóíêöèè äëÿ ãëàâíîãî îêíà ïðèëîæåíèÿ.
static HDC hdc; // Õýíäë êîíòåêñòà óñòðîéñòâà                         

// Ìåíþ îêíà è ïîäìåíþ "Ôàéë", "Âèä"
HMENU hMainMenu, hFileMenu, hViewMenu;

// Âûñîòà ñòðîêè ìåíþ â ïèêñåëÿõ - äëÿ ïåðåñòðîåíèÿ îêíà
static INT32 nMenuHeight;   

// Ýëåìåíò ListView
HWND hLstWeather;

// Âåêòîð äàííûõ äëÿ îáðàáîòêè - âåêòîð îáúåêòîâ êëàññà Student
WeatherLoad weather;

// Ñòàíäàðòíûé äèàëîã îòêðûòèÿ ôàéëà
OPENFILENAME ofn;

LOGFONT lf;
COLORREF colfont;
CHOOSEFONT cfont;
HFONT font;
HANDLE hOldFont;

CHOOSECOLOR ccol;
COLORREF clf;
COLORREF clfusers[16];

// Îêîííàÿ ôóíêöèÿ - îáðàáîòêà ñîîáùåíèé, ïîëó÷àåìûõ îêíîì
// hwnd	  - äåñêðèïòîð îêíà
// msg	  - ÷èñëîâîé êîä ñîîáùåíèÿ
// wParam - ïåðâàÿ ÷àñòü ïàðàìåòðîâ ñîîáùåíèÿ
// lParam - âòîðàÿ ÷àñòü ïàðàìåòðîâ ñîîáùåíèÿ
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
		HANDLE_MSG(hwnd, WM_CREATE, OnCreate);  // ñîçäàíèå îêíà
		HANDLE_MSG(hwnd, WM_SIZE, OnSize);      // Èçìåíåíèå ðàçìåðà ýêðàíà
		HANDLE_MSG(hwnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hwnd, WM_CLOSE, OnClose);
		HANDLE_MSG(hwnd, WM_DESTROY, OnDestroy);
		HANDLE_MSG(hwnd, WM_GETMINMAXINFO, OnGetMinMaxInfo);
		HANDLE_MSG(hwnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hwnd, WM_CTLCOLORSTATIC, OnCtlColorStatic);
	
		// Îáðàáîòêà ñîîáùåíèé äëÿ êîòîðûõ íå ïðåäóñìîòðåíà îáðàáîòêà â íàøåì îêíå
		default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	} // switch

	return 0;
} // WndProc


// Îáðàáîò÷èê ñîîáùåíèÿ WM_CREATE - îáðàáîò÷èê ñîáûòèÿ "Ïðè ñîçäàíèè" 
// íàøåãî îêíà
BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
	RECT rect;
	GetClientRect(hwnd, &rect);

	#pragma region Ñîçäàíèå ìåíþ
	hMainMenu = CreateMenu();
	hFileMenu = CreatePopupMenu();
	hViewMenu = CreatePopupMenu();

	AppendMenu(hMainMenu, MF_STRING | MF_POPUP, (UINT_PTR)hFileMenu, _T("&Ôàéë"));
	AppendMenu(hFileMenu, MF_STRING, IDC_OPEN, _T("&Îòêðûòü..."));
	AppendMenu(hFileMenu, MF_SEPARATOR, NULL, _T(""));
	AppendMenu(hFileMenu, MF_STRING, IDC_QUIT, _T("Âû&õîä"));

	AppendMenu(hMainMenu, MF_STRING | MF_POPUP, (UINT_PTR)hViewMenu, _T("&Âèä"));
	AppendMenu(hViewMenu, MF_STRING, IDC_FONT, _T("Øð&èôò òåêñòà..."));
	AppendMenu(hViewMenu, MF_STRING, IDC_COLOR, _T("Ö&âåò ôîíà..."));
	SetMenu(hwnd, hMainMenu);

	// Ïîëó÷èòü âûñîòó ñòðîêè ìåíþ â ïèêñåëàõ
	nMenuHeight = GetSystemMetrics(SM_CYMENU);
	#pragma endregion

	#pragma region Ñîçäàíèå ýëåìåíòà ListView
	hLstWeather = CreateWindowEx(0, WC_LISTVIEW, NULL,
		WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_REPORT | LVS_ALIGNLEFT,
		rect.left + 10, rect.top + 10, rect.right - 20, rect.bottom - nMenuHeight, 
		hwnd, (HMENU)IDC_LISTVIEW, lpCreateStruct->hInstance, NULL);
	// SendMessage(hLstStudents, WM_SETFONT, WPARAM(hFontList), NULL);

	// Äîáàâëåíèå ñòîëáöîâ
	LV_COLUMN lvCol;
	ZeroMemory(&lvCol, sizeof(LV_COLUMN));

	// Äîáàâëåíèå 0-ãî ñòîëáöà - Ôàìèëèÿ è èíèöèàëû
	lvCol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvCol.fmt  = LVCFMT_LEFT;
	lvCol.cx   = (rect.right - rect.left - 20) / 5;

	lvCol.iSubItem = 0;
	lvCol.pszText  = _T("Ãîðîä");
	ListView_InsertColumn(hLstWeather, 0, &lvCol);

	// Òåïåðü äîáàâëÿåì ïîäýëåìåíòû
	lvCol.iSubItem = 1;
	lvCol.pszText  = _T("Íàïðàâëåíèå âåòðà");
	ListView_InsertColumn(hLstWeather, 1, &lvCol);

	lvCol.iSubItem = 2;
	lvCol.pszText  = _T("Ñêîðîñòü âåòðà, ì/ñ");
	ListView_InsertColumn(hLstWeather, 2, &lvCol);

	lvCol.iSubItem = 3;
	lvCol.pszText  = _T("Ìàêñ. äíåâ. òåìïåð.");
	ListView_InsertColumn(hLstWeather, 3, &lvCol);

	lvCol.iSubItem = 4;
	lvCol.pszText  = _T("Ìèí. íî÷. òåìïåð.");
	ListView_InsertColumn(hLstWeather, 4, &lvCol);

	ListView_SetExtendedListViewStyle(hLstWeather,
		ListView_GetExtendedListViewStyle(hLstWeather) | LVS_EX_FULLROWSELECT);
	#pragma endregion
	
	// Çàãðóçêà äàííûõ èç ôàéëà
	weather = WeatherLoad(_T("Ìåòåîäàííûå.txt"));
	weather.LoadFromFile();

	// Âûâîä âåêòîðà ñòóäåíòîâ â ýëåìåíò ListView
	weather.ListView(hLstWeather);

	#pragma region Ñîçäàíèå äèàëîãà îòêðûòèÿ ôàéëà
	static TCHAR fileName[256];
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = sizeof(fileName);
	ofn.lpstrFilter = _T("Òåêñòîâûå ôàéëû (*.txt)\0*.txt\0CSV-ôàéëû (*.csv)\0*.csv\0Âñå ôàéëû (*.*)\0*.*\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrInitialDir = _T(".");  // òåêóùèé êàòàëîã/òåêóùàÿ ïàïêà
	ofn.lpstrDefExt = _T("txt");
	#pragma endregion

	#pragma region Ñîçäàíèå äèàëîãà âûáîðà øðèôòà
	colfont = RGB(0, 0, 0);
	lf.lfHeight = 13;
	lf.lfWidth = 13;
	lf.lfEscapement = 0;
	lf.lfOrientation = 0;
	lf.lfItalic = 0;
	lf.lfUnderline = 0;
	lf.lfStrikeOut = 0;
	lf.lfWeight = FW_NORMAL;
	lf.lfCharSet = RUSSIAN_CHARSET;
	_tcscpy(lf.lfFaceName, _T("Calibri"));
	cfont.lStructSize = sizeof(CHOOSEFONT);
	cfont.Flags = CF_SCREENFONTS | CF_EFFECTS | CF_INITTOLOGFONTSTRUCT;
	#pragma endregion

	#pragma region Ñîçäàíèå äèàëîãà âûáîðà öâåòà
	ccol.lStructSize = sizeof(CHOOSECOLOR);
	ccol.Flags = CC_RGBINIT;
	ccol.lpCustColors = clfusers;
	clf = RGB(255, 255, 255);
	#pragma endregion

	return TRUE;
} // OnCreate


// Îáðàáîò÷èê ñîîáùåíèÿ WM_SIZE - îáðàáîò÷èê ñîáûòèÿ "Ïðè èçìåíåíèè ðàçìåðà" 
// íàøåãî îêíà
void OnSize(HWND hwnd, UINT state, int cx, int cy)
{
	RECT rect;       // Ïðÿìîóãîëüíèê - äëÿ õðàíåíèÿ êîîðäèíàò ðàáî÷åé îáëàñòè îêíà 
	INT32 nWidth;    // Øèðèíà ñòîëáöà ýëåìåíòà ListView

	GetClientRect(hwnd, &rect);         // Çàäàòü îáëàñòü îêíà äëÿ ïåðåðèñîâêè

	// Íîâûé ðàçìåð ListView
	MoveWindow(hLstWeather, 10, 10, rect.right - 20, rect.bottom - nMenuHeight - 10, TRUE);

	// Ïîñëàòü ñîîáùåíèÿ ListView äëÿ óñòàíîâêè øèðèíû ñòîëáöîâ
	nWidth = (rect.right - 20) / 5;
	for (size_t i = 0; i < 5; i++)
		ListView_SetColumnWidth(hLstWeather, i, nWidth);

	InvalidateRect(hwnd, &rect, TRUE);  // Îáúÿâèòü îáëàñòü íåäåéñòâèòåëüíîé => ôîðìèðóåòñÿ WM_PAINT
} // OnSize


// Îáðàáîò÷èê ñîîáùåíèÿ WM_PAINT - îáðàáîò÷èê ñîáûòèÿ "Ïðè îòðèñîâêå" 
void OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;  // Ïàðàìåòðû êîíòåêñòà óñòðîéñòâà
	RECT rect;       // Ïðÿìîóãîëüíèê - äëÿ õðàíåíèÿ êîîðäèíàò ðàáî÷åé îáëàñòè îêíà 

	hdc = BeginPaint(hwnd, &ps);    // Ïîëó÷èòü õýíäë êîíòåêñòà óñòðîéñòâà
	
	font = CreateFontIndirect(&lf);
	hOldFont = SelectObject(hdc, font);
	SetTextColor(hdc, colfont);
	TextOut(hdc, 20, 20, lf.lfFaceName, _tcslen(lf.lfFaceName));
	SelectObject(hdc, hOldFont);
	DeleteObject(font);

	GetClientRect(hwnd, &rect);     // Ïîëó÷èòü êîîðäèíàòû îáëàñòè äëÿ ðèñîâàíèÿ

	EndPaint(hwnd, &ps);            // Îñâîáîäèòü êîíòåêñò äëÿ êîððåêòíîé ðàáîòû ñèñòåìû
} // OnPaint


// Îáðàáîò÷èê ñîîáùåíèÿ WM_CLOSE - îáðàáîò÷èê ñîáûòèÿ "Ïðè çàêðûòèè îêíà" 
void OnClose(HWND hwnd)
{
	DestroyWindow(hwnd);
} // OnClose


// Îáðàáîò÷èê ñîîáùåíèÿ WM_DESTROY - îáðàáîò÷èê ñîáûòèÿ "Ïðè óíè÷òîæåíèè îêíà" 
void OnDestroy(HWND hwnd)
{
	PostQuitMessage(0);
} // OnDestroy


// Îãðàíè÷åíèå ìèíèìàëüíîãî ðàçìåðà ãëàâíîãî îêíà ïðèëîæåíèÿ
// !! Ðàáîòàåò âìåñòå ñ OnSize !!
void OnGetMinMaxInfo(HWND hwnd, LPMINMAXINFO lpMinMaxInfo)
{
	lpMinMaxInfo->ptMinTrackSize = { 480, 240 };
} // OnGetMinMaxInfo


// Îáðàáîòêà ñîîáùåíèé WM_COMMAND - îíè ïîñûëàþòñÿ îò ýëåìåíòîâ óïðàâëåíèÿ
// â ÷àñòíîñòè - îò êíîïîê
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	BOOL bResult;

	switch (id) {
		// Âûáîð ôàéëà äàííûõ ïðè ïîìîùè ñòàíäàðòíîãî äèàëîãà è
		// âûâîä äàííûõ èç ýòîãî ôàéëà
	case IDC_OPEN:
		ofn.Flags = OFN_EXPLORER;
		bResult = GetOpenFileName(&ofn);
		if (!bResult) break;

		weather.SetFileName(wstring(ofn.lpstrFile));
		weather.LoadFromFile();
		weather.ListView(hLstWeather);
		break;

		// Âûáîð øðèôòà äëÿ âûâîäà òåêñòà â ListView è óñòàíîâêà øðèôòà
	case IDC_FONT:
		cfont.lpLogFont = &lf;
		cfont.rgbColors = colfont;
		if (ChooseFont(&cfont)) {
			lf = *cfont.lpLogFont;
			colfont = cfont.rgbColors;
			ListView_SetTextColor(hLstWeather, colfont);
			SendMessage(hLstWeather, WM_SETFONT, (WPARAM)CreateFontIndirect(&lf), TRUE);
		} // if
		break;

		// Âûáîð öâåòà äëÿ âûâîäà òåêñòà â ListtView è óñòàíîâêà öâåòà
	case IDC_COLOR:
		ccol.rgbResult = clf;
		if (ChooseColor(&ccol)) {
			clf = ccol.rgbResult;
			ListView_SetTextBkColor(hLstWeather, clf);
			RECT rt;
			GetClientRect(hLstWeather, &rt);
			InvalidateRect(hLstWeather, &rt, TRUE);
		} // if
		break;

	case IDC_QUIT:
		PostQuitMessage(0);
		break;
	} // switch
} // OnCommand


// Îòðèñîâêà ôîíà ñòàòè÷åñêîãî óïðàâëÿþùåãî ýëåìåíòà
// Ôîí - ñîâïàäàåò ñ ôîíîì ðàáî÷åé îáëàñòè îêíà
HBRUSH OnCtlColorStatic(HWND, HDC hdc, HWND, int)
{
	SetBkMode(hdc, TRANSPARENT);
	return CreateSolidBrush(BACKGROUND);
} // OnCtlColorStatic
