#define UNICODE

#include <windows.h>
#include "resource.h"

TCHAR szClassName[] = TEXT("Window");

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static INT nStep;
	static HICON hIcon16[12];
	static HICON hIcon32[12];
	switch (msg)
	{
	case WM_CREATE:
	{
		for (int i = 0; i < 12; i++)
		{
			hIcon16[i] = LoadIcon(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDI_ICON16_00 + i));
			hIcon32[i] = LoadIcon(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDI_ICON32_00 + i));
		}
		SetTimer(hWnd, 0x1234, 100, 0);
	}
	break;
	case WM_TIMER:
	{
		const HDC hdc = GetDC(hWnd);
		const HBRUSH hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
		DrawIconEx(hdc, 0, 0, hIcon16[nStep], 16, 16, 0, hBrush, DI_NORMAL);
		DrawIconEx(hdc, 16, 0, hIcon32[nStep], 32, 32, 0, hBrush, DI_NORMAL);
		ReleaseDC(hWnd, hdc);
		if (nStep < 12 - 1)
			nStep++;
		else
			nStep = 0;
	}
	break;
	case WM_DESTROY:
	{
		for (int i = 0; i < 12; i++)
		{
			DestroyIcon(hIcon16[i]);
			DestroyIcon(hIcon32[i]);
		}
	}
	PostQuitMessage(0);
	break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInst, LPSTR pCmdLine, int nCmdShow)
{
	MSG msg;
	WNDCLASS wndclass = {
		CS_HREDRAW | CS_VREDRAW,
		WndProc,
		0,
		0,
		hInstance,
		0,
		LoadCursor(0,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		0,
		szClassName
	};
	RegisterClass(&wndclass);
	HWND hWnd = CreateWindow(
		szClassName,
		TEXT("Window"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		0,
		CW_USEDEFAULT,
		0,
		0,
		0,
		hInstance,
		0
	);
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}
