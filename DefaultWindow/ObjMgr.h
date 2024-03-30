#pragma once

class CObj;
class CScene;

class CObjMgr
{
	SINGLETONE(CObjMgr);

public:
	void	Update(void);
	void	LateUpdate(void);
	void	Render(HDC _hDC);
	void	Release(void);


	void	Add_Obj(OBJ_TYPE _Type, CObj* pObj);
	void	Add_Render(RENDERID _eRender, CScene* pScene);


	void	Delete_ID(OBJ_TYPE _eID);
	CObj*	Find_Obj(OBJ_TYPE _eType, float x, float y, DIRECTION eDir, float fSpeed, float fRange);
	CObj*	Find_Block(OBJ_TYPE _eType, float x, float y, float Range);
	CObj*	Get_Target(OBJ_TYPE eID, CObj* pObj);
	void	ObjLock();


public: // Getter

	list<CObj*>& GetObjList(OBJ_TYPE eType) { return m_ObjList[(UINT)eType]; }
	list<CObj*>& GetRender(RENDERID eRender) { return m_RenderSort[(UINT)eRender]; }

private:
	list<CObj*> m_ObjList[(UINT)OBJ_TYPE::END];
	list<CObj*> m_RenderSort[(UINT)RENDERID::END];
};

