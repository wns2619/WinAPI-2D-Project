#pragma once
#include "Obj.h"


class CBulldog :
	public CObj
{
public:
	CBulldog();
	virtual ~CBulldog();

public:
	virtual void	Initialize(void);
	virtual int		Update(void);
	virtual void	LateUpdate(void);
	virtual void	Render(HDC hDC);
	virtual void	Release(void);

	virtual void	Collider(CObj* _pObj, COL_DIR eDir, float fPush) override;
	
public:
	void MoveFrame(void);
	void SetMotion(void);
	void DogPattern(void);


public: //Getter
	bool	GetReturn()			    { return m_bReturn; }
	bool	GetAttack()				{ return m_bAttack; }
	STATE	GetState(void)			{ return m_eCurState; }


public: // Setter
	void	SetReturn(bool _Return) { m_bReturn = _Return; }
	void	SetState(STATE _State)  { m_eCurState = _State; }
	void	SetAttack(bool _Attack) { m_bAttack = _Attack; }

private:
	STATE	m_ePreState;
	STATE	m_eCurState;

	DWORD	m_dwTime;

	bool	m_bReturn;
	bool	m_bAttack;

	float	m_fAngle;
	
	int		PrevRandomValue;
	int		CurRandomValue;
};

