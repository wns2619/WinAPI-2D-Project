#pragma once
class CTexture
{
public:
	CTexture();
	~CTexture();

public: // Getter
	HDC		Get_MemDC()		{ return m_hMemDC; }


public:
	void	Load_Texture(const TCHAR* pFilePath);
	void	Release(void);

private:
	HDC		m_hMemDC;
	HBITMAP	m_hBitmap;
	HBITMAP	m_hOldmap;
};

