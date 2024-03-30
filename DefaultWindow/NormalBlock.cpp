#include "stdafx.h"
#include "NormalBlock.h"
#include "Player.h"

// Manager Header
#include "ResMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"
#include "ObjMgr.h"

CNormalBlock::CNormalBlock()
{
}


CNormalBlock::~CNormalBlock()
{
	Release();
}

void CNormalBlock::Initialize(void)
{
	SetInfo(INFO{ 0, 0, TILECX, TILECY });
	

	Set_Block(0, 1);


	SetObjType(OBJ_TYPE::NORMAL_BLOCK);
	Set_Tile(TILE_TYPE::NORMAL_BLOCK);

	CResMgr::GetInst()->Insert_Texture(L"../DuckMazeImg/Tile/Normal.bmp", L"Normal");

	SetRenderID(RENDERID::GAMEOBJECT);
}

int CNormalBlock::Update(void)
{
	CObj::Update_Rect();

	SetTarget(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::EGG).front());

	return OBJ_NOEVENT;
}

void CNormalBlock::LateUpdate(void)
{
}

void CNormalBlock::Render(HDC hDC)
{
	float fScrollX = CScrollMgr::GetInst()->GetScrollX();
	float fScrollY = CScrollMgr::GetInst()->GetScrollY();

	HDC	  hMemDC = CResMgr::GetInst()->Find_Image(L"Normal");


	if(GetBlockState() == BLOCK_STATE::USING_BLOCK)
	BitBlt(hDC,
		int(GetRect().left + fScrollX),
		int(GetRect().top + fScrollY),
		TILECX,
		TILECY,
		hMemDC,
		TILECX * Get_DrawID(), 0, SRCCOPY);
	//else
	//{
	//	Rectangle(hDC, GetRect().left, GetRect().top + fScrollY, GetRect().right, GetRect().bottom + fScrollY);
	//}
}

void CNormalBlock::Release(void)
{

}

void CNormalBlock::Collider(CObj * _pObj, COL_DIR eDir, float fPush)
{
	OBJ_TYPE eType = _pObj->GetObjType();

	switch (eType)
	{
	case OBJ_TYPE::PLAYER:
		switch (eDir)
		{
		case COL_DIR::TOP:
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
