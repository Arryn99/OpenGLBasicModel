#include "main.h"
#include "textures.h"
#include "Game.h"	
#include "Window.h"	
#include "OpenGl.h"
#include <windows.h>

/////////
//#include <stdio.h>
//#include <mmsystem.h>
//#include <math.h>
//#include <gl/gl.h>
//#include <gl/glu.h>
/////////

#define S_WIDTH	800		//client area resolution
#define S_HEIGHT 600

typedef struct Mouse
{
	int x,y;
}Mouse;

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);
void DrawScene();
/////////

bool gameRunning = true;
bool keys[256]; 

Mouse MousePos;
Game* game;

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)											
    {														
		case WM_CREATE:	
			break;

		case WM_SIZE:
			//resize the open gl window when the window is resized
			//ResizeGLWindow(LOWORD(lParam),HIWORD(lParam));
			//GetClientRect(hwnd, &gRect);
			break;	

		case WM_KEYDOWN:
			keys[wParam]=true;
			break;

		case WM_KEYUP:
			keys[wParam]=false;
			break;

		case WM_MOUSEMOVE:
			MousePos.x = LOWORD (lParam);
			MousePos.y = HIWORD (lParam);
			break;

		case WM_PAINT:
		    break;		

		case WM_DESTROY:	
			PostQuitMessage(0);				
			break;		
	}													

	return DefWindowProc (hwnd, message, wParam, lParam);																
}

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int nCmdShow)			
{	

    MSG         msg;	

	// initialise windows
	Window window("SuperDuper Opengl APP", S_WIDTH, S_HEIGHT, 0, false, hInstance, WndProc);
	HWND	hwnd = window.getHwnd();

	// initialise openGL
	OpenGL openGl;
	openGl.InitializeOpenGL(window.getRect().right, window.getRect().bottom, hwnd);
	game = new Game();
		
	while (gameRunning) {							
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE)) {
		    if (msg.message==WM_QUIT)
				break;
			TranslateMessage (&msg);							
			DispatchMessage (&msg);
		} else {
			//any intensive proccessing for the app,  do it here. 
			game->draw();
			openGl.swapBuffersGL();
		}
    }
	
	return msg.wParam ;										
}