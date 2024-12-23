
#pragma once
#include <iostream>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "ObjParser.h"

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")
#define WINDOW_TITLE "OpenGL Window"

HWND g_hWnd = NULL; //is variable, is a pointer, set to NULL for safety
WNDCLASS wndClass;

int xRot = 0;
int zRot = 0;

void createWindow();

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:

		switch (wParam) {
			case VK_UP:
				xRot++;
				break;
			case VK_DOWN:
				xRot--;
				break;
			case VK_RIGHT:
				zRot++;
				break;
			case VK_LEFT:
				zRot--;
				break;
			default:
				break;
		}

		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

//Object* obj;
ObjParser parser = ObjParser();

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);


	
	glPushMatrix();
	glTranslatef(0, 0, -20.0f);
	glRotatef(-90, 0, 1, 0);
	glRotatef(zRot, 0, 1, 0);

	for (auto object : parser.objectList) {
		for (auto face : object->faceData) {
			glBegin(GL_LINE_LOOP);
			for (auto vertex : face) {
				glVertex3f(vertex.x, vertex.y, vertex.z);
				//auto vert = vertex.to_array();
				//glVertex3fv(vert);
				//delete vert;
			}
			glEnd();
		}
	}

	glPopMatrix();
}

void loadMaterial(Material material) {
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material.properties[GL_SHININESS][0]);
}

//--------------------------------------------------------------------

int main(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	//WNDCLASSEX wc;
	//ZeroMemory(&wc, sizeof(WNDCLASSEX));
	
	//wc.cbSize = sizeof(WNDCLASSEX);
	//wc.hInstance = GetModuleHandle(NULL);
	//wc.lpfnWndProc = WindowProcedure;
	//wc.lpszClassName = WINDOW_TITLE;
	//wc.style = CS_HREDRAW | CS_VREDRAW;

	//if (!RegisterClassEx(&wc))
	//	return false;

	//HWND hWnd = CreateWindowExA(0, WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
	//	CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
	//	NULL, NULL, wc.hInstance, NULL);


	createWindow();

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	//HDC hdc = GetDC(hWnd);
	HDC hdc = GetDC(g_hWnd);
	
	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	//ShowWindow(hWnd, 1);
	ShowWindow(g_hWnd, 1);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	//init

	//obj = new Object();
	//OpenGlParser parser = OpenGlParser();

	parser = ObjParser();

	parser.openMtl("robot.mtl");
	parser.loadMaterial();

	parser.openObj("robot.obj");
	parser.load();


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, 1, 1, 30);
	//glFrustum(-10, 10, -10, 10, 0, 150);


	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		
		display();

		SwapBuffers(hdc);
	}

	//UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}

void createWindow()
{
	HINSTANCE hInstance = GetModuleHandle(NULL);
	/*
		Step 1
		Define and Register a Window.
	*/

	//	Window's structure
	//	Set all members in wndClass to 0.
	ZeroMemory(&wndClass, sizeof(wndClass));

	//int x = 0;
	//ZeroMemory(&x, sizeof(x)); //set all memory in address of x to 0

	//	Filling wndClass. You are to refer to MSDN for each of the members details.
	//	These are the fundamental structure members to be specify, in order to create your window.
	//	MINIMAL
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hInstance = hInstance;	//	GetModuleHandle(NULL);
	wndClass.lpfnWndProc = WindowProcedure;		//event handler, MUST HAVE
	wndClass.lpszClassName = "ABC";
	wndClass.style = CS_HREDRAW | CS_VREDRAW;	//redraw

	//	Register the window.
	RegisterClass(&wndClass);

	/*
		Step 2
		Create the Window.
	*/
	//	You are to refer to MSDN for each of the parameters details.
	g_hWnd = CreateWindowEx(0, wndClass.lpszClassName, "Practical", WS_OVERLAPPEDWINDOW, 0, 100, 1024, 1024, NULL, NULL, hInstance, NULL);
	ShowWindow(g_hWnd, 1);
}
//--------------------------------------------------------------------

