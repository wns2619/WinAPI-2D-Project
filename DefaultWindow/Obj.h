#pragma once

#include "Define.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual void	Initialize(void)	PURE;
	virtual int		Update(void)		PURE;
	virtual void	LateUpdate(void)	PURE;
	virtual void	Render(HDC hDC)		PURE;
	virtual void	Release(void)		PURE;

	virtual void	Collider(CObj* _pObj, COL_DIR eDir, float fPush)	PURE;
	
	
public: // Getter
	RECT			GetRect(void)		{ return m_tRect; }
	INFO			GetInfo(void)		{ return m_tInfo; }
	FRAME			GetFrame(void)		{ return m_tFrame; }
	DIRECTION		GetDirection(void)	{ return m_eDir; }
	TCHAR*			GetFrameKey(void)	{ return m_pFrameKey; }
	OBJ_TYPE		GetObjType(void)    { return m_tObjType; }
	RENDERID		GetRenderID(void)	{ return m_eRender; }
	TILE_TYPE		GetTile(void)		{ return m_TileType; }
	CObj*			GetObjTarget(void)	{ return m_pTarget; }
	BLOCK_STATE		GetBlockState()		{ return m_eBlockState; }


	const bool&			GetDead(void)		{ return m_bDead; }
	const bool&			GetJump(void)       { return m_bJump; }
	const bool&			GetGround(void)		{ return m_bGround; }
	const float			GetSpeed(void)		{ return m_fSpeed; }
	const float			GetDistance(void)   { return m_fDistance; }
	const float			GetJumpPower(void)	{ return m_fPower; }
	const float			GetJumpTime(void)	{ return m_fTime; }
	const bool&			GetMoving(void)	    { return m_IsMoving; }
	int					Get_DrawID()		{ return m_iDrawID; }
	int					Get_Option()		{ return m_iOption; }
	int					Get_FrameStart()	{ return m_tFrame.iFrameStart; }
	int					Get_FrameEnd()	    { return m_tFrame.iFrameEnd; }
	bool				GetGravity()		{ return m_bGravity; }
	bool				GetCollision()		{ return m_bCol; }
	int					GetBlockID()		{ return m_iBlockID; }


public: // Setter
	void				SetRenderID(RENDERID eRender) { m_eRender = eRender; }

	void				SetDead(bool _Dead)			  { m_bDead = _Dead; }
	void				SetY(float _fY)				  { m_tInfo.fY = _fY; }
	void				SetX(float _fX)				  { m_tInfo.fX = _fX; }
	void				SetXDir(float _fX)			  { m_fSpeed *= _fX; }
	void				SetDir(DIRECTION _eDir)		  { m_eDir = _eDir; }
	void				SetFrameKey(TCHAR* pFrameKey) { m_pFrameKey = pFrameKey; }
	void				SetInfo(INFO _Info)			  { m_tInfo = _Info; }
	void				SetSpeed(float _Speed)		  { m_fSpeed = _Speed; }
	void				SetDistance(float _Distance)  { m_fDistance = _Distance; }
	void				SetFrame(FRAME _frame)		  { m_tFrame = _frame; }
	void				SetFrameStart(int _Start)	  { m_tFrame.iFrameStart = _Start; }
	void				SetFrameEnd(int _End)		  { m_tFrame.iFrameEnd = _End; }
	void				SetFrameTime(DWORD _Time)	  { m_tFrame.dwTime = _Time; }
	void				SetIsMoving(bool _Move)		  { m_IsMoving = _Move; }

	void				SetPos(float _fX, float _fY)  { m_tInfo.fX = _fX, m_tInfo.fY = _fY; }
	void				SetJump(bool _bJump)		  { m_bJump = _bJump; }
	void				SetJumpPower(float _fPower)	  { m_fPower = _fPower; }
	void				SetJumpTime(float _ftime)	  { m_fTime = _ftime; }
	void				SetObjType(OBJ_TYPE _type)	  { m_tObjType = _type; }
	void				SetGround(bool _ground)		  { m_bGround = _ground; }
	void				SetMoving(bool _Move)		  { m_IsMoving = _Move; }
	void				Set_Block(int _iDrawID, int _iOption) { m_iDrawID = _iDrawID; m_iOption = _iOption; }
	void				Set_Tile(TILE_TYPE eTile)	  { m_TileType = eTile; }
	void				SetGravity(bool _Graivity)	  { m_bGravity = _Graivity; }
	void				SetCollision(bool _Collision) { m_bCol = _Collision; }
	void				SetTarget(CObj*	_target)	  { m_pTarget = _target; }
	void				SetBlockState(BLOCK_STATE _eBlock) { m_eBlockState = _eBlock; }
	void				SetBlockID(int _id)				{ m_iBlockID = _id; }

public:
	void				AddY(float _fY)				  { m_tInfo.fY += _fY; }
	void				AddX(float _fX)				  { m_tInfo.fX += _fX; }
	void				AddXTime(double _fX, double _time);
	void				AddTime(float _ftime)		  { m_fTime += _ftime; }
	void				AddJumpPower(float _fPower)	  { m_fPower += _fPower; }
	void				AddFrameStart(int _Start)	  { m_tFrame.iFrameStart += _Start; }


protected:
	void		Update_Rect(void);
	void		MoveFrame(void);
	void		CheckBlockCollision(OBJ_TYPE eType, float fX, float fY, OBJ_TYPE eOtherType);

private:
	// Object 
	INFO		m_tInfo;		// 객체 중점 및 크기
	RECT		m_tRect;		// 객체박스
	RECT		m_tColRect;
	DIRECTION	m_eDir;			// 객체 이동 위치
	RENDERID	m_eRender;		// 객체 렌더타입
	DWORD		m_dwTime;
	TILE_TYPE	m_TileType;
	CObj*		m_pTarget;
	BLOCK_STATE		m_eBlockState;


	// Animatino
	FRAME		m_tFrame;		// 애니메이션 프레임
	TCHAR*		m_pFrameKey;	// 애니메이션에 맞는 키를 저장할 변수

	// Player State
	OBJ_TYPE	m_tObjType;
	bool		m_IsMoving;
	bool		m_bDead;		// 플레이어 및 에그 사망 변수
	float		m_fSpeed;		// OBJ 상속 객체의 속도 변수
	float		m_fDistance;	// OBJ 상속 객체의 거리


	// Jump
	bool	m_bGround; // 땅 위인지 확인
	bool	m_bJump;  // 점프 상태를 확인할 변수
	float	m_fPower; // 점프 할 때 힘
	float	m_fTime;  // 점프에서 흐른 시간

	// Block
	int		m_iDrawID; // 
	int		m_iOption; // 
	int		m_iBlockID;
	bool	m_bGravity;
	bool	m_bCol;

};

