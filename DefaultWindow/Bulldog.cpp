#include "stdafx.h"
#include "Bulldog.h"
#include "Player.h"
#include "NormalBlock.h"

// Header Manager
#include "ResMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "SoundMgr.h"
#include "SceneMgr.h"
#include "Scene.h"

CBulldog::CBulldog()
	: m_eCurState(STATE::END), m_bReturn(false), m_dwTime(GetTickCount()), m_bAttack(false), m_fAngle(0.f), PrevRandomValue(0), CurRandomValue(0)
{
}


CBulldog::~CBulldog()
{
}

void CBulldog::Initialize(void)
{
	SetInfo(INFO{ 350.f, 300.f, 45.f, 45.f });
	SetSpeed(1.f);
	SetDistance(100.f);
	SetObjType(OBJ_TYPE::BULLDOG);
	SetGround(true);
	SetDir(DIRECTION::RIGHT);
	SetRenderID(RENDERID::GAMEOBJECT);

	// Bulldog Motion
	CResMgr::GetInst()->Insert_Texture(L"../DuckMazeImg/Duck45/Dog_LeftIDLE.bmp", L"DOG_LEFT_IDLE");
	CResMgr::GetInst()->Insert_Texture(L"../DuckMazeImg/Duck45/Dog_RightIDLE.bmp", L"DOG_RIGHT_IDLE");
	CResMgr::GetInst()->Insert_Texture(L"../DuckMazeImg/Duck45/Dog_RightMove.bmp", L"DOG_RIGHT_MOVE");
	CResMgr::GetInst()->Insert_Texture(L"../DuckMazeImg/Duck45/Dog_LeftMove.bmp", L"DOG_LEFT_MOVE");
	CResMgr::GetInst()->Insert_Texture(L"../DuckMazeImg/Duck45/Dog_LeftAttack.bmp", L"DOG_LEFT_ATTACK");
	CResMgr::GetInst()->Insert_Texture(L"../DuckMazeImg/Duck45/Dog_RightAttack.bmp", L"DOG_RIGHT_ATTACK");
	CResMgr::GetInst()->Insert_Texture(L"../DuckMazeImg/Duck45/Dog_RightAttack.bmp", L"DOG_DANCE");

	SetFrameKey(L"DOG_RIGHT_MOVE");

	m_eCurState = STATE::WALK;
	SetFrame(FRAME{ 0, 0, 0, 200, GetTickCount() });
}

int CBulldog::Update(void)
{
	if (GetDead())
	{
		m_eCurState = STATE::IDLE;
		SetFrameKey(L"DOG_LEFT_IDLE");

		if (m_dwTime + 1000 < GetTickCount())
		{
			return OBJ_DEAD;
		}
	}

	CObj::Update_Rect();

	return OBJ_NOEVENT;
}

void CBulldog::LateUpdate(void)
{

	if (CSceneMgr::GetInst()->GetScene()->GetName() == L"Logo")
	{
		AddX(1.5f);
		MoveFrame();
		SetMotion();
	}
	else
	{
		DogPattern();

		AddY(-(0.f * (GetJumpTime() + 0.01f) - 9.8f * GetJumpTime() * GetJumpTime() * 0.5));
		AddTime(0.05f); // 그리고 중력의 영향에 의해서 떨어지고 나서?

		MoveFrame();

		SetMotion();
	}
}

void CBulldog::Render(HDC hDC)
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

void CBulldog::Release(void)
{

}

