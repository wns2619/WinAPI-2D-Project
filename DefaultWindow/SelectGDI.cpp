#include "stdafx.h"
#include "SelectGDI.h"
#include "MainGame.h"


CSelectGDI::CSelectGDI(HDC _dc, FONT_TYPE _eFontType)
	: m_hDC(_dc), m_hDefaultFont(nullptr)
{
	HFONT hFont = (HFONT)CMainGame::GetInst()->GetFont(_eFontType);
	m_hDefaultFont = (HFONT)SelectObject(_dc, hFont);
}


CSelectGDI::~CSelectGDI()
{
	SelectObject(m_hDC, m_hDefaultFont);
}
