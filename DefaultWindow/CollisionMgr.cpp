#include "stdafx.h"
#include "CollisionMgr.h"
#include "Obj.h"
#include "Egg.h"
#include "ObjMgr.h"
#include "NormalBlock.h"

CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Collision_Rect(list<CObj*> Dst, list<CObj*> Src)
{
	RECT	rc{};

	for (auto& Dest : Dst)
	{
		for (auto& Sour : Src)
		{
			if (IntersectRect(&rc, &(Dest->GetRect()), &(Sour->GetRect())))
			{
				// 충돌 시 조금 수정 
				Dest->SetDead(true);
				Sour->SetDead(true);
			}
		}
	}
}

void CCollisionMgr::Collision_Sphere(list<CObj*> Dst, list<CObj*> Src)
{
	for (auto& Dest : Dst)
	{
		for (auto& Sour : Src)
		{
			if (Check_Sphere(Dest, Sour))
			{
				Dest->SetDead(true);
				Sour->SetDead(true);
			}
		}
	}
}

bool CCollisionMgr::Check_Sphere(CObj * pDst, CObj * pSrc)
{
	float fWidth = fabs(pDst->GetInfo().fX - pSrc->GetInfo().fX);
	float fHeight = fabs(pDst->GetInfo().fY - pSrc->GetInfo().fY);

	float fDiagonal = sqrtf(pow(fWidth, 2) + pow(fHeight, 2));

	float fRadius = (pDst->GetInfo().fCX + pSrc->GetInfo().fCX) * 0.5f;

	return fDiagonal <= fRadius;
}

void CCollisionMgr::Collision_RectEx(list<CObj*> Dst, list<CObj*> Src)
{
	float fX = 0.f, fY = 0.f;

	for (auto& Dest : Dst)
	{
		for (auto& Sour : Src)
		{
			if (Check_Rect(Dest, Sour, &fX, &fY))
			{
				// 상하 충돌
				if (fX > fY)
				{
					// 상하 충돌 조건문 나중에 개편
					if (Dest->GetInfo().fY < Sour->GetInfo().fY)
					{
						Dest->SetY(-fY);
					}
					else
					{
						Dest->SetY(fY);
					}
				}
				// 좌우 충돌
				else
				{
					// 좌우 충돌 조건문도 나중에 개편 
					if (Dest->GetInfo().fX < Sour->GetInfo().fX)
					{
						Dest->SetX(-fX);
					}
					else
					{
						Dest->SetX(fX);
					}
				}
			}
		}
	}
}

void CCollisionMgr::Collision_RectWall(list<CObj*> Dst, list<CObj*> Src)
{
	float fX = 0.f, fY = 0.f;

	for (auto& Dest : Dst)
	{
		for (auto& Sour : Src)
		{
			// 둘이 충돌체가 같거나, 타입이 BLOCK이 아니라면 충돌처리 안함.
	/*		if (Dest == Sour
				&&(Dest->GetObjType() == OBJ_TYPE::NORMAL_BLOCK) == (Sour->GetObjType() == OBJ_TYPE::NORMAL_BLOCK))
				return;*/

			if (Dest->GetObjType() == OBJ_TYPE::EGG && Sour->GetObjType() == OBJ_TYPE::NORMAL_BLOCK)
			{
				if (Egg_Rect(Dest, Sour, &fX, &fY))
				{
					if (fX > fY)
					{
						// 상하 충돌
						if (Dest->GetInfo().fY < Sour->GetInfo().fY)
						{
							Dest->Collider(Sour, COL_DIR::BOTTOM, fY);
							Sour->Collider(Dest, COL_DIR::TOP, fY);
						}
						else
						{
							Dest->Collider(Sour, COL_DIR::TOP, fY);
							Sour->Collider(Dest, COL_DIR::BOTTOM, fY);
						}
					}
					else if (fX < fY)
					{
						// 좌우 충돌
						if (Dest->GetInfo().fX < Sour->GetInfo().fX)
						{
							Dest->Collider(Sour, COL_DIR::RIGHT, fX);
							Sour->Collider(Dest, COL_DIR::LEFT, fX);
						}
						else if (Dest->GetInfo().fX > Sour->GetInfo().fX)
						{
							Dest->Collider(Sour, COL_DIR::LEFT, fX);
							Sour->Collider(Dest, COL_DIR::RIGHT, fX);
						}
					}
				}
				else
				{
					/*dynamic_cast<CEgg*>(Dest)->Set_AllEggCol(false);*/
				}
			}
		
			else if (Check_Rect(Dest, Sour, &fX, &fY))
			{
				if (fX > fY)
				{
					// 상하 충돌
					if (Dest->GetInfo().fY < Sour->GetInfo().fY)
					{
 						Dest->Collider(Sour, COL_DIR::BOTTOM, fY);
						Sour->Collider(Dest, COL_DIR::TOP, fY);
					}
					else
					{
						Dest->Collider(Sour, COL_DIR::TOP, fY);
						Sour->Collider(Dest, COL_DIR::BOTTOM, fY);
					}
				}
				else
				{
					// 좌우 충돌
					if (Dest->GetInfo().fX < Sour->GetInfo().fX)
					{
						Dest->Collider(Sour, COL_DIR::RIGHT, fX);
						Sour->Collider(Dest, COL_DIR::LEFT, fX);
					}
					else if (Dest->GetInfo().fX > Sour->GetInfo().fX)
					{
						Dest->Collider(Sour, COL_DIR::LEFT, fX);        
						Sour->Collider(Dest, COL_DIR::RIGHT, fX);
					}
				}
			}
		}
	}
}


