#include "stdafx.h"
#include "Stage_01.h"
#include "Player.h"
#include "ObjMgr.h"
#include "MainGame.h"
#include "Block.h"
#include "MoveBlock.h"
#include "NormalBlock.h"
#include "CAbstractFactory.h"
#include "Egg.h"
#include "Bulldog.h"
#include "Wolf.h"
#include "TransParentBlock.h"
#include "MainGame.h"

// Manager Header
#include "ResMgr.h"
#include "ScrollMgr.h"
#include "TileMgr.h"
#include "SoundMgr.h"
#include "SceneMgr.h"
#include "ObjMgr.h"

bool Gravity = false;
int	 TotalScore = 0;

Stage_01::Stage_01()
	: m_dwMonsterTime(GetTickCount()), m_dwEggTime(GetTickCount()), m_bStartBgm(true), m_tcString(0), hFont(nullptr), iScore(0), iFontSize(25), iFont_X(0), iFont_Y(0)
	, m_dwTime(GetTickCount())
{
}


Stage_01::~Stage_01()
{
	Release();
}

void Stage_01::Initialize(void)
{

	CResMgr::GetInst()->Insert_Texture(L"../DuckMazeImg/BackGround.bmp", L"BackGround");

	// SetInfo(INFO{ 300.f, 300.f, 32.f, 32.f });
	//AddObject(CAbstractFactory<CPlayer>::Create(),OBJ_TYPE::PLAYER);
	//AddObject(CAbstractFactory<CEgg>::Create(364 + (64 * 2), 190), OBJ_TYPE::EGG);

	Stage_01::CreateFontW();

	CObjMgr::GetInst()->Add_Obj(OBJ_TYPE::PLAYER, CAbstractFactory<CPlayer>::Create(120.f, 355.f));
	CObjMgr::GetInst()->Add_Obj(OBJ_TYPE::EGG, CAbstractFactory<CEgg>::Create(142.5f, 355.f));
	CObjMgr::GetInst()->Add_Obj(OBJ_TYPE::BULLDOG, CAbstractFactory<CBulldog>::Create(100, 755.f));
	CObjMgr::GetInst()->Add_Obj(OBJ_TYPE::BULLDOG, CAbstractFactory<CBulldog>::Create(647.5, 1377.5));
	CObjMgr::GetInst()->Add_Obj(OBJ_TYPE::BULLDOG, CAbstractFactory<CBulldog>::Create(373.5, 1777.5));
	CObjMgr::GetInst()->Add_Obj(OBJ_TYPE::BULLDOG, CAbstractFactory<CBulldog>::Create(327.5, 2077.5));
	CObjMgr::GetInst()->Add_Obj(OBJ_TYPE::BULLDOG, CAbstractFactory<CBulldog>::Create(437.5, 2277.5));

	for (UINT i = 0; i < 16; ++i)
	{
		CObjMgr::GetInst()->Add_Obj(OBJ_TYPE::TRANSPARENT_BLOCK, CAbstractFactory<CTransParentBlock>::Create(0 + (i*50), 3100));
	}
	
	
	// Y 1625, 400
	// Y 2075, 250

	TileMgr::GetInst()->Load_Tile();
	CreateFont();
	SetName(L"Stage_01");
	/*CSoundMgr::GetInst()->PlayBGM(L"DuckMazeBgm.wav", 0.3f);*/

}

void Stage_01::Update(void)
{
	if (!dynamic_cast<CPlayer*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::PLAYER).front())->GetStartAnimation())
	{
		if (m_bStartBgm)
		{
			CSoundMgr::GetInst()->PlayBGM(L"DuckMazeBgm.wav", 0.3f);
			m_bStartBgm = false;
		}
	}
	CObjMgr::GetInst()->Update();

}

void Stage_01::Render(HDC _hDC)
{

	HDC	hGroundDC = CResMgr::GetInst()->Find_Image(L"BackGround");
	// Manager Render

	float fScrollX = CScrollMgr::GetInst()->GetScrollX();
	float fScrollY = CScrollMgr::GetInst()->GetScrollY();
	
	BitBlt(_hDC, 0, fScrollY, 800, 3100, hGroundDC, 0, 0, SRCCOPY);
	


	OnPaint(_hDC);
	SetScore(TotalScore);

	SetString(L"SCORE");
	COLORREF crTextColor = RGB(255, 255, 255);
	HFONT hPrevFont = (HFONT)SelectObject(_hDC, hFont);
	SetTextColor(_hDC, crTextColor);
	SetBkMode(_hDC, TRANSPARENT);
	TextOut(_hDC, 100, 25, GetString() , lstrlen(GetString()));
	SelectObject(_hDC, hPrevFont);
	ReleaseDC(g_hWnd, _hDC);
	
	CObjMgr::GetInst()->Render(_hDC);
}

void Stage_01::Enter(void)
{

}

void Stage_01::Exit(void)
{
}

void Stage_01::LateUpdate(void)
{
	CObjMgr::GetInst()->LateUpdate();

	CEgg* pEgg = dynamic_cast<CEgg*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::EGG).front());
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::PLAYER).front());
	
	float fWitdh = fabs(pEgg->GetInfo().fX - pPlayer->GetInfo().fX); // 절대값 x 값 차이
	float fHeight = fabs(pEgg->GetInfo().fY - pPlayer->GetInfo().fY); // 절대값 y 값 차이..

	// 가로 800 에 세로 600이니까, 타일끼리의 거리 좌우 2개 뺐을 때 14개씩, 6개 정도?


	if ((fWitdh > 400.f || fHeight > 200.f) && pEgg->GetInfo().fY < 2600.f)
	{
		if (m_dwMonsterTime + 15000 < GetTickCount())
		{
			int iTileX = static_cast<int>(pEgg->GetInfo().fX) / TILECX;
			int iTileY = static_cast<int>(pEgg->GetInfo().fY) / TILECY;

			float fWolfX = static_cast<float>(iTileX * TILECX);
			float fWolfY = static_cast<float>(iTileY * TILECY) + 80.f; // 늑대 위치 offset + 

			CObjMgr::GetInst()->Add_Obj(OBJ_TYPE::WOLF, CAbstractFactory<CWolf>::Create(fWolfX, fWolfY));
			m_dwMonsterTime = GetTickCount();
		}
	}



	STATE eState = pEgg->GetState();
	FRAME eFrame = pEgg->GetFrame();
	bool  bDead = pEgg->GetDead();

	if (m_dwEggTime + 2000 < GetTickCount())
	{
		if (bDead && eFrame.iFrameStart == 1)
		{	
			TileMgr::GetInst()->Release();
			CObjMgr::GetInst()->Release();

			CSoundMgr::GetInst()->StopAll();
			CSceneMgr::GetInst()->Scene_Change(SCENE_ID::STAGE_RE);
		}

		m_dwEggTime = GetTickCount();
	}
	else if (dynamic_cast<CEgg*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::EGG).front())->GetClear() && 
		dynamic_cast<CEgg*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::EGG).front())->GetState() == STATE::DANCE
		&& dynamic_cast<CEgg*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::EGG).front())->GetCount() == 15
		&& m_dwTime + 3000 < GetTickCount())
	{
		CScrollMgr::GetInst()->ReSetScroll();
		CSceneMgr::GetInst()->Scene_Change(SCENE_ID::STAGE_CLEAR);
	}
}

void Stage_01::Release(void)
{
	DeleteObject(hFont);
}
