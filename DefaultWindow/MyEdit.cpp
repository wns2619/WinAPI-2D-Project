#include "stdafx.h"
#include "MyEdit.h"

// ManagerHeader
#include "TileMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"
#include "ResMgr.h"



CMyEdit::CMyEdit()
	: iOption(1)
{
	SetTile(TILE_TYPE::NORMAL_BLOCK);
}


CMyEdit::~CMyEdit()
{
	Release();
}

void CMyEdit::Initialize(void)
{
	Gravity = false;

	CResMgr::GetInst()->Insert_Texture(L"../DuckMazeImg/BackGround.bmp", L"Background");


	TileMgr::GetInst()->Initialize();
}

void CMyEdit::Update(void)
{
	TileMgr::GetInst()->Update();

	//if (CKeyMgr::GetInst()->Key_Pressing(VK_LEFT))
	//	CScrollMgr::GetInst()->SetScrollX(5.f);

	//if (CKeyMgr::GetInst()->Key_Pressing(VK_RIGHT))
	//	CScrollMgr::GetInst()->SetScrollX(-5.f);

	if (CKeyMgr::GetInst()->Key_Pressing(VK_UP))
		CScrollMgr::GetInst()->SetScrollY(5.f);

	if (CKeyMgr::GetInst()->Key_Pressing(VK_DOWN))
		CScrollMgr::GetInst()->SetScrollY(-5.f);

	if (CKeyMgr::GetInst()->Key_Down(VK_RETURN))
		CSceneMgr::GetInst()->Scene_Change(SCENE_ID::STAGE_01);


	//if (CKeyMgr::GetInst()->Key_Down('0'))
	//{
	//	SetTile(TILE_TYPE::NONE);
	//	iOption = 0;
	//}


	if (CKeyMgr::GetInst()->Key_Down('0'))
	{
		SetTile(TILE_TYPE::NONE);
		SetBlockState(BLOCK_STATE::USING_BLOCK);
		iOption = 0;
	}

	if (CKeyMgr::GetInst()->Key_Down('1'))
	{
		SetTile(TILE_TYPE::NORMAL_BLOCK);
		SetBlockState(BLOCK_STATE::USING_BLOCK);
		iOption = 1;
	}

	if (CKeyMgr::GetInst()->Key_Down('2'))
	{
		SetTile(TILE_TYPE::NORMAL_BLOCK);
		SetBlockState(BLOCK_STATE::DELETE_BLOCK);
		iOption = 1;
	}

	if (CKeyMgr::GetInst()->Key_Down('3'))
	{
		SetTile(TILE_TYPE::MOVE_BLOCK);
		SetBlockState(BLOCK_STATE::USING_BLOCK);
		iOption = 2;
	}

	if (CKeyMgr::GetInst()->Key_Down('4'))
	{
		SetTile(TILE_TYPE::SIDE_BLOCK);
		SetBlockState(BLOCK_STATE::USING_BLOCK);
		iOption = 3;
	}

	if (CKeyMgr::GetInst()->Key_Down('5'))
	{
		SetTile(TILE_TYPE::PASS_BLOCK);
		SetBlockState(BLOCK_STATE::USING_BLOCK);
		iOption = 4;
	}

	if (CKeyMgr::GetInst()->Key_Down('6'))
	{
		SetTile(TILE_TYPE::PATTERN_BLOCK);
		SetBlockState(BLOCK_STATE::USING_BLOCK);
		iOption = 5;
	}


	if (CKeyMgr::GetInst()->Key_Pressing(VK_LBUTTON))
	{
		POINT pt{};
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (LONG)CScrollMgr::GetInst()->GetScrollX();
		pt.y -= (LONG)CScrollMgr::GetInst()->GetScrollY();

		TileMgr::GetInst()->Picking_Tile(pt, GetTile(), GetBlockState(), 0,iOption);
	}

	if (CKeyMgr::GetInst()->Key_Down('S'))
		TileMgr::GetInst()->Save_Tile();

	if (CKeyMgr::GetInst()->Key_Down('L'))
		TileMgr::GetInst()->Load_Tile();


}


void CMyEdit::Render(HDC _hDC)
{


	HDC	hGroundDC = CResMgr::GetInst()->Find_Image(L"Background");
	// Manager Render

	float fScrollX = CScrollMgr::GetInst()->GetScrollX();
	float fScrollY = CScrollMgr::GetInst()->GetScrollY();

	BitBlt(_hDC, 0, fScrollY, 800, 3100, hGroundDC, 0, 0, SRCCOPY);

	TileMgr::GetInst()->Render(_hDC);

	//CObjMgr::GetInst()->Render(_hDC);
}

void CMyEdit::LateUpdate(void)
{
	TileMgr::GetInst()->LateUpdate();
}


void CMyEdit::Release(void)
{
}

void CMyEdit::Enter(void)
{
}

void CMyEdit::Exit(void)
{
}
