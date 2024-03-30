#include "stdafx.h"
#include "Logo.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "ResMgr.h"
#include "Obj.h"
#include "MainGame.h"
#include "ObjMgr.h"
#include "CAbstractFactory.h"
#include "Bulldog.h"
#include "Egg.h"

CLogo::CLogo()
	: m_cLogoName(nullptr)
{
}


CLogo::~CLogo()
{
	Release();
}

void CLogo::Initialize(void)
{
	CResMgr::GetInst()->Insert_Texture(L"../DuckMazeImg/TitleImg.bmp", L"Title");
	CResMgr::GetInst()->Insert_Texture(L"../DuckMazeImg/TitleImg2.bmp", L"Title2");

	CObjMgr::GetInst()->Add_Obj(OBJ_TYPE::PLAYER, CAbstractFactory<CPlayer>::Create(-45, 280));
	CObjMgr::GetInst()->Add_Obj(OBJ_TYPE::BULLDOG, CAbstractFactory<CBulldog>::Create(-90, 280));
	CObjMgr::GetInst()->Add_Obj(OBJ_TYPE::EGG, CAbstractFactory<CEgg>::Create(0, 280));
	


	SetName(L"Logo");

	SetLogoSelect(L"Title");
}

void CLogo::Update(void)
{
	//if(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::PLAYER).empty())
	//	CObjMgr::GetInst()->Add_Obj(OBJ_TYPE::PLAYER, CAbstractFactory<CPlayer>::Create(0, 280));


	CObjMgr::GetInst()->Update();

}

void CLogo::LateUpdate(void)
{
	CObjMgr::GetInst()->LateUpdate();

	if (CKeyMgr::GetInst()->Key_Down(VK_RETURN))
	{
		/*CSceneMgr::GetInst()->Scene_Change(SCENE_ID::STAGE_01);*/
		CSceneMgr::GetInst()->Scene_Change(SCENE_ID::STAGE_01);
	}

	if (CKeyMgr::GetInst()->Key_Down('E'))
	{
		CSceneMgr::GetInst()->Scene_Change(SCENE_ID::EDIT);
	}

	if (CKeyMgr::GetInst()->Key_Down(VK_DOWN))
	{
		SetLogoSelect(L"Title2");
	}

	if (CKeyMgr::GetInst()->Key_Down(VK_UP))
	{
		SetLogoSelect(L"Title");
	}


 	if (CObjMgr::GetInst()->GetObjList(OBJ_TYPE::PLAYER).front()->GetInfo().fX > 800.f)
		CObjMgr::GetInst()->GetObjList(OBJ_TYPE::PLAYER).front()->SetX(0);

	if (CObjMgr::GetInst()->GetObjList(OBJ_TYPE::BULLDOG).front()->GetInfo().fX > 800.f)
		CObjMgr::GetInst()->GetObjList(OBJ_TYPE::BULLDOG).front()->SetX(0);

	if (CObjMgr::GetInst()->GetObjList(OBJ_TYPE::EGG).front()->GetInfo().fX > 800.f)
		CObjMgr::GetInst()->GetObjList(OBJ_TYPE::EGG).front()->SetX(0);

}

void CLogo::Render(HDC _hDC)
{
	HDC		hMemDC = CResMgr::GetInst()->Find_Image(GetLogoSelect());

	//GdiTransparentBlt(_hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0,
	//	WINCX, WINCY, NULL);

	BitBlt(_hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
		

	CObjMgr::GetInst()->Render(_hDC);
}

void CLogo::Release(void)
{
	CObjMgr::GetInst()->Release();
}

void CLogo::Enter(void)
{
	/*CResMgr::GetInst()->Insert_Texture(L"../DuckMazeImg/TitleImg.bmp", L"Title");*/
}

void CLogo::Exit(void)
{
}
