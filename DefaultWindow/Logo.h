#pragma once
#include "Scene.h"


class CLogo :
	public CScene
{
public:
	CLogo();
	virtual ~CLogo();

public:
	virtual void Initialize(void) override;
	virtual void Update(void)	  override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void)    override;


	virtual void Enter(void)	  override;
	virtual void Exit(void)		  override;

public: // Getter
	TCHAR*	GetLogoSelect() { return m_cLogoName; }


public: // Setter
	void	SetLogoSelect(TCHAR* _logo) { m_cLogoName = _logo; }



private:
	TCHAR*	m_cLogoName;
};

