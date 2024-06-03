#pragma once
#include "BitMapManager.h"



struct Position
{
	int X;
	int Y;
};


class Object // 추상 클래스
{
protected:
	BitMap* m_BitMap;
	int m_ix, m_iy;

public:
	Object() : m_ix(0), m_iy(0) {};
	virtual ~Object() { delete m_BitMap; }

	virtual void Draw(HDC backDC, float DeltaTime = 0.0f) = 0; 
	virtual void Reset() = 0;


};
