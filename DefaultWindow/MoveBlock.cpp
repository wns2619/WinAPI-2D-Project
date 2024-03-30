#include "stdafx.h"
#include "MoveBlock.h"
#include "Player.h"
#include "NormalBlock.h"

// Manager Header
#include "ResMgr.h"
#include "ScrollMgr.h"
#include "LineMgr.h"
#include "SoundMgr.h"
#include "ObjMgr.h"

bool	IsMoveBlock = false;

CMoveBlock::CMoveBlock()
	: m_bIsBlocked(false)
	, m_fCurPos(0.f)
	, m_fPrePos(0.f)
{

}


CMoveBlock::~CMoveBlock()
{
	Release();
}

void CMoveBlock::Initialize(void)
{
	SetJumpTime(0.f);
	SetJumpPower(10.f);
	SetObjType(OBJ_TYPE::PLAYER);
	SetGround(true);
	SetJump(false);
	SetDir(DIRECTION::RIGHT);
	Set_Block(0, 2);



	SetInfo(INFO{ 0, 0, TILECX, TILECY });
	SetObjType(OBJ_TYPE::MOVE_BLOCK);
	Set_Tile(TILE_TYPE::MOVE_BLOCK);
	CResMgr::GetInst()->Insert_Texture(L"../DuckMazeImg/Tile/Move.bmp", L"MoveTile");

	SetRenderID(RENDERID::GAMEOBJECT);
}

int CMoveBlock::Update(void)
{
	CObj::Update_Rect();



	return OBJ_NOEVENT;

}

void CMoveBlock::LateUpdate(void)
{
	//if (GetGround() == false)
	//{
	//	AddY(-(GetJumpPower() * (GetJumpTime() + 0.01f) - 9.8f * GetJumpTime() * GetJumpTime() * 0.5f));
	//	AddTime(0.15f);
	//}


	float fY = 0.f;
	float InfofX = GetInfo().fX;
	float InfofY = GetInfo().fY;
	float InfofCY = GetInfo().fCY;

	bool bLineCol = CLineMgr::GetInst()->Collision_Line(InfofX, InfofY, InfofCY, &fY);



	if (GetGravity())
	{
		AddY(-(0.f * (GetJumpTime()) - 9.8f * GetJumpTime() * GetJumpTime() * 0.5));
		AddTime(0.05f);

		if (0.f != m_fCurPos && 0.f != m_fPrePos)
		{
			if (m_fCurPos - m_fPrePos > 49)
			{
				CSoundMgr::GetInst()->PlaySoundW(L"MoveBlock.wav", MOVEBLOCK_SOUND, 1.f);
			}
		}
	}

}

void CMoveBlock::Render(HDC hDC)
{
	float fScrollX = CScrollMgr::GetInst()->GetScrollX();
	float fScrollY = CScrollMgr::GetInst()->GetScrollY();

	HDC	  hMemDC = CResMgr::GetInst()->Find_Image(L"MoveTile");



	BitBlt(hDC,
		int(GetRect().left + fScrollX),
		int(GetRect().top + fScrollY),
		TILECX,
		TILECY,
		hMemDC,
		TILECX * Get_DrawID(), 0, SRCCOPY);
}

void CMoveBlock::Release(void)
{

}

