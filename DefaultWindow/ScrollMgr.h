#pragma once


class CScrollMgr
{
	SINGLETONE(CScrollMgr);

public: // Setter
	void SetScrollX(float _fX) { m_fScrollX += _fX; }
	void SetScrollY(float _fY) { m_fScrollY += _fY; }

public: // Getter
	float GetScrollX(void)	   { return m_fScrollX; }
	float GetScrollY(void)	   { return m_fScrollY; }

public:
	void  ScrollLock(void);
	void  ReSetScroll(void)	   { m_fScrollY = 0.f, m_fScrollX = 0.f; }

private:
	float	m_fScrollX; // X绵 胶农费 
	float	m_fScrollY; // Y绵 胶农费
};

