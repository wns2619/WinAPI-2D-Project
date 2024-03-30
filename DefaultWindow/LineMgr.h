#pragma once

class CLine;
class CLineMgr
{
	SINGLETONE(CLineMgr);

public:
	void Initialize(void);
	void Render(HDC _hDC);
	void Release(void);
	bool Collision_Line(float &fX, float& fY, float & fCY, float *pY);

private:
	list<CLine*> m_LineList;
};

