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
	QueryPerformanceCounter(&m_llPrevCount); // ���� ī��Ʈ

	QueryPerformanceFrequency(&m_llFrequncy); // �ʴ� ī��Ʈ �߻� Ƚ��
}

void CTimeMgr::Update(void)
{
	QueryPerformanceCounter(&m_llCurCount); // ���� ī��Ʈ

	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequncy.QuadPart;
	// �����Ӱ� ������ ������ ī��Ʈ ��

	m_llPrevCount = m_llCurCount; // ���� ī��Ʈ ���� ���� ī��Ʈ ������ ����

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