void CMoveBlock::Collider(CObj * _pObj, COL_DIR eDir, float fPush)
{
	
	OBJ_TYPE eType = _pObj->GetObjType();

	void(CObj::*fp)(double, double);


	fp = &CObj::AddXTime;

	switch (eType)
	{
	case OBJ_TYPE::PLAYER:
		switch (eDir)
		{
		case COL_DIR::BOTTOM:

			break;
		case COL_DIR::TOP:
			break;
		case COL_DIR::LEFT:
		{
			if (dynamic_cast<CPlayer*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::PLAYER).front())->GetCountY() == 8)
				{
					if (GetMoving() == false)
					{
						SetMoving(true);
						thread t(fp, this, 50.f, 1.f);
						t.detach();
					}

					SetGravity(true);
				}
		}
		break;

		case COL_DIR::RIGHT:
		{
			if (dynamic_cast<CPlayer*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::PLAYER).front())->GetCountY() == 8)
				{
					if (GetMoving() == false)
					{
						SetMoving(true);
						thread t(fp, this, -50.f, 1.f);
						t.detach();
					}

					SetGravity(true);
				}
		}
		break;
		}
		break;

	case OBJ_TYPE::MOVE_BLOCK:
		switch (eDir)
		{
		case COL_DIR::RIGHT:
			if (dynamic_cast<CPlayer*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::PLAYER).front())->GetCountY() == 8)
				{
					AddX(-fPush);
					SetGravity(true);
				}
			break;
		case COL_DIR::LEFT:
			if (dynamic_cast<CPlayer*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::PLAYER).front())->GetCountY() == 8)
				{
					AddX(fPush);
					SetGravity(true);
				}
			break;
		case COL_DIR::TOP:
			//AddY(-fPush);
			if (dynamic_cast<CPlayer*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::PLAYER).front())->GetCountY() == 8)
				{
					SetJumpTime(0.f);
					SetGravity(true);
				}
			break;
		case COL_DIR::BOTTOM:
			if (dynamic_cast<CPlayer*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::PLAYER).front())->GetCountY() == 8)
				{
					SetGravity(false);


					m_fPrePos = m_fCurPos;

					m_fCurPos = _pObj->GetInfo().fY;
				}
			break;
		}
		break;

		// 두 물체가 충돌했을 때. 위 아래.

	case OBJ_TYPE::NORMAL_BLOCK:
		switch (eDir)
		{
			// 노말블록과 닿았을 때 움직이는 방향의 힘을 반대로 돌리면 멈춘다.
		case COL_DIR::RIGHT:
			if (dynamic_cast<CPlayer*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::PLAYER).front())->GetCountY() == 8)
				if (dynamic_cast<CNormalBlock*>(_pObj)->GetBlockState() == BLOCK_STATE::USING_BLOCK)
				{
					AddX(-fPush);
					SetGravity(false);
				}
			break;
		case COL_DIR::LEFT:
			if (dynamic_cast<CPlayer*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::PLAYER).front())->GetCountY() == 8)
				if (dynamic_cast<CNormalBlock*>(_pObj)->GetBlockState() == BLOCK_STATE::USING_BLOCK)
				{
					AddX(fPush);
					SetGravity(false);
				}
			break;
		case COL_DIR::BOTTOM:
			if (dynamic_cast<CPlayer*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::PLAYER).front())->GetCountY() == 8)
				if (dynamic_cast<CNormalBlock*>(_pObj)->GetBlockState() == BLOCK_STATE::USING_BLOCK)
				{
					if (!GetGround())
					{
						SetJump(false);
						SetGravity(false);
					}


					m_fPrePos = m_fCurPos;

					m_fCurPos = _pObj->GetInfo().fY;


					/*		CSoundMgr::GetInst()->PlaySoundW(L"MoveBlock.wav", MOVEBLOCK_SOUND, 1.f);*/


					AddY(-fPush);
					SetJumpTime(0.f);

					/*Gravity = false;*/
				}
			break;
		case COL_DIR::TOP:
			if (dynamic_cast<CPlayer*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::PLAYER).front())->GetCountY() == 8)
				if (dynamic_cast<CNormalBlock*>(_pObj)->GetBlockState() == BLOCK_STATE::USING_BLOCK)
				{
					SetGravity(true);
					AddY(fPush);
				}
			break;
		}
		break;

	case OBJ_TYPE::SIDE_BLOCK:
		switch (eDir)
		{
		case COL_DIR::RIGHT:
			if (dynamic_cast<CPlayer*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::PLAYER).front())->GetCountY() == 8)
				{
					AddX(-fPush);
				}
			break;
		case COL_DIR::LEFT:
			if (dynamic_cast<CPlayer*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::PLAYER).front())->GetCountY() == 8)
				{
					AddX(fPush);
				}
			break;
		}
		break;

	case OBJ_TYPE::PATTERN_BLOCK:
		switch (eDir)
		{
			// 노말블록과 닿았을 때 움직이는 방향의 힘을 반대로 돌리면 멈춘다.
		case COL_DIR::RIGHT:
			if (dynamic_cast<CPlayer*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::PLAYER).front())->GetCountY() == 8)
				{
					SetGravity(false);
					AddX(-fPush);
				}
			break;
		case COL_DIR::LEFT:
			if (dynamic_cast<CPlayer*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::PLAYER).front())->GetCountY() == 8)
				{
					SetGravity(false);
					AddX(fPush);
				}
			break;
		case COL_DIR::BOTTOM:
			if (dynamic_cast<CPlayer*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::PLAYER).front())->GetCountY() == 8)
				{
					if (!GetGround())
					{
						SetJump(false);
						SetGravity(false);
					}


					m_fPrePos = m_fCurPos;

					m_fCurPos = _pObj->GetInfo().fY;


					AddY(-fPush);
					SetJumpTime(0.f);

					/*CSoundMgr::GetInst()->PlaySoundW(L"MoveBlock", MOVEBLOCK_SOUND, 1.f);*/
					/*Gravity = false;*/
				}
			break;
		case COL_DIR::TOP:
			if (dynamic_cast<CPlayer*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::PLAYER).front())->GetCountY() == 8)
			AddY(fPush);
			break;
		}
		break;

	case OBJ_TYPE::PASS_BLOCK:
		switch (eDir)
		{
		case COL_DIR::RIGHT:
			if (dynamic_cast<CPlayer*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::PLAYER).front())->GetCountY() == 8)
				{
					AddX(-fPush);
					SetGravity(false);
				}
			break;
		case COL_DIR::LEFT:
			if (dynamic_cast<CPlayer*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::PLAYER).front())->GetCountY() == 8)
				{
					AddX(fPush);
					SetGravity(false);
				}
			break;
		case COL_DIR::BOTTOM:
			if (dynamic_cast<CPlayer*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::PLAYER).front())->GetCountY() == 8)
				{
					if (!GetGround())
					{
						SetJump(false);
						SetGravity(false);
					}


					m_fPrePos = m_fCurPos;

					m_fCurPos = _pObj->GetInfo().fY;


					AddY(-fPush);
					SetJumpTime(0.f);

					/*	CSoundMgr::GetInst()->PlaySoundW(L"MoveBlock.wav", MOVEBLOCK_SOUND, 1.f);*/
					/*Gravity = false;*/
				}
			break;
		case COL_DIR::TOP:
			if (dynamic_cast<CPlayer*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::PLAYER).front())->GetCountY() == 8)
				{
					SetGravity(false);
					AddY(fPush);
				}
			break;
		}
		break;
	}

}
