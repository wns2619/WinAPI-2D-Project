#include "stdafx.h"
#include "Obj.h"



CObj::CObj() :
	m_fSpeed(0.f),
	m_bDead(false),
	m_eDir(DIRECTION::END),
	m_fDistance(0.f),
	m_pFrameKey(nullptr),
	m_bJump(false),
	m_fPower(0.f),
	m_fTime(0.f),
	m_bGround(false),
	m_IsMoving(false),
	m_iDrawID(0),
	m_iOption(0),
	m_TileType(TILE_TYPE::NONE),
	m_tObjType(OBJ_TYPE::END),
	m_bGravity(false),
	m_bCol(true),
	m_pTarget(nullptr),
	m_eBlockState(BLOCK_STATE::END)
	
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}


CObj::~CObj()
{
}

void CObj::AddXTime(double _fX, double _time)
{

	double fVal = _fX / 10.f;
	double fTime = _time / 10.f;
	double Sum = 0.f;

	for (int i = 0; i < 10; ++i)
	{
		m_tInfo.fX += static_cast<float>(fVal);
		Sleep(fTime * 1000);
		Sum += static_cast<float>(fVal);
	}

	int x = (int)(m_tInfo.fX + 0.5);
	m_tInfo.fX = (float)x;

	SetMoving(false);
}

void CObj::Update_Rect(void)
{
	m_tRect.left	= LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top		= LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right	= LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom	= LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}

void CObj::MoveFrame(void)
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		// bool이나 true나 false로 키를 땠을 때,
		++m_tFrame.iFrameStart; // IDLE 0으로 만들어서 고정시켜버려라.

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;

		m_tFrame.dwTime = GetTickCount();
	}
}