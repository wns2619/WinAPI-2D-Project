#pragma once


class CObj;
class CScene
{
public:
	CScene();
	virtual ~CScene();

public:
	virtual void Render(HDC _hDC);
	virtual void Update(void);
	virtual void LateUpdate(void);


	virtual void Initialize(void)	PURE;
	virtual void Release(void)		PURE;
	virtual void Enter(void)		PURE;
	virtual void Exit(void)			PURE;

public: // Scene Add
	void AddObject(CObj* _Other, OBJ_TYPE _Type) { m_arrObjList[(UINT)_Type].push_back(_Other); }
	

public: // Getter
	const wstring&	GetName() { return m_strName; } // Scene이름 Get
	const list<CObj*>&	GetObjList(OBJ_TYPE _eType) { return m_arrObjList[(UINT)_eType]; }
	TILE_TYPE		GetTile()	{ return m_eTileType; }
	BLOCK_STATE		GetBlockState()	{ return m_eBlockState; }
	TCHAR*			GetFrameKey() { return m_tFrameKey; }
	
public: // Setter
	void	SetName(const wstring& _strName) { m_strName = _strName; }
	void	SetTile(TILE_TYPE eTile)		 { m_eTileType = eTile; }
	void	SetBlockState(BLOCK_STATE _eBlock) { m_eBlockState = _eBlock; }
	void	SetFrameKey(TCHAR* _Key) { m_tFrameKey = _Key; }

private:
	list<CObj*>		m_arrObjList[(UINT)OBJ_TYPE::END];
	wstring			m_strName; // Scene 이름
	TCHAR*			m_tFrameKey;

	TILE_TYPE		m_eTileType;
	BLOCK_STATE		m_eBlockState;
};

