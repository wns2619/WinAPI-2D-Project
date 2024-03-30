#include "stdafx.h"
#include "Wolf.h"

// Manager Header
#include "ScrollMgr.h"
#include "ResMgr.h"
#include "ObjMgr.h"
#include "SoundMgr.h"

CWolf::CWolf()
	: m_eCurState(STATE::END), m_dwTime(GetTickCount()), m_bPosUp(false), m_iCount(0), m_bGravity(false), m_bCollision(false)
{
}


CWolf::~CWolf()
{
	Release();
}

void CWolf::Initialize(void)
{
	SetInfo(INFO{ 350.f, 300.f, 45.f, 45.f });
	SetSpeed(2.f);
	SetDistance(100.f);
	SetObjType(OBJ_TYPE::WOLF);
	SetGround(true);
	SetDir(DIRECTION::RIGHT);
	SetRenderID(RENDERID::WOLF_OBJECT);

	CResMgr::GetInst()->Insert_Texture(L"../DuckMazeImg/Duck45/Wolf.bmp", L"Wolf");

	SetFrameKey(L"Wolf");
	m_eCurState = STATE::IDLE;
}

int CWolf::Update(void)
{
	CObj::Update_Rect();

	if (GetDead())
		return OBJ_DEAD;

	SetTarget(CObjMgr::GetInst()->Get_Target(OBJ_TYPE::EGG, this));

	float m_fAngle = 0.f;

	if (GetState() == STATE::IDLE)
	{
		if (m_dwTime + 200 < GetTickCount())
		{
			if (!m_bPosUp && m_iCount < 28)
			{
				AddY(-2.f);
				m_bPosUp = true;
				++m_iCount;
			}

			m_dwTime = GetTickCount();
		}

		if (m_iCount == 27)
		{
			m_eCurState = STATE::WALK;
			m_iCount = 0;
		}

		m_bPosUp = false;
	}

	if (!m_bPosUp && GetState() == STATE::WALK)
	{
		if (GetObjTarget())
		{
			float fWidth = GetObjTarget()->GetInfo().fX - this->GetInfo().fX;
			float fHeight = GetObjTarget()->GetInfo().fY - this->GetInfo().fY;

			float fDiagonal = sqrtf(pow(fWidth, 2) + pow(fHeight, 2));
			float fRadian = acosf(fWidth / fDiagonal);
				
			if (GetObjTarget()->GetInfo().fY > this->GetInfo().fY)
				fRadian = (2 * PI) - fRadian;

			m_fAngle = fRadian * 180.f / PI;
		}

		AddX(LONG(GetSpeed() * cosf(m_fAngle * PI / 180.f)));
		//AddY(-(LONG(GetSpeed() * sinf(m_fAngle * PI / 180.f))));

		SetGravity(true);
		SetCollision(true);
	}
	

	return OBJ_NOEVENT;
}

void CWolf::LateUpdate(void)
{

	if (GetGravity())
	{
		AddY(-(0.f * (GetJumpTime() + 0.01f) - 9.8f * GetJumpTime() * GetJumpTime() * 0.5));
		AddTime(0.05f); // 그리고 중력의 영향에 의해서 떨어지고 나서?
	}

	MoveFrame();

	SetMotion();
}

void CWolf::Render(HDC hDC)
{
	float fScrollX = CScrollMgr::GetInst()->GetScrollX();
	float fScrollY = CScrollMgr::GetInst()->GetScrollY();

	HDC	  hMemDC = CResMgr::GetInst()->Find_Image(GetFrameKey());


	GdiTransparentBlt(hDC,
		(int)GetRect().left,
		(int)GetRect().top + fScrollY,
		(int)GetInfo().fCX,
		(int)GetInfo().fCY,
		hMemDC,
		GetFrame().iFrameStart * (int)GetInfo().fCX,
		GetFrame().iMotion * (int)GetInfo().fCY,
		(int)GetInfo().fCX,
		(int)GetInfo().fCY,
		RGB(0, 0, 0));
}

void CWolf::Release(void)
{
}

