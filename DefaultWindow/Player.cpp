#include "stdafx.h"
#include "Player.h"
#include "Egg.h"
#include "NormalBlock.h"
#include "Scene.h"

// Manager Header
#include "ResMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "LineMgr.h"
#include "ObjMgr.h"
#include "SoundMgr.h"
#include "SceneMgr.h"


CPlayer::CPlayer()
	: m_ePreState(STATE::END)
	, dwTime(GetTickCount())
	, dwRenderTime(GetTickCount())
	, m_pOtherObj(nullptr)
	, m_bAttack(false)
	, m_bMoveFrame(false)
	, m_bHit(false)
	, m_bFallDownCheck(false)
	, m_iCountX(0)
	, m_iCountY(0)
	, m_bStartAnimation(true)
	, m_bRender(false)
	, m_bCountX(false)
{
	ZeroMemory(&m_fPlayerFrame, sizeof(FRAME));
}

CPlayer::~CPlayer()	
{
	Release();
}

void CPlayer::Initialize(void)
{
	// Player State

	SetInfo(INFO{ 300.f, 400.f, 45.f, 45.f });
	SetSpeed(3.f);
	SetDistance(100.f);
	SetJumpTime(0.f);
	SetJumpPower(10.f);
	SetObjType(OBJ_TYPE::PLAYER);
	SetGround(true);
	SetJump(false);
	SetDir(DIRECTION::RIGHT);
	m_iCountX = 0;
	m_pOtherObj = nullptr;

	// CResMgr Insert = Player Animation Motion 
	


	CResMgr::GetInst()->Insert_Texture(L"../DuckMazeImg/Duck45/Right_Move.bmp", L"PLAYER_RIGHT");
	CResMgr::GetInst()->Insert_Texture(L"../DuckMazeImg/Duck45/Left_Move.bmp",  L"PLAYER_LEFT");
	CResMgr::GetInst()->Insert_Texture(L"../DuckMazeImg/Duck45/Right_Attack.bmp", L"PLAYER_RIGHT_ATTACK");
	CResMgr::GetInst()->Insert_Texture(L"../DuckMazeImg/Duck45/Left_Attack.bmp", L"PLAYER_LEFT_ATTACK");
	CResMgr::GetInst()->Insert_Texture(L"../DuckMazeImg/Duck45/Right_Hit.bmp", L"PLAYER_RIGHT_HIT");
	CResMgr::GetInst()->Insert_Texture(L"../DuckMazeImg/Duck45/Left_Hit.bmp", L"PLAYER_LEFT_HIT");
	//CResMgr::GetInst()->Insert_Texture(L"../DuckMazeImg/Duck_Idle.bmp", L"PLAYER_IDLE");
	
	// Animation State
	
	SetFrameKey(L"PLAYER_RIGHT");
	m_eCurState = STATE::WALK;
	SetFrame(FRAME{ 0, 3, 0, 200, GetTickCount() });

	SetRenderID(RENDERID::PLAYER_OBJECT);
	
}

int CPlayer::Update(void)
{

	CObj::Update_Rect();


	if (CSceneMgr::GetInst()->GetScene()->GetName() == L"Logo")
	{
		m_bMoveFrame = true;
		AddX(1.5f);
		MoveFrame();
		SetMotion();
	}
	else
	{
		if (m_bStartAnimation) // 처음 Start 할 때.
		{
			StartAnimation();
		}
		// 570.f에 도달 -> AddY(); -> 


		else // Start가 끝나고, 본 게임이 시작할 때.
		{
			PlayerState();


			// int a = 0;

			CEgg* pEgg = dynamic_cast<CEgg*>(CObjMgr::GetInst()->GetObjList(OBJ_TYPE::EGG).front());


			if (GetState() != STATE::HIT && !(pEgg->GetClear()))
			{
				Key_Input();
			}
		}
	}
	
	return OBJ_NOEVENT;
}

void CPlayer::LateUpdate(void)
{	
	if (!m_bStartAnimation)
	{
		Jump();

		MoveFrame();

		SetMotion();
	}
}

