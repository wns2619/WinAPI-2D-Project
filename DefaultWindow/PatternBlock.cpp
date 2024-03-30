#include "stdafx.h"
#include "PatternBlock.h"
#include "Player.h"
// Manager Header
#include "ResMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"

CPatternBlock::CPatternBlock()
{
}


CPatternBlock::~CPatternBlock()
{
}

void CPatternBlock::Initialize(void)
{
	SetInfo(INFO{ 0, 0, TILECX, TILECY });
	Set_Block(0, 5);
	SetObjType(OBJ_TYPE::PATTERN_BLOCK);
	Set_Tile(TILE_TYPE::PATTERN_BLOCK);
	CResMgr::GetInst()->Insert_Texture(L"../DuckMazeImg/Tile/Pattern.bmp", L"Pattern");

	SetRenderID(RENDERID::GAMEOBJECT);
}

int CPatternBlock::Update(void)
{
	if (GetDead())
		return OBJ_DEAD;

	CObj::Update_Rect();

	return OBJ_NOEVENT;
}

void CPatternBlock::LateUpdate(void)
{
}

void CPatternBlock::Render(HDC hDC)
{
	float fScrollX = CScrollMgr::GetInst()->GetScrollX();
	float fScrollY = CScrollMgr::GetInst()->GetScrollY();

	HDC	  hMemDC = CResMgr::GetInst()->Find_Image(L"Pattern");



	BitBlt(hDC,
		int(GetRect().left + fScrollX),
		int(GetRect().top + fScrollY),
		TILECX,
		TILECY,
		hMemDC,
		TILECX * Get_DrawID(), 0, SRCCOPY);
}

void CPatternBlock::Release(void)
{
}

void CPatternBlock::Collider(CObj * _pObj, COL_DIR eDir, float fPush)
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
		case COL_DIR::BOTTOM:
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
	}
}
