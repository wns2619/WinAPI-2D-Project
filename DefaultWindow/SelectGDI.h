#pragma once
class CSelectGDI
{
public:
	CSelectGDI(HDC _dc, FONT_TYPE _eFontType);
	~CSelectGDI();

private:
	HDC        m_hDC;
	HFONT    m_hDefaultFont;

};

