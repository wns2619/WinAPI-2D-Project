#pragma once
#include "Scene.h"
class CScene_Clear :
	public CScene
{
public:
	CScene_Clear();
	virtual ~CScene_Clear();

public:
	virtual	void Initialize(void) override;
	virtual void Update(void)	  override;
	virtual void LateUpdate(void) override;
	virtual void Release(void)	  override;
	virtual void Render(HDC _hDC) override;


	virtual void Enter(void)	  override;
	virtual void Exit(void)		  override;
};

