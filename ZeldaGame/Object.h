#pragma once
#include "BitMapManager.h"



struct Position
{
	int X;
	int Y;

	Position operator+(const Position& ref)
	{
		Position pos = { X + ref.X, Y + ref.Y };
		return pos;
	}

	Position operator*(const int& ref)
	{
		Position pos = { X + ref, Y + ref};
		return pos;
	}

};



class Object // 추상 클래스
{
protected:
	BitMap* m_BitMap;
	int m_ix, m_iy;

public:
	Object() : m_ix(0), m_iy(0) {};
	Object(int x, int y) : m_ix(x), m_iy(y) {};
	virtual ~Object() { delete m_BitMap; }

	virtual void Draw(HDC backDC, float DeltaTime = 0.0f) = 0; 
	virtual void Reset() = 0;


};
