#include "window.h"

#define WIN32_LEAN_AND_MEAN
#include <windef.h>
#include <winuser.h>
#include <wingdi.h>

#include <stdio.h>

void init_window()
{
	HINSTANCE h_inst = GetModuleHandle(NULL);
	const char *class_name = "chess_window_class";
	WNDCLASS wc = {};
	wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = h_inst;
	wc.lpszClassName = class_name;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	RegisterClass(&wc);

	HWND hwnd = CreateWindowEx(0, class_name, "Chess", WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, h_inst, NULL);

	if(hwnd == NULL)
	{
		fprintf(stderr, "Failed to create window\n");
		exit(0);
	}

	ShowWindow(hwnd, SW_SHOW);
}

void window_loop()
{

}