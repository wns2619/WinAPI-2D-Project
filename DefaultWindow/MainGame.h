#pragma once

#include "Define.h"
#include "Player.h"

class CMainGame
{
	SINGLETONE(CMainGame);

public:
	void		Initialize(void);
	void		Update(void);
	void		LateUpdate(void);
	void		Render();
	void		Release(void);

public: // Getter
	HDC			GetMainDC(void) { return m_DC; }
	HDC			GetSubDC(void)	{ return m_memDC; }


	HFONT		GetFont(FONT_TYPE _eFontType) { return m_hfArr[(UINT)_eFontType]; }

public:

private:
	HDC			m_DC;
	HFONT		m_hfArr[(UINT)FONT_TYPE::END];

	// Double buffering 관련
	HDC			m_memDC;
	HBITMAP		m_hBit;

	// 프레임 관련
	int			m_iFPS;
	TCHAR		m_szFPS[32];
	DWORD		m_dwTime;

};

