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

	LARGE_INTEGER m_llCurCount; // ���� ī��Ʈ
	LARGE_INTEGER m_llPrevCount; // ���� ī��Ʈ
	LARGE_INTEGER m_llFrequncy; // ī���� Ƚ��

	double		  m_dDT; // ��Ÿ Ÿ��(������ ������ �ð� ��);
	double		  m_dAcc; // 1�� üũ�� ���� ���� ���� ���� ����
	UINT		  m_iCallCount; // �ʴ� ȣ�� Ƚ��
	UINT		  m_iFPS; 

};

