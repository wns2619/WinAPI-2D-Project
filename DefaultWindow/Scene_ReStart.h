#pragma once
#include "Scene.h"

class CScene_ReStart : public CScene
{
public:
	CScene_ReStart();
	virtual ~CScene_ReStart();

public:
	virtual	void Initialize(void) override;
	virtual void Update(void)	  override;
	virtual void LateUpdate(void) override;
	virtual void Release(void)	  override;
	virtual void Render(HDC _hDC) override;


	virtual void Enter(void)	  override;
	virtual void Exit(void)		  override;

private:
	DWORD		m_dwTime;
};

