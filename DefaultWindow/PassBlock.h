#include "Block.h"

class CPassBlock :
	public CBlock
{
public:
	CPassBlock();
	virtual ~CPassBlock();

public:
	virtual void	Initialize(void);
	virtual int		Update(void);
	virtual void	LateUpdate(void);
	virtual void	Render(HDC hDC);
	virtual void	Release(void);

	virtual void	Collider(CObj* _pObj, COL_DIR eDir, float fPush) override;


};
