#include "stdafx.h"
#include "LineMgr.h"
#include "Line.h"

CLineMgr::CLineMgr()
{
}


CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize(void)
{
}

void CLineMgr::Render(HDC _hDC)
{
	for (auto& iter : m_LineList)
		iter->Render(_hDC);
}

void CLineMgr::Release(void)
{
	for_each(m_LineList.begin(), m_LineList.end(), CDeleteObj());
	m_LineList.clear();
}

bool CLineMgr::Collision_Line(float & fX, float & fY, float & fCY, float * pY)
{
	if (m_LineList.empty())
		return false;

	float fLineY(0), fClosestDistance(50);
	CLine*	pTarget = nullptr;
	float	x1 = 0;
	float	x2 = 0;
	float	y1 = 0;
	float	y2 = 0;
	for (auto& iter : m_LineList)
	{
		if (fX >= iter->GetLine().tLPoint.fX && fX <= iter->GetLine().tRPoint.fX)
		{
			x1 = iter->GetLine().tLPoint.fX;
			x2 = iter->GetLine().tRPoint.fX;
			y1 = iter->GetLine().tLPoint.fY;
			y2 = iter->GetLine().tRPoint.fY;
			fLineY = ((y2 - y1) / (x2 - x1)) * (fX - x1) + y1;
			if (fY + fCY*0.5f - 5.f < fLineY)
			{
				float fDistance = fabs(fY + fCY*0.5f - 5.f - fLineY);
				if (fClosestDistance > fDistance)
				{
					pTarget = iter;
					fClosestDistance = fDistance;
				}
			}

		}
	}

	if (!pTarget)
		return false;

	// Y - y1 = ((y2 - y1) / (x2 - x1)) * (X - x1)

	x1 = pTarget->GetLine().tLPoint.fX;
	x2 = pTarget->GetLine().tRPoint.fX;
	y1 = pTarget->GetLine().tLPoint.fY;
	y2 = pTarget->GetLine().tRPoint.fY;

	*pY = ((y2 - y1) / (x2 - x1)) * (fX - x1) + y1 - fCY*0.5f;

	return true;
}
