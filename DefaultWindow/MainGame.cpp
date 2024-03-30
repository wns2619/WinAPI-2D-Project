#include "stdafx.h"
#include "MainGame.h"

// Manager Header
#include "TimeMgr.h"
#include "ResMgr.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"

CMainGame::CMainGame()
	: m_dwTime(GetTickCount()), m_iFPS(0), m_hBit(0), m_memDC(0)
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_DC = GetDC(g_hWnd);

	//  더블버퍼 
	m_hBit = CreateCompatibleBitmap(m_DC, WINCX, WINCY);
	m_memDC = CreateCompatibleDC(m_DC);
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(hOldBit);



	// Texture Insert
	CResMgr::GetInst()->Insert_Texture(L"../DuckMazeImg/Back.bmp", L"Back");


	// Manager Initialize
	CTimeMgr::GetInst()->Initialize();
	CSoundMgr::GetInst()->Initialize();
	//CSceneMgr::GetInst()->Initialize();
	CSceneMgr::GetInst()->Scene_Change(SCENE_ID::LOGO);

}

void CMainGame::Update(void)
{
	// SceneMgr 
	CSceneMgr::GetInst()->Update();
	CSceneMgr::GetInst()->LateUpdate();
	CScrollMgr::GetInst()->ScrollLock();

	// Render
	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}

	// Clear
	Rectangle(m_memDC, -1, -1, WINCX + 1, WINCY + 1);
	// Render
	m_memDC = CResMgr::GetInst()->Find_Image(L"Back");

	CSceneMgr::GetInst()->Render(m_memDC);
	//HFONT hPrevFont = (HFONT)SelectObject(m_memDC, m_hfArr[(UINT)FONT_TYPE::DEFAULT]);
	//TextOut(m_memDC, 0, 0, TEXT("Hello World"), 11);
	//SelectObject(m_memDC, hPrevFont);
	//ReleaseDC(g_hWnd, m_memDC);

	BitBlt(m_DC, 0, 0, WINCX, WINCY, m_memDC, 0, 0, SRCCOPY);

}

void CMainGame::LateUpdate(void)
{
}

void CMainGame::Render()
{
	//m_memDC = CResMgr::GetInst()->Find_Image(L"Back");
	//++m_iFPS;

	//if (m_dwTime + 1000 < GetTickCount())
	//{
	//	swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
	//	SetWindowText(g_hWnd, m_szFPS);

	//	m_iFPS = 0;
	//	m_dwTime = GetTickCount();
	//}

	//// Clear
	//Rectangle(m_memDC, -1, -1, WINCX + 1, WINCY + 1);
	//// Render

	//CSceneMgr::GetInst()->Render(m_memDC);

	//BitBlt(m_DC, 0, 0, WINCX, WINCY, m_memDC, 0, 0, SRCCOPY);

}

void CMainGame::Release(void)
{
	ReleaseDC(g_hWnd, m_DC);
	DeleteDC(m_memDC);
	DeleteObject(m_hBit);

	//for (int i = 0; i < (UINT)FONT_TYPE::END; ++i)
	//{
	//	DeleteObject(m_hfArr[i]);
	//}
}