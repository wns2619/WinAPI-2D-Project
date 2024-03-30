#include "stdafx.h"
#include "Scene_Clear.h"

// Manager Header
#include "ResMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"

CScene_Clear::CScene_Clear()
{
}


CScene_Clear::~CScene_Clear()
{
}

void CScene_Clear::Initialize(void)
{
	CResMgr::GetInst()->Insert_Texture(L"../DuckMazeImg/Clear.bmp", L"Clear");
	SetFrameKey(L"Black");
}

void CScene_Clear::Update(void)
{
	CScrollMgr::GetInst()->ReSetScroll();
}

void CScene_Clear::LateUpdate(void)
{
}

void CScene_Clear::Release(void)
{
	CObjMgr::GetInst()->Release();
}

void CScene_Clear::Render(HDC _hDC)
{
	HDC	hGroundDC = CResMgr::GetInst()->Find_Image(L"Clear");
	// Manager Render

	float fScrollX = CScrollMgr::GetInst()->GetScrollX();
	float fScrollY = CScrollMgr::GetInst()->GetScrollY();

	BitBlt(_hDC, 0, fScrollY, 800, 3100, hGroundDC, 0, 0, SRCCOPY);

	CObjMgr::GetInst()->Render(_hDC);
}

void CScene_Clear::Enter(void)
{
}

void CScene_Clear::Exit(void)
{
}