void CBulldog::Collider(CObj * _pObj, COL_DIR eDir, float fPush)
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
			if (!m_bAttack)
			{
				AddX(-fPush);
				SetState(STATE::ATTCK);
				SetFrameKey(L"DOG_LEFT_ATTACK");
				SetSpeed(0.f);
				SetAttack(true);
				CSoundMgr::GetInst()->StopSound(HIT_SOUND);
				CSoundMgr::GetInst()->PlaySoundW(L"Duck_HIt.wav", HIT_SOUND, 1.f);
			}
			break;
		case COL_DIR::LEFT:
			if (!m_bAttack)
			{
				AddX(fPush);
				SetState(STATE::ATTCK);
				SetFrameKey(L"DOG_RIGHT_ATTACK");
				SetSpeed(0.f);
				SetAttack(true);
				CSoundMgr::GetInst()->StopSound(HIT_SOUND);
				CSoundMgr::GetInst()->PlaySoundW(L"Duck_HIt.wav", HIT_SOUND, 1.f);
			}
			break;
		case COL_DIR::TOP:
			break;
		case COL_DIR::BOTTOM:
			break;
		}
		break;
	case OBJ_TYPE::SIDE_BLOCK:
		switch (eDir)
		{
		case COL_DIR::RIGHT:
			SetReturn(false);
			AddX(-fPush);
			break;
		case COL_DIR::LEFT:
			SetReturn(true);
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
			if (dynamic_cast<CNormalBlock*>(_pObj)->GetBlockState() == BLOCK_STATE::USING_BLOCK)
			{
				SetReturn(false);
				AddX(-fPush);
			}
			break;
		case COL_DIR::LEFT:
			if (dynamic_cast<CNormalBlock*>(_pObj)->GetBlockState() == BLOCK_STATE::USING_BLOCK)
			{
				SetReturn(true);
				AddX(fPush);
			}
			break;
		case COL_DIR::TOP:
			if (dynamic_cast<CNormalBlock*>(_pObj)->GetBlockState() == BLOCK_STATE::USING_BLOCK)
			SetJumpPower(0);
			break;
		case COL_DIR::BOTTOM:
			if (dynamic_cast<CNormalBlock*>(_pObj)->GetBlockState() == BLOCK_STATE::USING_BLOCK)
			{
				if (!GetGround())
					SetJump(false);

				float fBlockX = 0.f, fBlockY = 0.f;
				if (GetDirection() == DIRECTION::RIGHT)
				{
					// 현재 객체가 오른 쪽이다.
					fBlockX = GetInfo().fX + 55 + GetSpeed();;
					fBlockY = GetInfo().fY + 50;
				}
				else if (GetDirection() == DIRECTION::LEFT)
				{
					// 현재 객체가 왼 쪽을 바라 볼 때
					fBlockX = GetInfo().fX - 55 - GetSpeed();
					fBlockY = GetInfo().fY + 50;
				}


				_pObj = CObjMgr::GetInst()->Find_Obj(OBJ_TYPE::NORMAL_BLOCK, fBlockX, fBlockY, GetDirection(), GetSpeed(), 50);

				if (_pObj != nullptr)
				{

					if (dynamic_cast<CNormalBlock*>(_pObj)->GetBlockState() == BLOCK_STATE::DELETE_BLOCK)
					{
						if (dynamic_cast<CNormalBlock*>(_pObj)->GetInfo().fY > this->GetInfo().fY)
						{
							if (GetDirection() == DIRECTION::RIGHT)
								SetReturn(false);
							else
								SetReturn(true);
						}
					}
				}


				SetGround(true);
				SetCollision(true);

				SetJumpTime(0);
				AddY(-fPush);

			}
	/*		if (dynamic_cast<CNormalBlock*>(_pObj)->GetBlockState() == BLOCK_STATE::USING_BLOCK)
			{
			}*/


			break;
		}
		break;
	case OBJ_TYPE::MOVE_BLOCK:
		switch (eDir)
		{
		case COL_DIR::RIGHT:
			SetReturn(false);
			AddX(-fPush);
			break;
		case COL_DIR::LEFT:
			SetReturn(true);
			AddX(fPush);
			break;
		case COL_DIR::TOP:
			SetDead(true);
			break;
		case COL_DIR::BOTTOM:
			if (!GetGround())
				SetJump(false);

			SetGround(true);
			SetCollision(true);

			SetJumpTime(0);
			AddY(-fPush);

			break;
		}
		break;
	case OBJ_TYPE::PATTERN_BLOCK:
		switch (eDir)
		{
		case COL_DIR::RIGHT:
			SetReturn(false);
			AddX(-fPush);
			break;
		case COL_DIR::LEFT:
			SetReturn(true);
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

			SetJumpTime(0.05f);
			AddY(-fPush);

			break;
		}
		break;
	case OBJ_TYPE::PASS_BLOCK:
		switch (eDir)
		{
		case COL_DIR::RIGHT:
			SetReturn(false);
			break;
		case COL_DIR::LEFT:
			SetReturn(true);
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
			if (!m_bAttack)
			{
				_pObj->SetDead(true);
				SetFrameKey(L"DOG_DANCE");
				m_eCurState = STATE::DANCE;
				CSoundMgr::GetInst()->PlaySoundW(L"Egg_Die.wav", EGG_DIE, 1.f);
				SetAttack(true);
			}
			break;
		case COL_DIR::RIGHT:
			if (!m_bAttack)
			{
				_pObj->SetDead(true);
				SetFrameKey(L"DOG_DANCE");
				m_eCurState = STATE::DANCE;
				CSoundMgr::GetInst()->PlaySoundW(L"Egg_Die.wav", EGG_DIE, 1.f);
				SetAttack(true);
			}
			break;
		}
		break;
	}
}

