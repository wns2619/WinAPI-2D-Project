#include "stdafx.h"
#include "TileMgr.h"
#include "CAbstractFactory.h"
#include "ScrollMgr.h"
#include "Block.h"
#include "MoveBlock.h"
#include "NormalBlock.h"
#include "SideBlock.h"
#include "PassBlock.h"
#include "PatternBlock.h"
#include "ObjMgr.h"


TileMgr::TileMgr()
{
}


TileMgr::~TileMgr()
{
	Release();
}

void TileMgr::Initialize(void)
{
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			float fX = float(TILECX * j) + (TILECX >> 1);
			float fY = float(TILECY * i) + (TILECY >> 1);

			CObj* pObj = nullptr;

			pObj = CAbstractFactory<CBlock>::Create();
			pObj->SetPos(fX, fY);
			m_vecTile.push_back(pObj);
		}
	}
}

void TileMgr::Update(void)
{
	for (auto& iter : m_vecTile)
		iter->Update();
}

void TileMgr::LateUpdate(void)
{
	for (auto& iter : m_vecTile)
		iter->LateUpdate();
}

void TileMgr::Picking_Tile(POINT _pt, TILE_TYPE eType, BLOCK_STATE _eBlock, int _iDrawID, int _iOption)
{
	int		j = _pt.x / TILECX;
	int		i = _pt.y / TILECY;

	int		iIndex = i * TILEX + j;

	if (0 > iIndex || m_vecTile.size() <= (UINT)iIndex)
		return;	

	//CObj* pTile = m_vecTile[iIndex];


	float fX = m_vecTile[iIndex]->GetInfo().fX;
	float fY = m_vecTile[iIndex]->GetInfo().fY;


	CObj* pObj = nullptr;

	Safe_Delete<CObj*>(m_vecTile[iIndex]);


	switch (eType)
	{
	case TILE_TYPE::NONE:
		pObj = CAbstractFactory<CBlock>::Create();
		break;
	case TILE_TYPE::NORMAL_BLOCK:
		pObj = CAbstractFactory<CNormalBlock>::Create();
		break;
	case TILE_TYPE::MOVE_BLOCK:
		pObj = CAbstractFactory<CMoveBlock>::Create();
		break;
	case TILE_TYPE::SIDE_BLOCK:
		pObj = CAbstractFactory<CSideBlock>::Create();
		break;
	case TILE_TYPE::PASS_BLOCK:
		pObj = CAbstractFactory<CPassBlock>::Create();
		break;
	case TILE_TYPE::PATTERN_BLOCK:
		pObj = CAbstractFactory<CPatternBlock>::Create();
		break;
	}

	pObj->SetBlockState(_eBlock);
	pObj->SetPos(fX, fY);
	pObj->Set_Block(_iDrawID, _iOption);
	m_vecTile[iIndex] = pObj;
}

void TileMgr::Create_Tile(POINT _pt, TILE_TYPE eType)
{
	int	j = _pt.x / TILECX;
	int i = _pt.y / TILECY;

	int iIndex = i * TILECX + j;

	if (0 > iIndex || m_vecTile.size() <= (UINT)iIndex)
		return;

	float fX = m_vecTile[iIndex]->GetInfo().fX;
	float fY = m_vecTile[iIndex]->GetInfo().fY;

	CObj* pObj = nullptr;

	Safe_Delete<CObj*>(m_vecTile[iIndex]);

	switch (eType)
	{
	case TILE_TYPE::NONE:
		break;
	case TILE_TYPE::NORMAL_BLOCK:
		pObj = CAbstractFactory<CNormalBlock>::Create();
		break;
	case TILE_TYPE::MOVE_BLOCK:
		pObj = CAbstractFactory<CMoveBlock>::Create();
		break;
	}

	pObj->SetPos(fX, fY);
	m_vecTile[iIndex] = pObj;

}

