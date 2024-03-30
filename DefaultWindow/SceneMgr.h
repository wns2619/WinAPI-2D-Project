#pragma once

class CScene;
class CSceneMgr
{
	SINGLETONE(CSceneMgr);

public:
	void	Initialize(void);
	void	Update(void);
	void	LateUpdate(void);
	void	Render(HDC _hDC);
	void	Release(void);

public:
	void	NextStage(void) { m_bNextStage = true; }
	void	Game_End(void)	{ m_bSetEnd = true; }
	void	Scene_Change(SCENE_ID eID);


public: //Getter
	CScene*			GetScene(void)	 { return m_pCurScene; }
	SCENE_ID		GetSceneID(void) { return m_eCurScene; }

private:
	CScene*				m_pCurScene;
	DWORD				m_dwTime;

	SCENE_ID			m_eCurScene; // ÇöÀç ¾À
	SCENE_ID			m_ePreScene; // ÀÌÀü ¾À

	void				Change_Scene(void);



	vector<CScene*>		m_vecStage;
	int					m_iStage;
	bool				m_bNextStage;
	bool				m_bSetEnd;
	bool				m_bEnd;
};