void CBulldog::MoveFrame(void)
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
	else if (GetState() == STATE::ATTCK)
	{
		if (GetFrame().dwTime + GetFrame().dwSpeed < GetTickCount())
		{
			AddFrameStart(1); // IDLE 0으로 만들어서 고정시켜버려라.

			if (GetFrame().iFrameStart > GetFrame().iFrameEnd)
				SetFrameStart(0);

			SetFrameTime(GetTickCount());
		}
	}
	else if (GetState() == STATE::DANCE)
	{
		if (GetFrame().dwTime + GetFrame().dwSpeed < GetTickCount())
		{
			AddFrameStart(1); // IDLE 0으로 만들어서 고정시켜버려라.

			if (GetFrame().iFrameStart > GetFrame().iFrameEnd)
				SetFrameStart(2);

			SetFrameTime(GetTickCount());
		}
	}



}

void CBulldog::SetMotion(void)
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
			SetFrame(FRAME{ 0,3,0,300,GetTickCount() });
			break;
		case STATE::DANCE:
			SetFrame(FRAME{ 2,6,0,350,GetTickCount() });
			break;
		case STATE::ATTCK:
			SetFrame(FRAME{ 0,6,0,500,GetTickCount() });
			break;
		}


		m_ePreState = m_eCurState;
	}
}

