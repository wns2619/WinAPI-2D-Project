#pragma once


class CObj;
class CNormalBlock;
class CMoveBlock;

class TileMgr
{
	SINGLETONE(TileMgr);

public:
	void Initialize(void);
	void Update(void);
	void LateUpdate(void);
	void Render(HDC _hDC);
	void Release(void);

public:
	void	Picking_Tile(POINT _pt, TILE_TYPE eType, BLOCK_STATE _eBlock, int _iDrawID, int _iOption);
	void	Create_Tile(POINT _pt, TILE_TYPE eType);
	void	Save_Tile(void);
	void	Load_Tile(void);

public:
	void	AddNormalBlock(CNormalBlock* pBlock) { m_vecNormal.push_back(pBlock); }
	void	AddCMoveBlock(CMoveBlock* pBlock)	 { m_vecMove.push_back(pBlock); }

public:
	vector<CObj*>&	 GetTile(void) { return m_vecTile; }

private:
	vector<CObj*>			m_vecTile;
	vector<CMoveBlock*>		m_vecMove;
	vector<CNormalBlock*>   m_vecNormal;
	
};

