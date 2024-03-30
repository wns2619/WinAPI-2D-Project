#pragma once
#include "Obj.h"



class CPlayer :	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();
public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize(void)	override;
	virtual int	 Update(void)		override;
	virtual void LateUpdate(void)	override;
	virtual void Render(HDC hDC)	override;
	virtual void Release(void)		override;

	virtual void	Collider(CObj* _pObj, COL_DIR eDir, float fPush) override;

public: // Getter
	STATE	GetState(void)			{ return m_eCurState; }
	FRAME	GetHitFrame(void)		{ return m_fPlayerFrame; }
	bool	GetAttack(void)			{ return m_bAttack; }
	bool	GetHit(void)			{ return m_bHit; }
	bool	GetStartAnimation(void) { return m_bStartAnimation; }
	bool	GetRenderOff(void)		{ return m_bRender; }
	bool	GetPrevX(void)			{ return m_bCountX; }
	int		GetCountY(void)			{ return m_iCountY; }
	int		GetCountX(void)			{ return m_iCountX; }


public: // Setter
	void	SetAttack(bool _attack)		   { m_bAttack = _attack; }
	void	SetHit(bool _Hit)			   { m_bHit = _Hit; }
	void	SetStartAnimation(bool _Start) { m_bStartAnimation = _Start; }
	void	SetRenderOff(bool _Render)	   { m_bRender = _Render; }

private:
	void	Key_Input(void);
	void	OffSet(void);
	void	SetMotion(void);
	void	Jump(void);
	void	MoveFrame();
	void	PlayerLock(void);
	void	PlayerState(void);

	void	StartAnimation(void);

private:
	STATE	m_ePreState; // 이전 상태
	STATE	m_eCurState; // 현재 상태

	FRAME	m_fPlayerFrame;
	
	// Player Animation
	DWORD	dwTime;
	DWORD	dwRenderTime;

	// Collider
	CObj*	m_pOtherObj;

	// Attack
	bool	m_bAttack;
	bool	m_bMoveFrame;
	bool	m_bHit;
	bool	m_bFallDownCheck;
	bool	m_bStartAnimation;
	bool	m_bRender;


	int		m_iCountX;
	bool	m_bCountX;

	int		m_iCountY;

};

