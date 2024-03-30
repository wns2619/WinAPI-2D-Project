#pragma once
#include "Obj.h"


class CWolf :
	public CObj
{
public:
	CWolf();
	virtual ~CWolf();

public:
	virtual void	Initialize(void);
	virtual int		Update(void);
	virtual void	LateUpdate(void);
	virtual void	Render(HDC hDC);
	virtual void	Release(void);

	virtual void	Collider(CObj* _pObj, COL_DIR eDir, float fPush) override;

public: // Getter
	STATE	GetState(void)	 { return m_eCurState; }
	bool	GetAttack()		 { return m_bAttack; }
	bool	GetPosUp()		 { return m_bPosUp; }
	bool	GetGravity()	 { return m_bGravity; }
	bool	GetCollision()	 { return m_bCollision; }


public: // Setter
	void	SetAttack(bool _Attack)		{ m_bAttack = _Attack; }
	void	SetState(STATE _State)		{ m_eCurState = _State; }
	void	SetPosUp(bool _pos)			{ m_bPosUp = _pos; }
	void	SetGravity(bool _gravity)	{ m_bGravity = _gravity; }
	void	SetCollision(bool _Col)		{ m_bCollision = _Col; }


public:
	void MoveFrame(void);
	void SetMotion(void);

private:
	STATE	m_ePreState;
	STATE	m_eCurState;

	DWORD	m_dwTime;

	int		m_iCount;

	bool	m_bAttack;
	bool	m_bPosUp;
	bool	m_bGravity;
	bool	m_bCollision;
};

