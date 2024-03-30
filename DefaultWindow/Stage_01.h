#pragma once
#include "Scene.h"


class Stage_01 :
	public CScene
{
public:
	Stage_01();
	virtual ~Stage_01();

public:
	virtual	void Initialize(void) override;
	virtual void Update(void)	  override;
	virtual void LateUpdate(void) override;
	virtual void Release(void)	  override;
	virtual void Render(HDC _hDC) override;


	virtual void Enter(void)	  override;
	virtual void Exit(void)		  override;

public: // Getter
	LPCWSTR	GetString(void)			{ return m_tcString; }

public: // Setter
	void	SetString(LPCWSTR _char) { m_tcString = _char; }

public:
	void	CreateFont()
	{
		LOGFONT logFont = { 0 };
		logFont.lfHeight = iFontSize;
		logFont.lfWeight = FW_NORMAL;
		logFont.lfCharSet = DEFAULT_CHARSET;
		wcscpy_s(logFont.lfFaceName, L"둥근모꼴");

		hFont = ::CreateFontIndirect(&logFont);
	}
	void SetScore(int score)
	{
		iScore = score;
		InvalidateRect(g_hWnd, NULL, FALSE);
	}
	void OnPaint(HDC _hDC)
	{
		HFONT	hOldFont = (HFONT)SelectObject(_hDC, hFont);

		wchar_t score_text[100];
		wsprintf(score_text, L"%d", iScore);
		SetTextColor(_hDC, RGB(255,255,255));
		SetBkMode(_hDC, TRANSPARENT);
		TextOut(_hDC, 175, 25, score_text, wcslen(score_text));
		SelectObject(_hDC, hOldFont);
		ReleaseDC(g_hWnd, _hDC);

		DeleteObject(hOldFont);
	}


private:
	DWORD	m_dwMonsterTime;
	DWORD	m_dwEggTime;
	DWORD	m_dwTime;


	LPCWSTR	m_tcString;
	bool	m_bStartBgm;


	// 폰트 관련
	HFONT	hFont;
	int		iScore;
	int		iFontSize;
	int		iFont_X;
	int		iFont_Y;

};

