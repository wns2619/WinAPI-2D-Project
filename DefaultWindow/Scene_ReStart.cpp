#include "stdafx.h"
#include "Scene_ReStart.h"
#include "Egg.h"

// Manager Header
#include "ResMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"

CScene_ReStart::CScene_ReStart()
	: m_dwTime(GetTickCount())
{
}


CScene_ReStart::~CScene_ReStart()
{
	Release();
}

void CScene_ReStart::Initialize(void)
{
	CResMgr::GetInst()->Insert_Texture(L"../DuckMazeImg/Black.bmp", L"Black");
	SetFrameKey(L"Black");
}

void CScene_ReStart::Update(void)
{
	if (m_dwTime + 2000 < GetTickCount())
	{
		CSceneMgr::GetInst()->Scene_Change(SCENE_ID::STAGE_01);
	}
}

void CScene_ReStart::LateUpdate(void)
{
	
}

void CScene_ReStart::Release(void)
{
	CObjMgr::GetInst()->Release();
}

void CScene_ReStart::Render(HDC _hDC)
{

	HDC	hGroundDC = CResMgr::GetInst()->Find_Image(GetFrameKey());
	// Manager Render

	float fScrollX = CScrollMgr::GetInst()->GetScrollX();
	float fScrollY = CScrollMgr::GetInst()->GetScrollY();

	BitBlt(_hDC, 0, fScrollY, 800, 3100, hGroundDC, 0, 0, SRCCOPY);

	CObjMgr::GetInst()->Render(_hDC);
}

void CScene_ReStart::Enter(void)
{
}

void CScene_ReStart::Exit(void)
{
}
