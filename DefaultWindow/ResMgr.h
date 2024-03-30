#pragma once


class CTexture;

class CResMgr
{
	SINGLETONE(CResMgr);

public:
	void	Insert_Texture(const TCHAR* pFilePath, const TCHAR* pImgKey);
	HDC		Find_Image(const TCHAR* pImgKey);
	void	Release(void);

private:
	map<const TCHAR*, CTexture*>	m_mapBit;
};

