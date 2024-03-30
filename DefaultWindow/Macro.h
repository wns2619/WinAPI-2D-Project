#pragma once

#define			WINCX		800
#define			WINCY		600

#define			PURE		= 0
#define			VK_MAX		0xff

#define			TILECX		50
#define			TILECY		50

#define			TILEX		16
#define			TILEY		54

#define			PI			3.14159265f


#define SINGLETONE(type)\
public:\
	static type* GetInst()\
	{\
		static type manager;\
		return &manager;\
	}\
private:\
	type();\
	~type();



#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW 

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 

#endif
#endif