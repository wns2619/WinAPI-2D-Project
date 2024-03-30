#pragma once

typedef struct tagInfo
{
	float	fX;
	float	fY;
	float	fCX;
	float	fCY;

}INFO;

struct CDeleteObj
{
	template<typename T>
	void operator()(T& Temp)
	{
		if (Temp)
		{
			delete Temp;
			Temp = nullptr;
		}
	}
};

struct CDeleteMap
{
	template<typename T>
	void operator()(T& Temp)
	{
		if (Temp.second)
		{
			delete Temp.second;
			Temp.second = nullptr;
		}
	}
};

struct tagFinder
{
public:
	tagFinder(const TCHAR* pString) : m_pString(pString) {}

public:
	template<typename T>
	bool	operator()(T& MyPair)
	{
		return !lstrcmp(m_pString, MyPair.first);
	}


private:
	const TCHAR*	m_pString;
};

typedef struct tagFrame
{
	int		iFrameStart;	 // 애니메이션 시작 프레임
	int		iFrameEnd;		 // 애니메이션 끝 프레임
	int		iMotion;		 // 모션 번호?
	DWORD	dwSpeed;		 // 모션 속도
	DWORD	dwTime;			 // 모션 딜레이?
}FRAME;



typedef struct tagLinePoint {
	float fX;
	float fY;
	tagLinePoint() { ZeroMemory(this, sizeof(tagLinePoint)); }
	tagLinePoint(float _fX, float _fY) : fX(_fX), fY(_fY) {}
}LINEPOINT;



typedef struct tagLine {
	LINEPOINT tLPoint;
	LINEPOINT tRPoint;

	tagLine() { ZeroMemory(this, sizeof(tagLine)); }
	tagLine(LINEPOINT _LPoint, LINEPOINT _RPoint) :tLPoint(_LPoint), tRPoint(_RPoint) {}
}LINE;


typedef struct tagInfo_JSL
{
	float fX;
	float fY;
	float fCX;
	float fCY;
}LINEINFO;


typedef struct Col_Switch
{
	int m_bColLeft;
	int m_bColRight;
	int m_bColTop;
	int m_bColBottom;

	Col_Switch(int r, int l, int t, int b)
		: m_bColRight(r), m_bColLeft(l), m_bColBottom(b), m_bColTop(t)
	{}

}COL_SWITCH;