void CBulldog::DogPattern(void)
{
	srand((unsigned)time(NULL));

	if ((int)CObjMgr::GetInst()->GetObjList(OBJ_TYPE::EGG).front()->GetInfo().fY == (int)this->GetInfo().fY) // 알이랑 불독이랑 동일 선상에 있을 때 패턴
	{
		SetTarget(CObjMgr::GetInst()->Get_Target(OBJ_TYPE::EGG, this));

		SetState(STATE::WALK);

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



		if (this->GetState() == STATE::WALK) // 동일 선상에 있고, 워크상태일 때만 이걸 한다.
		{
			if (CObjMgr::GetInst()->GetObjList(OBJ_TYPE::EGG).front()->GetInfo().fX > this->GetInfo().fX)
			{
				SetFrameKey(L"DOG_RIGHT_MOVE");
				AddX(GetSpeed());
			}
			else if (CObjMgr::GetInst()->GetObjList(OBJ_TYPE::EGG).front()->GetInfo().fX < this->GetInfo().fX)
			{
				SetFrameKey(L"DOG_LEFT_MOVE");
				AddX(-GetSpeed());
			}
		}

		else if (this->GetState() == STATE::ATTCK)
		{
			if (GetAttack() && m_dwTime + 4000 < GetTickCount())
			{
				SetAttack(false);

				m_dwTime = GetTickCount();

				m_eCurState = STATE::WALK;

				SetSpeed(1.f);
			}
		}
	}
	// 달걀이 불독이랑 동일 선상에 있을 때, 불독이 달걀을 따라온다.

	else if (GetAttack() && m_dwTime + 4000 < GetTickCount()) // 공격 할 때
	{
		SetAttack(false);

		m_dwTime = GetTickCount();

		m_eCurState = STATE::WALK; // 공격 이후에 다시 걷는다.

		SetSpeed(1.f);

	}
	// 공격 이후에, 다시 걷기까지의 시간 

	//else if (GetState() == STATE::IDLE && m_dwTime + 5000 < GetTickCount())
	//{
	//	if (!GetReturn())
	//	{
	//		SetFrameKey(L"DOG_LEFT_MOVE");
	//		SetDir(DIRECTION::LEFT);
	//	}
	//	else
	//	{
	//		SetFrameKey(L"DOG_RIGHT_MOVE");
	//		SetDir(DIRECTION::RIGHT);
	//	}
	//	SetState(STATE::WALK);
	//	m_dwTime = GetTickCount();
	//}
	else if (!GetAttack())
	{
		if (GetState() == STATE::WALK)
		{
			if (!GetReturn())
			{
				SetFrameKey(L"DOG_LEFT_MOVE");
				SetDir(DIRECTION::LEFT);
				AddX(-GetSpeed());
			}
			else
			{
				SetFrameKey(L"DOG_RIGHT_MOVE");
				SetDir(DIRECTION::RIGHT);
				AddX(GetSpeed());
			}

			SetState(STATE::WALK);

		}

		if (m_dwTime + 5000 < GetTickCount())
		{
			do
			{
				CurRandomValue = rand() % 4;

			} while (CurRandomValue == PrevRandomValue); // 두 값이 다를 떄까지 반복인데 


			if (CurRandomValue)
			{
				if (CurRandomValue == 1)
				{
					if (GetDirection() == DIRECTION::LEFT)
					{
						SetFrameKey(L"DOG_LEFT_IDLE");
						SetState(STATE::IDLE);
					}
					else
					{
						SetFrameKey(L"DOG_RIGHT_IDLE");
						SetState(STATE::IDLE);
					}
				}
				else if (CurRandomValue == 2)
				{
					SetFrameKey(L"DOG_DANCE");
					SetState(STATE::DANCE);
				}
				else if (CurRandomValue == 3)
				{
					if (!GetReturn())
					{
						SetFrameKey(L"DOG_LEFT_MOVE");
						SetDir(DIRECTION::LEFT);
					}
					else
					{
						SetFrameKey(L"DOG_RIGHT_MOVE");
						SetDir(DIRECTION::RIGHT);
					}

					SetState(STATE::WALK);
				}
			}
			m_dwTime = GetTickCount();
			PrevRandomValue = CurRandomValue;
		}

		//if (GetState() == STATE::IDLE && m_dwTime + 5000 < GetTickCount())
		//{
		//	int RandomVal = rand() % 2;


		//	if (RandomVal == 0)
		//	{
		//		SetState(STATE::WALK);
		//	}
		//	else
		//	{
		//		SetFrameKey(L"DOG_DANCE");
		//		SetState(STATE::DANCE);
		//	}

		//	m_dwTime = GetTickCount();
		//}

		//if (m_dwTime + 20000 < GetTickCount())
		//{
		//	if (GetDirection() == DIRECTION::LEFT)
		//	{
		//		SetState(STATE::IDLE);
		//	}
		//	else
		//	{
		//		SetState(STATE::IDLE);
		//	}
		//	m_dwTime = GetTickCount();
		//}

	}
	// 단순히 걸을 때 행동 패턴인데, 주기적으로 다음 STATE로 넘겨줘야함.
}
