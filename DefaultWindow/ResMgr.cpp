#include "stdafx.h"
#include "ResMgr.h"
#include "Texture.h"


CResMgr::CResMgr()
{
}


CResMgr::~CResMgr()
{
	Release();
}

void CResMgr::Insert_Texture(const TCHAR * pFilePath, const TCHAR * pImgKey)
{
	auto iter = find_if(m_mapBit.begin(), m_mapBit.end(), tagFinder(pImgKey));

	if (iter == m_mapBit.end())
	{
		CTexture*	pTexture = new CTexture;
		pTexture->Load_Texture(pFilePath);

		m_mapBit.emplace(pImgKey, pTexture);
	}
}

HDC CResMgr::Find_Image(const TCHAR * pImgKey)
{
	auto iter = find_if(m_mapBit.begin(), m_mapBit.end(), tagFinder(pImgKey));

	if (iter == m_mapBit.end())
		return nullptr;

	return iter->second->Get_MemDC();
}

void CResMgr::Release(void)
{
	for_each(m_mapBit.begin(), m_mapBit.end(), CDeleteMap());
	m_mapBit.clear();
}
