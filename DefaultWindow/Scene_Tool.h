#pragma once
#include "Scene.h"


class CScene_Tool :
	public CScene
{
public:
	CScene_Tool();
	virtual ~CScene_Tool();

public:
	virtual void Render(HDC _hDC);
	virtual void Update(void);
	virtual void LateUpdate(void);


	virtual void Initialize(void);
	virtual void Release(void);
	virtual void Enter(void);
	virtual void Exit(void);
};

