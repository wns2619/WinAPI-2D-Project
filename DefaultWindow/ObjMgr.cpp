#include "stdafx.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "CollisionMgr.h"
#include "SceneMgr.h"
#include "NormalBlock.h"
#include "Egg.h"

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	Release();
}

void CObjMgr::Update(void)
{
	for (UINT i = 0; i < (UINT)OBJ_TYPE::END; ++i)
	{
		for (auto iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end();)
		{
			int iEvent = (*iter)->Update();

			if (OBJ_DEAD == iEvent)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}
}

void CObjMgr::LateUpdate(void)
{
	for (UINT i = 0; i < (UINT)OBJ_TYPE::END; ++i)
	{
		for (auto& iter : m_ObjList[i])
		{
			iter->LateUpdate();

			if (m_ObjList[i].empty())
				break;

			RENDERID eID = iter->GetRenderID();

			m_RenderSort[(UINT)eID].push_back(iter);
			
		}
	}

	//Player
	CCollisionMgr::GetInst()->Collision_RectWall(m_ObjList[(UINT)OBJ_TYPE::PLAYER], m_ObjList[(UINT)OBJ_TYPE::EGG]);
	CCollisionMgr::GetInst()->Collision_RectWall(m_ObjList[(UINT)OBJ_TYPE::PLAYER], m_ObjList[(UINT)OBJ_TYPE::NORMAL_BLOCK]);
	CCollisionMgr::GetInst()->Collision_RectWall(m_ObjList[(UINT)OBJ_TYPE::PLAYER], m_ObjList[(UINT)OBJ_TYPE::MOVE_BLOCK]);
	CCollisionMgr::GetInst()->Collision_RectWall(m_ObjList[(UINT)OBJ_TYPE::PLAYER], m_ObjList[(UINT)OBJ_TYPE::SIDE_BLOCK]);
	CCollisionMgr::GetInst()->Collision_RectWall(m_ObjList[(UINT)OBJ_TYPE::PLAYER], m_ObjList[(UINT)OBJ_TYPE::PASS_BLOCK]);
	CCollisionMgr::GetInst()->Collision_RectWall(m_ObjList[(UINT)OBJ_TYPE::PLAYER], m_ObjList[(UINT)OBJ_TYPE::PATTERN_BLOCK]);
	CCollisionMgr::GetInst()->Collision_RectWall(m_ObjList[(UINT)OBJ_TYPE::PLAYER], m_ObjList[(UINT)OBJ_TYPE::BULLDOG]);
	CCollisionMgr::GetInst()->Collision_RectWall(m_ObjList[(UINT)OBJ_TYPE::PLAYER], m_ObjList[(UINT)OBJ_TYPE::TRANSPARENT_BLOCK]);

	// Egg
	CCollisionMgr::GetInst()->Collision_RectWall(m_ObjList[(UINT)OBJ_TYPE::EGG], m_ObjList[(UINT)OBJ_TYPE::PLAYER]);
	CCollisionMgr::GetInst()->Collision_RectWall(m_ObjList[(UINT)OBJ_TYPE::EGG], m_ObjList[(UINT)OBJ_TYPE::NORMAL_BLOCK]);
	CCollisionMgr::GetInst()->Collision_RectWall(m_ObjList[(UINT)OBJ_TYPE::EGG], m_ObjList[(UINT)OBJ_TYPE::MOVE_BLOCK]);
	CCollisionMgr::GetInst()->Collision_RectWall(m_ObjList[(UINT)OBJ_TYPE::EGG], m_ObjList[(UINT)OBJ_TYPE::SIDE_BLOCK]);
	CCollisionMgr::GetInst()->Collision_RectWall(m_ObjList[(UINT)OBJ_TYPE::EGG], m_ObjList[(UINT)OBJ_TYPE::PASS_BLOCK]);
	CCollisionMgr::GetInst()->Collision_RectWall(m_ObjList[(UINT)OBJ_TYPE::EGG], m_ObjList[(UINT)OBJ_TYPE::PATTERN_BLOCK]);
	CCollisionMgr::GetInst()->Collision_RectWall(m_ObjList[(UINT)OBJ_TYPE::EGG], m_ObjList[(UINT)OBJ_TYPE::BULLDOG]);
	CCollisionMgr::GetInst()->Collision_RectWall(m_ObjList[(UINT)OBJ_TYPE::EGG], m_ObjList[(UINT)OBJ_TYPE::TRANSPARENT_BLOCK]);

	// Move

	CCollisionMgr::GetInst()->Collision_RectWall(m_ObjList[(UINT)OBJ_TYPE::MOVE_BLOCK], m_ObjList[(UINT)OBJ_TYPE::PLAYER]);
	CCollisionMgr::GetInst()->Collision_RectWall(m_ObjList[(UINT)OBJ_TYPE::MOVE_BLOCK], m_ObjList[(UINT)OBJ_TYPE::EGG]);
	CCollisionMgr::GetInst()->Collision_RectWall(m_ObjList[(UINT)OBJ_TYPE::MOVE_BLOCK], m_ObjList[(UINT)OBJ_TYPE::NORMAL_BLOCK]);
	CCollisionMgr::GetInst()->Collision_RectWall(m_ObjList[(UINT)OBJ_TYPE::MOVE_BLOCK], m_ObjList[(UINT)OBJ_TYPE::MOVE_BLOCK]);
	CCollisionMgr::GetInst()->Collision_RectWall(m_ObjList[(UINT)OBJ_TYPE::MOVE_BLOCK], m_ObjList[(UINT)OBJ_TYPE::SIDE_BLOCK]);
	CCollisionMgr::GetInst()->Collision_RectWall(m_ObjList[(UINT)OBJ_TYPE::MOVE_BLOCK], m_ObjList[(UINT)OBJ_TYPE::PASS_BLOCK]);
	CCollisionMgr::GetInst()->Collision_RectWall(m_ObjList[(UINT)OBJ_TYPE::MOVE_BLOCK], m_ObjList[(UINT)OBJ_TYPE::PATTERN_BLOCK]);
	CCollisionMgr::GetInst()->Collision_RectWall(m_ObjList[(UINT)OBJ_TYPE::MOVE_BLOCK], m_ObjList[(UINT)OBJ_TYPE::BULLDOG]);

	// Pass

	CCollisionMgr::GetInst()->Collision_RectWall(m_ObjList[(UINT)OBJ_TYPE::PASS_BLOCK], m_ObjList[(UINT)OBJ_TYPE::EGG]);

	// BULLDOG

	CCollisionMgr::GetInst()->Collision_RectWall(m_ObjList[(UINT)OBJ_TYPE::BULLDOG], m_ObjList[(UINT)OBJ_TYPE::PLAYER]);
	CCollisionMgr::GetInst()->Collision_RectWall(m_ObjList[(UINT)OBJ_TYPE::BULLDOG], m_ObjList[(UINT)OBJ_TYPE::EGG]);
	CCollisionMgr::GetInst()->Collision_RectWall(m_ObjList[(UINT)OBJ_TYPE::BULLDOG], m_ObjList[(UINT)OBJ_TYPE::NORMAL_BLOCK]);
	CCollisionMgr::GetInst()->Collision_RectWall(m_ObjList[(UINT)OBJ_TYPE::BULLDOG], m_ObjList[(UINT)OBJ_TYPE::MOVE_BLOCK]);
	CCollisionMgr::GetInst()->Collision_RectWall(m_ObjList[(UINT)OBJ_TYPE::BULLDOG], m_ObjList[(UINT)OBJ_TYPE::SIDE_BLOCK]);
	CCollisionMgr::GetInst()->Collision_RectWall(m_ObjList[(UINT)OBJ_TYPE::BULLDOG], m_ObjList[(UINT)OBJ_TYPE::PASS_BLOCK]);
	CCollisionMgr::GetInst()->Collision_RectWall(m_ObjList[(UINT)OBJ_TYPE::BULLDOG], m_ObjList[(UINT)OBJ_TYPE::PATTERN_BLOCK]);


	// Wolf

	CCollisionMgr::GetInst()->Collision_RectWall(m_ObjList[(UINT)OBJ_TYPE::WOLF], m_ObjList[(UINT)OBJ_TYPE::PLAYER]);
	CCollisionMgr::GetInst()->Collision_RectWall(m_ObjList[(UINT)OBJ_TYPE::WOLF], m_ObjList[(UINT)OBJ_TYPE::EGG]);
	CCollisionMgr::GetInst()->Collision_RectWall(m_ObjList[(UINT)OBJ_TYPE::WOLF], m_ObjList[(UINT)OBJ_TYPE::NORMAL_BLOCK]);
	CCollisionMgr::GetInst()->Collision_RectWall(m_ObjList[(UINT)OBJ_TYPE::WOLF], m_ObjList[(UINT)OBJ_TYPE::MOVE_BLOCK]);
	CCollisionMgr::GetInst()->Collision_RectWall(m_ObjList[(UINT)OBJ_TYPE::WOLF], m_ObjList[(UINT)OBJ_TYPE::SIDE_BLOCK]);
	CCollisionMgr::GetInst()->Collision_RectWall(m_ObjList[(UINT)OBJ_TYPE::WOLF], m_ObjList[(UINT)OBJ_TYPE::PASS_BLOCK]);
	CCollisionMgr::GetInst()->Collision_RectWall(m_ObjList[(UINT)OBJ_TYPE::WOLF], m_ObjList[(UINT)OBJ_TYPE::PATTERN_BLOCK]);
	


	// { PLAYER, EGG, NONE_BLOCK, NORMAL_BLOCK, MOVE_BLOCK, SIDE_BLOCK, PASS_BLOCK, PATTERN_BLOCK, BULLDOG, WOLF, END };
}

void CObjMgr::Render(HDC _hDC)
{

	for (UINT i = 0; i < (UINT)RENDERID::END; ++i)
	{
		m_RenderSort[i].sort([&](CObj* pDest, CObj* pSrc)->bool
		{
			return pDest->GetInfo().fY < pSrc->GetInfo().fY;
		});

		for (auto& iter : m_RenderSort[i])
			iter->Render(_hDC);

		m_RenderSort[i].clear();
	}
}

void CObjMgr::Release(void)
{

	for (UINT i = 0; i < (UINT)OBJ_TYPE::END; ++i)
	{
		list<CObj*>::iterator iter = m_ObjList[i].begin();
		for (; iter != m_ObjList[i].end();)
		{
			if ((*iter) != nullptr)
				Safe_Delete<CObj*>(*iter);
			else
				++iter;
		}

		m_ObjList[i].clear();
	}

	for (UINT i = 0; i < (UINT)RENDERID::END; ++i)
	{
		m_RenderSort[i].clear();
	}
}

void CObjMgr::Add_Obj(OBJ_TYPE _Type, CObj * pObj)
{
	if ((UINT)OBJ_TYPE::END <= (UINT)_Type || pObj == nullptr)
		return;

	m_ObjList[(UINT)_Type].push_back(pObj);
}

void CObjMgr::Add_Render(RENDERID _eRender, CScene * pScene)
{
	if ((UINT)RENDERID::END <= (UINT)_eRender || pScene == nullptr)
		return;

}

void CObjMgr::Delete_ID(OBJ_TYPE _eID)
{
	for (auto& iter : m_ObjList[(UINT)_eID])
		Safe_Delete(iter);

m_ObjList[(UINT)_eID].clear();
}

CObj * CObjMgr::Find_Obj(OBJ_TYPE _eType, float x, float y, DIRECTION eDir, float fSpeed, float fRange)
{
	for (UINT i = 0; i < (UINT)OBJ_TYPE::END; ++i)
	{
		for (auto iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); ++iter)
		{
			if ((*iter)->GetObjType() == OBJ_TYPE::NORMAL_BLOCK)
			{
				float fBlockX = 0.f;
				INFO objInfo = (*iter)->GetInfo();

				if (eDir == DIRECTION::RIGHT)
				{
					fBlockX = objInfo.fX + (objInfo.fCX / 2.f);
				}
				else
					fBlockX = objInfo.fX - (objInfo.fCX / 2.f);


				float fBlockY = objInfo.fY + objInfo.fCY;

				// 플레이어와 블록의 거리와 각도 계산
				float fDistanceX = fBlockX - x;
				float fDistanceY = fBlockY - y;
				float fDistance = sqrtf(fDistanceX * fDistanceX + fDistanceY * fDistanceY);
				float fAngle = atan2f(fDistanceY, fDistanceX) * 180.f / PI;

				// 블록이 대각선 방향인지 확인 
				bool bDiagonal = (fAngle > 45.f && fAngle <= 135.f) || (fAngle > -135.f && fAngle <= -45.f);

				if (bDiagonal && fDistance <= fRange) // 대각선에 블록이 있다면. Iter 반환해. + 근데 조건이 하나 더 붙어.
				{
					// (state == delete) // 그럼 이 상태인 애를 리턴하고.
					// else *iter;
					if (dynamic_cast<CNormalBlock*>(*iter)->GetBlockState() == BLOCK_STATE::DELETE_BLOCK)
						return *iter;
					else if (dynamic_cast<CNormalBlock*>(*iter)->GetBlockState() == BLOCK_STATE::USING_BLOCK)
						return *iter; // state = 얘는 존재하는 블록과 내가 삭제한 블록을 나눠.
				}
			}
			else
			{
				if ((*iter)->GetObjType() == _eType)
				{
					float fBlockX = 0.f;
					INFO objInfo = (*iter)->GetInfo();

					if (eDir == DIRECTION::RIGHT)
					{
						fBlockX = objInfo.fX + (objInfo.fCX / 2.f);
					}
					else
						fBlockX = objInfo.fX - (objInfo.fCX / 2.f);


					float fBlockY = objInfo.fY + objInfo.fCY;

					// 플레이어와 블록의 거리와 각도 계산
					float fDistanceX = fBlockX - x;
					float fDistanceY = fBlockY - y;
					float fDistance = sqrtf(fDistanceX * fDistanceX + fDistanceY * fDistanceY);
					float fAngle = atan2f(fDistanceY, fDistanceX) * 180.f / PI;

					// 블록이 대각선 방향인지 확인 
					bool bDiagonal = (fAngle > 45.f && fAngle <= 135.f) || (fAngle > -135.f && fAngle <= -45.f);

					if (bDiagonal && fDistance <= fRange) // 대각선에 블록이 있다면. Iter 반환해. + 근데 조건이 하나 더 붙어.
					{
						return *iter;
					}
				}
			}
		}
	}
	return nullptr;
}

