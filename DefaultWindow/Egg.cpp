#include "stdafx.h"
#include "Egg.h"
#include "Scene.h"
#include "Player.h"
#include "NormalBlock.h"

// Manager Header
#include "ResMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"

CEgg::CEgg()
	: m_eCurState(STATE::END)
	, m_bPosCheck(true)
	, m_fCurPos(0.f)
	, m_fPrePos(0.f)
	, m_dwTime(GetTickCount())
	, m_iCount(0)
	, m_bStateOff(false)
	, m_iCountY(0)
	, Col_EggSwitch({ false,false,false,false })
{
	ZeroMemory(&m_tEggColRect, sizeof(RECT));
	ZeroMemory(&m_tEggColSize, sizeof(POINT));
}


CEgg::~CEgg()
{
	CScrollMgr::GetInst()->ReSetScroll();
}

void CEgg::Initialize(void)
{
	// Egg State
	SetInfo(INFO{ 350.f, 300.f, 45.f, 45.f });
	SetDistance(100.f);
	SetJumpTime(0.f);
	SetJumpPower(10.f);
	SetSpeed(3.f);
	SetObjType(OBJ_TYPE::EGG);
	SetRenderID(RENDERID::EGG_OBJECT);
	SetGround(true);
	SetJump(false);
	SetDir(DIRECTION::RIGHT);
	SetMoving(false);
	SetDead(false);
	SetClear(false);

	// Egg Motion
	CResMgr::GetInst()->Insert_Texture(L"../DuckMazeImg/Duck45/Egg_Move.bmp", L"EGG_RIGHT");
	CResMgr::GetInst()->Insert_Texture(L"../DuckMazeImg/Duck45/Egg_Move.bmp", L"EGG_LEFT");
	CResMgr::GetInst()->Insert_Texture(L"../DuckMazeImg/Duck45/Egg_Hit.bmp", L"EGG_HIT");
	CResMgr::GetInst()->Insert_Texture(L"../DuckMazeImg/Duck45/DuckBaby.bmp", L"DuckBaby");

	SetFrameKey(L"EGG_RIGHT");
	m_eCurState = STATE::WALK;
	SetFrame(FRAME{ 0, 3, 0, 200, GetTickCount() });

	m_tEggColSize.x = 50.f;
	m_tEggColSize.y = 50.f;
}

int CEgg::Update(void)
{
	/*if (GetDead())
		return OBJ_DEAD;*/

	m_tEggColRect.left = LONG(GetInfo().fX - (m_tEggColSize.x * 0.5f));
	m_tEggColRect.top = LONG(GetInfo().fY - (m_tEggColSize.y * 0.5f));
	m_tEggColRect.right = LONG(GetInfo().fX + (m_tEggColSize.x * 0.5f));
	m_tEggColRect.bottom = LONG(GetInfo().fY + (m_tEggColSize.y * 0.5f));

	CObj::Update_Rect();

	return OBJ_NOEVENT;
}

void CEgg::LateUpdate(void)
{

	// 현재 위치저장하고 있는 CurPos의 값을 주고?
	
	if (CSceneMgr::GetInst()->GetScene()->GetName() == L"Logo")
	{
		AddX(1.5f);
		MoveFrame();
		SetMotion();
	}
	else
	{
		if (dynamic_cast<CPlayer*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::PLAYER).front())->GetStartAnimation())
		{
			if (dynamic_cast<CPlayer*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::PLAYER).front())->GetPrevX() == false)
			{
				EggState();
				MoveFrame();
			}

			if (dynamic_cast<CPlayer*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::PLAYER).front())->GetCountY() != 8 &&
				dynamic_cast<CPlayer*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::PLAYER).front())->GetPrevX())
			{
				if (m_dwTime + 500 < GetTickCount())
				{
					if (m_iCountY < 8)
					{
						SetFrameStart(0);
						AddY(25.f);
						++m_iCountY;
					}

					m_dwTime = GetTickCount();
				}
			}
		}

		else
		{
			if (GetMoving() && !GetClear())
			{
				MoveFrame();
				SetMoving(false);
			}


			
			AddY(-(0.f * (GetJumpTime() + 0.01f) - 9.8f * GetJumpTime() * GetJumpTime() * 0.5));
			AddTime(0.05f); // 그리고 중력의 영향에 의해서 떨어지고 나서?
			

			EggState();

			SetMotion();

			OffSet();
		}

		// 달걀이 자기 Y값의 위치에서 4칸 밑으로 한 번에 떨어지면 부셔져야함. 그럼 어떻게 해야하나.
		// 현재 달걀의 Y값 위치를 저장할 멤버변수? Prev? 그리고 현재 위치를 저장할 Cur? 둘 차이가 50비트짜리 4개 차이라면
		// 부셔지는 애니메이션으로 전환하고, 목숨이 있는 동안 시작 위치에서 리스폰한다?.
	}
}

