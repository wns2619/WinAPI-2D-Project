#pragma once


class CKeyMgr
{
	SINGLETONE(CKeyMgr);

public:
	bool	Key_Pressing(int _iKey);
	bool	Key_Down(int _iKey);
	bool	Key_Up(int _iKey);

private:
	bool	m_bKeyState[VK_MAX];

};

