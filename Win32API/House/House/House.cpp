#include <Windows.h>
#include <windowsx.h>
#include <tchar.h>


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nCmdShow)
{
	// ���������������� ����� �������� ����
	TCHAR szClassName[] = _T("WindowName");				// ����� ����
	TCHAR szTitle[] = _T("���");	// ��������� ����

	// ��������� 
	MSG msg;

	// ��������� ��� ����������� ����
	WNDCLASS wc;

	ZeroMemory(&wc, sizeof(WNDCLASS));					// ��������� ����� ��������� �������� �� ���������
	
	wc.lpfnWndProc	 = WndProc;							// ���������� ������� ��������� ��� �������� ����
	wc.hInstance	 = hInstance;					    // ��������� ���������� ����������
	wc.hIcon		 = LoadIcon(NULL, IDI_INFORMATION);	// ������ ����������
	wc.hCursor		 = LoadCursor(NULL, IDC_IBEAM);		// ������ ����������
	wc.hbrBackground = GetStockBrush(WHITE_BRUSH);		// �������� ����� ��� �������� ���� ����
	wc.lpszClassName = szClassName;						// ������ ����� ����

	// ���������� ����������� ����
	RegisterClass(&wc);

	// ������� ������� ���� ����������
	HWND hwnd = CreateWindow(szClassName, szTitle,	// ����� � ��������� ����
		WS_OVERLAPPED | WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, 15, 15, 740, 580,		// �����, ���������� �������� ������ ����, ������ ���� (������, ������)
		HWND_DESKTOP, NULL, hInstance, NULL);       // ������ ����, ���������� ����, ���������� ����������, ���. ���������

	// �������� ������� ���� ����������
	ShowWindow(hwnd, SW_SHOWNORMAL);

	// ���� ��������� ���������
	while (GetMessage(&msg, NULL, 0, 0)) {
		DispatchMessage(&msg);
	} // while

	return 0;
} // WinMain