void CWolf::Collider(CObj * _pObj, COL_DIR eDir, float fPush)
{
	OBJ_TYPE eType = _pObj->GetObjType();
	//m_pOtherObj = _pObj;


	switch (eType)
	{
		// Egg의 방향이 -> 노멀 블록에 닿았을 때.
	case OBJ_TYPE::PLAYER:
		switch (eDir)
		{
		case COL_DIR::RIGHT:
			SetDead(true);
			break;
		case COL_DIR::LEFT:
			SetDead(true);
			break;
		case COL_DIR::TOP:
			SetDead(true);
			break;
		case COL_DIR::BOTTOM:
			SetDead(true);
			break;
		}
		break;
	case OBJ_TYPE::SIDE_BLOCK:
		switch (eDir)
		{
		case COL_DIR::RIGHT:
			AddX(-fPush);
			break;
		case COL_DIR::LEFT:
			AddX(fPush);
			break;
		case COL_DIR::TOP:
			break;
		case COL_DIR::BOTTOM:
			break;
		}
		break;
	case OBJ_TYPE::NORMAL_BLOCK:
		switch (eDir)
		{
		case COL_DIR::RIGHT:
			if(GetCollision())
			AddX(-fPush);
			break;
		case COL_DIR::LEFT:
			if (GetCollision())
			AddX(fPush);
			break;
		case COL_DIR::TOP:
			if (GetCollision())
			SetJumpPower(0);
			break;
		case COL_DIR::BOTTOM:
			if (GetCollision())
			{
				SetJumpTime(0.05f);
				AddY(-fPush);
			}
			break;
		}
		break;
	case OBJ_TYPE::MOVE_BLOCK:
		switch (eDir)
		{
		case COL_DIR::RIGHT:
			if (GetCollision())
			AddX(-fPush);
			break;
		case COL_DIR::LEFT:
			if (GetCollision())
			AddX(fPush);
			break;
		case COL_DIR::TOP:
			if (GetCollision())
			AddY(fPush);
			break;
		case COL_DIR::BOTTOM:
			if (GetCollision())
			{
				if (!GetGround())
					SetJump(false);

				SetGround(true);

				SetJumpTime(0);
				AddY(-fPush);
			}

			break;
		}
		break;
	case OBJ_TYPE::PATTERN_BLOCK:
		switch (eDir)
		{
		case COL_DIR::RIGHT:
			if (GetCollision())
			AddX(-fPush);
			break;
		case COL_DIR::LEFT:
			if (GetCollision())
			AddX(fPush);
			break;
		case COL_DIR::TOP:
			if (GetCollision())
			{
				AddY(fPush);
				AddJumpPower(-1.f);
			}
			break;
		case COL_DIR::BOTTOM:
			if (GetCollision())
			{
				if (!GetGround())
					SetJump(false);

				SetGround(true);

				SetJumpTime(0.05f);
				AddY(-fPush);
			}

			break;
		}
		break;
	case OBJ_TYPE::PASS_BLOCK:
		switch (eDir)
		{
		case COL_DIR::RIGHT:
			break;
		case COL_DIR::LEFT:
			break;
		case COL_DIR::BOTTOM:
			if (GetCollision())
			{
				SetGround(true);

				SetJumpTime(0.05f);
				AddY(-fPush);
			}
			break;
		}
		break;
	case OBJ_TYPE::EGG:
		switch (eDir)
		{
		case COL_DIR::LEFT:
			if (GetCollision())
			{
				_pObj->SetDead(true);
				CSoundMgr::GetInst()->PlaySoundW(L"Egg_Die.wav", EGG_DIE, 1.f);
				SetCollision(false);
				SetSpeed(0.f);
			}
			break;
		case COL_DIR::RIGHT:
			if (GetCollision())
			{
				_pObj->SetDead(true);
				CSoundMgr::GetInst()->PlaySoundW(L"Egg_Die.wav", EGG_DIE, 1.f);
				SetCollision(false);
				SetSpeed(0.f);
			}
			break;
		}
		break;
	}
}

void CWolf::MoveFrame(void)
{
	if (GetState() == STATE::WALK)
	{
		if (GetFrame().dwTime + GetFrame().dwSpeed < GetTickCount())
		{
			// bool이나 true나 false로 키를 땠을 때,
			AddFrameStart(1); // IDLE 0으로 만들어서 고정시켜버려라.

			if (GetFrame().iFrameStart > GetFrame().iFrameEnd)
				SetFrameStart(0);

			SetFrameTime(GetTickCount());
		}
	}
}

void CWolf::SetMotion(void)
{
	int iNum = 0;

	if (m_ePreState != m_eCurState) // 현재 모션과 지금 모션이 같지 않을 때
	{
		switch (m_eCurState)
		{
			// FRAME Setting
			// FrameStart, Frame End, iMotion, dwSpeed, dwTime
		case STATE::IDLE:
			SetFrame(FRAME{ 0,0,0,200, GetTickCount() });
			break;
		case STATE::WALK:
			SetFrame(FRAME{ 0,3,0,600,GetTickCount() });
			break;
		}


		m_ePreState = m_eCurState;
	}
}
