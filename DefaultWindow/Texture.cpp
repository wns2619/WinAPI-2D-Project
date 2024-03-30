#include "stdafx.h"
#include "Texture.h"


CTexture::CTexture()
{
}


CTexture::~CTexture()
{
	Release();
}

void CTexture::Load_Texture(const TCHAR * pFilePath)
{
	HDC	hDC = GetDC(g_hWnd);
	m_hMemDC = CreateCompatibleDC(hDC);
	ReleaseDC(g_hWnd, hDC);

	m_hBitmap = (HBITMAP)LoadImage
	(NULL, pFilePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	m_hOldmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
}

void CTexture::Release(void)
{
	SelectObject(m_hMemDC, m_hOldmap);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}
