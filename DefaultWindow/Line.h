#pragma once


class CLine
{
public:
	CLine();
	CLine(LINEPOINT _LPoint, LINEPOINT _RPoint);
	CLine(LINE& tLine);
	~CLine();

public: // Getter
	LINE GetLine() { return m_tLine; }
public:
	void Render(HDC _hDC);
private:
	LINE m_tLine;
};