void CPlayer::Render(HDC hDC)
{

	float fScrollX = CScrollMgr::GetInst()->GetScrollX();
	float fScrollY = CScrollMgr::GetInst()->GetScrollY();

	HDC	  hMemDC = CResMgr::GetInst()->Find_Image(GetFrameKey());

	
	if(!m_bRender)
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

void CPlayer::Release(void)
{
}

void CPlayer::Collider(CObj * _pObj, COL_DIR eDir, float fPush)
{
	OBJ_TYPE eType = _pObj->GetObjType();


	switch (eType)
	{
		// 플레이어의 방향이 -> 노멀 블록에 닿았을 때.
	case OBJ_TYPE::NORMAL_BLOCK:
		switch (eDir)
		{
		case COL_DIR::RIGHT:
			if(!m_bStartAnimation)
				if(dynamic_cast<CNormalBlock*>(_pObj)->GetBlockState() == BLOCK_STATE::USING_BLOCK)
			AddX(-fPush);
			break;
		case COL_DIR::LEFT:
			if (!m_bStartAnimation)
				if (dynamic_cast<CNormalBlock*>(_pObj)->GetBlockState() == BLOCK_STATE::USING_BLOCK)
			AddX(fPush);
			break;
		case COL_DIR::TOP:
			if (!m_bStartAnimation)
			{
				if (dynamic_cast<CNormalBlock*>(_pObj)->GetBlockState() == BLOCK_STATE::USING_BLOCK)
				{
					AddY(fPush);
					AddJumpPower(-1.f);
				}
			}
			break;
		case COL_DIR::BOTTOM:
			if (!m_bStartAnimation)
			{
				if (dynamic_cast<CNormalBlock*>(_pObj)->GetBlockState() == BLOCK_STATE::USING_BLOCK)
				{
					if (!GetGround())
						SetJump(false);
					SetGround(true);

					if (GetAttack())
					{
						float fBlockX = 0.f, fBlockY = 0.f;
						if (GetDirection() == DIRECTION::RIGHT)
						{
							// 현재 객체가 오른 쪽이다.
							fBlockX = GetInfo().fX + 55 + GetSpeed();
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
							if (dynamic_cast<CNormalBlock*>(_pObj)->GetBlockState() == BLOCK_STATE::USING_BLOCK)
							{
								// 그 위치에 블록이 있다면 삭제
								dynamic_cast<CNormalBlock*>(_pObj)->SetBlockState(BLOCK_STATE::DELETE_BLOCK);
								dynamic_cast<CNormalBlock*>(_pObj)->SetBlockID(0);
								_pObj->SetDead(true);
								SetAttack(false); // 이건 Normal 블록을 삭제 .
							}
						}
					}


					SetJumpTime(0.05f);
					AddY(-fPush);
				}
			}
			break;
		}
		break;
	case OBJ_TYPE::MOVE_BLOCK:
		switch (eDir)
		{
		case COL_DIR::RIGHT:
			if (!m_bStartAnimation)
			AddX(-fPush);
			break;
		case COL_DIR::LEFT:
			if (!m_bStartAnimation)
			AddX(fPush);
			break;
		case COL_DIR::TOP:
			if (!m_bStartAnimation)
			AddY(fPush);
			break;
		case COL_DIR::BOTTOM:
			if (!m_bStartAnimation)
			{
				if (!GetGround())
					SetJump(false);
				SetGround(true);

				if (GetAttack())
				{
					float fBlockX = 0.f, fBlockY = 0.f;
					if (GetDirection() == DIRECTION::RIGHT)
					{
						// 현재 객체가 오른 쪽이다.
						fBlockX = GetInfo().fX + 55 + GetSpeed();
						fBlockY = GetInfo().fY + 50;
					}
					else if (GetDirection() == DIRECTION::LEFT)
					{
						// 현재 객체가 왼 쪽을 바라 볼 때
						fBlockX = GetInfo().fX - 55 - GetSpeed();
						fBlockY = GetInfo().fY + 50;
					}


					_pObj = CObjMgr::GetInst()->Find_Obj(OBJ_TYPE::MOVE_BLOCK, fBlockX, fBlockY, GetDirection(), GetSpeed(), 50);


					if (_pObj)
					{
						// 그 위치에 블록이 있다면 삭제
						_pObj->SetGravity(true);
						SetAttack(false); // 모든 객체가 영향을 받네..
					}
				}


				SetJumpTime(0.05f);
				AddY(-fPush);
			}
			break;
		}
		break;
	case OBJ_TYPE::SIDE_BLOCK:
		switch (eDir)
		{
		case COL_DIR::RIGHT:
			if(!m_bStartAnimation)
			AddX(-fPush);
			break;
		case COL_DIR::LEFT:
			if (!m_bStartAnimation)
			AddX(fPush);
			break;
		}
		break;
	case OBJ_TYPE::EGG:
		switch (eDir)
		{
		case COL_DIR::RIGHT:
			if (!m_bStartAnimation)
			AddX(-fPush);
			break;
		case COL_DIR::LEFT:
			if (!m_bStartAnimation)
			AddX(fPush);
			break;
		case COL_DIR::TOP:
			break;
		case COL_DIR::BOTTOM:
			break;
		}
		break;
	case OBJ_TYPE::PATTERN_BLOCK:
		switch (eDir)
		{
		case COL_DIR::RIGHT:
			if (!m_bStartAnimation)
			AddX(-fPush);
			break;
		case COL_DIR::LEFT:
			if (!m_bStartAnimation)
			AddX(fPush);
			break;
		case COL_DIR::TOP:
			if (!m_bStartAnimation)
			{
				AddY(fPush);
				AddJumpPower(-1.f);
			}
			break;
		case COL_DIR::BOTTOM:
			if (!m_bStartAnimation)
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
			if (!m_bStartAnimation)
			AddX(-fPush);
			break;
		case COL_DIR::LEFT:
			if (!m_bStartAnimation)
			AddX(fPush);
			break;
		case COL_DIR::TOP:
			if (!m_bStartAnimation)
			{
				AddY(fPush);
				AddJumpPower(-1.f);
			}
			break;
		case COL_DIR::BOTTOM:
			if (!m_bStartAnimation)
			{
				if (!GetGround())
					SetJump(false);
				SetGround(true);

				if (GetAttack())
				{
					float fBlockX = 0.f, fBlockY = 0.f;
					if (GetDirection() == DIRECTION::RIGHT)
					{
						// 현재 객체가 오른 쪽이다.
						fBlockX = GetInfo().fX + 55 + GetSpeed();
						fBlockY = GetInfo().fY + 50;
					}
					else if (GetDirection() == DIRECTION::LEFT)
					{
						// 현재 객체가 왼 쪽을 바라 볼 때
						fBlockX = GetInfo().fX - 55 - GetSpeed();
						fBlockY = GetInfo().fY + 50;
					}


					_pObj = CObjMgr::GetInst()->Find_Obj(OBJ_TYPE::PASS_BLOCK, fBlockX, fBlockY, GetDirection(), GetSpeed(), 50);


					if (_pObj != nullptr)
					{

						CSoundMgr::GetInst()->PlaySoundW(L"PatternOrPass.wav", PATTERN_OR_PASS, 1.f);

						// 그 위치에 블록이 있다면 삭제
						_pObj->SetCollision(false);
						SetAttack(false); // 모든 객체가 영향을 받네..

					}
				}


				SetJumpTime(0.05f);
				AddY(-fPush);
			}
			break;
		}
		break;
	case OBJ_TYPE::BULLDOG:
		switch (eDir)
		{
			case COL_DIR::RIGHT:
				SetFrameKey(L"PLAYER_LEFT_HIT");
				m_eCurState = STATE::HIT;
				SetDir(DIRECTION::LEFT);
				break;
			case COL_DIR::LEFT:
				SetFrameKey(L"PLAYER_RIGHT_HIT");
				m_eCurState = STATE::HIT;
				SetDir(DIRECTION::RIGHT);
				break;
			case COL_DIR::TOP:
				break;
			case COL_DIR::BOTTOM:
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

			break;
		}
		break;
	}
}

void CPlayer::Key_Input(void)
{
	// 오리는 좌우로만 움직이면서 점프만 가능함.
	// 공격으로 벽돌을 부셔서 아래로 내려갈 수 있음.
	SetAttack(false);
	cout << "Y : " << GetInfo().fY << "\t" << "X : " << GetInfo().fX << endl;

	if (CKeyMgr::GetInst()->Key_Pressing(VK_LEFT))
	{
		AddX(-GetSpeed());
		SetFrameKey(L"PLAYER_LEFT");
		m_eCurState = STATE::WALK;
		SetDir(DIRECTION::LEFT);
		m_bMoveFrame = true;


	}
	else if (CKeyMgr::GetInst()->Key_Pressing(VK_RIGHT))
	{
		AddX(GetSpeed());
		SetFrameKey(L"PLAYER_RIGHT");
		m_eCurState = STATE::WALK;
		SetDir(DIRECTION::RIGHT);
		m_bMoveFrame = true;

	}


	else if (CKeyMgr::GetInst()->Key_Pressing('Z'))
	{
		// 플레이어 공격 모션 'Z'
		SetAttack(true);

		if (GetFrameKey() == L"PLAYER_RIGHT")
		{
			SetFrameKey(L"PLAYER_RIGHT_ATTACK");
			m_eCurState = STATE::ATTCK;
			SetDir(DIRECTION::RIGHT);
			CSoundMgr::GetInst()->StopSound(ATTACK_SOUND);
			CSoundMgr::GetInst()->PlaySoundW(L"AttackSound.wav", ATTACK_SOUND, 1.f);

		}
		else if (GetFrameKey() == L"PLAYER_LEFT")
		{
			SetFrameKey(L"PLAYER_LEFT_ATTACK");
			m_eCurState = STATE::ATTCK;
			SetDir(DIRECTION::LEFT);
			CSoundMgr::GetInst()->StopSound(ATTACK_SOUND);
			CSoundMgr::GetInst()->PlaySoundW(L"AttackSound.wav", ATTACK_SOUND, 1.f);
		}
		m_bMoveFrame = true;
	}

	if (CKeyMgr::GetInst()->Key_Down(VK_SPACE))
	{
		// 플레이어 점프 모션 'SPACE'
		CSoundMgr::GetInst()->StopSound(JUMP_SOUND);
		CSoundMgr::GetInst()->PlaySound(L"JumpSound.wav", JUMP_SOUND, 1.f);
		SetJumpPower(9.f);
		SetJump(true);
	}

	if (CKeyMgr::GetInst()->Key_Down('S'))
	{
		CSoundMgr::GetInst()->StopSound(JUMP_SOUND);
		CSoundMgr::GetInst()->PlaySound(L"JumpSound.wav", JUMP_SOUND, 1.f);
		SetJumpPower(15.f);
		SetJump(true);
	}

}

void CPlayer::OffSet(void)
{
	float	fOffSetMinY = 100.f;
	float	fOffSetMaxY = 250.f;
	
	float	fScrollY = CScrollMgr::GetInst()->GetScrollY();


	if (fOffSetMinY > GetInfo().fY + fScrollY)
		CScrollMgr::GetInst()->SetScrollY(GetSpeed());

	if (fOffSetMaxY < GetInfo().fY + fScrollY)
		CScrollMgr::GetInst()->SetScrollY(-GetSpeed());

}

void CPlayer::SetMotion(void)
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
		case STATE::ATTCK:
			SetFrame(FRAME{ 0,2,0,20,GetTickCount() });
			break;
		case STATE::HIT:
			SetFrame(FRAME{ 0,2,0,590,GetTickCount() });
			break;
		}

		m_ePreState = m_eCurState;
	}
}

