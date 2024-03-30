#include "stdafx.h"
#include "TransParentBlock.h"

// Manager Header
#include "ResMgr.h"
#include "ScrollMgr.h"

CTransParentBlock::CTransParentBlock()
{
}


CTransParentBlock::~CTransParentBlock()
{
	Release();
}

void CTransParentBlock::Initialize(void)
{
	SetInfo(INFO{ 0, 0, TILECX, TILECY });
	//Set_Block(0, 1);
	SetObjType(OBJ_TYPE::TRANSPARENT_BLOCK);
	Set_Tile(TILE_TYPE::TRANSPARENT_BLOCK);

	SetRenderID(RENDERID::GAMEOBJECT);
}

int CTransParentBlock::Update(void)
{

	CObj::Update_Rect();


	return OBJ_NOEVENT;
}

void CTransParentBlock::LateUpdate(void)
{
}

void CTransParentBlock::Render(HDC hDC)
{
	float fScrollX = CScrollMgr::GetInst()->GetScrollX();
	float fScrollY = CScrollMgr::GetInst()->GetScrollY();

	//HDC	  hMemDC = CResMgr::GetInst()->Find_Image(L"Pass");



	//BitBlt(hDC,
	//	int(GetRect().left + fScrollX),
	//	int(GetRect().top + fScrollY),
	//	TILECX,
	//	TILECY,
	//	hMemDC,
	//	TILECX * Get_DrawID(), 0, SRCCOPY);


	//Rectangle(hDC, GetRect().left, GetRect().top + fScrollY, GetRect().right, GetRect().bottom + fScrollY);

}

void CTransParentBlock::Release(void)
{
}

void CTransParentBlock::Collider(CObj * _pObj, COL_DIR eDir, float fPush)
{
	OBJ_TYPE eType = _pObj->GetObjType();

	switch (eType)
	{
	case OBJ_TYPE::PLAYER:
		switch (eDir)
		{
		case COL_DIR::TOP:
			break;
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
		case COL_DIR::TOP:
			break;
		case COL_DIR::BOTTOM:
			break;
		}
	}
}
