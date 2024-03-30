#include "stdafx.h"
#include "ScrollMgr.h"


CScrollMgr::CScrollMgr()
{
}


CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::ScrollLock(void)
{
	if (0.f < m_fScrollX)
		m_fScrollX = 0.f;

	if (0.f < m_fScrollY)
		m_fScrollY = 0.f;

	if (WINCX - 800 > m_fScrollX)
		m_fScrollX = WINCX - 800;

	if (WINCY - 3100 > m_fScrollY)
		m_fScrollY = WINCY - 3100;
}
