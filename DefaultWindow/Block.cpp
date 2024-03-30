#include "stdafx.h"
#include "Block.h"

// Manager Header
#include "ScrollMgr.h"
#include "ResMgr.h"

CBlock::CBlock()
{
}


CBlock::~CBlock()
{
}

void CBlock::Initialize(void)
{
	SetInfo(INFO{ 0, 0, TILECX, TILECY });
	Set_Block(0, 0);
	Set_Tile(TILE_TYPE::NONE);
	//CResMgr::GetInst()->Insert_Texture(L"../DuckMazeImg/Tile/None_Block.bmp", L"None");

	SetRenderID(RENDERID::GAMEOBJECT);
}

int CBlock::Update(void)
{
	if (GetDead())
		return OBJ_DEAD;

	CObj::Update_Rect();

	return OBJ_NOEVENT;
}

void CBlock::LateUpdate(void)
{

}

void CBlock::Render(HDC hDC)
{

	float fScrollX = CScrollMgr::GetInst()->GetScrollX();
	float fScrollY = CScrollMgr::GetInst()->GetScrollY();

	HDC	  hMemDC = 0;


	BitBlt(hDC,
		int(GetRect().left + fScrollX),
		int(GetRect().top + fScrollY),
		TILECX,
		TILECY,
		hMemDC,
		TILECX * Get_DrawID(), 0, SRCCOPY);
}

void CBlock::Release(void)
{
}

void CBlock::Collider(CObj * _pObj, COL_DIR eDir, float fPush)
{

}
