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
	float	m_fScrollX; // X�� ��ũ�� 
	float	m_fScrollY; // Y�� ��ũ��
};