bool CCollisionMgr::Check_Rect(CObj * pDst, CObj * pSrc, float * pX, float * pY)
{
	float fWidth = fabs(pDst->GetInfo().fX - pSrc->GetInfo().fX);
	float fHeight = fabs(pDst->GetInfo().fY - pSrc->GetInfo().fY);

	float fRadiusX = (pDst->GetInfo().fCX + pSrc->GetInfo().fCX) * 0.5f;
	float fRadiusY = (pDst->GetInfo().fCY + pSrc->GetInfo().fCY) * 0.5f;

	if ((fRadiusX > fWidth) && (fRadiusY > fHeight))
	{
		*pX = fRadiusX - fWidth;
		*pY = fRadiusY - fHeight;

		return true;
	}

	return false;
}

bool CCollisionMgr::Egg_Rect(CObj * pDst, CObj * pSrc, float * pX, float * pY)
{
	float fWidth = fabs(pDst->GetInfo().fX - pSrc->GetInfo().fX);
	float fHeight = fabs(pDst->GetInfo().fY - pSrc->GetInfo().fY);

	float fRadiusX = (pDst->GetInfo().fCX + pSrc->GetInfo().fCX) * 0.5f;
	float fRadiusY = (pDst->GetInfo().fCY + pSrc->GetInfo().fCY) * 0.5f;

	if ((fRadiusX > fWidth) && (fRadiusY > fHeight))
	{
		*pX = fRadiusX - fWidth;
		*pY = fRadiusY - fHeight;

		return true;
	}

	return false;

	//float fWidth = fabs(pDst->GetInfo().fX - pSrc->GetInfo().fX);
	//float fHeight = fabs(pDst->GetInfo().fY - pSrc->GetInfo().fY);

	//float fRadiusX = (pDst->GetInfo().fCX + pSrc->GetInfo().fCX) * 0.5f;
	//float fRadiusY = (pDst->GetInfo().fCY + pSrc->GetInfo().fCY) * 0.5f;

	//int ColLeft = dynamic_cast<CEgg*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::EGG).front())->GetEggCol().m_bColLeft;
	//int ColRight = dynamic_cast<CEgg*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::EGG).front())->GetEggCol().m_bColRight;
	//int ColTop = dynamic_cast<CEgg*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::EGG).front())->GetEggCol().m_bColTop;
	//int ColBottom = dynamic_cast<CEgg*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::EGG).front())->GetEggCol().m_bColBottom;

	//int a = 0;
	//// pDst - egg 

	//if (pSrc->GetBlockID() == dynamic_cast<CEgg*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::EGG).front())->GetEggCol().m_bColRight)
	//{
	//	if ((fRadiusX + 2.5f <= fWidth) || (fRadiusY <= fHeight))
	//	{
	//		dynamic_cast<CEgg*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::EGG).front())->Set_EggColRight(false);
	//	}
	//}

	//if (pSrc->GetBlockID() == dynamic_cast<CEgg*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::EGG).front())->GetEggCol().m_bColLeft)
	//{
	//	if ((fRadiusX + 2.5f <= fWidth) || (fRadiusY <= fHeight))
	//	{
	//		dynamic_cast<CEgg*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::EGG).front())->Set_EggColLeft(false);
	//	}
	//}

	//if (pSrc->GetBlockID() == dynamic_cast<CEgg*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::EGG).front())->GetEggCol().m_bColTop)
	//{
	//	if ((fRadiusX + 2.5f <= fWidth) || (fRadiusY <= fHeight))
	//	{
	//		dynamic_cast<CEgg*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::EGG).front())->Set_EggColTop(false);
	//	}
	//}

	//if (pSrc->GetBlockID() == dynamic_cast<CEgg*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::EGG).front())->GetEggCol().m_bColBottom)
	//{
	//	if ((fRadiusX + 2.5f <= fWidth) || (fRadiusY <= fHeight))
	//	{
	//		dynamic_cast<CEgg*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::EGG).front())->Set_EggColBottm(false);
	//	}
	//}


	//if ((fRadiusX + 2.5f > fWidth) && (fRadiusY > fHeight))
	//{
	//	*pX = fRadiusX- fWidth;
	//	*pY = (fRadiusY + 2.5f - fHeight);

	//	return true;
	//}

	//return false;
}
