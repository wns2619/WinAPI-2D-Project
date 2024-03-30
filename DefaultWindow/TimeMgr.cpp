#include "stdafx.h"
#include "TimeMgr.h"


CTimeMgr::CTimeMgr()
	: m_llCurCount{}
	, m_llFrequncy{}
	, m_llPrevCount{}
	, m_dDT(0.f)
	, m_iCallCount(0)
	, m_dAcc(0.f)
{
}


CTimeMgr::~CTimeMgr()
{
}

void CTimeMgr::Initialize(void)
{
	QueryPerformanceCounter(&m_llPrevCount); // 이전 카운트

	QueryPerformanceFrequency(&m_llFrequncy); // 초당 카운트 발생 횟수
}

void CTimeMgr::Update(void)
{
	QueryPerformanceCounter(&m_llCurCount); // 현재 카운트

	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequncy.QuadPart;
	// 프레임과 프레임 사이의 카운트 값

	m_llPrevCount = m_llCurCount; // 이전 카운트 값을 현재 카운트 값으로 대입

	++m_iCallCount;
	m_dAcc += m_dDT;

	if (m_dAcc >= 1.f)
	{
		m_iFPS = m_iCallCount;
		m_dAcc = 0;
		m_iCallCount = 0;
	}

}

void CTimeMgr::LateUpdate(void)
{
}