void TileMgr::Render(HDC _hDC)
{
	int iCullX = abs((int)CScrollMgr::GetInst()->GetScrollX() / TILECX);
	int iCullY = abs((int)CScrollMgr::GetInst()->GetScrollY() / TILECY);

	int iMaxX = iCullX + WINCX / TILECX + 2;
	int iMaxY = iCullY + WINCY / TILECY + 2;

	for (int i = iCullY; i < iMaxY; ++i)
	{
		for (int j = iCullX; j < iMaxX; ++j)
		{
			int iIndex = i * TILEX + j;

			if (0 > iIndex || m_vecTile.size() <= (UINT)iIndex)
				continue;

			m_vecTile[iIndex]->Render(_hDC);
		}
	}

}


void TileMgr::Release(void)
{
	for_each(m_vecTile.begin(), m_vecTile.end(), CDeleteObj());

	m_vecTile.clear();
	m_vecTile.shrink_to_fit();

}

void TileMgr::Save_Tile(void)
{
	HANDLE	hFile = CreateFile(L"../Data/Tile.dat",
		GENERIC_WRITE,
		NULL,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (INVALID_HANDLE_VALUE == hFile)	// 파일 개방에 실패했다면
	{
		MessageBox(g_hWnd, _T("save File"), L"Fail", MB_OK);
		return;
	}

	DWORD    dwByte = 0;
	int		iDrawID = 0, iOption = 0;

	int   eObjType;
	TILE_TYPE  eTileType;
	BLOCK_STATE eBlockState;

	for (auto& iter : m_vecTile)
	{
		eObjType = iter->Get_Option();
		WriteFile(hFile, &(iter->GetInfo()), sizeof(INFO), &dwByte, nullptr); //INFO를 저장
		WriteFile(hFile, &(eObjType), sizeof(int), &dwByte, nullptr); // OBJ_TYPE 저장


		switch (eObjType)
		{
		case 0:
			eTileType = dynamic_cast<CBlock*>(iter)->GetTile();
			eBlockState = dynamic_cast<CBlock*>(iter)->GetBlockState();
			WriteFile(hFile, &eBlockState, sizeof(BLOCK_STATE), &dwByte, nullptr);
			WriteFile(hFile, &eTileType, sizeof(TILE_TYPE), &dwByte, nullptr);
			break;
		case 1:
			eTileType = dynamic_cast<CNormalBlock*>(iter)->GetTile();
			eBlockState = dynamic_cast<CNormalBlock*>(iter)->GetBlockState();
			WriteFile(hFile, &eBlockState, sizeof(BLOCK_STATE), &dwByte, nullptr);
			WriteFile(hFile, &eTileType, sizeof(TILE_TYPE), &dwByte, nullptr);
			break;
		case 2:
			eTileType = dynamic_cast<CMoveBlock*>(iter)->GetTile();
			eBlockState = dynamic_cast<CMoveBlock*>(iter)->GetBlockState();
			WriteFile(hFile, &eBlockState, sizeof(BLOCK_STATE), &dwByte, nullptr);
			WriteFile(hFile, &eTileType, sizeof(TILE_TYPE), &dwByte, nullptr);
			break;
		case 3:
			eTileType = dynamic_cast<CSideBlock*>(iter)->GetTile();
			eBlockState = dynamic_cast<CSideBlock*>(iter)->GetBlockState();
			WriteFile(hFile, &eBlockState, sizeof(BLOCK_STATE), &dwByte, nullptr);
			WriteFile(hFile, &eTileType, sizeof(TILE_TYPE), &dwByte, nullptr);
			break;
		case 4:
			eTileType = dynamic_cast<CPassBlock*>(iter)->GetTile();
			eBlockState = dynamic_cast<CPassBlock*>(iter)->GetBlockState();
			WriteFile(hFile, &eBlockState, sizeof(BLOCK_STATE), &dwByte, nullptr);
			WriteFile(hFile, &eTileType, sizeof(TILE_TYPE), &dwByte, nullptr);
			break;
		case 5:
			eTileType = dynamic_cast<CPatternBlock*>(iter)->GetTile();
			eBlockState = dynamic_cast<CPatternBlock*>(iter)->GetBlockState();
			WriteFile(hFile, &eBlockState, sizeof(BLOCK_STATE), &dwByte, nullptr);
			WriteFile(hFile, &eTileType, sizeof(TILE_TYPE), &dwByte, nullptr);
			break;
		}
		
	}


	MessageBox(g_hWnd, _T("Save File"), L"Succese", MB_OK);

	CloseHandle(hFile);
}

void TileMgr::Load_Tile(void)
{
	HANDLE	hFile = CreateFile(L"../Data/Tile.dat",
		GENERIC_READ,
		NULL,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (INVALID_HANDLE_VALUE == hFile)	// 파일 개방에 실패했다면
	{
		MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
		return;
	}

	DWORD    dwByte = 0;
	int		iDrawID = 0, iOption = 0;

	int	 eObjType = 0;
	TILE_TYPE	 eTileType;
	INFO		 m_tInfo{};
	CObj*		 pObj = nullptr;

	OBJ_TYPE	 m_Obj;
	BLOCK_STATE	 eBlockState;

	int iNumber = 0;

	while (true)
	{

		
		ReadFile(hFile, &m_tInfo, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &eObjType, sizeof(int), &dwByte, nullptr);


		if (eObjType == 0)
		{
			ReadFile(hFile, &eBlockState, sizeof(BLOCK_STATE), &dwByte, nullptr);
			ReadFile(hFile, &eTileType, sizeof(TILE_TYPE), &dwByte, nullptr);
			/*pObj = CAbstractFactory<CBlock>::Create();*/
			m_Obj = OBJ_TYPE::NONE_BLOCK;
		}
		else if (eObjType == 1)
		{
			ReadFile(hFile, &eBlockState, sizeof(BLOCK_STATE), &dwByte, nullptr);
			ReadFile(hFile, &eTileType, sizeof(TILE_TYPE), &dwByte, nullptr);
			pObj = CAbstractFactory<CNormalBlock>::Create();
			m_Obj = OBJ_TYPE::NORMAL_BLOCK;
		}
		else if (eObjType == 2)
		{
			ReadFile(hFile, &eBlockState, sizeof(BLOCK_STATE), &dwByte, nullptr);
			ReadFile(hFile, &eTileType, sizeof(TILE_TYPE), &dwByte, nullptr);
			pObj = CAbstractFactory<CMoveBlock>::Create();
			m_Obj = OBJ_TYPE::MOVE_BLOCK;
		}
		else if (eObjType == 3)
		{
			ReadFile(hFile, &eBlockState, sizeof(BLOCK_STATE), &dwByte, nullptr);
			ReadFile(hFile, &eTileType, sizeof(TILE_TYPE), &dwByte, nullptr);
			pObj = CAbstractFactory<CSideBlock>::Create();
			m_Obj = OBJ_TYPE::SIDE_BLOCK;
		}
		else if (eObjType == 4)
		{
			ReadFile(hFile, &eBlockState, sizeof(BLOCK_STATE), &dwByte, nullptr);
			ReadFile(hFile, &eTileType, sizeof(TILE_TYPE), &dwByte, nullptr);
			pObj = CAbstractFactory<CPassBlock>::Create();
			m_Obj = OBJ_TYPE::PASS_BLOCK;
		}
		else if (eObjType == 5)
		{
			ReadFile(hFile, &eBlockState, sizeof(BLOCK_STATE), &dwByte, nullptr);
			ReadFile(hFile, &eTileType, sizeof(TILE_TYPE), &dwByte, nullptr);
			pObj = CAbstractFactory<CPatternBlock>::Create();
			m_Obj = OBJ_TYPE::PATTERN_BLOCK;
		}

		if (m_Obj != OBJ_TYPE::NONE_BLOCK)
		{
			pObj->SetBlockState(eBlockState);
			pObj->SetPos(m_tInfo.fX, m_tInfo.fY);
			pObj->SetBlockID(iNumber);
			CObjMgr::GetInst()->Add_Obj(m_Obj, pObj);
		}

		iNumber++;

		if (0 == dwByte)
			break;
	}


	CloseHandle(hFile);
}