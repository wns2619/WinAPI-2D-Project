#pragma once

#include "Obj.h"

template<typename T>
class CAbstractFactory
{
public:
	CAbstractFactory() {}
	~CAbstractFactory() {}

	static	CObj*	Create(void)
	{
		CObj* pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CObj*	Create(float _fX, float _fY)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->SetPos(_fX, _fY);
		
		return pObj;
	}

	static CObj*	Create(BLOCK_STATE _eBlockState)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->SetBlockState(_eBlockState);

		return pObj;
	}
};