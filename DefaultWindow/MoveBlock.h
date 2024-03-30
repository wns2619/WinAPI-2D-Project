#pragma once
#include "Obj.h"

class CMoveBlock :
	public CObj
{
public:
	CMoveBlock();
	virtual ~CMoveBlock();

	virtual void	Initialize(void);
	virtual int		Update(void);
	virtual void	LateUpdate(void);
	virtual void	Render(HDC hDC);
	virtual void	Release(void);

	virtual void	Collider(CObj* _pObj, COL_DIR eDir, float fPush) override;
	

public: // Setter

public: // Getter

private:
	bool	m_bIsBlocked;

	float	m_fPrePos;
	float	m_fCurPos;
};