void CPlayer::Jump(void)
{
	// Jump 일단 중력만 적용.

	float fY = 0.f;
	float InfofX = GetInfo().fX;
	float InfofY = GetInfo().fY;
	float InfofCY = GetInfo().fCY;

	bool bLineCol = CLineMgr::GetInst()->Collision_Line(InfofX, InfofY, InfofCY, &fY);


	if (GetJump())
	{
		SetGround(false);

		AddY(-(GetJumpPower() * (GetJumpTime()) - 9.8f * GetJumpTime() * GetJumpTime() * 0.3f));
		AddTime(0.1f);

		if (bLineCol && (fY < GetInfo().fY))
		{
			SetJump(false);
			SetJumpTime(0.f);
			SetJumpPower(10.f);
			SetY(fY);
		}
		else if (GetGround())
		{
			SetJump(false);
			SetJumpTime(0.f);
			SetJumpPower(10.f);
		}
	}
	else if (bLineCol)
	{
		SetY(fY);
		SetJumpTime(0.f);
		SetJump(false);
	}
	else if (!GetJump() || GetJumpTime() > 1.0f)
	{
		AddY(-(0.f * (GetJumpTime() + 0.01f) - 9.8f * GetJumpTime() * GetJumpTime() * 0.5));
		AddTime(0.1f);
		if (bLineCol && (fY < GetInfo().fY))
		{
			SetJumpTime(0.f);
			SetY(fY);
		}
	}
}

