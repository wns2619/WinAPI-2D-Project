#include "stdafx.h"
#include "PassBlock.h"
#include "Player.h"

// Manager Header
#include "ResMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"
#include "ObjMgr.h"

CPassBlock::CPassBlock()
{
}


CPassBlock::~CPassBlock()
{
}

void CPassBlock::Initialize(void)
{
	SetInfo(INFO{ 0, 0, TILECX, TILECY });
	Set_Block(0, 4);
	SetObjType(OBJ_TYPE::PASS_BLOCK);
	Set_Tile(TILE_TYPE::PASS_BLOCK);
	CResMgr::GetInst()->Insert_Texture(L"../DuckMazeImg/Tile/Pass.bmp", L"Pass");

	SetRenderID(RENDERID::GAMEOBJECT);
}

int CPassBlock::Update(void)
{
	if (GetDead())
		return OBJ_DEAD;

	CObj::Update_Rect();

	return OBJ_NOEVENT;
}

void CPassBlock::LateUpdate(void)
{
}

void CPassBlock::Render(HDC hDC)
{
	float fScrollX = CScrollMgr::GetInst()->GetScrollX();
	float fScrollY = CScrollMgr::GetInst()->GetScrollY();

	HDC	  hMemDC = CResMgr::GetInst()->Find_Image(L"Pass");



	BitBlt(hDC,
		int(GetRect().left + fScrollX),
		int(GetRect().top + fScrollY),
		TILECX,
		TILECY,
		hMemDC,
		TILECX * Get_DrawID(), 0, SRCCOPY);
}

void CPassBlock::Release(void)
{
}

void CPassBlock::Collider(CObj * _pObj, COL_DIR eDir, float fPush)
{
	OBJ_TYPE eType = _pObj->GetObjType();

	switch (eType)
	{
	case OBJ_TYPE::PLAYER:
		switch (eDir)
		{
		case COL_DIR::TOP:
			if (dynamic_cast<CPlayer*>(_pObj)->GetAttack())
			{
				CSoundMgr::GetInst()->PlaySoundW(L"PatternOrPass.wav", PATTERN_OR_PASS, 1.f);
			}
			break;
		}
		break;

	case OBJ_TYPE::NORMAL_BLOCK:
		switch (eDir)
		{
		case COL_DIR::RIGHT:
			/*	AddX(-fPush);*/
			break;
		case COL_DIR::LEFT:
			/*	AddX(fPush);*/
			break;
		}
		break;

	case OBJ_TYPE::MOVE_BLOCK:
		switch (eDir)
		{
		case COL_DIR::RIGHT:
			break;
		case COL_DIR::LEFT:
			break;
		case COL_DIR::TOP:
			break;
		case COL_DIR::BOTTOM:
			break;
		}

	case OBJ_TYPE::EGG:
		switch (eDir)
		{
		case COL_DIR::RIGHT:
			break;
		case COL_DIR::LEFT:
			break;
		case COL_DIR::TOP:
			if (dynamic_cast<CPlayer*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::PLAYER).front())->GetCountY() == 8)
			{
				if (GetCollision())
				{
					_pObj->AddY(-fPush);
				}
				else if (!GetGround())
				{
					_pObj->SetCollision(false);
				}
			}
			break;
		case COL_DIR::BOTTOM:
			//if (GetCollision())
			//{
			//	if (!_pObj->GetGround())
			//		_pObj->SetJump(false);
			//	_pObj->SetGround(true);


			//	_pObj->SetJumpTime(0.05f);
			//	_pObj->AddY(fPush);
			//}
			break;
		}
	}
}
