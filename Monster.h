#pragma once
#include "Object.h"
#include "math.h"

enum MonsterType
{
	MonsterType_Snake,
	MonsterType_Octoroc,
	MonsterType_Boss,
};

class Monster : public Object
{
protected:
	float fMoveDeltaTime;
	int AnimationCount;
	bool bHit;
	int  m_eDir;
	int  HP;
	bool DieAim;
	bool Die;
	int MaxAnimCount;
protected:
	 RECT collision;
	 bool Move;		//이동하는 몬스터인지
	 float m_fAngle;
	 float fSpeed;
	 MonsterType m_Type;
public:
	Monster(int x, int y, MonsterType Type);
	~Monster() {};
	virtual void Init(int x, int y) = 0;
	virtual bool Collision(RECT rect) = 0;
	virtual void Draw(HDC backDC, float DeltaTime) override;
	virtual void Hit() = 0;
	virtual void Reset() override;
	RECT& GetCollision() { return collision; }
	bool GetDie() const { return Die; }

};