CObj * CObjMgr::Find_Block(OBJ_TYPE _eType, float x, float y, float Range)
{
	for (UINT i = 0; i < (UINT)OBJ_TYPE::END; ++i)
	{
		for (auto iter = m_ObjList[i].begin(); iter != m_ObjList[i].end(); ++iter)
		{
			if ((*iter)->GetObjType() == OBJ_TYPE::NORMAL_BLOCK)
			{
				float fBlockX = 0.f;
				INFO ObjInfo = (*iter)->GetInfo();

				if (dynamic_cast<CEgg*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::EGG).front())->GetEggCol().m_bColBottom &&
					dynamic_cast<CEgg*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::EGG).front())->GetEggCol().m_bColLeft) // 노멀블록이고 bottom이 켜져있다면?
				{
					fBlockX = ObjInfo.fX + (ObjInfo.fCX / 2.f);
				}
				else if (dynamic_cast<CEgg*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::EGG).front())->GetEggCol().m_bColBottom &&
					dynamic_cast<CEgg*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::EGG).front())->GetEggCol().m_bColRight)
				{
					fBlockX = ObjInfo.fX - (ObjInfo.fCX / 2.f);
				}

				float fEggX = dynamic_cast<CEgg*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::EGG).front())->GetInfo().fX;

				float fDistanceX = fBlockX - x;

				if (fDistanceX <= Range)
				{
					if (dynamic_cast<CNormalBlock*>(*iter)->GetBlockState() == BLOCK_STATE::USING_BLOCK)
					{
						return *iter;
					}
				}
			}
		}
	}
	return nullptr;
}

CObj * CObjMgr::Get_Target(OBJ_TYPE eID, CObj * pObj)
{
	if (m_ObjList[(UINT)eID].empty() || nullptr == pObj)
		return nullptr;

	CObj*		pTarget = nullptr;
	float		fDistance = 0.f;

	for (auto& iter : m_ObjList[(UINT)eID])
	{
		if (iter->GetDead())
			continue;

		float	fWidth = fabs(iter->GetInfo().fX - pObj->GetInfo().fX);
		float	fHeight = fabs(iter->GetInfo().fY - pObj->GetInfo().fY);

		float	fDiagonal = sqrtf(pow(fWidth, 2) + pow(fHeight, 2));

		if ((!pTarget) || fDistance > fDiagonal)
		{
			pTarget = iter;
			fDistance = fDiagonal;
		}
	}

	return pTarget;
}

void CObjMgr::ObjLock()
{
}
