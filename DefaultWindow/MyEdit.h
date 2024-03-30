#pragma once
#include "Scene.h"
class CMyEdit :
	public CScene
{
public:
	CMyEdit();
	virtual ~CMyEdit();

public:
	virtual void Render(HDC _hDC);
	virtual void Update(void);
	virtual void LateUpdate(void);


	virtual void Initialize(void);
	virtual void Release(void);
	virtual void Enter(void);
	virtual void Exit(void);

private:
	int		iOption;

};