void CEgg::Render(HDC hDC)
{

	float fScrollX = CScrollMgr::GetInst()->GetScrollX();
	float fScrollY = CScrollMgr::GetInst()->GetScrollY();

	HDC	  hMemDC = CResMgr::GetInst()->Find_Image(GetFrameKey());

	/*Rectangle(hDC, m_tEggColRect.left, m_tEggColRect.top + fScrollY, m_tEggColRect.right, m_tEggColRect.bottom + fScrollY);*/

	if (!dynamic_cast<CPlayer*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::PLAYER).front())->GetRenderOff())
	{
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



}

void CEgg::Release(void)
{
}

void CEgg::Collider(CObj * _pObj, COL_DIR eDir, float fPush)
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
			AddX(-fPush);
			SetMoving(true);
		break;
		case COL_DIR::LEFT:
			AddX(fPush);
			SetMoving(true);
		break;
		case COL_DIR::TOP:
			if (GetEggCol().m_bColRight != 0 && GetEggCol().m_bColLeft != 0 && GetEggCol().m_bColBottom != 0)
				SetDead(true);
		break;
		case COL_DIR::BOTTOM:
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
			if (dynamic_cast<CPlayer*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::PLAYER).front())->GetCountY() == 8)
			{
				if (_pObj->GetBlockState() == BLOCK_STATE::USING_BLOCK)
				{
					AddX(-fPush);
					Set_EggColRight(_pObj->GetBlockID());
				}
				else if (_pObj->GetBlockState() == BLOCK_STATE::DELETE_BLOCK)
				{
					Set_EggColRight(false);
					SetBlockID(0);
				}
			}
			break;
		case COL_DIR::LEFT:
			if (dynamic_cast<CPlayer*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::PLAYER).front())->GetCountY() == 8)
			{
				if (_pObj->GetBlockState() == BLOCK_STATE::USING_BLOCK)
				{
						AddX(fPush);
						Set_EggColLeft(_pObj->GetBlockID());
				}
				else if (_pObj->GetBlockState() == BLOCK_STATE::DELETE_BLOCK)
				{
					Set_EggColLeft(false);
					SetBlockID(0);
				}
			}
			break;
		case COL_DIR::TOP:
			if (dynamic_cast<CPlayer*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::PLAYER).front())->GetCountY() == 8)
			{
				if (_pObj->GetBlockState() == BLOCK_STATE::USING_BLOCK)
				{
					Set_EggColTop(_pObj->GetBlockID());
					SetJumpPower(0);
				}
				else if (_pObj->GetBlockState() == BLOCK_STATE::DELETE_BLOCK)
				{
					SetGround(false);
					Set_EggColTop(false);
					SetBlockID(0);
				}
			}
			break;
		case COL_DIR::BOTTOM:
			if (dynamic_cast<CPlayer*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::PLAYER).front())->GetCountY() == 8)
			{
				if (_pObj->GetBlockState() == BLOCK_STATE::USING_BLOCK)
				{
					if (!GetGround())
					{
						SetJump(false);
					}
					SetGround(true);


					m_fPrePos = m_fCurPos;

					m_fCurPos = _pObj->GetInfo().fY;


					SetJumpTime(0);
					AddY(-fPush);
					SetCollision(true);
					Set_EggColBottm(_pObj->GetBlockID());
				}

				else if (_pObj->GetBlockState() == BLOCK_STATE::DELETE_BLOCK)
				{
					Set_EggColBottm(false);
					SetBlockID(0);
				}
			}
			break;
		}
		break;
	case OBJ_TYPE::MOVE_BLOCK:
		switch (eDir)
		{
		case COL_DIR::RIGHT:
			AddX(-fPush);
			break;
		case COL_DIR::LEFT:
			AddX(fPush);
			break;
		case COL_DIR::TOP:
			AddY(fPush);
			break;
		case COL_DIR::BOTTOM:
			if (!GetGround())
			{
				SetJump(false);
			}

			SetGround(true);
			SetCollision(true);

			m_fPrePos = m_fCurPos;

			m_fCurPos = _pObj->GetInfo().fY;

			SetJumpTime(0);
			AddY(-fPush);

			break;
		}
		break;
	case OBJ_TYPE::PATTERN_BLOCK:
		switch (eDir)
		{
		case COL_DIR::RIGHT:
			AddX(-fPush);
			break;
		case COL_DIR::LEFT:
			AddX(fPush);
			break;
		case COL_DIR::TOP:
			AddY(fPush);
			AddJumpPower(-1.f);
			break;
		case COL_DIR::BOTTOM:
			if (!GetGround())
				SetJump(false);

			SetGround(true);

			m_fPrePos = m_fCurPos;

			m_fCurPos = _pObj->GetInfo().fY;

			SetJumpTime(0.05f);
			AddY(-fPush);

			break;
		}
		break;
	case OBJ_TYPE::PASS_BLOCK:
		switch (eDir)
		{
		case COL_DIR::BOTTOM:
			if (GetCollision())
			{
				SetGround(true);



				m_fPrePos = m_fCurPos;

				m_fCurPos = _pObj->GetInfo().fY;

				SetJumpTime(0.05f);
				AddY(-fPush);
			}
			break;
		}
		break;
	case OBJ_TYPE::TRANSPARENT_BLOCK:
		switch (eDir)
		{
		case COL_DIR::BOTTOM:
			if (!GetGround())
				SetJump(false);
			SetGround(true);

			SetJumpTime(0.05f);
			AddY(-fPush);
			SetClear(true);

			if (!GetStateOff())
			{
				SetState(STATE::WALK);
				SetStateOff(true);
			}

			break;

		}
		break;
	default:
	/*	Set_AllEggCol(false);*/
		break;
	}

}

