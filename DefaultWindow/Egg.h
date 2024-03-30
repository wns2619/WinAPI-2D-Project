#pragma once
#include "Obj.h"


class CEgg :
	public CObj
{
public:
	CEgg();
	virtual ~CEgg();

	virtual void	Initialize(void);
	virtual int		Update(void);
	virtual void	LateUpdate(void);
	virtual void	Render(HDC hDC);
	virtual void	Release(void);

	virtual void	Collider(CObj* _pObj, COL_DIR eDir, float fPush) override;
	void	OffSet(void);
	void	EggLock(void);
	void	EggState(void);
	bool	EggColRect(void);

public: // Setter
	void	SetMotion(void);
	void	MoveFrame(void);
	void	SetPosCheck(bool _pos)		 { m_bPosCheck = true; }
	void	SetState(STATE _state)		 { m_eCurState = _state; }
	void	SetClear(bool _Clear)		 { m_bClear = _Clear; }
	void	SetStateOff(bool _State)	 { m_bStateOff = _State; }
	void	Set_EggColLeft (int Left)	 { Col_EggSwitch.m_bColLeft = Left; }
	void	Set_EggColRight (int Right) { Col_EggSwitch.m_bColRight = Right; }
	void	Set_EggColTop (int Top)	 { Col_EggSwitch.m_bColTop = Top; }
	void	Set_EggColBottm(int Bottom) { Col_EggSwitch.m_bColBottom = Bottom; }
	void	Set_AllEggCol(int All)		 { Col_EggSwitch = { All, All ,All ,All }; }

public: // Getter
	bool		GetPosCheck()		   { return m_bPosCheck; }
	bool		GetClear()			   { return m_bClear; }
	bool		GetStateOff()		   { return m_bStateOff; }
	STATE		GetState()			   { return m_eCurState; }
	COL_SWITCH	GetEggCol()			   { return Col_EggSwitch; }
	POINT		GetEggColSize()		   { return m_tEggColSize; }
	const RECT*	GetEggColRect()		   { return &m_tEggColRect; }
	int			GetCount()			   { return m_iCount; }

private:
	STATE	m_ePreState;
	STATE	m_eCurState;

	DWORD	m_dwTime;

	float	m_fCurPos;
	float	m_fPrePos;

	bool	m_bPosCheck;
	bool	m_bClear;
	bool	m_bStateOff;

	int		m_iCount;
	int		m_iCountY;

	RECT	m_tEggColRect;
	POINT	m_tEggColSize;


	COL_SWITCH Col_EggSwitch;
};

