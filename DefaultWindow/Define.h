#pragma once

#define			WINCX		800
#define			WINCY		600

#define			PURE		= 0
#define			OBJ_NOEVENT	0
#define			OBJ_DEAD	1

//#ifdef UNICODE
//#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
//#else
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
//#endif


extern HWND	g_hWnd;
extern bool Gravity;
extern int TotalScore;