#include "stdafx.h"
#include "SideBlock.h"

// Manager Header
#include "ResMgr.h"
#include "ScrollMgr.h"


CSideBlock::CSideBlock()
{
}


CSideBlock::~CSideBlock()
{
	Release();
}

void CSideBlock::Initialize(void)
{
	SetInfo(INFO{ 0, 0, TILECX, TILECY });
	Set_Block(0, 3);
	SetObjType(OBJ_TYPE::SIDE_BLOCK);
	Set_Tile(TILE_TYPE::SIDE_BLOCK);
	CResMgr::GetInst()->Insert_Texture(L"../DuckMazeImg/Tile/Side.bmp", L"Side");

	SetRenderID(RENDERID::GAMEOBJECT);
}

int CSideBlock::Update(void)
{
	if (GetDead())
		return OBJ_DEAD;

	CObj::Update_Rect();

	return OBJ_NOEVENT;
}

void CSideBlock::LateUpdate(void)
{
}

void CSideBlock::Render(HDC hDC)
{
	float fScrollX = CScrollMgr::GetInst()->GetScrollX();
	float fScrollY = CScrollMgr::GetInst()->GetScrollY();

	HDC	  hMemDC = CResMgr::GetInst()->Find_Image(L"Side");



	BitBlt(hDC,
		int(GetRect().left + fScrollX),
		int(GetRect().top + fScrollY),
		TILECX,
		TILECY,
		hMemDC,
		TILECX * Get_DrawID(), 0, SRCCOPY);
}

void CSideBlock::Release(void)
{
}

void CSideBlock::Collider(CObj * _pObj, COL_DIR eDir, float fPush)
{
	OBJ_TYPE eType = _pObj->GetObjType();

	switch (eType)
	{
	case OBJ_TYPE::PLAYER:
		switch (eDir)
		{
		case COL_DIR::BOTTOM:
			break;
		}
		break;

	case OBJ_TYPE::EGG:
		switch (eDir)
		{
		case COL_DIR::RIGHT:
			break;
		case COL_DIR::LEFT:
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
