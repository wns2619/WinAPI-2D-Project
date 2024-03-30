#include "stdafx.h"
#include "Scene.h"
#include "Obj.h"
#include "ResMgr.h"
#include "SceneMgr.h"

CScene::CScene()
	: m_eTileType(TILE_TYPE::NONE), m_eBlockState(BLOCK_STATE::USING_BLOCK)
{
}


CScene::~CScene()
{
	for (UINT i = 0; i < (UINT)OBJ_TYPE::END; ++i)
	{
		list<CObj*>::iterator iter = m_arrObjList[i].begin();
		for (; iter != m_arrObjList[i].end();)
		{
			if ((*iter) != nullptr)
				Safe_Delete<CObj*>(*iter);
		}
	}
}

void CScene::Render(HDC _hDC)
{
	//HDC		hMemDC = CResMgr::GetInst()->Find_Image(L"Background");

	//BitBlt(_hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);


	for (UINT i = 0; i < (UINT)OBJ_TYPE::END; ++i)
	{
		list<CObj*>::iterator iter = m_arrObjList[i].begin();
		for (; iter != m_arrObjList[i].end(); ++iter)
		{
			(*iter)->Render(_hDC);
		}
	}
}

void CScene::Update(void)
{
	for (UINT i = 0; i < (UINT)OBJ_TYPE::END; ++i)
	{
		list<CObj*>::iterator iter = m_arrObjList[i].begin();
		for (; iter != m_arrObjList[i].end();)
		{
			bool iEvent = (*iter)->Update();

			if (iEvent == OBJ_DEAD) // 달걀,불독,늑대 등 조건에 의한 사망
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_arrObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}

	// 향후 처리
}

void CScene::LateUpdate(void)
{
	for (UINT i = 0; i < (UINT)OBJ_TYPE::END; ++i)
	{
		list<CObj*>::iterator iter = m_arrObjList[i].begin();
		for (; iter != m_arrObjList[i].end(); ++iter)
		{
			(*iter)->LateUpdate();
		}
	}
}
