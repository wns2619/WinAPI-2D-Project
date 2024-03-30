#include "stdafx.h"
#include "Line.h"
#include "ScrollMgr.h"


CLine::CLine()
{
}

CLine::CLine(LINEPOINT _LPoint, LINEPOINT _RPoint)
	: m_tLine(_LPoint, _RPoint)
{
}

CLine::CLine(LINE & tLine)
	: m_tLine(tLine)
{
}


CLine::~CLine()
{
}

void CLine::Render(HDC _hDC)
{
	float	fScrollX = CScrollMgr::GetInst()->GetScrollX();
	MoveToEx(_hDC, int(m_tLine.tLPoint.fX + fScrollX), (int)m_tLine.tLPoint.fY, nullptr);
	LineTo(_hDC, int(m_tLine.tRPoint.fX + fScrollX), (int)m_tLine.tRPoint.fY);
}
