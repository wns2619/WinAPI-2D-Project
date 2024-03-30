#pragma once


class CObj;
class CCollisionMgr
{
	SINGLETONE(CCollisionMgr);

public:
	void	Collision_Rect(list<CObj*>Dst, list<CObj*> Src);
	void	Collision_Sphere(list<CObj*> Dst, list<CObj*> Src);
	void	Collision_RectEx(list<CObj*>Dst, list<CObj*> Src);
	void	Collision_RectWall(list<CObj*>Dst, list<CObj*> Src);

	bool	Check_Sphere(CObj* pDst, CObj* pSrc);
	bool	Check_Rect(CObj* pDst, CObj* pSrc, float* pX, float* pY);
	bool	Egg_Rect(CObj* pDst, CObj* pSrc, float *pX, float *pY);
};