// ������� ������� - ��������� ���������, ���������� �����
// hwnd	  - ���������� ����
// msg	  - �������� ��� ���������
// wParam - ������ ����� ���������� ���������
// lParam - ������ ����� ���������� ���������
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;         // ����� ��������� ����������
	PAINTSTRUCT ps;  // ��������� ��������� ����������
	RECT rect;       // ������������� - ��� �������� ��������� ������� ������� ���� 
	//POINT point;     // ���������� �����, ����� ������� MoveToEx

	const UINT N_POINTS = 3;
	POINT apt[N_POINTS] = { {30, 200}, {370, 30}, {700, 200} };

	TCHAR str[] = _T("House");
	TCHAR str1[] = _T("�"); // ����� �����

	// ����� ��� ���������
	HPEN hPen, hPenRect, hPenSkyblue, hOldPen;
	// ����� ��� ��������
	HBRUSH hRectBrushGreen, hRectBrushBlue;	// ��� ������� ����
	HBRUSH hRedBrush, hGreyBrush, hBlackBrush, hBrownBrush, hTanBrush, hWhiteBrush, hOrangeRedBrush, hOldBrush;    

	switch (msg) {

	case WM_SIZE:   // ��������� ������� ������
		GetClientRect(hwnd, &rect);         // ������ ������� ���� ��� �����������
		InvalidateRect(hwnd, &rect, TRUE);  // �������� ������� ���������������� => ����������� WM_PAINT
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);    // �������� ����� ��������� ����������
		GetClientRect(hwnd, &rect);     // �������� ���������� ������� ��� ���������

		// �������� ��������� � ����� ��������� ��� ��������� 
		hPen		 = CreatePen(PS_SOLID, 1, RGB(85, 26, 139));   // ��� �����
		hPenRect	 = CreatePen(PS_SOLID, 2, RGB(28, 28, 28));    // ��� ����� ����
		hPenSkyblue  = CreatePen(PS_SOLID, 9, RGB(135, 206, 235)); // ��� "����" ����

		// �������� ���� - ��� ������ �����
		hRectBrushGreen = CreateSolidBrush(RGB(127, 255, 0));
		hRectBrushBlue  = CreateSolidBrush(RGB(0, 192, 255));
		hRedBrush		= CreateSolidBrush(RGB(0xcc, 0, 0));
		hGreyBrush		= CreateSolidBrush(RGB(220, 220, 220));
		hBlackBrush		= CreateSolidBrush(RGB(28, 28, 28));
		hBrownBrush		= CreateSolidBrush(RGB(139, 69, 19));
		hTanBrush		= CreateSolidBrush(RGB(205, 133, 63));
		hWhiteBrush		= CreateSolidBrush(RGB(255, 255, 255));
		hOrangeRedBrush = CreateSolidBrush(RGB(139, 37, 0));

		hOldPen   = SelectPen(hdc, hPenRect); // �������� �������� ��� ��������� ����� ����
		// ����
		hOldBrush = SelectBrush(hdc, hRectBrushBlue);				      
		Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
		// �����
		hOldBrush = SelectBrush(hdc, hRectBrushGreen);				   
		Rectangle(hdc, rect.left, rect.top + 380, rect.right, rect.bottom);

		// �������� �������� ��� ������� ����� ����
		hOldPen = SelectPen(hdc, hPen);

		// ������ ����
		hOldBrush = SelectBrush(hdc, hGreyBrush);
		Rectangle(hdc, rect.left + 50, rect.top + 200, rect.right - 50, rect.bottom - 50);

		// �������� ������� ����� ��� �������� ����� ������ ����
		hOldBrush = SelectBrush(hdc, hRedBrush);
		Polygon(hdc, apt, N_POINTS);

		// ���������
		hOldBrush = SelectBrush(hdc, hBlackBrush);
		Rectangle(hdc, rect.left + 35, rect.top + 450, rect.right - 35, rect.bottom - 50);
		
		// �����
		hOldBrush = SelectBrush(hdc, hBrownBrush);
		Rectangle(hdc, rect.left + 400, rect.top + 310, rect.right - 200, rect.bottom - 50);
		hOldBrush = SelectBrush(hdc, hTanBrush);
		Rectangle(hdc, rect.left + 420, rect.top + 330, rect.right - 220, rect.bottom - 50);

		// ����
		hOldPen   = SelectPen(hdc, hPenSkyblue);    // �������� �������� � ���������� ��������
		hOldBrush = SelectBrush(hdc, hWhiteBrush);	// ���
		Rectangle(hdc, rect.left + 120, rect.top + 250, rect.right - 420, rect.bottom - 200);
		/* ����� ���������� 2 ����� ������ ���� � ������� LineTo(), �� �� �����, ��� ��� �������
		�������� ������: */
		Rectangle(hdc, rect.left + 180, rect.top + 250, rect.right - 480, rect.bottom - 200);
		hOldPen = SelectPen(hdc, hPen);

		// �����
		hOldBrush = SelectBrush(hdc, hOrangeRedBrush);
		Rectangle(hdc, rect.left + 180, rect.top + 60, rect.right - 480, rect.bottom - 400);

		TextOut(hdc, rect.left + 342, rect.top + 10, str, _tcslen(str));	// ������� �����
		TextOut(hdc, rect.left + 430, rect.top + 400, str1, _tcslen(str1));	// ������� �����

		// ������������ ������� �� ��������� ��� �������������
		SelectPen(hdc, hOldPen);
		DeletePen(hPen);
		DeletePen(hPenRect);
		DeletePen(hPenSkyblue);

		SelectBrush(hdc, hOldBrush);
		DeleteBrush(hRectBrushGreen);
		DeleteBrush(hRectBrushBlue);
		DeleteBrush(hRedBrush);
		DeleteBrush(hGreyBrush);
		DeleteBrush(hBlackBrush);
		DeleteBrush(hBrownBrush);
		DeleteBrush(hTanBrush);
		DeleteBrush(hWhiteBrush);
		DeleteBrush(hOrangeRedBrush);

		// ���������� �������� ��� ���������� ������ �������
		EndPaint(hwnd, &ps);
		break;

	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:		// ��������� "��������� ������"
		PostQuitMessage(0);	// �������� ��������� "����� ������" ��� ������ �� ����� ���������
		break;

	// ��������� ��������� ��� ������� �� ������������� ��������� � ����� ����
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	} // switch

	return 0;
} // WndProce