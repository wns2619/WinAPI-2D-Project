#include "stdafx.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Logo.h"
#include "Stage_01.h"
#include "MyEdit.h"
#include "Scene_ReStart.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "Scene_Clear.h"

CSceneMgr::CSceneMgr()
	: m_iStage(0), m_bNextStage(false), m_bEnd(false), m_bSetEnd(false), m_pCurScene(nullptr)
	, m_eCurScene(SCENE_ID::LOGO), m_ePreScene(SCENE_ID::END), m_dwTime(GetTickCount())
{
	
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Initialize(void)
{
}

void CSceneMgr::Update(void)
{
	m_pCurScene->Update();
}

void CSceneMgr::LateUpdate(void)
{
	m_pCurScene->LateUpdate();
}

void CSceneMgr::Render(HDC _hDC)
{
	m_pCurScene->Render(_hDC);

	//m_vecStage[m_iStage]->Render(_hDC);
}

void CSceneMgr::Release(void)
{
	Safe_Delete(m_pCurScene);
}


void CSceneMgr::Scene_Change(SCENE_ID eID)
{
	m_eCurScene = eID;

	if (m_ePreScene != m_eCurScene)
	{
		Safe_Delete<CScene*>(m_pCurScene);

		switch (m_eCurScene)
		{
		case SCENE_ID::LOGO:
			m_pCurScene = new CLogo;
			break;
		case SCENE_ID::EDIT:
			m_pCurScene = new CMyEdit;
			break;
		case SCENE_ID::STAGE_01:
			m_pCurScene = new Stage_01;
			break;
		case SCENE_ID::STAGE_RE:
			m_pCurScene = new CScene_ReStart;
			break;
		case SCENE_ID::STAGE_CLEAR:
			m_pCurScene = new CScene_Clear;
			break;

		}
		m_pCurScene->Initialize();
		m_ePreScene = m_eCurScene;
	}
}
