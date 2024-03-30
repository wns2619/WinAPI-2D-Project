#pragma once
class CTimeMgr
{
	SINGLETONE(CTimeMgr);

public:
	void Initialize(void);
	void Update(void);
	void LateUpdate(void);

public: // Getter;


private: // Member

	LARGE_INTEGER m_llCurCount; // 현재 카운트
	LARGE_INTEGER m_llPrevCount; // 이전 카운트
	LARGE_INTEGER m_llFrequncy; // 카운터 횟수

	double		  m_dDT; // 델타 타임(프레임 사이의 시간 값);
	double		  m_dAcc; // 1초 체크를 위한 값을 누적 받을 변수
	UINT		  m_iCallCount; // 초당 호출 횟수
	UINT		  m_iFPS; 

};