void CEgg::OffSet(void)
{
	float	fOffSetMinY = 245.f;
	float	fOffSetMaxY = 250.f;

	float	fScrollY = CScrollMgr::GetInst()->GetScrollY();


	if (fOffSetMinY > GetInfo().fY + fScrollY)
		CScrollMgr::GetInst()->SetScrollY(GetSpeed());

	if (fOffSetMaxY < GetInfo().fY + fScrollY)
		CScrollMgr::GetInst()->SetScrollY(-GetSpeed());
}

void CEgg::EggLock(void)
{
	if (0.f < GetInfo().fX)
		SetX(0.f);

	if (0.f < GetInfo().fY)
		SetY(0.f);


	if (WINCX - 800 > GetInfo().fX)
		SetX(WINCX - 800);

	if (WINCY - 3100 > GetInfo().fY)
		SetY(WINCY - 3100);
}

void CEgg::EggState(void)
{
	if (GetDead())
	{
		CSoundMgr::GetInst()->PlaySoundW(L"Egg_Die.wav", EGG_DIE, 1.f);
	}

	if (0.f != m_fCurPos && 0.f != m_fPrePos)
	{
		if (m_fCurPos - m_fPrePos > 199 && !GetClear())
		{
			SetDead(true);
			CSoundMgr::GetInst()->PlaySoundW(L"Egg_Die.wav", EGG_DIE, 1.f);
		}
	}

	if (0.f != m_fCurPos && 0.f != m_fPrePos)
	{
		if (m_fCurPos - m_fPrePos > 49 && m_fCurPos - m_fPrePos < 199)
		{
			CSoundMgr::GetInst()->PlaySoundW(L"Egg_Drop.wav", EGG_DROP, 1.f);
		}
	}

	if (GetDead())
	{
		m_eCurState = STATE::HIT;
		SetInfo(INFO{ GetInfo().fX, GetInfo().fY, 90.f, 45.f });
		SetMoving(false);

		MoveFrame();
	}

	if (GetClear() && GetState() != STATE::HIT) // 게임이 클리어 상태라면 
	{
		if (m_dwTime + 200 < GetTickCount()) // 알을 오른쪽으로 조금 움직인 뒤에 부화시킨다.
		{
			CSoundMgr::GetInst()->StopAll();
			if (GetMoving() && m_iCount < 40)
			{
				AddX(5.f);
				SetMoving(false);
				++m_iCount;
				MoveFrame();
			}

			m_dwTime = GetTickCount();
		}

		if (m_iCount == 39 && GetState() != STATE::DANCE)
		{
			m_eCurState = STATE::HIT;
			SetInfo(INFO{ GetInfo().fX, GetInfo().fY, 90.f, 45.f });
			SetFrameKey(L"EGG_HIT");
			CSoundMgr::GetInst()->PlaySoundW(L"Egg_Die.wav", EGG_DIE, 1.f);
			m_iCount = 0;
		}

		SetMoving(true);
	}

	else if (GetState() == STATE::HIT && GetClear()) //달걀이 다 굴러가서, 애기로 부화 
	{
		if (GetFrame().iFrameStart != 1)
		{
			MoveFrame();
		}
		else if (GetFrame().iFrameStart == 1 && m_dwTime + 1500 < GetTickCount() && GetState() != STATE::DANCE)
		{
			m_eCurState = STATE::DANCE;
			SetInfo(INFO{ GetInfo().fX, GetInfo().fY, 45.f, 45.f });
			SetFrameKey(L"DuckBaby");

			m_dwTime = GetTickCount();
		}
	}

	else if (GetState() == STATE::DANCE)
	{
		if (m_dwTime + 200 < GetTickCount()) // 알을 오른쪽으로 조금 움직인 뒤에 부화시킨다.
		{
			if (GetMoving() && m_iCount < 15)
			{
				AddX(5.f);
				SetMoving(false);
				++m_iCount;
				MoveFrame();
			}

			m_dwTime = GetTickCount();
		}

		SetMoving(true);
	}

}

