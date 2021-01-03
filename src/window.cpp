#include "window.h"

#define WIN32_LEAN_AND_MEAN
#include <windef.h>
#include <winuser.h>
#include <wingdi.h>

#include <stdio.h>
#include <GL/gl.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HDC hdc;
bool key_states[256];

char key_buff[256];
short key_buff_sz;

void init_keyboard()
{
	memset(key_states, 0, sizeof key_states);
	memset(key_buff, 0, sizeof key_buff);
	key_buff_sz = 0;
}

void init_window()
{
	HINSTANCE h_inst = GetModuleHandle(NULL);
	const char *class_name = "chess_window_class";
	WNDCLASS wc = {};
	wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = h_inst;
	wc.lpszClassName = class_name;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpfnWndProc = WndProc;
	RegisterClass(&wc);

	HWND hwnd = CreateWindowEx(0, class_name, "Chess", WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, h_inst, NULL);

	if(hwnd == NULL)
	{
		fprintf(stderr, "Failed to create window\n");
		exit(0);
	}

	hdc = GetDC(hwnd);

	PIXELFORMATDESCRIPTOR pfd = {};
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	int pfIdx = ChoosePixelFormat(hdc, &pfd);
	if(pfIdx == 0)
	{
		fprintf(stderr, "Failed to choose pixel format\n");
		return;
	}
	if(!SetPixelFormat(hdc, pfIdx, &pfd))
	{
		fprintf(stderr, "Failed to set pixel format\n");
		return;
	}

	HGLRC hrc = wglCreateContext(hdc);
	wglMakeCurrent(hdc, hrc);

	printf("GL version: %s\n", (char*)glGetString(GL_VERSION));

	init_keyboard();

	ShowWindow(hwnd, SW_SHOW);
}

bool window_loop()
{
	MSG msg;
	SwapBuffers(hdc);
	while(PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
	{
		if(GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			return false;
		}
	}
	return true;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
		case WM_CLOSE:
			DestroyWindow(hwnd);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_SIZE:
		{
			int width = LOWORD(lParam);
			int height = HIWORD(lParam);
			glViewport(0, 0, width, height);
			break;
		}
		case WM_KEYDOWN:
		{
			char key = wParam;
			key_states[wParam] = true;
			break;
		}
		case WM_KEYUP:
		{
			char key = wParam;
			key_states[wParam] = false;
			break;
		}
		case WM_CHAR:
		{
			char key = wParam;
			key_buff[key_buff_sz++] = key;
			key_buff[key_buff_sz] = 0;
			break;
		}
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}