void CPlayer::MoveFrame(void)
{

	if (GetState() == STATE::HIT)
	{
		if (GetFrame().dwTime + GetFrame().dwSpeed < GetTickCount())
		{
			// bool이나 true나 false로 키를 땠을 때,
			AddFrameStart(1); // IDLE 0으로 만들어서 고정시켜버려라.

			if (GetFrame().iFrameStart > GetFrame().iFrameEnd)
			{
				SetFrameStart(1);
			}

			SetFrameTime(GetTickCount());
		}
	}

	else if (GetState() == STATE::WALK && m_bMoveFrame)
	{
		// bool이나 true나 false로 키를 땠을 때,

		if (GetFrame().dwTime + GetFrame().dwSpeed < GetTickCount())
		{
			// bool이나 true나 false로 키를 땠을 때,
			AddFrameStart(1); // IDLE 0으로 만들어서 고정시켜버려라.

			if (GetFrame().iFrameStart > GetFrame().iFrameEnd)
			{
				SetFrameStart(0);
			}

			SetFrameTime(GetTickCount());
		}
		m_bMoveFrame = false;
	}

	else if (GetState() == STATE::ATTCK && m_bAttack)
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

void CPlayer::PlayerLock(void)
{
}

void CPlayer::PlayerState(void)
{
	if (GetState() == STATE::HIT)
	{
		if (dwTime + 200 < GetTickCount() && GetDirection() == DIRECTION::RIGHT)
		{
			if (!m_bFallDownCheck && m_iCountX < 10)
			{
				AddX(5.f);
				m_bFallDownCheck = true;
				++m_iCountX;
			}

			dwTime = GetTickCount();
		}
		else if (dwTime + 200 < GetTickCount() && GetDirection() == DIRECTION::LEFT)
		{
			if (!m_bFallDownCheck && m_iCountX < 10)
			{
				AddX(-5.f);
				m_bFallDownCheck = true;
				++m_iCountX;
			}

			dwTime = GetTickCount();
		}

		if (m_iCountX == 9)
		{
			Sleep(800);
			m_eCurState = STATE::WALK;
			m_iCountX = 0;

			if (GetDirection() == DIRECTION::LEFT)
				SetFrameKey(L"PLAYER_RIGHT");
			else
				SetFrameKey(L"PLAYER_LEFT");
		}

		m_bFallDownCheck = false;
	}
}

void CPlayer::StartAnimation(void)
{
	// Y = 375.f // x = 120.f ~ 565.f 까지 
	if (dwTime + 200 < GetTickCount() && m_iCountX != 18)
	{
		if (m_iCountX < 18)
		{
			AddX(25.f); // x = 570.f
			++m_iCountX;
			m_bMoveFrame = true;
			MoveFrame();
		}

		if (m_iCountX == 18)
		{
			SetRenderOff(true);
			SetFrameStart(0);
		}

		m_bMoveFrame = false;
		dwTime = GetTickCount();
	}

	else if (dwTime + 500 < GetTickCount() && m_iCountX == 18)
	{
		m_bCountX = true;

		if (m_iCountY < 8)
		{
			AddY(25.f);
			++m_iCountY;
		}

		if (m_iCountY == 3)
		{
			SetRenderOff(false);
		}

		if (m_iCountY == 8)
		{
			m_bStartAnimation = false;
			m_iCountX = 0;
		}

		dwTime = GetTickCount();
	}

}

 