bool CEgg::EggColRect(void)
{
	RECT rc{};

	// bool bCheck = IntersectRect{&rc, GetRect(), }
	// 일단 여기서부터 시작
	return false;
}

void CEgg::SetMotion(void)
{

	int iNum = 0;

	if (m_ePreState != m_eCurState) // 현재 모션과 지금 모션이 같지 않을 때
	{
		switch (m_eCurState)
		{
			// FRAME Setting
			// FrameStart, Frame End, iMotion, dwSpeed, dwTime
		case STATE::WALK:
			SetFrame(FRAME{ 0,3,0,300,GetTickCount() });
			break;
		case STATE::HIT:
			SetFrameKey(L"EGG_HIT");
			SetFrame(FRAME{ 0,1,0,350,GetTickCount() });
			break;
		case STATE::DANCE:
			SetFrameKey(L"DuckBaby");
			SetFrame(FRAME{ 0,3,0,300,GetTickCount() });
			break;
		}

		m_ePreState = m_eCurState;
	}
}

void CEgg::MoveFrame(void)
{
	if (GetFrame().dwTime + GetFrame().dwSpeed < GetTickCount())
	{
		// bool이나 true나 false로 키를 땠을 때,
		
		if (GetState() == STATE::HIT)
		{
			AddFrameStart(1);
		}
		else
		{
			AddFrameStart(1);
		}
			/*++m_tFrame.iFrameStart;*/ // IDLE 0으로 만들어서 고정시켜버려라.

		if (GetFrame().iFrameStart > GetFrame().iFrameEnd)
			SetFrameStart(1);

		SetFrameTime(GetTickCount());
	}
}
